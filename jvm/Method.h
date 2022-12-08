#pragma once
#include <stdint.h>
#include "Array.h"
#include "ConstantPool.h"

class ConstMethod {
public:
	unsigned long _fingerprint;
	ConstantPool* _constants;
	Array<unsigned char>* _stackmap_data;
	int _constMethod_size;
	unsigned short _flags;
	unsigned char _result_type;
	unsigned short _name_index;
	unsigned short _signature_index;
};

class Method
{
public:
	char pad_0000[0x8]; //0x0000
	ConstMethod* _constMethod; //0x0008
	char pad_0010[0x10]; //0x0010
	uint32_t _flags; //0x0020
	char pad_0024[0xC]; //0x0024
	unsigned char* _i2i_entry; //0x0030
	char pad_0038[0x8]; //0x0038
	unsigned char* _from_compiled_entry; //0x0040	
	unsigned char* nmethod; //0x0048
	unsigned char* _from_interpreted_entry; //0x0050
	char pad_0058[0x28]; //0x0058
};