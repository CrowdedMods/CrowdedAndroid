#include "memory.h"

uintptr_t getLibBase_r(const char *name)
{
    FILE *fp;
    uintptr_t addr = 0;
    char filename[32], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", getpid());
    fp = fopen(filename, "rt");
    if (fp != NULL)
    {
        while (fgets(buffer, sizeof(buffer), fp))
        {
            if (strstr(buffer, name))
            {
                addr = (uintptr_t)strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    LOGF("address for %s: 0x%X", name, addr);
    return addr;
}

namespace Memory
{
    uintptr_t _base = 0x0;
    long _pageSize = sysconf(_SC_PAGE_SIZE);
    uintptr_t getIl2cppBase()
    {
        if (_base != 0)
            return _base;
        uintptr_t res = getLibBase_r(IL2CPP_LIB_NAME);
        _base = res;
        return res;
    }
    uintptr_t getLibBase(const char *name)
    {
        if (name == IL2CPP_LIB_NAME)
            return getIl2cppBase();
        return getLibBase_r(name);
    }
    uintptr_t getAbsoluteAddress(uintptr_t addr)
    {
        if(_base == 0) getIl2cppBase();
        return _base+addr;
    }
} // namespace Memory