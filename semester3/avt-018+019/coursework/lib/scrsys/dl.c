#include "dl.h"


void*
s_dlopen(const char* filename, int flags)
{
    void* handle = dlopen(filename, flags);

    if (handle == NULL)
        throw_dlerror();

    return handle;
}

int
s_dlclose(void* handle)
{
    int result = dlclose(handle);

    if (result != 0)
        throw_dlerror();

    return result;
}

void*
s_dlsym(void* restrict handle, const char* restrict symbol)
{
    void* addr = dlsym(handle, symbol);

    if (addr == NULL)
        throw_dlerror();

    return addr;
}
