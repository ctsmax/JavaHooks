#pragma once
#include <jni.h>
#include "Array.h"
#include "Symbol.h"
#include "Klass.h"

class Klass;
class ConstantPoolCache;
class Monitor;
class ConstantPool {
public:
	char pad[8];
	Array<unsigned char>* _tags;
	ConstantPoolCache* _constantPoolCache;
	Klass* _pool_holder;
	Array<unsigned short>*           _operands;    // for variable-sized (InvokeDynamic) nodes, usually empty
	
	// Array of resolved objects from the constant pool and map from resolved
	// object index to original constant pool index
	jobject              _resolved_references;
	Array<unsigned short>*           _reference_map;

	enum {
		_has_preresolution = 1,           // Flags
	    	_on_stack          = 2
	};

	int                  _flags;  // old fashioned bit twiddling
	int                  _length; // number of elements in the array

	union {
		// set for CDS to restore resolved references
		int                _resolved_reference_length;
		// keeps version number for redefined classes (used in backtrace)
		int                _version;
	} _saved;

	Monitor*             _lock;

	intptr_t* base() const {
		return (intptr_t*)(((char*)this) + sizeof(ConstantPool));
	}

	Symbol** symbol_at_addr(int idx) const {
		return (Symbol**)&base()[idx];
	}

	Symbol* symbol_at(int idx) const {
		return *symbol_at_addr(idx);
	}
};
