#include <iostream>
#include "texttools/TextTools.hpp"
#include "langeng/TranslationLoader.hpp"

using namespace std;
using namespace vas;

int main()
{
	try
	{
		langeng::TranslationLoader translator("en_gb.json", [](LANGENG_VALIDATOR_ARGS)
		{
			std::string error("Cannot load file \"" + fileName + "\"");
			if (!document.HasMember("lang")) throw std::runtime_error(error);
			if (!document["lang"].HasMember("magic")) throw std::runtime_error(error);
			auto& var = document["lang"]["magic"];
			if (!var.IsString()) throw std::runtime_error(error);
			if (static_cast<string>(var.GetString()) != "CC50") throw std::runtime_error(error);
		});

		Cout() << translator.getTranslatedText("lang.window.title") << endl;
	}
	catch (const std::exception& e)
	{
		Cout() << e.what() << endl;
	}
	system("pause");
	return 0;
}