# C++ container printer - CPPCP
Printing in C++ with IOstream is quite cumbersome and inconvenient. C++ also does not have a default output for containers (only available with `std::print` in C++23). Printing nested containers is even more difficult. This library provides a simple solution for fast debug printing (with competitive programming in mind).

## About
CPPCP is a header file providing 2 (overloaded/templatized) functions

 - `print` - Prints and formats a (nested) container (or a basic type)
 - `printx` - Formats a string, replacing `{}` with formatted values

The `print` function relies on having a special overload for any special type. Hence it can be simply extended by providing overload for an additional type (custom struct/class) or for a specific pair/tuple.

## Supported types
All basic types that std::ostream can print are supported, some are printed a bit differently. `bool` is printed as `true`/`false`, `std::string`/`const char*` is printed with quotes. Arbitrary `std::pair` and `std::tuple` are also supported.

**Containers**
All the [basic containers from STL]([url](https://en.cppreference.com/w/cpp/container)) are included. More specifically:
`std::array`, `std::vector`, `std::stack`, `std::queue`, `std::deque`, `std::list`, `std::forward_list`, `std::map`, `std::unordered_map`, `std::set`, `std::unordered_set`, `std::multimap`, `std::unordered_multimap`, `std::multiset`, `std::unordered_multiset`, `std::priority_queue`.

## Future TODO

 - Add support for the remaining containers/adaptors/views: `std::span`, `std::flat_map`, `std::flat_set`, `std::flat_multimap`, `std::flat_multiset`, `std::mdspan` (more are C++23 only).
 - Add support for printing all possible iterators.
 - Make an optional way to print `std::vector`/`std::array` with indices
 - Make `printx` work without any interpolated value
 - Add support for C style arrays

## Example usage
**Array of Tuples:**

    std::vector<std::tuple<int,bool,std::string>> tuple_arr({{17, false, "First"}, {-5, true, "Second"}});
    printx("Content: {}", tuple_arr);
    
Will print:

    Content: V[T(17, false, "First"), T(-5, true, "Second")]

**2D array:**

    vector<vector<int>> array2d({{1, 5, 7, 2, 6}, {0}, {3, 1, 4}});
    print(array2d);

Will print:

    V[
      V[1, 5, 7, 2, 6]
      V[0]
      V[3, 1, 4]
    ]

**Map with list**

    std::map<std::pair<int, int>, std::list<std::string>> tasks({{{5, 4}, {"Cleaning", "Dinner"}}, {{7, 2}, {"Hiking"}}});
    print(tasks);

Will print:

    M{
      P(5, 4) -> DL<("Cleaning") <-> ("Dinner")>
      P(7, 2) -> DL<("Hiking")>
    }
