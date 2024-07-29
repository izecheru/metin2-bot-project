#pragma once
#include <map>
#include <stdint.h>

struct Vector3
{
		float x;
		float y;
		float z;
};

#define CHECK_BAD_PTR(x) if(IsBadReadPtr(this,sizeof(x))) return nullptr
#define CHECK_BAD(x) if(IsBadReadPtr(this, sizeof(x))) return
#define CHECK_BAD_NUM(x) if(IsBadReadPtr(this, sizeof(x))) return 0
#define CHECK_BAD_VEC3(x) if(IsBadReadPtr(this, sizeof(x))) return Vector3{0,0,0}

class Entity
{
public:
		char pad_0000[32]; //0x0000
		char name[20]; //0x0020
		char pad_0034[464]; //0x0034
		Vector3 position; //0x0204
		char pad_0210[1144]; //0x0210
		int32_t attackStance; //0x0688
		char pad_068C[2508]; //0x068C

}; //Size: 0x1058

