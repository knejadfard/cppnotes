# Data Structures: Deque

`std::deque` (double-ended queue) from C++ standard library allows fast insertion and deletion at both its beginning and its end, without invalidating pointers or references to the other elements.

By using `std::deque`'s `push_back`, `front`, and `pop_front` member functions, you can use it as a **queue** data structure (first-in-first-out) for implementing algorithms such as **breadth-first search**.
Moreover, by using `std::deque`'s `push_back`, `back`, and `pop_back` member functions, you can use it as a **stack** data structure (last-in-first-out) for implementing algorithms such as **depth-first search**. Alternatively, a `std::vector` can also be used for this use case.

**Note:** It is important to keep in mind that unlike `std::vector`, `std::deque` **does not** guarantee a contiguous memory space for its elements.
**Note:** Similar to `std::vector`, `std::deque` automatically expands and contracts to fit the need of its elements. Although `std::deque`'s expansion is cheaper than `std::vector` because it does not need to move all of the elements to the newly-allocated space.

Below is a program show-casing the use of `std::deque`:
```
#include <iostream>
#include <deque>

template <typename Container>
void print_container(const Container& container) {
    for (const auto& elem: container) {
        std::cout << elem << ' ';
    }
}

int main(int argc, const char * argv[]) {
    std::deque<int> deque;
    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);
    deque.push_back(4);
    deque.push_back(5);

    print_container(deque);
    std::cout << '\n';

    deque.pop_front();

    print_container(deque);
    std::cout << '\n';

    return 0;
}
```

Compiling and running the above program yields this output:
> 1 2 3 4 5
> 2 3 4 5
