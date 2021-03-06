# generic_optional&lt;T&gt;

Compile-time wrapper over `std::optional<T>` that enables optional reference types.

### How it works

For non-reference types:
- `generic_optional<int>` &rarr; (deduces to) &rarr; `optional<int>`

For reference types:
- `generic_optional<const int&>` &rarr;  (deduces to) &rarr; `optional<reference_wrapper<const int>>`

### Usage

Use `generic_optional<T>` instead of `optional<T>` in the declaration.

### Example

```cpp
generic_optional<int> number;
generic_optional<const int&> number_cref;
int test_value = 33;

number = test_value;
number_cref = test_value;

test_value = 111;
    
assert(number == 33);
assert(number_cref == 111);
```
