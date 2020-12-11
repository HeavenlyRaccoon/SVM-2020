#include "CreateT.h"
#pragma warning(disable : 4996)

namespace CreateT {
	struct
	{
		int countLoop = 0;
		int countIf = 0;
		int DataType = 0;
		int type = 1;
		int vis = 0;
		bool visCheck = false;
		bool main = false;
		bool decl = false;
	}flags;
	stack < string > func;

	void fillTable(string text, LT::LexTable &lextable, IT::IdTable &idtable) {
		int countHesis = 0;
		int* linePosition = getLineNums(text);
		char* lexem = strtok(&text[0], " \n");
		for (int idx = 1, i = 0; lexem != NULL; i++) {

			LT::Entry entryBuf;
			entryBuf.lexema[0] = compareLexem(lexem, &idx, &entryBuf, &idtable);
			if (entryBuf.lexema[0] == LEX_LEFTHESIS)countHesis++;
			if (entryBuf.lexema[0] == LEX_RIGHTHESIS)countHesis--;
			entryBuf.sn = linePosition[i];
			LT::Add(lextable, entryBuf);
			lexem = strtok(NULL, " \n");
		}
		if (countHesis) {
			throw ERROR_THROW(122);
		}
		makeOutLt(lextable);
		makeOutIT(idtable);
	}

	int* getLineNums(string code) {
		int* array = new int[MAX_LEXEM_LENGTH];
		int size = 0;
		for (int i = 0, line = 0, pos = 0; i < code.length(); i++) {
			if (code[i] != ' ') {
				if (code[i] == '\n') {
					line++;
					continue;
				}

				array[pos] = line;
				pos++;
				size++;
				while (code[i] != ' ') {
					if (code[i] == '\n' || code[i] == ' ') {
						i--;
						break;
					}
					i++;
				}
			}
		}
		return array;
	}

	void makeOutLt(LT::LexTable &lextable) {
		LT::Entry *value = lextable.head;
		int i = 0, j = 0;
		while (value->next != nullptr) {
			if (value->sn != i) {
				i++;
				continue;
			}
			cout << j << '\t';
			while (value->sn == i) {
				cout << value->lexema[0];
				if (value->lexema[0] == LEX_ID || value->lexema[0] == LEX_LITERAL) {
					cout << "(" << value->idxTI << ")";
				}
				value = value->next;
			}
			cout << '\n';
			i++;
			j++;
		}
	}

	void makeOutIT(IT::IdTable &idtable) {
		IT::Entry *value = idtable.head;
		cout << "Номер\t|" << "\tНазвание\t|" << "\tТип данных\t|" << "\tТип идентификатора\t|" << "\tУровень видимости\t|" << "\t\tФункция\t\t|" << "\tЗначение" << endl;
		while (value->next != nullptr) {
			cout << value->idxfirstLE << "\t|\t" << value->id << "\t\t|\t" << value->iddatatype << "\t\t|\t\t" << value->idtype << "\t\t|\t\t" << value->visibility.visible << "\t\t|\t\t" << value->visibility.function << "\t\t|\t" << value->value.vstr->str<<"\t"<<value->declared;
			value = value->next;
			cout << '\n';
		}
	}

	char compareLexem(char* lexem, int *idx, LT::Entry* entry, IT::IdTable *idtable) {
		IT::Entry entryBuf;
		if (lexem[0] == *"\"" || lexem[0] == *"\'") {
			for (int i = 0; i < strlen(lexem); i++) {
				if (lexem[i] == '_')lexem[i] = ' ';
			}
			flags.type = 4;
			entry->idxTI = TI_NULLIDX;
			flags.DataType = 2;
		}
		FST::FST fst1(lexem, 8,		//integer
			FST::NODE(1, FST::RELATION('i', 1)),
			FST::NODE(1, FST::RELATION('n', 2)),
			FST::NODE(1, FST::RELATION('t', 3)),
			FST::NODE(1, FST::RELATION('e', 4)),
			FST::NODE(1, FST::RELATION('g', 5)),
			FST::NODE(1, FST::RELATION('e', 6)),
			FST::NODE(1, FST::RELATION('r', 7)),
			FST::NODE()
		);

		FST::FST fst2(lexem, 7,		//string
			FST::NODE(1, FST::RELATION('s', 1)),
			FST::NODE(1, FST::RELATION('t', 2)),
			FST::NODE(1, FST::RELATION('r', 3)),
			FST::NODE(1, FST::RELATION('i', 4)),
			FST::NODE(1, FST::RELATION('n', 5)),
			FST::NODE(1, FST::RELATION('g', 6)),
			FST::NODE()
		);

		FST::FST fst3(lexem, 9,		//function
			FST::NODE(1, FST::RELATION('f', 1)),
			FST::NODE(1, FST::RELATION('u', 2)),
			FST::NODE(1, FST::RELATION('n', 3)),
			FST::NODE(1, FST::RELATION('c', 4)),
			FST::NODE(1, FST::RELATION('t', 5)),
			FST::NODE(1, FST::RELATION('i', 6)),
			FST::NODE(1, FST::RELATION('o', 7)),
			FST::NODE(1, FST::RELATION('n', 8)),
			FST::NODE()
		);

		FST::FST fst4(lexem, 8,		//declare
			FST::NODE(1, FST::RELATION('d', 1)),
			FST::NODE(1, FST::RELATION('e', 2)),
			FST::NODE(1, FST::RELATION('c', 3)),
			FST::NODE(1, FST::RELATION('l', 4)),
			FST::NODE(1, FST::RELATION('a', 5)),
			FST::NODE(1, FST::RELATION('r', 6)),
			FST::NODE(1, FST::RELATION('e', 7)),
			FST::NODE()
		);

		FST::FST fst5(lexem, 7,		//return
			FST::NODE(1, FST::RELATION('r', 1)),
			FST::NODE(1, FST::RELATION('e', 2)),
			FST::NODE(1, FST::RELATION('t', 3)),
			FST::NODE(1, FST::RELATION('u', 4)),
			FST::NODE(1, FST::RELATION('r', 5)),
			FST::NODE(1, FST::RELATION('n', 6)),
			FST::NODE()
		);

		FST::FST fst6(lexem, 7,		//output
			FST::NODE(1, FST::RELATION('o', 1)),
			FST::NODE(1, FST::RELATION('u', 2)),
			FST::NODE(1, FST::RELATION('t', 3)),
			FST::NODE(1, FST::RELATION('p', 4)),
			FST::NODE(1, FST::RELATION('u', 5)),
			FST::NODE(1, FST::RELATION('t', 6)),
			FST::NODE()
		);
		FST::FST fst7(lexem, 11,		//outputline
			FST::NODE(1, FST::RELATION('o', 1)),
			FST::NODE(1, FST::RELATION('u', 2)),
			FST::NODE(1, FST::RELATION('t', 3)),
			FST::NODE(1, FST::RELATION('p', 4)),
			FST::NODE(1, FST::RELATION('u', 5)),
			FST::NODE(1, FST::RELATION('t', 6)),
			FST::NODE(1, FST::RELATION('l', 7)),
			FST::NODE(1, FST::RELATION('i', 8)),
			FST::NODE(1, FST::RELATION('n', 9)),
			FST::NODE(1, FST::RELATION('e', 10)),
			FST::NODE()
		);

		FST::FST fst8(lexem, 7,		//length
			FST::NODE(1, FST::RELATION('l', 1)),
			FST::NODE(1, FST::RELATION('e', 2)),
			FST::NODE(1, FST::RELATION('n', 3)),
			FST::NODE(1, FST::RELATION('g', 4)),
			FST::NODE(1, FST::RELATION('t', 5)),
			FST::NODE(1, FST::RELATION('h', 6)),
			FST::NODE()
		);

		FST::FST fst9(lexem, 5,		//ctoi
			FST::NODE(1, FST::RELATION('c', 1)),
			FST::NODE(1, FST::RELATION('t', 2)),
			FST::NODE(1, FST::RELATION('o', 3)),
			FST::NODE(1, FST::RELATION('i', 4)),
			FST::NODE()
		);

		FST::FST fst10(lexem, 5,		//loop
			FST::NODE(1, FST::RELATION('l', 1)),
			FST::NODE(1, FST::RELATION('o', 2)),
			FST::NODE(1, FST::RELATION('o', 3)),
			FST::NODE(1, FST::RELATION('p', 4)),
			FST::NODE()
		);

		FST::FST fst11(lexem, 3,		//if
			FST::NODE(1, FST::RELATION('i', 1)),
			FST::NODE(1, FST::RELATION('f', 2)),
			FST::NODE()
		);
		FST::FST fst12(lexem, 5,		//else
			FST::NODE(1, FST::RELATION('e', 1)),
			FST::NODE(1, FST::RELATION('l', 2)),
			FST::NODE(1, FST::RELATION('s', 3)),
			FST::NODE(1, FST::RELATION('e', 4)),
			FST::NODE()
		);

		FST::FST fst13(lexem, 3,		//++
			FST::NODE(1, FST::RELATION('+', 1)),
			FST::NODE(1, FST::RELATION('+', 2)),
			FST::NODE()
		);
		FST::FST fst14(lexem, 3,		//--
			FST::NODE(1, FST::RELATION('-', 1)),
			FST::NODE(1, FST::RELATION('-', 2)),
			FST::NODE()
		);
		FST::FST fst15(lexem, 2,		//;
			FST::NODE(1, FST::RELATION(';', 1)),
			FST::NODE()
		);

		FST::FST fst16(lexem, 2,		//,
			FST::NODE(1, FST::RELATION(',', 1)),
			FST::NODE()
		);

		FST::FST fst17(lexem, 2,		//[
			FST::NODE(1, FST::RELATION('[', 1)),
			FST::NODE()
		);
		FST::FST fst18(lexem, 2,		//]
			FST::NODE(1, FST::RELATION(']', 1)),
			FST::NODE()
		);

		FST::FST fst19(lexem, 2,		//{
			FST::NODE(1, FST::RELATION('{', 1)),
			FST::NODE()
		);

		FST::FST fst20(lexem, 2,		//}
			FST::NODE(1, FST::RELATION('}', 1)),
			FST::NODE()
		);

		FST::FST fst21(lexem, 2,		//(
			FST::NODE(1, FST::RELATION('(', 1)),
			FST::NODE()
		);

		FST::FST fst22(lexem, 2,		//)
			FST::NODE(1, FST::RELATION(')', 1)),
			FST::NODE()
		);

		FST::FST fst23(lexem, 2,		//+
			FST::NODE(1, FST::RELATION('+', 1)),
			FST::NODE()
		);

		FST::FST fst24(lexem, 2,		//-
			FST::NODE(1, FST::RELATION('-', 1)),
			FST::NODE()
		);

		FST::FST fst25(lexem, 2,		//*
			FST::NODE(1, FST::RELATION('*', 1)),
			FST::NODE()
		);

		FST::FST fst26(lexem, 2,		//
			FST::NODE(1, FST::RELATION('/', 1)),
			FST::NODE()
		);

		FST::FST fst27(lexem, 2,		//=
			FST::NODE(1, FST::RELATION('=', 1)),
			FST::NODE()
		);
		FST::FST fst28(lexem, 2,		//%
			FST::NODE(1, FST::RELATION('%', 1)),
			FST::NODE()
		);
		FST::FST fst29(lexem, 2,		//>
			FST::NODE(1, FST::RELATION('>', 1)),
			FST::NODE()
		);
		FST::FST fst30(lexem, 2,		//<
			FST::NODE(1, FST::RELATION('<', 1)),
			FST::NODE()
		);
		FST::FST fst31(lexem, 2,		//&
			FST::NODE(1, FST::RELATION('&', 1)),
			FST::NODE()
		);
		FST::FST fst32(lexem, 2,		//!
			FST::NODE(1, FST::RELATION('!', 1)),
			FST::NODE()
		);

		FST::FST fst33(lexem, 2,		//1234535
			FST::NODE(10, FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),
				FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
				FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1)),
			FST::NODE(10, FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),
				FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
				FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::NODE())

		);

		FST::FST fst34(lexem, 5,		//main
			FST::NODE(1, FST::RELATION('m', 1)),
			FST::NODE(1, FST::RELATION('a', 2)),
			FST::NODE(1, FST::RELATION('i', 3)),
			FST::NODE(1, FST::RELATION('n', 4)),
			FST::NODE()
		);

		entry->idxTI = TI_NULLIDX;
		entry->priority = NULL;
		if (FST::execute(fst1) == -1) { flags.DataType = 1; return LEX_INTEGER; }
		else if (FST::execute(fst2) == -1) { flags.DataType = 2; return LEX_STRING; }
		else if (FST::execute(fst3) == -1) { flags.type = 2; flags.visCheck = true; flags.decl = true;  return LEX_FUNCTION; }
		else if (FST::execute(fst4) == -1) { flags.decl = true; return LEX_DECLARE; }
		else if (FST::execute(fst5) == -1) return LEX_RETURN;
		else if (FST::execute(fst6) == -1) return LEX_OUTPUT;
		else if (FST::execute(fst7) == -1) return LEX_OUTPUTLINE;
		else if (FST::execute(fst8) == -1) return LEX_LENGTH;
		else if (FST::execute(fst9) == -1) return LEX_CONVERT;
		else if (FST::execute(fst10) == -1) { entry->numLoop = flags.countLoop; flags.countLoop++; return LEX_LOOP; }
		else if (FST::execute(fst11) == -1) { entry->numIf = flags.countIf; flags.countIf++; return LEX_IF; }
		else if (FST::execute(fst12) == -1) { return LEX_ELSE; }
		else if (FST::execute(fst13) == -1) { entry->priority = 2; return LEX_INC; }
		else if (FST::execute(fst14) == -1) { entry->priority = 2; return LEX_DEC;}
		else if (FST::execute(fst15) == -1) return LEX_SEMICOLON;
		else if (FST::execute(fst16) == -1) return LEX_COMMA;
		else if (FST::execute(fst17) == -1) return LEX_LEFTSQUARE;
		else if (FST::execute(fst18) == -1) return LEX_RIGHTSQUARE;
		else if (FST::execute(fst19) == -1) { if (flags.visCheck)flags.vis++; return LEX_LEFTBRACE; }
		else if (FST::execute(fst20) == -1) { if (flags.visCheck) { flags.vis--; func.pop(); if (func.empty()) { flags.visCheck = false; } } return LEX_BRACELET; }
		else if (FST::execute(fst21) == -1) { entry->priority = 0; flags.type = 3; if (flags.visCheck)flags.vis++; return LEX_LEFTHESIS; }
		else if (FST::execute(fst22) == -1) { entry->priority = 0; flags.type = 1; if (flags.visCheck)flags.vis--;  return LEX_RIGHTHESIS; }
		else if (FST::execute(fst23) == -1) { entry->priority = 2; return LEX_PLUS; }
		else if (FST::execute(fst24) == -1) { entry->priority = 2; return LEX_MINUS; }
		else if (FST::execute(fst25) == -1) { entry->priority = 3; return LEX_STAR; }
		else if (FST::execute(fst26) == -1) { entry->priority = 3; return LEX_DIRSLASH; }
		else if (FST::execute(fst27) == -1) return LEX_ASIGN;
		else if (FST::execute(fst28) == -1) { entry->priority = 3; return LEX_MODULO; }
		else if (FST::execute(fst29) == -1) { entry->priority = 2; return LEX_MORE;}
		else if (FST::execute(fst30) == -1) { entry->priority = 2; return LEX_LESS;}
		else if (FST::execute(fst31) == -1) { entry->priority = 2; return LEX_EQUAL;}
		else if (FST::execute(fst32) == -1) { entry->priority = 2; return LEX_DIFFERENT;}
		else {
			if (FST::execute(fst33) == -1) { flags.type = 4; flags.DataType = 1; }
			else if(FST::execute(fst34) == -1){
				flags.type = 2;
				flags.DataType = 1;
				flags.main = true;
				flags.visCheck = true;
			}
			if (ltHaveLex(*idtable, lexem)) {
				entry->idxTI = ltHaveLex(*idtable, lexem);
				if (IT::GetEntry(*idtable, ltHaveLex(*idtable, lexem)).idtype == 4) { return LEX_LITERAL; }
				else { return LEX_ID; }
			}
			else {

				entry->idxTI = *idx;
				entryBuf.idxfirstLE = *idx;
				entryBuf.visibility.visible = flags.vis;
				for (int i = 0; i < ID_MAXSIZE; i++) { entryBuf.id[i] = lexem[i]; }
				if (flags.DataType == 1)entryBuf.iddatatype = IT::INT;
				if (flags.DataType == 2)entryBuf.iddatatype = IT::STR;
				entryBuf.value.vint = NULL;
				entryBuf.value.vstr->len = NULL;
				strcpy(entryBuf.value.vstr->str, "");
				switch (flags.type) {
				case 1: {
					entryBuf.idtype = IT::V;
					entryBuf.declared = flags.decl;
					break;
				}
				case 2: {
					func.push(lexem);
					entryBuf.idtype = IT::F;
					entryBuf.declared = flags.decl;
					break;
				}
				case 3: {
					entryBuf.idtype = IT::P;
					entryBuf.declared = true;
					break;
				}
				case 4: {
					entryBuf.idtype = IT::L;
					string str = "Lex";
					string str2;
					stringstream os;
					os << *idx;
					os >> str2;
					str = str + str2;
					strcpy(entryBuf.id, &str[0]);
					if (entryBuf.iddatatype == IT::STR) {
						strcpy(entryBuf.value.vstr->str, lexem);
					}
					else
					{
						if (lexem[0] == '0') {
							int result = 0;
							for (int i = 1; i < strlen(lexem); i++) {
								result += pow(8, strlen(lexem)-1 - i)*((int)lexem[i] - 48);
							}
							entryBuf.value.vint = result;
						}
						else{ entryBuf.value.vint = atoi(lexem); }
						
					}
					
					break;
				}
				default:
					break;
				}
				strcpy(entryBuf.visibility.function, func.top().c_str());
				IT::Add(*idtable, entryBuf);
				(*idx)++;
				flags.decl = false;
				if (flags.type == 4) { flags.type = 1; return LEX_LITERAL; }
				if (flags.main) { flags.main = false; flags.type = 1; return MAIN_LITERAL; }
				else return LEX_ID;
			}
		}
	}

	int ltHaveLex(IT::IdTable idtable, char *lexem) {
		IT::Entry *value = idtable.head;
		while (value->next != nullptr)
		{
			if (strcmp(value->id, lexem) == 0 && (strcmp(func.top().c_str(), value->visibility.function) == 0 || strcmp(value->id, value->visibility.function) == 0)) {
				return value->idxfirstLE;
			}
			value = value->next;
		}
		return 0;	//если ноль то добовляем новый ид
	}
}