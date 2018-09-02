# TranslationLoader
A helper class that use to load translation file. [More](#more)

|Header|Namespace|
|:---:|:---:|
|langeng/TranslationLoader.hpp|langeng|

---

## Prototype
```cpp
class TranslationLoader;
```

## Macro
- [LANGENG_VALIDATOR_ARGS](#langeng_validator_args)

## Public Data Type
- [DocumentType](#DocumentType)
- [Validator](#Validator)

## Public Members

|Return Type|Name|
|---:|:---|
|&nbsp;|[TranslationLoader](#ctor_1)|
|std::string|[getTranslatedText](#getTranslatedText)|
|void|[loadTranslation](#loadTranslation)|

## Public Properties
- [validator](#validator)

---

# Detial Descriptions
## About This Class <a id="more"></a>
TranslationLoader is a helper class that use to load and phrase the translation file for the controller class ```Translator```. This class also help Translator to find an id of a translation and let it replace the original string with it.

An id of a translation is a kind of "string path" which will be converte to rapidJSON pointer's path format. For more information about string path, see [String Path](../StringPath.md).

## Macro
### LANGENG_VALIDATOR_ARGS <a id="langeng_validator_args"></a>
```#define``` of ```const langeng::TranslationLoader::DocumentType& document, const std::string& fileName```  
This macro use for reduce typing when implementing the validator function's argument list.

Expanded Arguments:
- __*const langeng::TranslationLoader::DocumentType& document*__  
    Document that represent the translation file.

- __*const std::string& fileName*__  
    Name of the translation file with full path which passed in by user.

## Public Data Types
### DocumentType <a id="DocumentType"></a>
Typedef of rapidjson::Document, repersent the raw structure of the translation file. Using rapidJSON's method to access it.

### Validator <a id="Validator"></a>
Validator that use to varify the document. This function is call after the file is open successfully.

If the macro ```LANGENG_USE_EXCEPTION``` is defined, return type is void and exception trown if error occured.  
If the same macro is not defined, return type is bool and return false if error occured.

## Public Members
### TranslationLoader() <a id="ctor_1"></a>
Default constructor that create empty TranslationLoader.

Other overload:
- [TranslationLoader(const std::string& path)](#ctor_2)
- [TranslationLoader(const std::string& path, TranslationLoader::Validator validator)](#ctor_3)

### TranslationLoader(const std::string& path) <a id="ctor_2"></a>
Create and load a file with file name ```path``` and default validator.

Other overload:
- [TranslationLoader()](#ctor_1)
- [TranslationLoader(const std::string& path, TranslationLoader::Validator validator)](#ctor_3)

### TranslationLoader(const std::string& path, TranslationLoader::Validator validator) <a id="ctor_3"></a>
Create and load a file with file name ```path``` and custom validator with ```validator```.

Other overload:
- [TranslationLoader()](#ctor_1)
- [TranslationLoader(const std::string& path)](#ctor_2)

### std::string getTranslatedText(const std::string& id) const <a id="getTranslatedText"></a>
Get translated text from translation file with id.

If macro ```LANGENG_USE_EXCEPTION``` is defined, empty string is returned.
If macro ```LANGENG_USE_DEFAULT_ACTION``` is defined, id is returned.

### void loadTranslation(const std::string& path) <a id="loadTranslation"></a>
Load translation file with file name ```path```.

## Public Properties
### Validator <a id="validator"></a>
Function that use to varify the document of the translation file, this function is called after the file is opened succesfully.

#### get
Get validator

#### set
Set validator