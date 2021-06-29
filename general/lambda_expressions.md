# Lambda Expressions
Lambdas in C++ allow for defining closures: unnamed function objects that can capture in-scope variables.

The following example shows a very simple lambda expression that does not capture any in-scope variables:
```
int number = 10;

auto lambda1 = []() {
    // number is not visible here!
};
```

In order to capture variables by value, `=` can be used in the captures list when defining the lambda:
```
int number = 10;

auto lambda2 = [=]() {
    // number is visible here, is a copy of the original number
    // variable, and is read-only in the closure.
};
```

In order to capture variables by value, `&` can be used in the captures list when defining the lambda:
```
int number = 10;

auto lambda2 = [&]() {
    // number is visible here, is a reference to
    // the original number variable. It can be modified
    // in this scope and it will affect the original
    // variable.
    number = 2;
};
```

Specific variables may be captured. The following example shows capturing a specific variable by value:
```
int number = 10;

auto lambda2 = [number]() {
    // number is visible here, and is a copy of the
    // original number variable. Since it is passed
    // in by value, it is read-only in this scope.
};
```

The following captures a specific variable by reference:
```
int number = 10;

auto lambda2 = [&number]() {
    // number is visible here, is a reference to
    // the original number variable. It can be modified
    // in this scope and it will affect the original
    // variable.
    number = 2;
};
```
