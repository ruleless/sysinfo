#ifndef __UTILS_H__
#define __UTILS_H__

extern "C"
{
#include "sigar.h"
};

const char * formatInteger(sigar_uint64_t n);

#endif // __UTILS_H__