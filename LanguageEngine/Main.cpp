#include <iostream>
#include "texttools/TextTools.hpp"
#include "langeng/Translator.hpp"

using namespace std;
using namespace vas;

void validator(LANGENG_VALIDATOR_ARGS)
{
	std::string error("Cannot load file \"" + fileName + "\"");
	if (!document.HasMember("lang")) throw std::runtime_error(error);
	if (!document["lang"].HasMember("magic")) throw std::runtime_error(error);
	auto& var = document["lang"]["magic"];
	if (!var.IsString()) throw std::runtime_error(error);
	if (static_cast<string>(var.GetString()) != "CC50") throw std::runtime_error(error);
}

int main()
{
	try
	{
		std::string title;
		Cout() << "Translation file: en_gb.json" << endl;
		langeng::Translator translator(std::make_unique<langeng::TranslationLoader>("en_gb.json", &validator), 
			{
				langeng::Translate("lang.window.title", title)
			}
		);
		Cout() << title << endl;
		while (true)
		{
			std::string file;
			file = TextTools::readln();
			if (file.empty()) break;

			Cout() << "Translation file: " << file << endl;
			translator.installTranslationLoader(std::make_shared<langeng::TranslationLoader>(file, &validator));
			translator.retranslate();

			Cout() << title << endl;
		}
	}
	catch (const std::exception& e)
	{
		Cout() << e.what() << endl;
	}
	system("pause");
	return 0;
}