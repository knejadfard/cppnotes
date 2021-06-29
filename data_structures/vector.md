# Data Structures: Vector

`std::vector` from C++ standard library is one of the most basic data structures often used in C++ programs. A vector guarantees a contiguous memory space for storing the elements, and resizes as needed. Because of this, it is important to reserve sufficient memory when such information is available, to avoid redundant vector resize operations while inserting new elements.

By using `std::vector`'s `push_back`, `back`, and `pop_back` member functions, you can use it as a **stack** data structure (last-in-first-out) for implementing algorithms such as **depth-first search**.

**Note:** A vector manages its size automatically. With every expansion, existing references/pointers to elements are invalidated because the elements are moved to a newly-allocated memory space.

Below is a program show-casing the use of `std::vector`:
```
#include <iostream>
#include <vector>

template <typename Container>
void print_container(const Container& container) {
    for (const auto& elem: container) {
        std::cout << elem << ' ';
    }
}

int main(int argc, const char * argv[]) {
    std::vector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);
    vector.push_back(5);

    print_container(vector);
    std::cout << '\n';

    vector.pop_back();

    print_container(vector);
    std::cout << '\n';

    return 0;
}
```

Compiling and running the above program yields this output:
```
1 2 3 4 5
1 2 3 4
```
