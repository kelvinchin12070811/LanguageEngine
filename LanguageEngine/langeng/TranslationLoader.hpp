#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include "EngConfig.hpp"

/*! \addtogroup macro
	@{
*/

/*! Represent the parameters of a Validator function for langeng::TranslationLoader.\n
	 This macro make the implementation of validator functions much more eiser.
*/
#define LANGENG_VALIDATOR_ARGS const langeng::TranslationLoader::DocumentType& document, const std::string& fileName

/*! @}*/

namespace langeng
{
	/*! \brief Load Translation file to the Translator

	The TranslationLoader is a helper class that help Translator to laod translation file. It also act as the main charater to
	drive the engine of searching translation string.

	| Header | Namespace |
	| : --- : | : --- : |
	| langeng/TranslationLoader.hpp | langeng |
	*/
	class TranslationLoader
	{
	public:
		/*! Document of the translation file, it just a typedef of rapidjson::Document. Use rapidjson's function to asccess it.
		*/
		using DocumentType = rapidjson::Document;
#ifdef LANGENG_USE_EXCEPTION

		/*!
			 A function that verify the translation file before phrasing it.\n
			 It takes two parameters in total, a TranslationLoader::DocumentType & std::string.

			 The first parameter represent the translation file that user required.
			 The string represent the name of the translation file that passed when creating TranslationLoader class.

			 Throw excection if error occur.

			 \note If `#LANGENG_USE_EXCEPTION` is defined, this function will have return type of bool instead of void and
			 return true on success, false otherwise.
		*/
		using Validator = std::function<void(const TranslationLoader::DocumentType&, const std::string&)>;
#else
		using Validator = std::function<bool(const TranslationLoader::DocumentType&, const std::string&)>;
#endif // LANGENG_USE_EXCEPTION

	public:
		TranslationLoader() = default;

		/*! Construct a TranslationLoader
			 \param path the file name of the translation file.
		*/
		TranslationLoader(const std::string& path)
		{
			loadTranslation(path);
		}
		/*! Construct a TranslationLoader
			 \param path The file name of the translation file.
			 \param validator Custom validator that use to verify custom file structure. Exp: checking version or magic number.
		*/
		TranslationLoader(const std::string& path, TranslationLoader::Validator validator):
			validator(validator)
		{
			loadTranslation(path);
		}

#ifdef LANGENG_USE_EXCEPTION
		/*! Load a translation file\n
			 Throw exception if error occur

			 \param path path to the translation file, or name of the translation file
			 \note If `#LANGENG_USE_EXCEPTION` is not defined, this function have the bellow signature
			 ```cpp
			 bool loadTranslation(const std::string& path)
			 ```
			 With this signature, it will return `true` if success, 'false' otherwise.
		*/
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

		/*! Return translated text from translation file with id. 
			 \param id id of translation string described in String Path format.
			 \retval translation string stated in translation file, if error occur, exception trown or id is returned if `#LANGENG_USE_DEFAULT_ACTION`
			 is defined. If `#LANGENG_USE_EXCEPTION' is not defined, empty string is returned
		*/
		std::string getTranslatedText(const std::string& id) const
		{
			std::string path = "/" + id;
			std::replace(path.begin(), path.end(), '.', '/');

			auto result = rapidjson::Pointer(path.c_str()).Get(document);
			if (result == nullptr)
#ifdef LANGENG_USE_DEFAULT_ACTION
				return id;
#else
#ifdef LANGENG_USE_EXCEPTION
				throw std::runtime_error("Cannot find transtation with id: \"" + id + "\"");
#else
				return "";
#endif // LANGENG_USE_EXCEPTION  
#endif // LANGENG_USE_DEFAULT_ACTION

			
			return result->GetString();
		}
	private:
		rapidjson::Document document;

#ifdef LANGENG_USE_EXCEPTION
		/*! [read & write] Validataor that use to verfy the translation file

			- __mutator__
				-# void setValidator(TranslationLoader::Validator validator)\n
					Assign to a new validator

			- __accessor__
				-# TranslationLoader::Validator getValidator()\n
					Return current validator
		*/
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