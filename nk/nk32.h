#pragma once

#include <stdint.h>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t QWORD;

typedef int8_t INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;

typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef void *LPARAM;
typedef void *HANDLE;
typedef void VOID;

typedef _Bool BOOL;
#define TRUE !0
#define FALSE 0

#define NKAPI __attribute__ ((__cdecl__))