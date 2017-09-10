# C++ Code Style Guide

## Ogólne

**Tabulacja: `\t` równy 4 spacjom**

**Styl klamer:**

```cpp
if(x)
{
    // kod
}
```

**Nazwy funkcji i metod:**
```cpp
void myFunction();
```

**Nazwy zmiennych i pól:**
```cpp
float myVariable;
```

**Nazwy stałych:**
```cpp
const float MY_CONST;
```

**Wskaźnik na stałą**:
```cpp
const int* p;
```

**Wyrażenia matematyczne:**
```cpp
float x = (1 + 1) / 2;
```

**Przerwy od nawiasów:**
```cpp
int suma(int x, int y);
```

**Namespace:**
```cpp
namespace Szczur
{
    // kod
}
```

**Kolejność pól i metod klasy:**

1. przyjaźnie klasy (*friend*)
2. publiczne pola
3. publiczne metody
4. chronione pola
5. chronione metody
6. prywatne pola
7. prywatne metody

**Pliki nagłówkowe linkujemy tylko w plikach *.h/.hpp*.**

## Porady

**Przy klasach, które nie mogą być dziedziczone, dodawaj *final*.**
**Przy metodach, które są dziedziczone, dodawaj *override*.**
**Przy funkcjach i metodach, które nie zmieniają wartości pól, dodawaj *const*.**
