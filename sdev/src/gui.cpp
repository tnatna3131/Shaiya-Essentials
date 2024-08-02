#include <array>
#include <format>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/util.h>
#include "include/main.h"

void format_chat_color_size(char* text)
{
    auto len = std::strlen(&text[8]);
    auto str = std::format("{:03}", len);
    std::memcpy(&text[2], str.data(), 3);
}

unsigned u0x57C56A = 0x57C56A;
void __declspec(naked) naked_0x57C565()
{
    __asm
    {
        pushad

        lea eax,[esi+edi]
        push eax
        call format_chat_color_size
        add esp,0x4

        popad

        // original
        mov dx,word ptr[esi+edi+0x2]
        jmp u0x57C56A
    }
}

unsigned u0x47E084 = 0x47E084;
void __declspec(naked) naked_0x47E07F()
{
    __asm
    {
        pushad

        lea eax,[edi+esi]
        push eax
        call format_chat_color_size
        add esp,0x4

        popad
        
        // original
        mov cx,word ptr[edi+esi+0x2]
        jmp u0x47E084
    }
}

unsigned n0x41F9ED = 0x41F9ED;
unsigned u0x41F9C9 = 0x41F9C9;
void __declspec(naked) naked_0x41F9C0()
{
    __asm
    {
        // character->wings
        cmp dword ptr[esi+0x434],0x0
        jne _0x41F9ED

        // original
        mov edx,[esi+0x10]
        fld dword ptr ds:[0x748160]
        jmp u0x41F9C9

        _0x41F9ED:
        jmp n0x41F9ED
    }
}

unsigned u0x41BB40 = 0x41BB40;
unsigned u0x4110F0 = 0x4110F0;
unsigned u0x41F5E6 = 0x41F5E6;
unsigned u0x41E2CD = 0x41E2CD;
void __declspec(naked) naked_0x41E2BB()
{
    __asm
    {
        // original
        mov ecx,esi
        call u0x41BB40
        test eax,eax
        jne original
        // continue
        jmp u0x41E2CD

        original:
        mov ecx,esi
        call u0x4110F0
        // exit
        jmp u0x41F5E6
    }
}

unsigned u0x528D96 = 0x528D96;
void __declspec(naked) naked_0x528D8D()
{
    __asm
    {
        pushad

        push 0x11 // VK_CONTROL
        call GetAsyncKeyState
        shr ax,0xF
        cmp ax,0x1

        popad

        jne original

        cmp ecx,0xA
        jl original

        sub ecx,0xA // x10
        mov dword ptr ds:[esi+0x4C],ecx
        add word ptr ds:[esi+eax*0x2+0x40],0xA
        jmp u0x528D96

        original:
        dec ecx // x1
        mov dword ptr ds:[esi+0x4C],ecx
        inc word ptr ds:[esi+eax*0x2+0x40]
        jmp u0x528D96
    }
}

void hook::gui()
{
    // chat color bug workaround

    // balloon
    util::detour((void*)0x57C565, naked_0x57C565, 5);
    // message box
    util::detour((void*)0x47E07F, naked_0x47E07F, 5);
    // dungeon wings shadow workaround
    util::detour((void*)0x41F9C0, naked_0x41F9C0, 9);
    // evolution bug
    util::detour((void*)0x41E2BB, naked_0x41E2BB, 7);
    // apply stats x10
    util::detour((void*)0x528D8D, naked_0x528D8D, 9);

    // remove ep6 vehicle section (auction board)
    util::write_memory((void*)0x463FE0, 0x07, 1);
    // speed recreation
    util::write_memory((void*)0x4C4D2F, 0x02, 1);
    // speed enchant
    util::write_memory((void*)0x501600, 0x02, 1);
    util::write_memory((void*)0x501602, 0x02, 1);
    util::write_memory((void*)0x501631, 0x02, 1);
    util::write_memory((void*)0x501633, 0x02, 1);
    util::write_memory((void*)0x501644, 0x03, 1);
    util::write_memory((void*)0x50164D, 0x03, 1);
    // costume lag workaround
    util::write_memory((void*)0x56F38D, 0x75, 1);
    util::write_memory((void*)0x583DED, 0x75, 1);
    // pet/wing lag workaround
    util::write_memory((void*)0x5881EE, 0x85, 1);
    // pass false to a function that appends '0' 
    // to exp text if said parameter is true
    util::write_memory((void*)0x4963DE, 0x00, 1);
    util::write_memory((void*)0x496407, 0x00, 1);
    util::write_memory((void*)0x529D05, 0x00, 1);
    util::write_memory((void*)0x529E19, 0x00, 1);
    util::write_memory((void*)0x594BA7, 0x00, 1);
    // ignore exp multiplication
    // note: does not affect locale 0 or 1 (different math)
    util::write_memory((void*)0x4FA494, 0x44, 1);
    util::write_memory((void*)0x4F9851, 0x00, 1);
}
