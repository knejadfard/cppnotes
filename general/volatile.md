# Volatile
`volatile` is a hint for avoiding aggressive optimization involving the relevant object, because the value of the object might be changed by means undetectable by an implementation. For example, when a value may end up being modified by asynchronous processes such as interrupt handlers. To put it simply, the compiler must perform loads and stores in the executable as often as they occur in the source code, without being eliminated or reordered.

## Resources
- [Modernes CPP: volatile and Other Small Improvements in C++20](https://www.modernescpp.com/index.php/volatile-and-other-small-improvements-in-c-20)
- [Microsoft Docs on Volatile Keyword](https://docs.microsoft.com/en-us/cpp/cpp/volatile-cpp?view=msvc-160)
