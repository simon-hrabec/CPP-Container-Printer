# C++ container printer - CPPCP
Printing in C++ with IOstream is quite cumbersome and inconvenient. C++ also does not have a default output for containers. Printing nested containers is even more difficult. This library provides a simple solution for fast debug printing (with competitive programming in mind).

## About
CPPCP is a header file providing 2 (overloaded/templatized) functions

 - `print` - Prints and formats a (nested) container (or a basic type)
 - `printx` - Formats a string, replacing `{}` with formatted values

The `print` function relies on having a special overload for any special type. Hence it can be simply extended by providing overload for an additional type (custom struct/class) or for a specific pair/tuple.

## Supported types
All basic types that std::ostream can print are supported, some are printed a bit differently. `bool` is printed as `true`/`false`, `sdt::string`/`const char*` is printed with quotes. Arbitrary `std::pair` and `std::tuple` are also supported.

**Containers**
Only some containers are currently supported. More specifically:
`std::array`, `std::vector`, `std::list`, `std::forward_list`, `std::map`, `std::unordered_map`, `std::set`, `std::unordered_set`

## Future TODO

 - Add support for other containers: `std::multimap`, `std::unordered_multimap`, `std::multiset`, `std::unordered_multiset`, `std::priority_queue` (vector based).
 - Add support for containers that require performing a copy of the container to print it: `std::stack`, `std::queue`, `std::deque`
 - Add support for printing all possible iterators.
 - Make an optional way to print `std::vector`/`std::array` with indices
 - Make `printx` work without any interpolated value

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
