#ifndef DL_H
#define DL_H

#include <dlfcn.h>
#include <stddef.h>

#include "error.h"


void*
s_dlopen(const char* filename, int flags);

int
s_dlclose(void* handle);

void*
s_dlsym(void* handle, const char* symbol);


#endif
