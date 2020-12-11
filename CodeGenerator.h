#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "IT.h"
#include "LT.h"

#define HEADER ".486\n.MODEL FLAT, STDCALL\nincludelib kernel32.lib\nincludelib libucrt.lib\nincludelib C:\\Users\\User\\Desktop\\LP\\Lab\\LPLab14\\Debug\\userLib.lib\n\nExitProcess PROTO, :DWORD\n"
#define DATA_INT {Asm << '\t' <<element->visibility.function <<'_' << element->id << "\t\t" << "SDWORD\t" << 0 << '\n'; }
#define DATA_STR {Asm << '\t' <<element->visibility.function << '_' << element->id << '\t' << "BYTE 255 DUP(0)" << "\n"; }
#define CONST_INT {Asm << '\t' <<element->visibility.function << '_' << element->id << '\t' << "SDWORD\t" << element->value.vint << '\n'; }
#define CONST_STR {Asm << '\t' <<element->visibility.function << '_' << element->id << '\t' << "BYTE\t" << element->value.vstr->str << ",0\n"; }

#define PUSH_INT {Asm<<"\tpush "<<itElement.visibility.function<<'_'<<itElement.id<<'\n';}
#define PUSH_STR {Asm<<"\tpush offset "<<itElement.visibility.function<<'_'<<itElement.id<<'\n';}
#define PUSH_PARM_STR {Asm<<"\tpush ["<<itElement.visibility.function<<'_'<<itElement.id<<"]\n";}
#define ASIGN_INT {Asm<<"\tpop eax\n\tmov "<<firstIdName<<", eax\n";}
#define ASIGN_STR {Asm<<"\tpush offset "<< firstIdName<<"\n\tcall copyStr\n";}
#define ASIGN_PARM_STR {Asm<<"\tpush ["<<firstIdName<<"]\n\tcall copyStr\n";}
#define OUTPUT_INT {Asm<<"\tmov ebx, ecx\n\tcall outint\n\tmov ecx, ebx\n";}
#define OUTPUTLINE_INT {Asm<<"\tmov ebx, ecx\n\tcall outlineint\n\tmov ecx, ebx\n";}
#define OUTPUT_STR {Asm<<"\tmov ebx, ecx\n\tcall outstr\n\tmov ecx, ebx\n";}
#define OUTPUTLINE_STR {Asm<<"\tmov ebx, ecx\n\tcall outlinestr\n\tmov ecx, ebx\n";}
#define PLUS_INT {Asm<<"\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\t push eax\n";}
#define PLUS_STR {Asm<<"\tcall concatStr\n\tpush eax\n";}
#define MINUS {Asm<<"\tpop ebx\n\tpop eax\n\tsub eax, ebx\n\t push eax\n";}
#define DIV {Asm<<"\tpop ebx\n\tpop eax\n\tcdq\n\tdiv ebx\n\tpush eax\n";}
#define MUL {Asm<<"\tpop ebx\n\tpop eax\n\tmul ebx\n\tpush eax\n";}
#define MODULO {Asm<<"\tpop ebx\n\tpop eax\n\tcdq\n\tcwd\n\tdiv ebx\n\t\push edx\n";}
#define RETURN_INT {Asm<<"\tmov eax, "<<itElement.visibility.function << '_' << itElement.id<<"\n\tret\n";}
#define RETURN_STR {Asm<<"\tmov eax, offset "<<itElement.visibility.function << '_' << itElement.id<<"\n\tret\n";}
#define FIRST_INC {Asm<<"\tinc "<<firstIdName<<"\n";}
#define FIRST_DEC {Asm<<"\tdec "<<firstIdName<<'\n';}
#define INC {Asm<<"\tpop eax\n\tinc eax\n\tpush eax\n";}
#define DEC {Asm<<"\tpop eax\n\tdec eax\n\tpush eax\n";}
#define MORE {Asm<<"\tpop ebx\n\tpop eax\n\tcmp eax, ebx\n\tJL ELSE_"<<f.countIf<<"\n";}
#define LESS {Asm<<"\tpop ebx\n\tpop eax\n\tcmp eax, ebx\n\tJG ELSE_"<<f.countIf<<"\n";}
#define EQUAL {Asm<<"\tpop ebx\n\tpop eax\n\tcmp eax, ebx\n\tJNE ELSE_"<<f.countIf<<"\n";}
#define DIFFERENT {Asm<<"\tpop ebx\n\tpop eax\n\tcmp eax, ebx\n\tJE ELSE_"<<f.countIf<<"\n";}
#define LENGTH {Asm<<"\tpush offset "<<itElement.visibility.function<<'_'<<itElement.id <<"\n\tcall len\n\tpush eax\n";}
#define CONVERT {Asm<<"\tpush offset "<<itElement.visibility.function<<'_'<<itElement.id <<"\n\tcall ctoi\n\tpush eax\n";}
#define LOOP_PARM {Asm<<"\tmov ecx, "<<itElement.visibility.function<<'_'<<itElement.id<<"\nLOOP_"<<f.countLoop<<":\n";}
#define LOOP {Asm<<"loop LOOP_"<<f.countLoop<<"\n";}

namespace CG {
	bool CodeGeneration(IT::IdTable& it, LT::LexTable& lt);
	void CreateDataSegment(IT::IdTable& it, std::ofstream& Asm);
	void CreateConstSegment(IT::IdTable& it, std::ofstream& Asm);
	void CreateCodeSegment(IT::IdTable& it, LT::LexTable lt, std::ofstream& Asm);
}