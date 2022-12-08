#pragma once
#include <jni.h>
#include "Array.h"
#include "Symbol.h"
#include "Klass.h"

class Klass;
class ConstantPoolCache;
class ConstantPool {
public:
	char pad[8];
	Array<unsigned char>* _tags;
	ConstantPoolCache* _constantPoolCache;
	Klass* _pool_holder;

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