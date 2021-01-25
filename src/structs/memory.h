#ifndef MEMORY_H
#define MEMORY_H

#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/mman.h>
#include "../log.h"

#define IL2CPP_LIB_NAME "libil2cpp.so"

namespace Memory
{
    extern uintptr_t _base;
    extern uint32_t _pageSize;

    inline void protect(uintptr_t addr, int flags)
    {
        uintptr_t pageAddr = addr & ~(_pageSize-1);
        mprotect((void *)pageAddr, _pageSize, flags);
    }
    inline void readOffset(uintptr_t addr, size_t len, char* buf)
    {
        protect(_base+addr, PROT_READ | PROT_EXEC);
        memcpy((void *)buf, (void *)(_base+addr), len);
    }
    inline void writeOffset(uintptr_t addr, char* data, size_t len)
    {
        protect(_base+addr, PROT_WRITE | PROT_EXEC);
        memcpy((void *)(_base+addr), (void *)data, len);
    }

    uintptr_t getIl2cppBase();
    uintptr_t getLibBase(const char *name = IL2CPP_LIB_NAME);
    uintptr_t getAbsoluteAddress(uintptr_t addr);
}; // namespace Memory

#endif