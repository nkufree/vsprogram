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
		add eax, 0x15; Խ�� decoder ��¼ shellcode ��ʼ��ַ
			xor ecx, ecx
			decode_loop :
		mov bl, [eax + ecx]
			xor bl, 0x44; �� 0x44 ��Ϊ key
			mov[eax + ecx], bl
			inc ecx
			cmp bl, 0x90; ĩβ��һ�� 0x90 ��Ϊ������
			jne decode_loop
	}
	return 0;
}


