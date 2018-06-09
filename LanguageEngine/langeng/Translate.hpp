#pragma once
#include <string>
#include <functional>
#include "TranslationLoader.hpp"

namespace langeng
{
	class Translate
	{
	public:
		Translate(const std::string& id, std::function<void(const std::string&)> target) :
			id(id), target(target)
		{
		}

		Translate(const std::string& id, std::string& target) :
			id(id)
		{
			this->target = [&](const std::string& translatedString) {
				target = translatedString;
			};
		}

		void translateTarget(const TranslationLoader& loader) const
		{
			target(loader.getTranslatedText(id));
		}
	private:
		std::string id;
		std::function<void(const std::string&)> target;
	};
}