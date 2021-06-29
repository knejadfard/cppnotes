# Performance Tips
The content in this section focuses on writing C++ code that performs better.

## IIFE
Short-hand for Immediately Invoked Function Expression, this technique involves defining and calling a lambda expression at the spot.
I have found a particular use case for this technique to improve performance in Jason Turner's talk at CppCon 2016 ([here](https://www.youtube.com/watch?v=uzF4u9KgUWI)).

Basically, this technique is used for optimizing complex initializations:
```
#include <string>

int main() {
    const int i = std::rand();
    std::string s;
    switch (i % 4) {
        case 0:
            s = "value 0";
            break;
        case 1:
            s = "value 1";
            break;
        case 2:
            s = "value 2";
            break;
        case 3:
            s = "value 3";
            break;
    }
}
```

The main issue with the above code is that, due to the use of switch statement, we have ended up using `operator=` to initialize the value of `s` after we have constructed it.

Using IIFE, the above can be revised to:
```
#include <string>

int main() {
    const int i = std::rand();
    std::string s = [&]() {
        switch (i % 4) {
            case 0:
                return "value 0";
                break;
            case 1:
                return "value 1";
                break;
            case 2:
                return "value 2";
                break;
            case 3:
                return "value 3";
                break;
        }
    }();
}
```

This way, we are able to set the value of `s` right when we construct it:

## Always Initialize When Const Isn't Practical
Also mentioned in Jason Turner's talk at CppCon 2016 ([here](https://www.youtube.com/watch?v=uzF4u9KgUWI)), this is very similar to the issue described in the IIFE section for setting values when constructing things, as opposed to constructing and then setting a value later.

Consider the following:
```
struct Int {
    Int(std::string t_s) {
        m_s = t_s;
    }

    int val() const {
        return std::atoi(m_s.c_str());
    }

    std::string m_s;
};
```

Using initializer lists, it can be revised as:
```
struct Int {
    Int(std::string t_s) : m_s{t_s}
    {
    }

    int val() const {
        return std::atoi(m_s.c_str());
    }

    std::string m_s;
};
```
