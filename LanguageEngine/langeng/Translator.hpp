#pragma once
#include <vector>
#include <memory>
#include "Translate.hpp"

namespace langeng
{
	class Translator
	{
	public:
		Translator(const std::shared_ptr<TranslationLoader>& loader, std::vector<Translate>&& target):
			loader(loader), translateTargets(std::move(target))
		{
			retranslate();
		}

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
		std::shared_ptr<TranslationLoader> loader{ nullptr };
		std::vector<Translate> translateTargets;
	};
}