#include "CodeGenerator.h"
#pragma warning(disable : 4996)

namespace CG {
	bool CodeGeneration(IT::IdTable& it, LT::LexTable& lt) {
		const char* fileName = "ASM.asm";
		std::ofstream Asm;
		Asm.open(fileName);
		if (!Asm.is_open()) {
			return false;
		}
		Asm << HEADER;
		Asm << "EXTRN copyStr: proc\n";
		Asm << "EXTRN outint: proc\n";
		Asm << "EXTRN outstr: proc\n";
		Asm << "EXTRN concatStr: proc\n";
		Asm << "\n.STACK 4096\n";

		CreateDataSegment(it, Asm);
		CreateConstSegment(it, Asm);
		CreateCodeSegment(it, lt, Asm);

		Asm.close();
		return true;
	}

	void CreateDataSegment(IT::IdTable& it, std::ofstream& Asm) {
		Asm << ".DATA\n";
		IT::Entry* element = it.head;
		while (element)
		{
			if (element->idtype == IT::V) {
				if (element->iddatatype == IT::INT) {
					DATA_INT;
				}
				else
				{
					DATA_STR;
				}
			}
			element = element->next;
		}
	}

	void CreateConstSegment(IT::IdTable& it, std::ofstream& Asm) {
		Asm << ".CONST\n";
		IT::Entry* element = it.head;
		while (element)
		{
			if (element->idtype == IT::L) {
				if (element->iddatatype == IT::INT) {
					CONST_INT;
				}
				else
				{
					CONST_STR;
				}
			}
			element = element->next;
		}
	}

	struct flag
	{	
		bool firstId = true;
		bool func = false;
		bool ret = false;
		int funcType = NULL;
		int iddatatype = NULL;
		int idtype = NULL;
		bool asign = false;
		bool print = false;
		bool funcBody = false;
		bool funcParm = false;
		bool mainBody = false;
		char* funcName = new char();
	};

	void CreateCodeSegment(IT::IdTable& it, LT::LexTable lt, std::ofstream& Asm) {
		flag f;
		char* firstIdName = new char();
		Asm << ".CODE\n";

		IT::Entry itElement;
		LT::Entry* ltElement = lt.head;

		while (ltElement->next)
		{
			switch (ltElement->lexema[0])
			{
			case LEX_ID: {
				itElement = IT::GetEntry(it, ltElement->idxTI);
				if (f.ret && !f.mainBody) { 
					if (itElement.iddatatype == 1) RETURN_INT
					else {
						if (itElement.idtype == 3) RETURN_INT
						else RETURN_STR;
					}
					f.ret = false; break; 
				}
				else if (f.ret&&f.mainBody) {
					if (itElement.iddatatype == 1)PUSH_INT
					else {
						if (itElement.idtype == 3) PUSH_PARM_STR
						else PUSH_STR;
					}
					Asm << "\tcall ExitProcess\n";
					f.ret = false; break;
				}
				else if (f.firstId&&ltElement->next->lexema[0] == LEX_SEMICOLON&&!f.print) break;
				else if (f.firstId&&!f.print&&!f.func&&f.funcBody) {
					f.iddatatype = itElement.iddatatype;
					f.idtype = itElement.idtype;
					strcpy(firstIdName, itElement.visibility.function);
					strcat(firstIdName, "_");
					strcat(firstIdName, itElement.id);
					if(ltElement->next->lexema[0]!=LEX_DEC&& ltElement->next->lexema[0] != LEX_INC) f.firstId = false;
					
				}
				else if (f.func && !f.funcBody) {
					if (!f.funcParm) {
						strcpy(f.funcName, itElement.id);
						Asm << itElement.id << " PROC ";
					}
					if (f.funcParm) {
						if (itElement.iddatatype == 1) Asm << itElement.visibility.function << '_' << itElement.id << ": SDWORD";
						else Asm << itElement.visibility.function << '_' << itElement.id << ": DWORD";
						if (ltElement->next->lexema[0] == LEX_COMMA) Asm << ", ";
						else { f.funcParm = false; Asm << '\n'; }
					}
				}
				else {
					if (itElement.iddatatype == 1) PUSH_INT
					else {
						if (itElement.idtype == 3) PUSH_PARM_STR
						else PUSH_STR;
					}
					if (f.print) {
						if (itElement.iddatatype == 1) PRINT_INT
						else PRINT_STR;
					}
					
				}
				break;
			}
			case LEX_ASIGN: {
				f.asign = true;
				break;
			}
			case LEX_LITERAL: {
				itElement = IT::GetEntry(it, ltElement->idxTI);
				if (f.ret && !f.mainBody) {
					if (itElement.iddatatype == 1) RETURN_INT
					else {
						if (itElement.idtype == 3) RETURN_INT
						else RETURN_STR;
					}
					f.ret = false; break;
				}
				else if (f.ret&&f.mainBody) {
					if (itElement.iddatatype == 1)PUSH_INT
					else {
						if (itElement.idtype == 3) PUSH_PARM_STR
						else PUSH_STR;
					}
					Asm << "\tcall ExitProcess\n";
					f.ret = false; break;
				}
				if (itElement.iddatatype == 1) PUSH_INT
				else {
					if (itElement.idtype == 3) PUSH_PARM_STR
					else PUSH_STR;
				}
				if (f.print) {
					if (itElement.iddatatype == 1) PRINT_INT
					else PRINT_STR;
				}
				break;
			}
			case LEX_SEMICOLON: {
				if (f.asign) {
					if (f.iddatatype == 1) ASIGN_INT
					else {
						if (f.idtype == 3) ASIGN_PARM_STR
						else ASIGN_STR;
					}
				}
				f.firstId = true;
				f.asign = false;
				f.print = false;
				break;
			}
			case LEX_PRINT: {
				f.print = true;
				break;
			}
			case LEX_PLUS: {
				if (f.iddatatype == 1) PLUS_INT
				else PLUS_STR;
				break;
			}
			case LEX_MINUS: {
				MINUS;
				break;
			}
			case LEX_DIRSLASH: {
				DIV;
				break;
			}
			case LEX_STAR: {
				MUL;
				break;
			}
			case LEX_MODULO: {
				MODULO;
				break;
			}
			case LEX_FUNCTION: {
				f.func = true;
				break;
			}
			case LEX_LEFTHESIS: {
				if (f.func && !f.funcBody) {
					f.funcParm = true;
				}
				break;
			}
			case LEX_LEFTBRACE: {
				if (f.func) {
					f.funcBody = true;
					f.func = false;
				}
				break;
			}
			case LEX_BRACELET: {
				if (f.funcBody && !f.mainBody) { f.funcBody = false; Asm << f.funcName << " ENDP\n"; }
				if (f.mainBody) { f.mainBody = false; f.funcBody = false; Asm << "END START\n"; }
				break;
			}
			case LEX_RETURN: {
				f.ret = true;
				break;
			}
			case MAIN_LITERAL: {
				Asm << "START:\n";
				strcpy(f.funcName, "main");
				f.funcBody = true;
				f.mainBody = true;
				break;
			}
			case LEX_FUNCPARM: {
				for (int i = ltElement->func.count-1 ; i>=0; i--) {
					if (IT::GetEntry(it, ltElement->func.idx[i]).iddatatype == 1) {
						Asm << "\tpush " << f.funcName << '_' << IT::GetEntry(it, ltElement->func.idx[i]).id << '\n';
					}
					else
					{
						Asm << "\tpush offset " << f.funcName << '_' << IT::GetEntry(it, ltElement->func.idx[i]).id << '\n';
					}
					
				}
				Asm << "\tcall " << ltElement->func.funcName<<'\n';
				Asm << "\tpush eax\n";
				break;
			}
			case LEX_INC: {
				if (f.firstId)FIRST_INC
				else INC;
				break;
			}
			case LEX_DEC: {
				if (f.firstId)FIRST_DEC
				else DEC;
				break;
			}

			default:
				break;
			}
			ltElement = ltElement->next;
		}
	}
}