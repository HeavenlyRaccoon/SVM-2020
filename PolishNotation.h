#pragma once
#include <iostream>
#include "LT.h"
#include "IT.h"

//namespace PN {
//	bool PolishNotation(int lextable_pos, LT::LexTable &lextable, IT::IdTable &idtable);
//}

namespace PN {
	void PolishNotation( // создание польской записи
		LT::LexTable& lexTable, // таблица лексем
		IT::IdTable& idTable, // таблица идентификаторов
		bool debug = false
	);
}
