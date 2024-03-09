#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main()
{
	__asm
	{
		call lable;
	lable:
		pop eax;
		add eax, 0x15; 越过 decoder 记录 shellcode 起始地址
			xor ecx, ecx
			decode_loop :
		mov bl, [eax + ecx]
			xor bl, 0x44; 用 0x44 作为 key
			mov[eax + ecx], bl
			inc ecx
			cmp bl, 0x90; 末尾放一个 0x90 作为结束符
			jne decode_loop
	}
	return 0;
}


