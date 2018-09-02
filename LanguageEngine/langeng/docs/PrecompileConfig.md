# Precompile Configuration

Configs that chang how this library will be compiled.

|Header|
|:---:|
|langeng/EngConfig.hpp|

---

## Configurations

The table below shows all configs that avaliable. To turn an option off, comment out the ```#define``` statement.

|Defined Macro|Meaning|Default option|
|:---|:---|:---:|
|LANGENG_USE_EXCEPTION|Use C++ exception to handle error. Return bool value instead if this option is off|ON|
|LANGENG_USE_DEFAULT_ACTION|If on, some action or function will not throw exception or return false. It will did the error correction by it self.<br>See [here](#fnaf_option_2) for a list of affected function.|ON|

<a id="fnaf_option_2"></a>
## Functions that will be affected by *LANGENG_USE_DEFAULT_ACTION*

- __TranslationLoader::getTranslatedString__  
    Use the id of the traget instead of throwing exception if the function failed to translate a target.

---

## Version Number

The structure ```LANGENG_VERSION``` contain the current version number of the engine.

### Prototype

```cpp
struct LANGENG_VERSION; 
```

### Public Members

1. __*static const uint32_t major*__  
    major number of version number.

- __*static const uint32_t minor*__  
    minor number of version number.

- __*static const uint32_t bugFixed*__  
    bug fixed (or reversion) number of version number.

- __*static std::string toString()*__  
    convert current version number to string.