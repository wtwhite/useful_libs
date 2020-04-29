#ifndef MAKESTRING_H
#define MAKESTRING_H 1

// Purpose: Enable a function that takes a char const* or std:string parameter
// to be conveniently called with a string built using ostream formatting
// functions.
//
// Example usage: puts(makestring() << "sin(3) = " << sin(3) << "\n");

#include <iostream>
#include <sstream>
#include <string>

class makestring {
public:
//	makestring() { cerr << "makestring::makestring() @ " << static_cast<void *>(this) << " called.\n"; }
//	~makestring() { cerr << "makestring::~makestring() @ " << static_cast<void *>(this) << " called.\n"; }
	
	// We rely on the default ctor.
	
	// It's crucial that _s be a member variable -- if we used a local variable
	// and returned it's address, it would be destroyed before the calling code
	// could actually use the returned pointer.
	// For the same reason, we can't just return _oss.str().c_str() -- the
	// temporary returned by _oss.str() would be destroyed at the end of
	// the statement, before the calling code could use the pointer.
	operator char const*() {
		_s = _oss.str();
		return _s.c_str();
	}
	
	// Unlike for operator char const*(), we can get away with returning
	// _oss.str() directly here.
	operator std::string() {
		return _oss.str();
	}
	
	template<typename T>
	makestring& operator<<(T const& t) {
		_oss << t;
		return *this;
	}
	
#ifdef _MSC_VER
	// Seems that MSVC++ fails to match certain iostream manipulators without
	// this additional non-const-binding operator<<().
	template<typename T>
	makestring& operator<<(T& t) {
		_oss << t;
		return *this;
	}
#endif	// _MSC_VER
	
private:
	ostringstream _oss;
	std::string _s;
	
	makestring(makestring const&);				// Forbid copy construction
	makestring& operator=(makestring const&);	// Forbid assignment
};
#endif	// MAKESTRING_H
