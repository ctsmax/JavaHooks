#pragma once
#include <string>
#include "jni.h"

class JavaThread {
public:
	char pad[0x1C8]; //
	void* _next; // 0X1C8
	char pad_[0X30]; // 0x1D
	JNIEnv env;
};