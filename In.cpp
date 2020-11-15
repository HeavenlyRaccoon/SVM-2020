#include "pch.h"
#include <fstream>
#include <string>
#include "Error.h"
#include "In.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#pragma warning(disable : 4996)
#define MAX_LEXEM_LENGTH 1000

namespace In {
	

	bool addSpaces(string &code, char symbol)
	{
		const char* symbols = "(),;-+*=/{}";
		for (int i = 0; i < strlen(symbols); i++) {
			if (symbol == symbols[i]) {
				code = code + " " + symbol + " ";
				return true;
			}
		}
		return false;
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
		while (value->next!=nullptr) {
			if (value->sn != i) {
				i++;
				continue;
			}
			cout << j << '\t';
			while (value->sn == i) {
				cout << value->lexema[0];
				if (value->lexema[0] == 'i'||value->lexema[0]=='l') {
					cout << "(" << value->idxTI<< ")";
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
		cout << "Номер\t|" << "\tНазвание\t|" << "\tТип данных\t|" << "\tТип идентификатора\t|" << "\tУровень видимости\t|" <<"\t\tФункция\t\t|"<< "\tЗначение" << endl;
		while (value->next != nullptr) {
			cout << value->idxfirstLE << "\t|\t"<<value->id<< "\t\t|\t" <<value->iddatatype<< "\t\t|\t\t" <<value->idtype<< "\t\t|\t\t" <<value->visibility.visible<<"\t\t|\t\t"<<value->visibility.function << "\t\t|\t" <<value->value.vstr->str;
			value = value->next;
			cout << '\n';
		}
	}

	IN getin(char infile[], char outfile[], LT::LexTable &lextable, IT::IdTable &idtable) {

		IN in;
		in.text = new char[IN_MAX_LEN_TEXT];
		in.lines = 0;
		in.ignor = 0;
		in.size = 0;
		int countHesis = 0;
		string timeCode = "";
		string str;
		bool _literal = false;
		ifstream file(infile);
		if (!file.is_open()) {
			throw ERROR_THROW(110);
		}

		

		while (getline(file,str))
		{
			in.lines++;
			//if (!str[0]) {//проверка на пустую строку
			//	continue;
			//}


			for (int i = 0, size = 0, space = 0, sizeStr = str.length(); i < sizeStr; i++, size++) {

				//проверка на литерал
				if (str[i] == '\"' || str[i] == '\'') {
					_literal ? _literal = false : _literal = true;
				}
				//если это литерал то заменяем пробел на _
				if (str[i] == ' '&&_literal) {
					timeCode += '_';
					continue;
				}

				//добавляем пробелы до и после спец знаков
				if (addSpaces(timeCode, str[i])) {
					continue;
				}

				if (IN_CODE_TABLE[(unsigned char)str[i]] == F) {
					throw ERROR_THROW_IN(111, in.lines , size+1 );
				}
				else if (IN_CODE_TABLE[(unsigned char)str[i]] == T) {
					timeCode += str[i];
					in.size++;
				}
				else if (IN_CODE_TABLE[(unsigned char)str[i]] == I) {
					in.ignor++;
					size--;
				}
				else {
					timeCode += str[i];
					in.size++;
				}
			}
			timeCode += "\n";
			in.size++;
		}

		//создаем out файл
		ofstream out(outfile);
		out << timeCode;
		out.close();

		//создаем таблицу лексем
		
		int* linePosition = getLineNums(timeCode);
		char* lexem = strtok(&timeCode[0], " \n");
		for (int idx=1,i=0; lexem != NULL;i++) {
			
			LT::Entry entryBuf;
			entryBuf.lexema[0] = LT::compareLexem(lexem, &idx, &entryBuf, &idtable);
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
		/*
		ofstream out(outfile);
		char* regular = strtok(in.text, "\n");
		short size = 0, position;
		while (regular != NULL) {
			FST::FST fst1(regular, 12,		// недетерминированный конечный автомат a;( )*b( )*(e(f+g);)+( )*c;
				FST::NODE(1, FST::RELATION('a', 1)),
				FST::NODE(1, FST::RELATION(';', 2)),
				FST::NODE(3, FST::RELATION(' ', 3), FST::RELATION(' ', 2), FST::RELATION('b', 4)),
				FST::NODE(1, FST::RELATION('b', 4)),
				FST::NODE(3, FST::RELATION(' ', 5), FST::RELATION(' ', 4), FST::RELATION('e', 6)),
				FST::NODE(1, FST::RELATION('e', 6)),
				FST::NODE(2, FST::RELATION('f', 7), FST::RELATION('g', 7)),
				FST::NODE(1, FST::RELATION(';', 8)),
				FST::NODE(4, FST::RELATION(' ', 9), FST::RELATION(' ', 8), FST::RELATION('c', 10), FST::RELATION('e', 6)),
				FST::NODE(1, FST::RELATION('c', 10)),
				FST::NODE(1, FST::RELATION(';', 11)),
				FST::NODE()
			);
			position = FST::execute(fst1);
			if (position == -1) {
				out << "Цепочка " << fst1.string << " распознана" << '\n';
			}
			else {
				out << "Цепочка " << fst1.string << " не распознана " << '\n';
				throw ERROR_THROW_IN(113, size, position + 1);
			}
			regular = strtok(NULL, "\n|");
			size++;
		}
		
		out.close(); */
		return in;
	}
}