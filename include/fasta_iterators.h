#ifndef FASTA_ITERATORS_H
#define FASTA_ITERATORS_H

/* fasta_iterators.h
 * =================
 * Created by: WTJW
 * Created on: 6/04/2006
 */

#include <iterator>
#include <iostream>
#include <string>
#include <utility>

typedef std::pair<std::string, std::string> NamedSeq;

class FastaInputIterator {
public:
	typedef std::input_iterator_tag iterator_category;
	typedef NamedSeq value_type;
	typedef std::ptrdiff_t difference_type;
	typedef NamedSeq* pointer;
	typedef NamedSeq& reference;
	
	FastaInputIterator() : _pIs(0) {}		// Default-construction creates end-of-sequence iterator.
	explicit FastaInputIterator(std::istream& is) : _pIs(&is), _loaded(false) { getline(*_pIs, _buf); if (!*_pIs) { _pIs = 0; } }
	FastaInputIterator(FastaInputIterator const& x) : _pIs(x._pIs), _loaded(x._loaded), _buf(x._buf), _curSeq(x._curSeq) {}		// NOTE: copying does not create an independent iterator!
	FastaInputIterator& operator=(FastaInputIterator const& x) { _pIs = x._pIs; _loaded = x._loaded; _buf = x._buf; _curSeq = x._curSeq; }		// NOTE: copying does not create an independent iterator!
	
	NamedSeq operator*() {
		_ensureLoaded();
		return _curSeq;
	}
	
	FastaInputIterator& operator++() {
		_ensureLoaded();
		_loaded = false;
		if (!*_pIs) {
			_pIs = 0;
		}
		return *this;
	}
	
	FastaInputIterator operator++(int dummy) {
		FastaInputIterator temp(*this);
		++*this;
		return temp;
	}
	
	// NOTE: only returns true if both iterators are at end-of-sequence.
	bool operator==(FastaInputIterator const& x) const {
		return _pIs == 0 && x._pIs == 0;
	}
	
	bool operator!=(FastaInputIterator const& x) const {
		return !(*this == x);
	}
	
private:
	void _ensureLoaded() {
		if (!_loaded) {
			// Read next FASTA name and sequence
			_trimCr(_buf);
			_curSeq.first = _buf.substr(1);		// First char should be '>', rest should be name.
			_curSeq.second = "";
			while (getline(*_pIs, _buf)) {
				if (_buf.size() && _buf[0] == '>') {
					break;
				} else {
					_trimCr(_buf);
					_curSeq.second += _buf;
				}
			}
			
			_loaded = true;
		}
	}
	
	// Handle Windows-formatted text lines CRLF on Unix, or in binary mode on
	// Windows.  Define FASTA_NOTRIMCR to avoid doing this.
#if defined(FASTA_NOTRIMCR)
	void _trimCr(std::string& s) {
		// Do nothing
	}
#else	// not defined(FASTA_NOTRIMCR)
	void _trimCr(std::string& s) {
		if (s.size() && s[s.size() - 1] == '\r') {
			s.erase(s.size() - 1);
		}
	}
#endif	// not defined(FASTA_NOTRIMCR)
	
	std::istream* _pIs;			// Points to istream to read from, or 0 to indicate end-of-sequence iterator.
	std::string _buf;			// Contains next line of text.
	NamedSeq _curSeq;			// Valid iff _loaded == true.
	bool _loaded;				// true if operator*() has been called to populate _curSeq since last pointer movement.
};

class FastaOutputIterator {
public:
	typedef std::output_iterator_tag iterator_category;
	typedef NamedSeq value_type;
//	typedef std::ptrdiff_t difference_type;
//	typedef NamedSeq* pointer;
//	typedef NamedSeq& reference;
	
	static const int FASTAWIDTH = 60;
	
	FastaOutputIterator() : _theProxy(0) {}		// Default-construction creates an invalid iterator.  There is no "end-of-sequence iterator" for output iterators.
	explicit FastaOutputIterator(std::ostream& os) : _theProxy(&os) {}
	FastaOutputIterator(FastaOutputIterator const& x) : _theProxy(x._theProxy._pOs) {}		// NOTE: copying does not create an independent iterator!
	FastaOutputIterator& operator=(FastaOutputIterator const& x) { _theProxy._pOs = x._theProxy._pOs; }		// NOTE: copying does not create an independent iterator!
	
private:
	class NamedSeqProxy {
		friend class FastaOutputIterator;
		
	public:
		NamedSeqProxy(std::ostream* pOs) : _pOs(pOs) {}
		void operator=(NamedSeq const& x) {
			_write(x);
		}
		
	private:
		void _write(NamedSeq const& x) {
			*_pOs << '>' << x.first << '\n';
			
			int i = 0;
			for (; i < x.second.size(); i += FASTAWIDTH) {
				*_pOs << x.second.substr(i, FASTAWIDTH) << '\n';		// When the 2nd arg to substr() would go past the end of the string, it stops at the end.
			}
		}
		
		std::ostream* _pOs;
	};
	
public:
	NamedSeqProxy& operator*() {
		return _theProxy;
	}
	
	FastaOutputIterator& operator++() {
		return *this;				// Do nothing
	}
	
	FastaOutputIterator& operator++(int dummy) {
		return *this;				// Do nothing
	}
	
	// NOTE: always returns false.
	bool operator==(FastaOutputIterator const& x) const {
		return false;
	}
	
	bool operator!=(FastaOutputIterator const& x) const {
		return true;
	}
	
private:
	NamedSeqProxy _theProxy;		// The object returned by dereferencing.
};
#endif	// FASTA_ITERATORS_H
