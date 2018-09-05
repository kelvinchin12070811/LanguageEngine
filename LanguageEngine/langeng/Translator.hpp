#pragma once
#include <vector>
#include <memory>
#include "Translate.hpp"

namespace langeng
{
	/*! \brief Main object that power up the entire library.
		 
		 Translator is the main object that power up the entire library. Translator are able to translate all target to the translated
		 string which stored in a translation file in json format.

		 Translator use TranslationLoader to load a translation file and translate all target.

		 | Header | Namespace |
		 | : --- : | : --- : |
		 | langeng/Translator.hpp | langeng |
	*/
	class Translator
	{
	public:
		/*! Create a Translator instance
			 \param loader TranslationLoader that loaded with a translation file
			 \param target A list of target which need to be translated. Note that this parameter is rvalue refrence.
		*/
		Translator(const std::shared_ptr<TranslationLoader>& loader, std::vector<Translate>&& target):
			loader(loader), translateTargets(std::move(target))
		{
			retranslate();
		}

		/*! Create a Translator instance but	`loader	` is moved.
			 \param loader TranslationLoader that loaded with a translation file. Note that this parameter is rvalue refrence.
			 \param target A list of target which need to be translated. Note that this parameter is rvalue refrence.
		*/
		Translator(std::shared_ptr<TranslationLoader>&& loader, std::vector<Translate>&& target) :
			loader(std::move(loader)), translateTargets(std::move(target))
		{
			retranslate();
		}

		/*! Retranslate all of the target */
		void retranslate() const
		{
			for (auto& itr : translateTargets)
				itr.translateTarget(*loader);
		}

		void installTranslationLoader(const std::shared_ptr<TranslationLoader>& loader)
		{
			if (this->loader != loader)
				this->loader = loader;
		}

		void installTranslationLoader(std::shared_ptr<TranslationLoader>&& loader)
		{
			this->loader = std::move(loader);
		}

		std::shared_ptr<TranslationLoader> getTranslationLoader() const
		{
			return loader;
		}

		const std::vector<Translate>& getTranslateTargets() const
		{
			return translateTargets;
		}

		std::vector<Translate>& getTranslateTargets()
		{
			return const_cast<std::vector<Translate>&>(const_cast<const Translator*>(this)->getTranslateTargets());
		}
	private:
		/*! [read & write] TranslationLoader that use to translate all target

		- __mutator__
			-# void installTranslationLoader(const std::shared_ptr<TranslationLoader>& loader)\n
				Install new TranslationLoader

			-# void installTranslationLoader(std::shared_ptr<TranslationLoader>&& loader)\n
				As [1], but loader is moved

		- __accessor__
			-# std::shared_ptr<TranslationLoader> getTranslationLoader() const\n
				Return current TranslationLoader.
		*/
		std::shared_ptr<TranslationLoader> loader{ nullptr };
		/*! [read only] Targets that need to translate
				- __accessor__
					-# std::vector<Translate>& getTranslateTargets()\n
						Return all translation targets

					-# const std::vector<Translate>& getTranslateTargets() const\
						as [1], but with const modifier.
		*/
		std::vector<Translate> translateTargets;
	};
}