# Translator class

The main class that perform translations. [More](#more)

|Header|Namespace|
|:---:|:---:|
|langeng/Translator.hpp|langeng|

---

## Prototype
```cpp
class Translator;
```

## Public Members
|Return Type|Name|
|---:|:---|
|&nbsp;|[Translator](#ctor_1)|
|std::shared_ptr&lt;TranslationLoader&gt;|[getTranslationLoader](#getTranslationLoader)|
|std::vector&lt;Translate&gt;|[getTranslateTargets](#getTranslateTargets)|
|void|[installTranslationLoader](#installTranslationLoader)|
|void|[retranslate](#retranslate)|

---

# Detial Description

## About This Class <a id="more"></a>
Translator is the main controller class that perform translation of all targets hold by it. Translator will load an language file in JSON format with the help of the class ```TranslationLoader```.

## Public Members

### Translator(const std::shared_ptr&lt;TranslationLoader&gt;& loader, std::vector&lt;Translate&gt;&& target)   <a id="ctor_1"></a>
Construct a Translator object with ```loader``` and ```target```, note that ```target``` is moved instead of copy.

Other overload:
- [Translator(std::shared_ptr&lt;TranslationLoader&gt;&& loader, std::vector&lt;Translate&gt;&& target)](#ctor_2)

### Translator(std::shared_ptr&lt;TranslationLoader&gt;&& loader, std::vector&lt;Translate&gt;&& target) <a id="ctor_2"></a>
Construct a Translator object with ```loader``` and ```target```, note that ```loader``` and ```target``` is moved instead of copy.

Other overload:
- [Translator(const std::shared_ptr&lt;TranslationLoader&gt;& loader, std::vector&lt;Translate&gt;&& target)](#ctor_1)

### std::shared_ptr&lt;TranslationLoader&gt; getTranslationLoader() const <a id="getTranslationLoader"></a>
Return ```TranslationLoader``` held by the translator.

### const std::vector&lt;Translate&gt;& getTranslateTargets() const <a id="getTranslateTargets"></a>
Return a vector of translation targets with const modifier.

Other overload:
- [std::vector<Translate>& getTranslateTargets()](#getTranslateTargets_nonconst)

### std::vector&lt;Translate&gt;& getTranslateTargets() <a id="getTranslateTargets_nonconst"></a>
Return a vector of translation targets without const modifier.

Other overload:
- [const std::vector&lt;Translate&gt;& getTranslateTargets() const](#getTranslateTargets)

### void installTranslationLoader(const std::shared_ptr&lt;TranslationLoader&gt;& loader) <a id="installTranslationLoader"></a>
Install a ```TranslationLoader``` into this Translator.

Other overload:
- [void installTranslationLoader(std::shared_ptr&lt;TranslationLoader&gt;&& loader)](#installTranslationLoader_1)

### void installTranslationLoader(std::shared_ptr&lt;TranslationLoader&gt;&& loader) <a id="installTranslationLoader_1"></a>
Install a ```TranslationLoader``` into this Translator. Note that ```loader``` is moved.

Other overload:
- [void installTranslationLoader(const std::shared_ptr&lt;TranslationLoader&gt;& loader)](#installTranslationLoader)

### void retranslate() const <a id="retranslate"></a>
Retranslate all translation targets.