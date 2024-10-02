# Reference
An alias (an alternate name) for an object.

## main characteristic of references
- mutating the *referent* through the *reference* changes the original value
(the referent is the object to which the reference refers)
- In the example below `a` and `b` are aliases for main’s `x` and `y` respectively. In other words, `a` is `x` **and**
    - **not** a pointer to *x*
    - **nor** a copy of *x*, but **x itself**.
Anything you do to `a` gets done to `x`, and vice versa.

> Example: Session1 -> functions -> pass-by.cpp

```cpp
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swap(x, y);
    cout << "After swap: x = " << x << ", y = " << y << endl;

    return 0;
}
```
- reference is a “lvalue” (something that can appear on the left hand side of an assignment operator) - discussed in more detail in the next chapter
- you can’t separate the *reference* from the *referent*. Unlike a pointer, once a reference is bound to an object, it can not be “reseated” to another object
- reference must refer to an object, not a dereferenced null pointer. The C++ language, as defined by the C++ standard, says it’s illegal, causing *undefined behaviour*:

 ```cpp
T* p = nullptr;
T& r = *p;  // illegal
```

## return with a reference
Function (which returns with a reference) call can appear on the left hand side of an assignment operator

> Example I.

## When should I use references, and when should I use pointers?
“Use references when you can, and pointers when you have to”
- Why is it often considered good advice?
    - References are simpler: References are generally easier to work with than pointers because you don't need to dereference them. References are usually preferred over pointers whenever you don’t need “reseating”.
    - References are safer: References are less error-prone than pointers because you can't create a null reference, and references always refer to valid objects
- When should you use pointers?
    - Dynamic memory allocation: If you need to allocate dynamic memory (e.g., using the new operator), you need a pointer to store the address of the allocated memory
    - Multiple indirection: If you need to refer to a variable from multiple places, you may need to use pointers
    - null values: If a variable can be null, you need to use a pointer
The exception to the above is where a function’s parameter or return value needs a “sentinel reference” — a reference that does not refer to an object. This is usually best done by returning/taking a pointer, and giving the `nullptr` value this special significance (references must always alias objects, not a dereferenced null pointer).

> Example II.

## call-by-value or call-by-reference
- If you want to change the object passed, *call by reference* or *use a pointer*; e.g., 
    - `void f(X&);` or
    - `void f(X*)`;
    - If you don’t want to change the object passed and it is *big*, call by *const reference*; e.g., `void f(const X&);`
    - Otherwise, call by value; e.g. `void f(X);`

Note also that a call of a member function is essentially **a call-by-reference on the object**, so we often use member functions when we want to modify the value/state of an object.
In the previous example we can directly access and modify the `content` member variable within the function because member functions implicitly receive a reference to the object, enabling direct modifications.