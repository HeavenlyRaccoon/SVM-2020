#pragma once
#include "IT.h"
#include"LT.h"
#define IN_MAX_LEN_TEXT 1024*1024 //макс. размер исходника 1мб
#define IN_CODE_ENDL '|'

// таблица проверки входной информации, индекс = код (windows-1251) символа
// значения In::F - запрещенный символ, IN::T - разрешенный символ, IN::I - игонрировать (не вводить),
// если 0 <= значение < 256 - то вводится данное значение

namespace In {
	enum { T = 1024, F = 2048, I = 4096 };
	struct IN {
		int size;
		int lines;
		int ignor;
		char* text;
	};
	IN getin(char infile[], char outfile[], LT::LexTable &lextable, IT::IdTable &idtable);
	void makeOutLt(LT::LexTable &lextable);

	const unsigned short IN_CODE_TABLE[256] = {
		//0      //1      //2      //3       //4      //5       //6      //7      //8      //9      //A      //B      //C      //D      //E      //F
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::I,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//0
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//1
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//2
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//3
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//4
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//5
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//6
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T, //7

		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//8
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//9
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//A
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//B
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//C
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,	//D
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T, //E
		In::T,   In::T,   In::T,   In::T,	 In::T,	  In::T,    In::T,	 In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T,   In::T 	//F
	};
}