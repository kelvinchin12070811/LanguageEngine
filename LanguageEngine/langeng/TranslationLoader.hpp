#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

#define LANGENG_USE_EXCEPTION
#define LANGENG_VALIDATOR_ARGS const langeng::TranslationLoader::DocumentType& document, const std::string& fileName

namespace langeng
{
	class TranslationLoader
	{
	public:
		using DocumentType = rapidjson::Document;
#ifdef LANGENG_USE_EXCEPTION
		using Validator = std::function<void(const TranslationLoader::DocumentType&, const std::string&)>;
#else
		using Validator = std::function<bool(const TranslationLoader::DocumentType&, const std::string&)>;
#endif // LANGENG_USE_EXCEPTION

	public:
		TranslationLoader() = default;
		TranslationLoader(const std::string& path)
		{
			loadTranslation(path);
		}

		TranslationLoader(const std::string& path, TranslationLoader::Validator validator):
			validator(validator)
		{
			loadTranslation(path);
		}

#ifdef LANGENG_USE_EXCEPTION
		void loadTranslation(const std::string& path)
#else
		bool loadTranslation(const std::string& path)
#endif // LANGENG_USE_EXCEPTION
		{
			std::stringstream readBuffer;
			std::ifstream reader;
			reader.open(path, std::ios::in);
#ifdef LANGENG_USE_EXCEPTION
			if (!reader.is_open())
				throw std::runtime_error("Unable open the file \"" + path + "\"");
#else
			if (!reader.is_open()) return false;
#endif // LANGENG_USE_EXCEPTION


			readBuffer << reader.rdbuf();
			document.Parse(readBuffer.str().c_str());

#ifdef LANGENG_USE_EXCEPTION
			validator(document, path);
#else
			return validator(document, path);
#endif // !LANGENG_USE_EXCEPTION

		}
	public: //Setters
		void setValidator(TranslationLoader::Validator validator)
		{
			this->validator = validator;
		}

	public: //Getters
		TranslationLoader::Validator getValidator()
		{
			return validator;
		}

		std::string getTranslatedText(const std::string& id) const
		{
			std::string path = "/" + id;
			std::replace(path.begin(), path.end(), '.', '/');

			auto result = rapidjson::Pointer(path.c_str()).Get(document);
			if (result == nullptr)
#ifdef LANGENG_USE_EXCEPTION
				throw std::runtime_error("Cannot find transtation with id: \"" + id + "\"");
#else
				return "";
#endif // LANGENG_USE_EXCEPTION
			
			return result->GetString();
		}
	private:
		rapidjson::Document document;

#ifdef LANGENG_USE_EXCEPTION
		TranslationLoader::Validator validator{ [](const rapidjson::Document& doc, const std::string& file) {
			if (!doc.IsObject()) throw std::runtime_error("Unable to parse the document \"" + file + "\"");
			} };
#else
		TranslationLoader::Validator validator{ [](const rapidjson::Document& doc) {
	return doc.IsObject();
} };
#endif // LANGENG_USE_EXCEPTION
	};
}