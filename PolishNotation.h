#pragma once
#include <iostream>
#include "LT.h"
#include "IT.h"

//namespace PN {
//	bool PolishNotation(int lextable_pos, LT::LexTable &lextable, IT::IdTable &idtable);
//}

namespace PN {
	void PolishNotation( // �������� �������� ������
		LT::LexTable& lexTable, // ������� ������
		IT::IdTable& idTable, // ������� ���������������
		bool debug = false
	);
}
