# The `mutable` Keyword
Found this good example [here](https://stackoverflow.com/questions/15999123/const-before-parameter-vs-const-after-function-name-c/15999152#15999152):
```
struct X {
    void func1() const {
        x = 42; // ERROR: this is a const member function
        y = 42; // OK: y is mutable
    }

    void func2() {
        x = 42; // OK: non-const member function
        y = 42; // OK: non-const member function
    }

    int x;
    mutable int y;
};
```

A very good use case for `mutable` is when dealing with `std::mutex` in an const object. Locking and releasing the lock on a mutex basically breaks the `const` contract. In this case, declaring the mutex instance as `mutable` allows for locking/unlocking the mutex while still keeping everything else in compliance with the `const` contract.

## Mutable Lambdas
Arguments captured by value cannot be modified in a lambda. Since C++11, the `mutable` can be used on the lambda to allow this:
```
int x = 0;
auto f1 = [=]() mutable { x = 42; };  // OK
auto f2 = [=]() { x = 42; };  // Error: a by-value capture cannot be modified in a non-mutable lambda
```
[Reference](https://stackoverflow.com/a/105061/14459318)
