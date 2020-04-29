#ifndef SCOPEGUARD_PLUS_H
#define SCOPEGUARD_PLUS_H

// scopeguard_plus.h
// WTJW 11/5/2007
//
// Extends the features of Scopeguard by Alexandrescu and Lehrer to enable
// convenient automatic deallocation of objects and arrays of objects via
// the delete and delete[] operators.

#include <scopeguard.h>

// These macros exist only because I want to be able to deallocate objects
// automatically with ScopeGuard/ON_BLOCK_EXIT() and I can't figure out a way to
// take the address of operator delete or operator delete [].
template <typename T>
void call_delete(T* t) {
	delete t;
}

template <typename T>
void call_array_delete(T* t) {
	delete [] t;
//	_ftprintf(stderr, _T("Called delete [].\n"));		//DEBUG
//	::MessageBox(NULL, _T("Called delete [].\n"), NULL, MB_OK);		//DEBUG
}

template <typename T>
void (*get_deleter(T* t))(T*) {
	return &call_delete<T>;
}

template <typename T>
void (*get_array_deleter(T* t))(T*) {
	return &call_array_delete<T>;
}

#define ON_BLOCK_EXIT_DELETE(x) ON_BLOCK_EXIT(get_deleter((x)), (x));
#define ON_BLOCK_EXIT_DELETE_ARRAY(x) ON_BLOCK_EXIT(get_array_deleter((x)), (x));

#endif	// SCOPEGUARD_PLUS_H
