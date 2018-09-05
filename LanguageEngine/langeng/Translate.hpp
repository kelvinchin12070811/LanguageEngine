#pragma once
#include <string>
#include <functional>
#include "TranslationLoader.hpp"

namespace langeng
{
	/*! \brief A pointer that pointing an id to a std::string.

		 Translate is the object that map an id to a std::string which need to be translated. Translate also know as Translation
		 target in this library.

		 | Header | Namespace |
		 | : --- : | : --- : |
		 | langeng/Translate.hpp | langeng |
	*/
	class Translate
	{
	public:
		/*! Create a Translate object, the target needed to be told how to modify the string.
			 \param id Id of the translation string, describe as [string path](string_path.html).
			 \param target Function pointer to a function which tell Language Engine how to translate the target.
		*/
		Translate(const std::string& id, std::function<void(const std::string&)> target) :
			id(id), target(target)
		{
		}

		/*! Create a Translate object, target is translated with default method
			 \param id Id of the translation string, describe as [string path](string_path.html).
			 \param target Refrence to a string that need to be translate.
		*/
		Translate(const std::string& id, std::string& target) :
			id(id)
		{
			this->target = [&](const std::string& translatedString) {
				target = translatedString;
			};
		}

		/*! Create a Translate object which point to a member function of a class
			 \param id Id of the translation string, describe as [string path](string_path.html).
			 \param p function of a class member, this will be binded with `i` using `std::bind`.
			 \param i instance of the owner class, this will be binded with `p` using `std::bind`.
		*/
		template <typename StrAssignFn, typename Instance>
		Translate(const std::string& id, StrAssignFn p, Instance* i):
			id(id), target(std::bind(p, i, std::placeholders::_1))
		{
		}

		/*! Translate this target.
			 \param loader TranslationLoader that passed by Translate class.

			 \note This function is called automaticaly by Translate class.
		*/
		void translateTarget(const TranslationLoader& loader) const
		{
			target(loader.getTranslatedText(id));
		}
	private:
		std::string id;
		std::function<void(const std::string&)> target;
	};
}