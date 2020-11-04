# Memory
The topics discussed in this section are related to memory uage and performance in C++ programs.

## Cache, Memory, and a Tale of Speed and Cost
TODO: talk about cache vs. memory

## Alignment
Data is transferred between memory/higher-level cache and lower-level cache in blocks of fixed size, called cache lines. In machines with Intel and AMD64 CPUs, the L1 cache line size is **64 bytes**. Knowing this fact, it brings up an important point: if the size of a piece of data (e.g. a class or struct instance) is larger than 64 bytes, then it needs to be transferred via multiple cache reads.

Let's take a look at a few examples:
```
// sizeof(Type1) = 8
// alignof(Type1) = 4
struct Type1 {
    int number_1; // 4 bytes
    int number_2; // 4 bytes
};
```
In the example above, the structure has 2 integers. Assuming integers are 4 bytes, `sizeof(Type)` resolves to 8 (bytes). The reason is obvious and doesn't need any explanation.

Now, let's take a look at more examples:
```
// sizeof(Type2) = 8
// alignof(Type2) = 4
struct Type2 {
    int number_1; // 4 bytes
    char char_1; // 1 byte
};
```

```
// sizeof(Type3) = 8
// alignof(Type3) = 4
struct Type3 {
    int number_1; // 4 bytes
    char char_1; // 1 byte
    short number_2; // 2 bytes
};
```

```
// sizeof(Type4) = 12
// alignof(Type4) = 4
struct Type4 {
    int number_1; // 4 bytes
    char char_1; // 1 byte
    short number_2; // 2 bytes
    short number_3; // 2 bytes
};
```

```
// sizeof(Type5) = 16
// alignof(Type5) = 4
struct Type5 {
    int number_1; // 4 bytes
    char char_1; // 1 byte
    int number_2; // 4 bytes
    char char_2; // 1 byte
};
```

```
// sizeof(Type5e) = 12
// alignof(Type5e) = 4
struct Type5e {
    int number_1; // 4 bytes
    int number_2; // 4 bytes
    char char_1; // 1 byte
    char char_2; // 1 byte
};
```

```
// sizeof(Type6) = 16
// alignof(Type6) = 8
struct alignas(8) Type6 {
    long number_1; // 8 bytes
    short number_2; // 2 bytes
};
```

## References:
- Jonathan Muller's talk at Meeting C++ 2018 ([video](https://www.youtube.com/watch?v=Nz9SiF0QVKY))
- Herb Sutter's talk at NWCPP ([video](https://www.youtube.com/watch?v=L7zSU9HI-6I&feature=youtu.be))
- [https://en.wikipedia.org/wiki/CPU\_cache
- https://vorbrodt.blog/2019/04/06/data-alignment-the-c-way/
- https://jitpaul.blog/2018/04/24/memory-alignment/
