# The `mutable` Keyword
```
struct Type {
    void func1() const {
        val1 = 2; // ERROR: assignment of member ‘Type::val1’ in read-only object
        val2 = 2; // OK
    }

    int val1;
    mutable int val2;
};

int main() {
    Type t{};
    return 0;
}
```

A very good use case for `mutable` is when dealing with `std::mutex` in a const object (either because the object itself is declared as const or just for a const member function). Locking and releasing the lock on a mutex basically breaks the `const` contract. In this case, declaring the mutex instance as `mutable` allows for locking/unlocking the mutex while still keeping everything else in compliance with the `const` contract.

## Mutable Lambdas
Arguments captured by value cannot be modified in a lambda. Since C++11, the `mutable` can be used on the lambda to allow this:
```
int x = 0;
auto f1 = [=]() mutable { x = 42; };  // OK
auto f2 = [=]() { x = 42; };  // Error: a by-value capture cannot be modified in a non-mutable lambda
```
[Reference](https://stackoverflow.com/a/105061/14459318)
