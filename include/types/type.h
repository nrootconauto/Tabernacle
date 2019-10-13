#ifndef TYPES_H
#define TYPES_H
#include "../../include/map/map.h"
#include <stdbool.h>
//unsigned of Holy C
typedef void U0;
typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
//signed of Holy C
typedef int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;
//floats
typedef double F64;
typedef struct __holyCClass holyCClass;
typedef map_t(holyCClass*) map_holyCClass_t;
typedef union {
	U8 _U8;
	U16 _U16;
	U32 _U32;
	U64 _U64;
	I8 _I8;
	I16 _I16;
	I32 _I32;
	I64 _I64;
	F64 _F64;
	holyCClass* _class;
} holyCPrimitiveTypeUnion;
typedef enum {
	_U8,
	_U16,
	_U32,
	_U64,
	_I8,
	_I16,
	_I32,
	_I64,
	_U0,
	_Class,
	_Union
} holyCPrimitiveValue;
typedef enum {
	_private,
	_public
} holyCAccessModifier;
struct __holyCClass {
	holyCPrimitiveTypeUnion type;
	holyCAccessModifier accessModifier;
	map_holyCClass_t items;
	char* name;
};
typedef union __holyCConstant holyCConstant;
typedef map_t(holyCConstant*) map_holyCConstant_t; 
union {
	holyCPrimitiveTypeUnion primitive;
	map_holyCConstant_t map;
} __holyCConstant;
#endif