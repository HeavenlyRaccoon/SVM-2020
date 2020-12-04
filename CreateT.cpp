#include "CreateT.h"
#pragma warning(disable : 4996)

namespace CreateT {

	struct
	{
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
			if (entryBuf.lexema[0] == '(')countHesis++;
			if (entryBuf.lexema[0] == ')')countHesis--;
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
				if (value->lexema[0] == 'i' || value->lexema[0] == 'l') {
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

		FST::FST fst6(lexem, 6,		//print
			FST::NODE(1, FST::RELATION('p', 1)),
			FST::NODE(1, FST::RELATION('r', 2)),
			FST::NODE(1, FST::RELATION('i', 3)),
			FST::NODE(1, FST::RELATION('n', 4)),
			FST::NODE(1, FST::RELATION('t', 5)),
			FST::NODE()
		);

		FST::FST fst7(lexem, 3,		//++
			FST::NODE(1, FST::RELATION('+', 1)),
			FST::NODE(1, FST::RELATION('+', 2)),
			FST::NODE()
		);
		FST::FST fst8(lexem, 3,		//--
			FST::NODE(1, FST::RELATION('-', 1)),
			FST::NODE(1, FST::RELATION('-', 2)),
			FST::NODE()
		);
		FST::FST fst9(lexem, 2,		//;
			FST::NODE(1, FST::RELATION(';', 1)),
			FST::NODE()
		);

		FST::FST fst10(lexem, 2,		//,
			FST::NODE(1, FST::RELATION(',', 1)),
			FST::NODE()
		);

		FST::FST fst11(lexem, 2,		//{
			FST::NODE(1, FST::RELATION('{', 1)),
			FST::NODE()
		);

		FST::FST fst12(lexem, 2,		//}
			FST::NODE(1, FST::RELATION('}', 1)),
			FST::NODE()
		);

		FST::FST fst13(lexem, 2,		//(
			FST::NODE(1, FST::RELATION('(', 1)),
			FST::NODE()
		);

		FST::FST fst14(lexem, 2,		//)
			FST::NODE(1, FST::RELATION(')', 1)),
			FST::NODE()
		);

		FST::FST fst15(lexem, 2,		//+
			FST::NODE(1, FST::RELATION('+', 1)),
			FST::NODE()
		);

		FST::FST fst16(lexem, 2,		//-
			FST::NODE(1, FST::RELATION('-', 1)),
			FST::NODE()
		);

		FST::FST fst17(lexem, 2,		//*
			FST::NODE(1, FST::RELATION('*', 1)),
			FST::NODE()
		);

		FST::FST fst18(lexem, 2,		//
			FST::NODE(1, FST::RELATION('/', 1)),
			FST::NODE()
		);

		FST::FST fst19(lexem, 2,		//=
			FST::NODE(1, FST::RELATION('=', 1)),
			FST::NODE()
		);
		FST::FST fst20(lexem, 2,		//%
			FST::NODE(1, FST::RELATION('%', 1)),
			FST::NODE()
		);

		FST::FST fst21(lexem, 2,		//1234535
			FST::NODE(10, FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),
				FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
				FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1)),
			FST::NODE(10, FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),
				FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
				FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::NODE())

		);

		FST::FST fst22(lexem, 5,		//main
			FST::NODE(1, FST::RELATION('m', 1)),
			FST::NODE(1, FST::RELATION('a', 2)),
			FST::NODE(1, FST::RELATION('i', 3)),
			FST::NODE(1, FST::RELATION('n', 4)),
			FST::NODE()
		);

		entry->idxTI = TI_NULLIDX;
		entry->priority = NULL;
		if (FST::execute(fst1) == -1) { flags.DataType = 1; return 't'; }
		else if (FST::execute(fst2) == -1) { flags.DataType = 2; return 't'; }
		else if (FST::execute(fst3) == -1) { flags.type = 2; flags.visCheck = true; flags.decl = true;  return 'f'; }
		else if (FST::execute(fst4) == -1) { flags.decl = true; return 'd'; }
		else if (FST::execute(fst5) == -1) return 'r';
		else if (FST::execute(fst6) == -1) return 'p';
		else if (FST::execute(fst7) == -1) { entry->priority = 2; return 'x'; }
		else if (FST::execute(fst8) == -1) { entry->priority = 2; return 'z';}
		else if (FST::execute(fst9) == -1) return ';';
		else if (FST::execute(fst10) == -1) return ',';
		else if (FST::execute(fst11) == -1) { if (flags.visCheck)flags.vis++; return '{'; }
		else if (FST::execute(fst12) == -1) { if (flags.visCheck) { flags.vis--; func.pop(); if (func.empty()) { flags.visCheck = false; } } return '}'; }
		else if (FST::execute(fst13) == -1) { entry->priority = 0; flags.type = 3; if (flags.visCheck)flags.vis++; return '('; }
		else if (FST::execute(fst14) == -1) { entry->priority = 0; flags.type = 1; if (flags.visCheck)flags.vis--;  return ')'; }
		else if (FST::execute(fst15) == -1) { entry->priority = 2; return '+'; }
		else if (FST::execute(fst16) == -1) { entry->priority = 2; return '-'; }
		else if (FST::execute(fst17) == -1) { entry->priority = 3; return '*'; }
		else if (FST::execute(fst18) == -1) { entry->priority = 3; return '/'; }
		else if (FST::execute(fst19) == -1) return '=';
		else if (FST::execute(fst20) == -1) { entry->priority = 3; return '%'; }
		else {
			if (FST::execute(fst21) == -1) { flags.type = 4; flags.DataType = 1; }
			else if(FST::execute(fst22) == -1){
				flags.type = 2;
				flags.DataType = 1;
				flags.main = true;
				flags.visCheck = true;
			}
			if (ltHaveLex(*idtable, lexem)) {
				entry->idxTI = ltHaveLex(*idtable, lexem);
				if (IT::GetEntry(*idtable, ltHaveLex(*idtable, lexem)).idtype == 4) { return LEX_LITERAL; }
				else { return 'i'; }
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
						entryBuf.value.vint = atoi(lexem);
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
				else return 'i';
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