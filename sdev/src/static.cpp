#include "include/static.h"
using namespace shaiya;

void Static::DrawRect(D3DCOLOR argb, long x, long y, long w, long h)
{
    typedef void(__cdecl* LPFN)(D3DCOLOR, long, long, long, long);
    (*(LPFN)0x4B6180)(argb, x, y, w, h);
}

void Static::GetMsg(int type, int line, int unknown)
{
    typedef void(__cdecl* LPFN)(int, int, int);
    (*(LPFN)0x423150)(type, line, unknown);
}

bool Static::PlayWav(const char* filename, D3DVECTOR* origin, float volume, bool repeat)
{
    typedef bool(__thiscall* LPFN)(void*, const char*, D3DVECTOR*, float, bool);
    return (*(LPFN)0x56C650)((void*)0x22B4030, filename, origin, volume, repeat);
}
