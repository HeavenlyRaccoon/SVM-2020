#pragma once
#include "pch.h"
#include "In.h"
#include "IT.h"
#include "LT.h"
#include "Error.h"
#include "FST.h"
#include <stack>
#include <sstream>
#define MAX_LEXEM_LENGTH 1000

namespace CreateT {

	void fillTable(string text, LT::LexTable &lextable, IT::IdTable &idtable);
	int* getLineNums(string code);
	void makeOutLt(LT::LexTable &lextable);
	void makeOutIT(IT::IdTable &idtable);
	char compareLexem(char* lexem, int *idx, LT::Entry* entry, IT::IdTable *idtable);
	int ltHaveLex(IT::IdTable idtable, char *lexem);
}