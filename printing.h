#include <bits/stdc++.h>

template<class T, typename = void>
struct is_iterator {
    static constexpr bool value = false;
};

template<class T>
struct is_iterator<T, typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type> {
    static constexpr bool value = true;
};

template<class T>
inline constexpr bool is_iterator_v = is_iterator<T>::value;

template<bool nested = false>
void print();

template<bool nested = false, class T>
void print(const T& elem);

template<bool nested = false>
void print(const bool& elem);

template<bool nested = false>
void print(const std::string& elem);

template<bool nested = false>
void print(const char* elem);

template<bool nested = false>
void print(const char& elem);

template<bool nested = false, class T, class U>
void print(const std::pair<T, U>& p);

template<bool nested = false, class TupType, size_t... I>
void print(const TupType& _tup, std::index_sequence<I...>);

template<bool nested = false, class... T>
void print(const std::tuple<T...>& _tup);

template<bool nested, class IT>
void print_sequence(IT from_it, IT to_it, const std::string &type, const std::string& separator, const char left_edge, const char right_edge);

template<bool nested, class C>
void print_private_container(const C& container, const std::string &type, const std::string& separator, const char left_edge, const char right_edge);

template<bool nested, class C>
void print_linear_sequence(const C &container, const std::string &type);

template<bool nested = false, class T>
void print(const std::vector<T>& vec);

template<bool nested = false, class T, size_t Size>
void print(const std::array<T, Size>& arr);

template<bool nested, class C>
void print_set(const C &container, const std::string &type);

template<bool nested = false, class K, class V>
void print(const std::set<K, V>& s);

template<bool nested = false, class K, class V>
void print(const std::multiset<K, V>& ms);

template<bool nested = false, class K, class V>
void print(const std::unordered_set<K, V>& us);

template<bool nested = false, class K, class V>
void print(const std::unordered_multiset<K, V>& ums);

template<bool nested, class C>
void print_map(const C &container, const std::string &type);

template<bool nested = false, class K, class V>
void print(const std::map<K, V>& m);

template<bool nested = false, class K, class V>
void print(const std::multimap<K, V>& mm);

template<bool nested = false, class K, class V>
void print(const std::unordered_map<K, V>& um);

template<bool nested = false, class K, class V>
void print(const std::unordered_multimap<K, V>& umm);

template<bool nested, class C>
void print_list(const C &container, const std::string &type, const std::string& separator);

template<bool nested = false, class T>
void print(const std::list<T>& l);

template<bool nested = false, class T>
void print(const std::forward_list<T>& fl);

template<bool nested = false, class T>
void print(const std::stack<T>& st);

template<bool nested = false, class T>
void print(const std::queue<T>& st);

template<bool nested = false, class T>
void print(const std::deque<T>& st);

template<bool nested = false, class T>
void print(const std::priority_queue<T>& st);

template<bool nested>
void print() {
    if constexpr (!nested) {
        std::cout << std::endl;
    }
}

template<bool nested, class T>
void print(const T& elem) {
    if constexpr (is_iterator_v<T>) {
        std::cout << "IT(";
        print(*elem);
        std::cout << ")";
    } else {
        std::cout << elem;
    }
    print<nested>();
}

template<bool nested>
void print(const bool& elem) {
    std::cout << (elem ? "true" : "false");
    print<nested>();
}

template<bool nested>
void print(const std::string& elem) {
    std::cout << '"' << elem << '"';
    print<nested>();
}

template<bool nested>
void print(const char* elem) {
    std::cout << '"' << elem << '"';
    print<nested>();
}

template<bool nested >
void print(const char& elem) {
    std::cout << '\'' << elem << '\'';
    print<nested>();
}

template<bool nested, class T, class U>
void print(const std::pair<T, U>& p) {
    std::cout << "P(";
    print<true>(p.first);
    std::cout << ", ";
    print<true>(p.second);
    std::cout << ")";
}

template<bool nested, class TupType, size_t... I>
void print(const TupType& _tup, std::index_sequence<I...>){
    std::cout << "T(";
    (..., (std::cout << (I == 0? "" : ", ") << std::get<I>(_tup)));
    std::cout << ")";
}

template<bool nested, class... T>
void print(const std::tuple<T...>& _tup){
    print(_tup, std::make_index_sequence<sizeof...(T)>());
}

template<bool nested, class IT>
void print_sequence(IT from_it, IT to_it, const std::string &type, const std::string& separator, const char left_edge, const char right_edge) {
    using T = typename std::decay<decltype(*from_it)>::type;
    if constexpr (std::is_fundamental_v<T> || nested) {
        std::cout << type << left_edge;
        if (from_it != to_it) {
            print<true>(*from_it);
            for(auto it = next(from_it); it != to_it; ++it) {
                std::cout << ", ";
                const auto& elem = *it;
                print<true>(elem);
            }
        }
        std::cout << right_edge;
        if constexpr (!nested) {
            std::cout << std::endl;
        }
    } else {
        std::cout << type << left_edge << std::endl;
        for(auto it = from_it; it != to_it; ++it) {
            std::cout << "  ";
            const auto& elem = *it;
            print<true>(elem);
            std::cout << std::endl;
        }
        std::cout << right_edge << std::endl;
    }
}

template<bool nested, class C>
void print_private_container(const C& container, const std::string &type, const std::string& separator, const char left_edge, const char right_edge) {
    struct Printer : C
    {
        void print_content(const std::string &type, const std::string& separator, const char left_edge, const char right_edge) const {
            print_sequence<nested>(this->c.begin(), this->c.end(), type, separator, left_edge, right_edge);
        }
    };

    static_cast<Printer const&>(container).print_content(type, separator, left_edge, right_edge);
}

template<bool nested, class C>
void print_linear_sequence(const C &container, const std::string &type) {
    using T = typename C::value_type;
    if constexpr (std::is_fundamental_v<T> || nested) {
        std::cout << type << "[";
        if (!container.empty()) {
            print<true>(*container.begin());
            for(auto it = next(container.begin()); it != container.end(); ++it) {
                std::cout << ", ";
                const auto& elem = *it;
                print<true>(elem);
            }
        }
        std::cout << "]";
        if constexpr (!nested) {
            std::cout << std::endl;
        }
    } else {
        std::cout << type << "[" << std::endl;
        for(const T& elem : container) {
            std::cout << "  ";
            print<true>(elem);
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl;
    }
}

template<bool nested, class T>
void print(const std::vector<T>& vec) {
    print_linear_sequence<nested>(vec, "V");
}

template<bool nested, class T, size_t Size>
void print(const std::array<T, Size>& arr) {
    print_linear_sequence<nested>(arr, "A");
}

template<bool nested, class C>
void print_set(const C &container, const std::string &type) {
    print_sequence<nested>(container.begin(), container.end(), type, ",", '{', '}');
}

template<bool nested, class K, class V>
void print(const std::set<K, V>& s) {
    print_set<nested>(s, "S");
}

template<bool nested, class K, class V>
void print(const std::multiset<K, V>& ms) {
    print_set<nested>(ms, "MS");
}

template<bool nested, class K, class V>
void print(const std::unordered_set<K, V>& us) {
    print_set<nested>(us, "US");
}

template<bool nested, class K, class V>
void print(const std::unordered_multiset<K, V>& ums) {
    print_set<nested>(ums, "UMS");
}

template<bool nested, class C>
void print_map(const C &container, const std::string &type) {
    if constexpr (nested) {
        std::cout << type << "{";
        if (!container.empty()) {
            print<true>(container.begin()->first);
            std::cout << " -> ";
            print<true>(container.begin()->second);
            for(auto it = next(container.begin()); it != container.end(); ++it) {
                const auto& [key, value] = *it;
                std::cout << ", ";
                print<true>(key);
                std::cout << " -> ";
                print<true>(value);
            }
        }
        std::cout << "}";
    } else {
        std::cout << type << "{" << std::endl;
        for(const auto& [key, value] : container) {
            std::cout << "  ";
            print<true>(key);
            std::cout << " -> ";
            print<true>(value);
            std::cout << std::endl;
        }
        std::cout << "}" << std::endl;
    }
}

template<bool nested, class K, class V>
void print(const std::map<K, V>& m) {
    print_map<nested>(m, "M");
}

template<bool nested, class K, class V>
void print(const std::multimap<K, V>& mm) {
    print_map<nested>(mm, "MM");
}

template<bool nested, class K, class V>
void print(const std::unordered_map<K, V>& um) {
    print_map<nested>(um, "U");
}

template<bool nested, class K, class V>
void print(const std::unordered_multimap<K, V>& umm) {
    print_map<nested>(umm, "UM");
}

template<bool nested, class C>
void print_list(const C &container, const std::string &type, const std::string& separator) {
    using T = typename C::value_type;
    if constexpr (std::is_fundamental_v<T> || nested) {
        std::cout << type << "<";
        if (!container.empty()) {
            std::cout << "(";
            print<true>(*container.begin());
            std::cout << ")";
            for(auto it = next(container.begin()); it != container.end(); ++it) {
                const auto& value = *it;
                std::cout << " " << separator <<" (";
                print<true>(value);
                std::cout << ")";
            }
        }
        std::cout << ">";
        if constexpr (!nested) {
            std::cout << std::endl;
        }
    } else {
        std::cout << type << "<" << std::endl;
        for(const T& elem : container) {
            std::cout << "  (";
            print<true>(elem);
            std::cout << ")" << std::endl;
        }
        std::cout << ">" << std::endl;
    }
}

template<bool nested , class T>
void print(const std::list<T>& l) {
    print_list<nested>(l, "DL", "<->");
}

template<bool nested, class T>
void print(const std::forward_list<T>& fl) {
    print_list<nested>(fl, "SL", "->");
}

template<bool nested, class T>
void print(const std::stack<T>& st) {
    print_private_container<nested>(st, "ST", ",", '[', ']');
}

template<bool nested, class T>
void print(const std::queue<T>& q) {
    print_private_container<nested>(q, "Q", ",", '[', ']');
}

template<bool nested, class T>
void print(const std::deque<T>& dq) {
    print_sequence<nested>(dq.begin(), dq.end(), "DQ", ",", '[', ']');
}

template<bool nested, class T>
void print(const std::priority_queue<T>& pq) {
    print_private_container<nested>(pq, "PQ", ",", '[', ']');
}

constexpr int paren_count(const char* cstr) {
    int iter = 0;
    int parens = 0;
    while(cstr[iter] != '\0') {
        if (cstr[iter] == '{') {
            if (cstr[iter+1] != '}') {
                return -1;
            }
            parens++;
            iter++;
        }
        iter++;
    }
    return parens;
}

#define printx(cstr, ...) {static_assert(paren_count(cstr) == std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value); _printx(cstr, 0, __VA_ARGS__ );}

template<class T, class... Ts>
void _printx(const char* cstr, int idx, const T& elem, const Ts&... ts) {
    while(cstr[idx] != '\0') {
        if (cstr[idx] == '{') {
            print<true>(elem);
            idx += 2;
            if constexpr (sizeof...(Ts) > 0) {
                _printx(cstr, idx, ts...);
                return;
            }
        } else {
            std::cout << cstr[idx];
            idx++;
        }
    }
    std::cout << std::endl;
}
