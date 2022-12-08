#pragma once

#include "Array.h"
#include "Method.h"
#include "Symbol.h"
#include "ConstantPool.h"

class Klass {
public:
	char pad[0x10];
	Symbol* _name;
	char pad_[0xC0];
	ConstantPool* _constant_pool;
	char pad__[0xA0];
	Array<Method*>* _methods;
};