#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/* string_utils.h
 * ==============
 * Created by: WTJW
 * Created on: 23/05/2007
 */

#include <string>
#include <algorithm>
#include <cctype>
#include <cwctype>

namespace string_utils {

namespace {
	template <typename C, typename T = std::char_traits<C> >
	struct caseconverter {};
	
	// Partial specialisation for char types.
	template <typename T>
	struct caseconverter<char, T> {
		static inline int toupper(int c) {
			return std::toupper(c);
		}
		
		static inline int tolower(int c) {
			return std::tolower(c);
		}
	};
	
	// Partial specialisation for wchar_t types.
	template <typename T>
	struct caseconverter<wchar_t, T> {
		static inline int toupper(int c) {
			return std::towupper(c);
		}
		
		static inline int tolower(int c) {
			return std::towlower(c);
		}
	};
	
	//HACK: experimental.  I want to make a template function,
	// stringify_as_necessary(), which can take a single argument of type either
	// basic_string<C, T, A> const& or C const*, and produce a return value of
	// type basic_string<C, T, A> const&.  This should be enabled for these two
	// types only.
	// The trick is realising that the conversion of a C const* to a basic_string
	// depends on the type of the **other** parameter: if the other parameter is a
	// basic_string<C, X, Y>, then convert the C const* to a basic_string<C, X, Y>,
	// otherwise if both parameters C const*, use the default
	// (basic_string<C, char_traits<C>, allocator<C> >) for both.
	
	//HACK: it would be nice to somehow make this type visible only within this
	// header file; unfortunately it seems that issuing "using namespace string_utils;"
	// in the source file also drags in stuff in nested unnamed namespaces...
	template <typename X, typename Y>
	struct ERROR;		// Deliberately deeclared but not defined
	
	// This template catches all calls to stringify_as_necessary() with
	// erroneously typed parameters.  Note that we want the compiler to error
	// out on the more informative "incomplete type for ERROR_invalid_types_passed_to_string_function"
	// rather than because of template parameter matching problems, therefore
	// the return type must be valid.
	template <typename X, typename Y>
	inline std::basic_string<char> stringify_as_necessary(X s1, Y s2) {
		ERROR<X, Y> ERROR_invalid_types_passed_to_string_function;		// We want compiler errors when the template is instantiated not when it is defined, so must use a dependent type
	}
	
	// If both parameters are of basic_string<C, T, A> type, no conversion is done.
	template <typename C, typename T, typename A>
	inline std::basic_string<C, T, A> const& stringify_as_necessary(std::basic_string<C, T, A> const& s1, std::basic_string<C, T, A> const& s2) {
		return s1;
	}
	
	// If one parameter is of type basic_string<C, T, A> type and the other is of
	// type C const*, convert the pointer to type basic_string<C, T, A>.
	
	// 1.  The first parameter is already the right type, so just return it as is.
	template <typename C, typename T, typename A>
	inline std::basic_string<C, T, A> const& stringify_as_necessary(std::basic_string<C, T, A> const& s1, C const* s2) {
		return s1;
	}
	
	// 2.  The first parameter is of pointer type, so create a temporary of the correct type.
	template <typename C, typename T, typename A>
	inline std::basic_string<C, T, A> stringify_as_necessary(C const* s1, std::basic_string<C, T, A> const& s2) {
		return std::basic_string<C, T, A>(s1);
	}
	
	// If both parameters are of C const* type, convert the first parameter to the
	// "default" type of basic_string (which is defined by the standard to be
	// basic_string<C, char_traits<C>, allocator<C> >).
	template <typename C>
	inline std::basic_string<C> stringify_as_necessary(C const* s1, C const* s2) {
		return std::basic_string<C>(s1);
	}
}

// Modifies the string in-place.
//HACK: should probably use locales somehow.
template <typename C, typename T, typename A>
inline void toupper(std::basic_string<C, T, A>& s) {
	std::transform(s.begin(), s.end(), s.begin(), &caseconverter<C, T>::toupper);
}

// Modifies the string in-place.
//HACK: should probably use locales somehow.
template <typename C, typename T, typename A>
inline void tolower(std::basic_string<C, T, A>& s) {
	std::transform(s.begin(), s.end(), s.begin(), &caseconverter<C, T>::tolower);
}

// Returns a negative value if s1 is lexiocographically less than s2, a
// positive value if s2 is lexicographically greater than s2, or 0 if they
// are equal, all without respect to case.
template <typename C, typename T, typename A>
inline int compare_case_insensitive(std::basic_string<C, T, A> const& s1, std::basic_string<C, T, A> const& s2) {
	std::basic_string<C, T, A> temp1(s1);
	std::basic_string<C, T, A> temp2(s2);
	toupper(temp1);
	toupper(temp2);
	return temp1.compare(temp2);
}

template <typename X, typename Y>
inline int compare_case_insensitive(X s1, Y s2) {
	return compare_case_insensitive(stringify_as_necessary(s1, s2), stringify_as_necessary(s2, s1));
}

// Returns true if s1 and s2 are equal, without respect to case.
template <typename C, typename T, typename A>
inline bool is_equal_case_insensitive(std::basic_string<C, T, A> const& s1, std::basic_string<C, T, A> const& s2) {
	return compare_case_insensitive(s1, s2) == 0;
}

template <typename X, typename Y>
inline bool is_equal_case_insensitive(X s1, Y s2) {
	return is_equal_case_insensitive(stringify_as_necessary(s1, s2), stringify_as_necessary(s2, s1));
}

// Returns true iff s1 starts with s2.
template <typename C, typename T, typename A>
inline bool starts_with(std::basic_string<C, T, A> const& s1, std::basic_string<C, T, A> const& s2) {
	return s1.substr(0, s2.size()) == s2;
}

template <typename X, typename Y>
inline bool starts_with(X s1, Y s2) {
	return starts_with(stringify_as_necessary(s1, s2), stringify_as_necessary(s2, s1));
}

// Returns true iff s1 ends with s2.
template <typename C, typename T, typename A>
inline bool ends_with(std::basic_string<C, T, A> const& s1, std::basic_string<C, T, A> const& s2) {
	return s1.size() >= s2.size() && s1.substr(s1.size() - s2.size(), s2.size()) == s2;
}

template <typename X, typename Y>
inline bool ends_with(X s1, Y s2) {
	return ends_with(stringify_as_necessary(s1, s2), stringify_as_necessary(s2, s1));
}

// This version works with full strings.  The string to find and the string to
// replace it with may be different lengths; if no replacement string is given,
// the default is to replace the first occurrence with the empty string
// (effectively deleting it).
template <typename C, typename T, typename A>
inline bool replace_first(std::basic_string<C, T, A>& s, std::basic_string<C, T, A> const& to_find, std::basic_string<C, T, A> const& replace_with = std::basic_string<C, T, A>()) {
	typename std::basic_string<C, T, A>::size_type pos = s.find(to_find);
	if (pos != std::basic_string<C, T, A>::npos) {
		s.replace(pos, to_find.size(), replace_with);
		return true;
	} else {
		return false;
	}
}

// See the definition of replace_all() below for an explanation of why I don't
// just use one template with a default function argument.
template <typename C, typename T, typename A, typename X, typename Y>
inline bool replace_first(std::basic_string<C, T, A>& s, X to_find, Y replace_with) {
	return replace_first(s, stringify_as_necessary(to_find, s), stringify_as_necessary(replace_with, s));
}

template <typename C, typename T, typename A, typename X>
inline bool replace_first(std::basic_string<C, T, A>& s, X to_find) {
	return replace_first(s, stringify_as_necessary(to_find, s), std::basic_string<C, T, A>());
}

// This version works with single characters.  Note that it cannot delete the
// character!  If you want to do that, you can use remove_if() from the
// <algorithm> header, followed by erase() (remove_if() does not resize the
// string).
template <typename C, typename T, typename A>
inline bool replace_first(std::basic_string<C, T, A>& s, C to_find, C replace_with) {
	typename std::basic_string<C, T, A>::size_type pos = s.find(to_find);
	if (pos != std::basic_string<C, T, A>::npos) {
		s[pos] = replace_with;
		return true;
	} else {
		return false;
	}
}

// This version works with full strings.  The string to find and the string to
// replace it with may be different lengths; if no replacement string is given,
// the default is to replace all occurrences with the empty string (effectively
// deleting all occurrences of the to_find string).  Note that replacements
// are never made within a just-replaced piece of the string (otherwise e.g.
// replace_all(s, "X", "XX") would result in infinite loops).
template <typename C, typename T, typename A>
inline typename std::basic_string<C, T, A>::size_type replace_all(std::basic_string<C, T, A>& s, std::basic_string<C, T, A> const& to_find, std::basic_string<C, T, A> const& replace_with = std::basic_string<C, T, A>()) {
	typename std::basic_string<C, T, A>::size_type pos = 0;
	typename std::basic_string<C, T, A>::size_type count = 0;
	while ((pos = s.find(to_find, pos)) != std::basic_string<C, T, A>::npos) {
		s.replace(pos, to_find.size(), replace_with);
		pos += replace_with.size();
		++count;
	}
	
	return count;
}

// It seems that we should be able to deal with the default argument using
// just one template as given in the comments below, however neither g++ 4.1.2
// nor MSVC++8 are able to deduce the type of Y from the default argument.
//template <typename C, typename T, typename A, typename X, typename Y>
//inline typename std::basic_string<C, T, A>::size_type replace_all(std::basic_string<C, T, A>& s, X to_find, Y replace_with = std::basic_string<C, T, A>()) {
//	return replace_all(s, stringify_as_necessary(to_find, s), stringify_as_necessary(replace_with, s));
//}
template <typename C, typename T, typename A, typename X>
inline typename std::basic_string<C, T, A>::size_type replace_all(std::basic_string<C, T, A>& s, X to_find) {
	return replace_all(s, stringify_as_necessary(to_find, s), std::basic_string<C, T, A>());
}

template <typename C, typename T, typename A, typename X, typename Y>
inline typename std::basic_string<C, T, A>::size_type replace_all(std::basic_string<C, T, A>& s, X to_find, Y replace_with) {
	return replace_all(s, stringify_as_necessary(to_find, s), stringify_as_necessary(replace_with, s));
}

// This version works with single characters.  Note that it cannot delete the
// character!  If you want to do that, you can use remove_if() from the
// <algorithm> header, followed by erase() (remove_if() does not resize the
// string).  This basically duplicates <algorithm>'s replace_if() template
// function, except that it provides a count of the number of replacements.
template <typename C, typename T, typename A>
inline typename std::basic_string<C, T, A>::size_type replace_all(std::basic_string<C, T, A>& s, C to_find, C replace_with) {
	typename std::basic_string<C, T, A>::size_type pos = 0;
	typename std::basic_string<C, T, A>::size_type count = 0;
	while ((pos = s.find(to_find, pos)) != std::basic_string<C, T, A>::npos) {
		s[pos] = replace_with;
		++pos;
		++count;
	}
	
	return count;
}

}	// Ends namespace string_utils

#endif	// STRING_UTILS_H
