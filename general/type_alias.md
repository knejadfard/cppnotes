# Type Alias
A type alias is a name that refers to an existing type.

There are two ways to define a type alias:
1. The `using` keyword
2. The `typedef` keyword

Here are examples showing the usage of each method:
```
using MyType1 = std::vector<std::string>;
typedef std::vector<std::string> MyType2;

MyType1 t1; // t1's type is std::vector<std::string>
MyType2 t2; // t2's type is std::vector<std::string>
```

The assembly generated for both `MyType1 t1` and `MyType2 t2` are identical.
