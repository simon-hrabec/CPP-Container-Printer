#include <bits/stdc++.h>

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

template<bool nested = false, class T>
void print(const std::vector<T>& vec);

template<bool nested = false, class T, size_t Size>
void print(const std::array<T, Size>& arr);

template <bool nested, class C>
void print_linear_sequence(const C &container, const std::string &type);

template<bool nested = false, class K, class V>
void print(const std::map<K, V>& m);

template<bool nested = false, class K, class V>
void print(const std::unordered_map<K, V>& um);

template<bool nested, class C>
void print_map(const C &container, const std::string &type);

template<bool nested = false, class T>
void print(const std::list<T>& l);

template<bool nested = false, class T>
void print(const std::forward_list<T>& fl);

template<bool nested, class C>
void print_list(const C &container, const std::string &type, const std::string& separator);

template<bool nested>
void print() {
	if constexpr (!nested) {
		std::cout << std::endl;
	}
}

template<bool nested, class T>
void print(const T& elem) {
	std::cout << elem;
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

template<bool nested, class T>
void print(const std::vector<T>& vec) {
	print_linear_sequence<nested>(vec, "V");
}

template<bool nested, class T, size_t Size>
void print(const std::array<T, Size>& arr) {
	print_linear_sequence<nested>(arr, "A");
}

template <bool nested, class C>
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

template<bool nested, class K, class V>
void print(const std::map<K, V>& m) {
	print_map<nested>(m, "M");
}

template<bool nested, class K, class V>
void print(const std::unordered_map<K, V>& um) {
	print_map<nested>(um, "U");
}

template<bool nested, class C>
void print_map(const C &container, const std::string &type) {
	if constexpr (nested) {
		std::cout << type << "{";
		if (!container.empty()) {
			print<true>(container.begin()->first);
			std::cout << " -> ";
			print<true>(container.begin()->second);
		}
		for(auto it = next(container.begin()); it != container.end(); ++it) {
			const auto& [key, value] = *it;
			std::cout << ", ";
			print<true>(key);
			std::cout << " -> ";
			print<true>(value);
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

template<bool nested , class T>
void print(const std::list<T>& l) {
	print_list<nested>(l, "DL", "<->");
}

template<bool nested, class T>
void print(const std::forward_list<T>& fl) {
	print_list<nested>(fl, "SL", "->");
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
		}
		for(auto it = next(container.begin()); it != container.end(); ++it) {
			const auto& value = *it;
			std::cout << " " << separator <<" (";
			print<true>(value);
			std::cout << ")";
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
