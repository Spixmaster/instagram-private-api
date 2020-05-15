# Contributing v0.0.31 (15.05.2020)
This file may content irrelevant content as all my projects include the same CONTRIBUTING.md for easier maintenance. I want to keep this file as simple as possible. Therefore, all rules a grouped in suitable subsections. Overall, British English is used as language for all text.

## 1. Description on how to contribute
Contributing works as always by forking the repository and then making a pull request.

## 2. Commenting
* The Doxygen syntax is used. 
* Everything is commented so that Doxygen does not output any error on documentation creation: classes, structs, functions, member variables. Additional comments are voluntary.
* All Doxygen comments are sentences in most cases if useful. There, sentence endings are to use either way. The reason is that Doxygen will add them too either way.
* Non-Doxygen comments shall be sentences except those which structure like the ones used in classes.
* // only for single a comment, otherwise /**/.
* In dynamic programming languages, the first word of the description shall contain the type.
```
@param[in|out] str {string} Is used as output.
```

### 2.1. Doxygen
* Doxygen comments have the following possible syntaxes of which the second one is used in my projects.
```
/*!
 *
 */
```

```
/**
 *
 */
```
* Special commands start with *\\* or *@*. We use the @.
* Special characters like '@', '<>' and '#' can be escaped with a preceding '\'.

#### 2.1.1. Special commands
##### 2.1.1.1. Structural indicators (define type of comment blocks)
* @class <name> [<header-file>] [<header-name>] - name(class name), header-file(file of header), header-name(include path for header)
* @dir [<path fragment>] - path fragment(directory name)
* @enum <name> - name(enum name)
* @file [<name>] - name(file name)
* @fn (function declaration) - only needed if a comment block is not placed in front (or behind) the function declaration or definition
* @mainpage [(title)] - title(for index.html)
* @namespace <name> - name(name of namespace)
* @page <name> (title) - name(reference to page; all lower case), title(like heading)
* @struct <name> [<header-file>] [<header-name>] - see @class
* @var (variable declaration)

##### 2.1.1.2. Section indicators (all followed by description)
* @author
* @brief
* @bug
* @copyright
* @details
* @exception <exception-object> - exception-object(name of class)
* @note
* @param '['dir']' <parameter-name> - dir(in, out)
* @throw <exception-object> - exception-object(thrown object)
* @todo
* @tparam <template-parameter-name> - template-parameter-name(parameter name)
* @return
* @retval <return value> - return value(e. g. error codes like -1)
* @see
* @version

##### 2.1.1.3. Commands to create links (work only in page documentation block)
* @section <subsection-name> (subsection title) - subsection-name(), subsection title(title)
* @section <section-name> (section title) - section-name(), section title(title)
* @paragraph <paragraph-name> (paragraph title) - paragraph-name, paragraph title(title)

#### 2.1.2. Example
```
/**
 * @page page1 A documentation page
 * @tableofcontents
 * Leading text.
 * @section sec An example section
 * This page contains the subsections \ref subsection1 and \ref subsection2.
 * For more info see page \ref page2.
 * @subsection subsection1 The first subsection
 * Text.
 * @subsection subsection2 The second subsection
 * More text.
 */
 
/**
 * @page page2 Another page
 * Even more info.
 */
```

#### 2.1.3. The main page
The main file of the project shall contain the @mainpage Doxygen comment block. Add version logs to it. Here you see an example:
```
/**
 * @mainpage tools-js
 * @author Matheus Gabriel Werny de Lima
 * @copyright GNU General Public License v2.0
 * @version
 * 0.0.4 (22.04.2020)
 * - Added the class "Messages".
 * @version
 * 0.0.3 (22.04.2020)
 * - Made a class out of the object literal.
 * @version
 * 0.0.2 (21.02.2020)
 * - Removed an unncessary function.
 * @version
 * 0.0.1 (20.04.2020)
 * - Starting the project.
 */
```

### 2.2. Only for C++
Comments are put only in .h and not in .cpp where the definitions are.

## 3. General programming behaviour by experience with C++
1. Always close open files.
2. Error handling: I prefer returning error messages or default values than throwing an exception but it depends on the use case. By throwing exception all the time in libraries, it bulks the source code and at the end there would not be a positive effect. Take for example a function that reads out file content. Good practice is to return nothing if the files does not exist and save a suitable message in the error log. If we threw an exception the file content would still be empty and we needed to use several try-catch blocks.
3. Have a struct "Constants" with version and release.
4. Have a class "Messages" with stored strings which are sent to the user. This simplifies translations a lot. Do not use string concatenation in this file as it makes translations impossible! Always use string formatting or template strings in here.
5. Prefer functions over overloaded operators.
```
.append() instead of +=
.at() instead of []
...
```
6. Empty files rather than deleting them.
7. Const declared variables are accessed faster. This is useful here:
```cpp
catch(const std::exception &e)
```
8. Use the C++ STL instead of the C library.
```
size_t              --> std::size_t
time_t              --> std::time_t
time()              --> std::time()
strftime()          --> std::strftime()
localtime()         --> std::localtime()
struct tm           --> struct std::tm()
#include <time.h>   --> #include <ctime>
srand()             --> std::srand()
rand()              --> std::rand()
remove()            --> std::remove()
```
9. Leave blank lines before and after compound statements like conditions and loops.
10. Write error messages to a log and not to stderr.
11. Check the stdout of the programme.

## 4. OOP
1. For every class or struct:
```cpp
typedef std::shared_ptr<class> ptr;
```
2. Structure it like this:
```
//Friend classes
//Pointer of itself
//Member variables
//Constructors
//Destructors
//Member functions
```
3. Member variables have prefix "m_" if they are not static.
4. Make all member function "const" and "noexcept" if possible.
5. If a class or struct needs to contain an other object include the class' ptr member variable (std::shared_ptr<ObjectX> ptr) but only if the object is not from the STL (std::map, std::vector, std::string and so on). That would be too much. Data types of normal objects cannot cope with forward declarations of their type which is needed when objects include each other as a type.
```cpp
struct Message;
struct Chat
{
    Message pinned_message; //Does not work!
}
```

## 5. Libraries
### 5.1. Rapidjson (C++)
1. IsObject() checks whether the passed string is a JSON object and IsArray() checks whether it is a JSON array.
2. doc.HasMember() and so on assert that doc is an object. The function even crashes if it is called on a json array.
3. If member of JSON object is accessed which does not exist the programme crashes.
4. Parsing is allowed even if the provided string is not JSON at all.
5. To get the array size call .GetArray().Size.

#### 5.1.1. Example
```cpp
rapidjson::Document doc;
doc.Parse(str.c_str());

if(doc.IsObject() || doc.IsArray())
{
    if(doc.HasMember("bla"))
    {
        if(doc.IsString()
        {
            doc["bla"].GetString();
        }
    }
}

const rapidjson::Value &items = doc["items"];
```

### 5.2. Puppeteer (JavaScript)
1. Ensure that elements exist: `await page.waitForSelector("input[name='username']", {timeout: Constants.srch_timeout()});`
2. Close browser instances at the end.
3. By default, use `await page.goto(url, {waitUntil: "domcontentloaded"});` if no JavaScript needs to be loaded by the page. Otherwise, `await page.goto(url, {waitUntil: "networkidle0"});` needs to be used.
