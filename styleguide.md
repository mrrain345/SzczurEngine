# C++ Code Style Guide

## General

### Tabulation

 `\t` equals to 4 spaces

### Braces

```cpp
void some(int a, int b) const {
    //...
}
```

### Naming Style

Local variables: `camelCase`.  
Constants: `UPPER_SNAKE`.  
Classes: `PascalCase`.  
Class attributes: `camelCase`.  
Class constants: `PascalCase`.  
Functions and methods: `camelCase`.  

### Conditional and control statements

With space: `if ()`.

### Expressions and function parameters

Without space: `(x + y)`.

### Variable declaration

Each declaration separately.

### Pointers and references

```cpp
typename* foo;
typename& bar;
```

### Templates

Template code keep in `.h` files.  
Types as `template<typename T>`.

### Oneline conditional statements

```cpp
if ()
    //...
else
    //...
```


### Files Extansions

Source: `.cpp`
Header: `.h`

### Files Structure

```
include/
    Szczur/
        *.h
src/
    Szczur/
        *.cpp
modules/
    ModuleName/
        *.h *.cpp
```

### Include Guards

```cpp
#pragma once
```

### Forward Declarations

Avoid using forward declarations where possible. Just `#include` the headers you need.

### Inline Functions

Define functions *inline* only when they are small, say, 10 lines or fewer.

### Order of Includes

1. Corresponding header file (if `.cpp`)
2. C++ system files
3. Other libraries' .h files
4. Your project's .h files

#### Example

```cpp
#include <CorrespondingHeader.h>

#include <iostream>
#include <ctime>
#include <string>

#include <SFML/System.hpp>

#include <AnotherProjectHeader.h>
```

### Namespaces

Namespaces subdivide the global scope into distinct, named scopes, and so are useful for preventing name collisions in the global scope.

```cpp
namespace X {
    namespace Y {
        // ...
    }
}
```

#### Naming

```
rat::
    core::
    menu::
    module1::
    module2::
```

### Using Declaration

Do not use `using namespace` nor e.g. `using std::string` in global scope, never!

### Descriptions of function and parameters in header file

```cpp
// Do foo
// angle : alpha
// index : index in main table
void Foo(float angle, int index);
```

## Classes

### Inheritance

Space before and after colon.

```cpp
class DerivedClass : public BaseClass {
    //...
}
```

### Order of attributes and methods

 * friend declarations  
 * public attributes
 * protected attributes
 * private attributes
 * public methods
 * protected methods  
 * private methods

### Private and protected attributes

Add `_` in front of the attribute's name e.g.

```cpp
private:
    typename _variableName;
```

## Tips

Use ***final*** keyword with classes that cannot be inherited.  
Use ***override*** keyword with methods that are inherited.  
Use ***const*** keyword with functions and methods that do not change the value of attributes.  
Use ***const T&*** to pass objects to functions and methods to avoid copying it.
