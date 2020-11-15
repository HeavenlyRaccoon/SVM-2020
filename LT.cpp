#include "pch.h"
#include "LT.h";
#include "IT.h";
#include "Error.h";
#include "FST.h"
#include <sstream>
#include <stack>
#pragma warning(disable : 4996)

namespace LT {

	int DataType = 0;
	int type = 1;
	int vis = 0;
	bool visCheck=false;
	bool main = false;
	stack < string > func;
	//создание таблицы
	LexTable Create(int size) {
		if (size <= LT_MAXSIZE) {
			LexTable *lextable = new LexTable;
			lextable->maxsize = size;
			lextable->size = 0;
			lextable->table = new Entry;
			lextable->head = lextable->table;
			return *lextable;
		}
		else {
			throw ERROR_THROW(118);
		}
		
	}

	//добавление строки в таблицу
	void Add(LexTable& lextable, Entry entry) {
		if (lextable.table != nullptr) {
			lextable.size++;
			if (lextable.size > lextable.maxsize) {
				throw ERROR_THROW(120);
			}

			lextable.table->lexema[0] = entry.lexema[0];
			lextable.table->sn = entry.sn;
			lextable.table->idxTI = entry.idxTI;
			lextable.table->priority = entry.priority;
			lextable.table->next = new Entry;
			lextable.table = lextable.table->next;
			lextable.table->next = nullptr;
		}
		else {
			throw ERROR_THROW(119);
		}
	}

	//возварщение строки таблицы
	Entry* GetEntry(LexTable& lextable, int n) {
		Entry *value = lextable.head;
		int pos = 0;
		while (value) {
			if (pos == n) {
				return value;
			}
			else {
				value = value->next;
				pos=value->sn;
			}
		}
		throw ERROR_THROW(121);
	}

	//удаление таблицы
	void Delete(LexTable& lextable) {
		delete &lextable;
	}

	int ltHaveLex(IT::IdTable idtable, char *lexem) {
		IT::Entry *value = idtable.head;
		while (value->next!=nullptr)
		{
			if (strcmp(value->id,lexem) == 0&&(strcmp(func.top().c_str(),value->visibility.function)==0||strcmp(value->id,value->visibility.function)==0)) {
				return value->idxfirstLE;
			}
			value = value->next;
		}
		return 0;	//если ноль то добовляем новый ид
	}

	
	char compareLexem(char* lexem, int *idx, Entry* entry, IT::IdTable *idtable) {
		IT::Entry entryBuf;
		if (lexem[0] == *"\"" || lexem[0] == *"\'") {
			for (int i = 0; i < strlen(lexem); i++) {
				if (lexem[i] == '_')lexem[i] = ' ';
			}
			type = 4;
			entry->idxTI = TI_NULLIDX;
			DataType = 2;
		}
		if (strcmp(lexem, "main") == 0) {
			func.push(lexem);
			type = 2;
			DataType = 1;
			main = true;
			visCheck = true;
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

		FST::FST fst7(lexem, 2,		//;
			FST::NODE(1, FST::RELATION(';', 1)),
			FST::NODE()
		);

		FST::FST fst8(lexem, 2,		//,
			FST::NODE(1, FST::RELATION(',', 1)),
			FST::NODE()
		);

		FST::FST fst9(lexem, 2,		//{
			FST::NODE(1, FST::RELATION('{', 1)),
			FST::NODE()
		);

		FST::FST fst10(lexem, 2,		//}
			FST::NODE(1, FST::RELATION('}', 1)),
			FST::NODE()
		);

		FST::FST fst11(lexem, 2,		//(
			FST::NODE(1, FST::RELATION('(', 1)),
			FST::NODE()
		);

		FST::FST fst12(lexem, 2,		//)
			FST::NODE(1, FST::RELATION(')', 1)),
			FST::NODE()
		);

		FST::FST fst13(lexem, 2,		//+
			FST::NODE(1, FST::RELATION('+', 1)),
			FST::NODE()
		);

		FST::FST fst14(lexem, 2,		//-
			FST::NODE(1, FST::RELATION('-', 1)),
			FST::NODE()
		);

		FST::FST fst15(lexem, 2,		//*
			FST::NODE(1, FST::RELATION('*', 1)),
			FST::NODE()
		);

		FST::FST fst16(lexem, 2,		//
			FST::NODE(1, FST::RELATION('/', 1)),
			FST::NODE()
		);

		FST::FST fst17(lexem, 2,		//=
			FST::NODE(1, FST::RELATION('=', 1)),
			FST::NODE()
		);

		FST::FST fst18(lexem, 2,		//1234535
			FST::NODE(9, FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),
						 FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
						 FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1)),
			FST::NODE(10, FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),
						 FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
						 FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::NODE())
			
		);

		entry->idxTI = TI_NULLIDX;
		entry->priority = NULL;
		if (FST::execute(fst1) == -1) { DataType = 1; return 't'; }
		else if (FST::execute(fst2) == -1) { DataType = 2; return 't'; }
		else if (FST::execute(fst3) == -1) { type = 2; visCheck = true;  return 'f'; }
		else if (FST::execute(fst4) == -1) return 'd';
		else if (FST::execute(fst5) == -1) return 'r';
		else if (FST::execute(fst6) == -1) return 'p';
		else if (FST::execute(fst7) == -1) return ';';
		else if (FST::execute(fst8) == -1) return ',';
		else if (FST::execute(fst9) == -1) { if (visCheck)vis++; return '{'; }
		else if (FST::execute(fst10) == -1) { if (visCheck) { vis--; func.pop(); if (func.empty()) { visCheck = false; } } return '}'; }
		else if (FST::execute(fst11) == -1) { entry->priority = 0; type = 3; if (visCheck)vis++; return '('; }
		else if (FST::execute(fst12) == -1) { entry->priority = 0; type = 1; if (visCheck)vis--;  return ')'; }
		else if (FST::execute(fst13) == -1) { entry->priority = 2; return '+'; }
		else if (FST::execute(fst14) == -1) { entry->priority = 2; return '-'; }
		else if (FST::execute(fst15) == -1) { entry->priority = 3; return '*'; }
		else if (FST::execute(fst16) == -1) { entry->priority = 3; return '/'; }
		else if (FST::execute(fst17) == -1) return '=';
		else {
			if (FST::execute(fst18) == -1) { type = 4; DataType = 1; }
			if (ltHaveLex(*idtable, lexem)) {
				entry->idxTI = ltHaveLex(*idtable, lexem);
				if (IT::GetEntry(*idtable,ltHaveLex(*idtable,lexem)).idtype == 4) { return LEX_LITERAL; }
				else { return 'i'; }
			}
			else {
				
				entry->idxTI = *idx;
				entryBuf.idxfirstLE = *idx;
				entryBuf.visibility.visible = vis;
				for (int i = 0; i < ID_MAXSIZE; i++) { entryBuf.id[i] = lexem[i]; }
				//strcpy(entryBuf.id, lexem);
				if (DataType == 1)entryBuf.iddatatype = IT::INT;
				if (DataType == 2)entryBuf.iddatatype = IT::STR;
				entryBuf.value.vint = NULL;
				entryBuf.value.vstr->len = NULL;
				strcpy(entryBuf.value.vstr->str, "");
				switch (type) {
				case 1: {
					entryBuf.idtype = IT::V;
					break;
				}
				case 2: {
					func.push(lexem);
					entryBuf.idtype = IT::F;
					break;
				}
				case 3: {
					entryBuf.idtype = IT::P;
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
					strcpy(entryBuf.value.vstr->str, lexem);
					break;
				}
				default:
					break;
				}
				strcpy(entryBuf.visibility.function, func.top().c_str());
				IT::Add(*idtable, entryBuf);
				(*idx)++;
				if (type == 4) return LEX_LITERAL;
				if (main) { main = false; return MAIN_LITERAL; }
				else return 'i';
			}
		}
	}

	int getSnByPos(LexTable& lex, int pos)
	{
		Entry* element = lex.head;
		for (int i = 0; i < pos; i++)
		{
			if (element->next != NULL)
				element = element->next;
		}
		if (element) return element->sn;
		else return 0;
	}
}