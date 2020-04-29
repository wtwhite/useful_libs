#ifndef SEQUENCE_LISTER_H
#define SEQUENCE_LISTER_H

#include <iostream>
#include <string>
#include <iterator>

// WTJW 29/4/2006: Move definition of operator<<() template function before
// sequence_lister template class declaration to satisfy the version of g++
// that TopCoder uses.  This now works across all versions of g++ that I use
// as well as MSVC++7.1.  Also needed to add a forward reference.
// WTJW 7/4/2006: We should not be altering the current namespace inside a
// header file!  Also added repeat-inclusion detection.
//using namespace std;

template<typename X> class sequence_lister;		// Forward reference

//template<typename InIter>
//inline std::ostream& operator<<(std::ostream& os, sequence_lister<InIter> const& sl);

template<typename InIter>
inline std::ostream& operator<<(std::ostream& os, sequence_lister<InIter> const& sl) {
//	copy(sl._first, sl._last, ostream_iterator<typename InIter::value_type>(os, sl._delim));
	for (InIter i = sl._first; i != sl._last; ++i) {
		if (i != sl._first) {
			os << sl._delim;
		}
		
		os << *i;
	}
	
	return os;
}

template<typename InIter>
class sequence_lister {
public:
	sequence_lister(InIter first, InIter last, char* delim = "") :
		_first(first),
		_last(last),
		_delim(delim)
	{}
	
	// Also allow construction from any container supporting begin() and end()
	template<typename Cont>
	sequence_lister(Cont& cont, char* delim = "") :
		_first(cont.begin()),
		_last(cont.end()),
		_delim(delim)
	{}
	
	sequence_lister(sequence_lister const& x) :
		_first(x._first),
		_last(x._last),
		_delim(x._delim)
	{}
	
	sequence_lister& operator=(sequence_lister const& x) {
		_first = x._first;
		_last = x._last;
		_delim = x._delim;
	}
	
	// WTJW 10/12/2008: It seems the new MSVC++9 emits an extraneous warning C4396 complaining
	// that "inline" cannot be used at the same time as "friend" in the declaration below, even though
	// we don't use "inline" there.  While this can be silenced by giving a forward decl of the
	// templated operator<<() and defining it after this class, there's not much point as according
	// to http://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=321690
	// it seems like this warning is just a (minor) compiler bug.
#if _MSC_VER == 1500
#pragma warning(push)
#pragma warning(disable : 4396)
#endif	// _MSC_VER == 1500
	friend std::ostream& operator<< <>(std::ostream& os, sequence_lister<InIter> const& sl);
#if _MSC_VER == 1500
#pragma warning(pop)
#endif	// _MSC_VER == 1500
	
private:
	InIter _first, _last;
	char* _delim;
};

template<typename InIter>
inline sequence_lister<InIter> list_sequence(InIter first, InIter last, char* delim = "") {
	return sequence_lister<InIter>(first, last, delim);
}

// WTJW 17/6/2006: Changed "iterator" to "const_iterator" to enable const containers
// to be used (these do not have an iterator datatype available, only const_iterator).
template<typename Cont>
inline sequence_lister<typename Cont::const_iterator> list_sequence(Cont& cont, char* delim = "") {
	return sequence_lister<typename Cont::const_iterator>(cont, delim);
}
#endif	// SEQUENCE_LISTER_H
