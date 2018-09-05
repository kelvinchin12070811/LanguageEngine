#pragma once
#include <cstdint>
#include <string>

/*! \addtogroup compile_time_config Compile Time Configuartion
	\brief Configs that change how this library will be compiled.

	The following shows all configs that avaliable. To turn an option off, comment out the ```#define``` statement.

	| Header |
	| : --- : |
	| langeng/EngConfig.hpp |
	@{
*/

/*! Use C++ exception to handle error. Return bool value instead if this option is off\n
	Default is ON
*/
#define LANGENG_USE_EXCEPTION

/*! If on, some action or function will not throw exception or return false. It will did the error correction by it self.\n
	Default is ON

	The following members will be affected by this option:
	- TranslationLoader::getTranslatedString \n
	  Use the id of the traget instead of throwing exception if the function failed to translate a target.
*/
#define LANGENG_USE_DEFAULT_ACTION

/*! @} */

/*! \brief The version of the library.
	
	This structure try it's best to tell what's the current version of the library

	| Header |
	| : --- : |
	| langeng/EngConfig.hpp |
*/
struct LANGENG_VERSION
{
	static const uint32_t major = 1; /*!< Major number of version number */
	static const uint32_t minor = 1; /*!< Minor number of version number */
	static const uint32_t bugFixed = 0; /*!< Bug fixed number of version number */

	static std::string toString()
	{
		return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(bugFixed);
	} /*!< Generate and return a string of current version. */
};