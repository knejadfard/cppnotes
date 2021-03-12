# Algorithm Analysis

When analyzing algorithms, the goal is to figure out how the running time or space complexity changes when input count changes.

## Big-O
Running time of algorithms is usually displayed using the Big-O notation which is defined as:
> If the growth of `f(n)` is at most the growth of `g(n)`, then `f(n)` is `O(g(n))`.
The order (or growth rate) of a function is the simplest, smallest function that is is a big-O of. For example, if `f(n) = 5n`, we can say it is `O(n^2)`. But the order of `f(n)` is `n`.

### Terminology
- Constant-time: `O(1)`, in other words the running time of algorithm is not related to n.
- Linear: `O(n)`, proportional to n.

### Combining Functions
If `T1(n) = O(f(n))` and `T2(n) = O(g(n))` then:
- `T1(n) + T2(n) = max(O(f(n)), O(g(n)))`
- `T1(n) * T2(n) = O(f(n)) * O(g(n))`

## Logarithms
When analyzing algorithms and their time complexity, it is critical to understand what logairthms are. Essentially, `log_m(n)` (read "log base m of n") means the number of times we must multiply `m` by itself to get to `n`. In other words:
```
log_m(n) = p
m ^ p = n
```
