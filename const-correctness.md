# Const correctness
It means using the keyword **const** to prevent *const* objects from getting mutated.
Let's explore the different dimensions of const correctness:

## const and variables
Object or variable it is applied to cannot be modified after it is initialized. It is a keyword in C++ used to enforce **immutability**, ensuring that the value or state of the object remains constant throughout its lifetime.

> Example I.

It's important to emphasize that not only is assigning a value prohibited (for primitive types, this is the only option), but mutation is also forbidden.

## const and function parameters
If you wanted to create a function `f()` that accepted a `string`, plus you want to promise callers not to change the caller’s `string` that gets passed to `f()`, you can have `f()` receive its string parameter...

```cpp
void f1(const string& s);      // Pass by reference-to-const
void f2(const string* sptr);   // Pass by pointer-to-const
void f3(string s);             // Pass by value
```
This check is done entirely at compile-time: there is no run-time space or speed cost for the const.

As an opposite example, suppose you wanted to create a function `g()` that accepted a `string`, but you want to let callers know that `g()` might change the caller’s `string` object. In this case you can have `g()` receive its `string` parameter...

```cpp
void g1(string& s);      // Pass by reference-to-non-const
void g2(string* sptr);   // Pass by pointer-to-non-const
```
A promise made to the caller must be guaranteed even through function call chains:

```cpp
void g1(string& s);
void f1(const string& s) {
  g1(s);                // Compile-time Error since s is const
  string localCopy = s;
  g1(localCopy);        // Okay since localCopy is not const
}
```

## const and pointers
The placement of the **const** keyword in a pointer declaration has significant implications for the mutability of the *pointed-to* value and the *pointer itself*.
- `const Correctness* ptr;`: The pointed-to value (Correctness) is constant, meaning you cannot modify the data it points to through **this** pointer. **However, the pointer itself can be reassigned to point to a different location**
- `Correctness* const ptr;`: The pointer itself is constant. You cannot reassign the pointer to point to a different location. **However, you can modify the data it points to**
- `const Correctness* const ptr;`: Both the pointed-to value and the pointer are constant. **Neither can be modified**

## const and reference
```cpp
const Correctness& cConstRef = c;
```
- It means `cConstRef` aliases an `Correctness` object (`c`), but you can’t change that c object via `cConstRef`.
- `Correctness const& cConstRef` is equivalent to `const Correctness& cConstRef`
- `Correctness& const cConstRef`: nosense; redundant — references are always const, in the sense that you can never reseat a reference to make it refer to a different object - results a comiple-time error

“consistent const” or “East const” style always puts the const on the right of what it constifies:
```cpp
int const a = 42;
static double const x = 3.14;
```

## const and member function
A const member function is indicated by a **const** suffix just after the member function’s parameter list.
Member functions with a const suffix are called *“const member functions”* or *“inspectors”*.
Member functions without a const suffix are called *“non-const member functions”* or *“mutators”*.

> Example II.

## Return-by-reference and a const member function

```cpp
int const& getSecret() const {
    return secret;
}
```
The `getSecret()` function returns a constant reference to an integer. This means that the caller cannot modify the value obtained through this reference. Furthermore, the function is declared as *const*, which guarantees that the object's state will not be altered during the function's execution.

> Example III.

## Const overloading
Const overloading is when you have an inspector method and a mutator method with the same name and the same number of and types of parameters. The two distinct methods differ only in that the inspector is const and the mutator is non-const.
Previous example: Session1 -> loops -> user_defined_collection.cpp
```cpp
#include <iostream>

using namespace std;

class SimpleArray
{
public:
    SimpleArray(int size) : size(size)
    {
        data = new int[size];
    }

    ~SimpleArray()
    {
        delete[] data;
    }

    int& operator[](int index) { return data[index]; } // <- mutator
    int const& operator[](int index) const { return data[index]; } // <- inspector

    int *begin() { return data; }
    int *end() { return data + size; }

private:
    int *data;
    int size;
};

int main()
{
    SimpleArray myArray(5);
    for (int i = 0; i < 5; ++i)
    {
        myArray[i] = i;
    }

    for (int value : myArray)
    {
        cout << value << " ";
    }
}
```

## constness of member functions...
...shall be based on what the method does to the object’s *logical* state.

An object can have a
- logical (abstract or meaningwise) and a
- physical (concrete or bitwise) state.

The logical state of an object is the concept it represents. However, a *const* method can modify certain member variables without affecting the object's external behavior. This is known as modifying the object's physical state.

This is about “logical const” over “physical const.” It means the decision about whether to decorate a method with const should based primarily on whether that method leaves the logical state unchanged, irrespective of whether the method happens to make real changes to the object’s physical state.

Summary:
1. If a method changes any part of the object’s logical state, it *logically is a mutator*; it should **not** be const even if the method doesn’t change any physical bits of the object’s concrete state.
2. Conversely, a method is *logically an inspector* and should **be** const if it never changes any part of the object’s logical state, *even if the method changes physical bits of the object’s concrete state.*

For the previous purpose (logically inspector changes the physical state of an object) use
- primarily `mutable` keyword
- `const_cast` operator

Facts:
- the `mutable` keyword marks those portions of the object’s physical state which are not part of the logical state
- `const_cast` can be used with both pointers and references, and the result type is the same as the input type, except that the const qualifier is removed

> Example IV.