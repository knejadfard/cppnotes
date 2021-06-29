# Prefix and Postfix Increment/Decrement Operator
I have been semi-ignorant of the way the increment/decrement operators work in C++ for a long time. I am familiar with what they do: to increment or decrement values. What I never quite understood was the difference between prefix and postfix versions of this operator.

To illustrate this important, somehow hidden point, lets review an example:
```
int i = 0;
if(i++ == 1) {
    std::cout << "i++ is equal to 1" << std::endl;
}

//here, the value of i is 1 for sure
if(++i == 2) {
    std::cout << "++i is equal to 2" << std::endl;
}
```

The output of the above example is:
```
++i is equal to 2
```

To understand what is going on here, lets see what these operators actually do:
- **Prefix increment and decrement** - Increments or decrements the value of the object and returns a reference.
- **Postfix increment and decrement** - Creates a copy of the object, increments or decrements the value of the object and returns the copy from before the increment-decrement operation happened.

**Note** - Due to the fact that post-increment and post-decrement operations involve creating a temporary copy object, they are less efficient than pre-increment and pre-decrement operators in contexts where the returned value is not really needed.

**Note** - Undefined Behavior due to sequencing order violations. TODO: needs research
