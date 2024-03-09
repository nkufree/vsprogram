#include<iostream>
using namespace std;

int main()
{
	_asm
	{
		.386
		.model flat, stdcall
		option casemap : none
		include \masm32\include\kernel32.inc
		include \masm32\include\masm32.inc
		includelib \masm32\lib\kernel32.lib
		includelib \masm32\lib\masm32.lib


		.data
		num BYTE 20 DUP(0)
		res BYTE 8 DUP(0)
		input_info BYTE "Please input a decimal number(0~4294967295): ", 0
		output_info BYTE "The hexdecimal number is : ", 0

		.code
		start :
		INVOKE StdOut, addr input_info
			INVOKE StdIn, addr num, 20

			MOV edx, 0h; 记录要处理的数字
			MOV ecx, 1h; 记录处理第几个数字
			MOV eax, 0h; 记录每一次计算结果
			L1 :
		MOV dl, BYTE PTR[num + ecx]
			CMP dl, 0h
			JE L6
			SUB dl, 30h
			MOV ebx, eax
			SHL ebx, 3
			SHL eax, 1
			ADD eax, ebx
			ADD eax, edx
			SHL ecx, 2
			JMP L1

			L6 :
		MOV ecx, 1h
			MOV edx, eax
			L2 :
		AND edx, 0Fh
			CMP dl, 0h
			JE L5
			CMP dl, 9h
			JB L3
			CMP dl, 9h
			JNB L4
			L3 :
		ADD dl, 30h
			MOV[res + ecx], dl
			SHL ecx, 2
			JMP L2
			L4 :
		ADD dl, 41h
			MOV[res + ecx], dl
			SHL ecx, 2
			JMP L2
			L5 :
		INVOKE StdOut, addr output_info
			INVOKE StdOut, addr res
			END start
	}
}