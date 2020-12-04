#include "pch.h"
#include <fstream>
#include <string>
#include "Error.h"
#include "In.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#pragma warning(disable : 4996)

namespace In {
	

	bool addSpaces(string &code, char symbol)
	{
		const char* symbols = "(),;-+*=/{}%[]<>!&";
		for (int i = 0; i < strlen(symbols); i++) {
			if (symbol == symbols[i]) {
				code = code + " " + symbol + " ";
				return true;
			}
		}
		return false;
	}

	IN getin(char infile[], char outfile[]) {

		IN in;
		in.lines = 0;
		in.ignor = 0;
		in.size = 0;
		in.text = "";
		string str;
		bool _literal = false;
		ifstream file(infile);
		if (!file.is_open()) {
			throw ERROR_THROW(110);
		}

		while (getline(file,str))
		{
			in.lines++;

			for (int i = 0, size = 0, space = 0, sizeStr = str.length(); i < sizeStr; i++, size++) {

				//проверка на литерал
				if (str[i] == '\"' || str[i] == '\'') {
					_literal ? _literal = false : _literal = true;
				}
				//если это литерал то заменяем пробел на _
				if (str[i] == ' '&&_literal) {
					in.text += '_';
					continue;
				}

				//добавляем пробелы до и после спец знаков
				if ((str[i] == '+'&&str[i + 1] == '+') || (str[i] == '-'&&str[i + 1] == '-')) {
					in.text = in.text + " " + str[i] + str[i + 1] + " ";
					i = i + 1;
					continue;
				}
				else if (addSpaces(in.text, str[i])) {
					continue;
				}

				if (IN_CODE_TABLE[(unsigned char)str[i]] == F) {
					throw ERROR_THROW_IN(111, in.lines , size+1 );
				}
				else if (IN_CODE_TABLE[(unsigned char)str[i]] == T) {
					in.text += str[i];
					in.size++;
				}
				else if (IN_CODE_TABLE[(unsigned char)str[i]] == I) {
					in.ignor++;
					size--;
				}
				else {
					in.text += str[i];
					in.size++;
				}
			}
			in.text += "\n";
			in.size++;
		}

		//создаем out файл
		ofstream out(outfile);
		out << in.text;
		out.close();
		return in;
	}
}