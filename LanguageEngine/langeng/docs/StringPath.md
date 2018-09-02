# String Path

String Path is a format of resource locator address that used in boost property_tree library. Each of the node are seperated by using "." seperator.

Beside that, in some INI file also able to found a similar formatted string with String Path.

Language Engine use String Path as the id of each translations' string in the translation file. The String Path will then converte into rapidJSON pointer's path format so rapidJSON can understand what user requesting for. Please refer to rapidJSON's documentation if more information about rapidJSON's JSON Pointer are intersted (which I'm recommended you do so).

## Basic Usage
The String Path begin with the root element of the JSON object and each object are seperated using "." seperator.

Example:
```json
{
    "gui_command": {
        "start_game": "Start",
        "exit_game": "Exit"
    }
}
```

With the JSON on top, the path to the node ```start_game``` under ```gui_command``` will be:
```
gui_command.start_game
```

the above String Path will be translated into rapidJSON pointer's format as bellow:
```
/gui_command/start_game
```

The string path can also point to a value of an array.
```json
{
    "array": [
        "item 1",
        "item 2",
        "item 3"
    ]
}
```

The array in JSON start form 0 therefore the path to "item 2" is:

```
array.1
```

This will be translated to:

```
/array/1
```

## Limitation
Language Engine translate String Path to rapidJSON pointer's path by insert a "/" in front of the string and then repalce all of the "." seperator with "/" seperator.

Therefore, all of the node's name are required not to contain any other "." or it will be replaced with "/" seperator too. This will cause Language Engine unable to find that value and return error.