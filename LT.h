#pragma once
#include "IT.h"
#include <stack>

#define LEXEMA_FIXSIZE	1			//фикс размер лексемы
#define FUNCTIONSIZE	20
#define LT_MAXSIZE		4096		//макс количество строк в таблице лексем
#define LT_TI_NULLIDX	0xffffffff	// нет элемента таблицы идентификаторов
#define LEX_INTEGER		't' //лексема для integer
#define LEX_STRING		't'	//лексема для string
#define LEX_ID			'i' //лексема для идентификатора
#define LEX_LITERAL		'l' //лексема для литерала
#define MAIN_LITERAL	'm' //лексема для точки входа
#define LEX_FUNCTION	'f'	//лексема для function
#define LEX_DECLARE		'd'	//лексема для declare
#define LEX_RETURN		'r'	//лексема для return
#define LEX_PRINT		'p' //лексема для print
#define LEX_SEMICOLON	';'
#define LEX_COMMA		','
#define LEX_LEFTBRACE	'{'
#define LEX_BRACELET	'}'
#define LEX_LEFTHESIS	'('
#define LEX_RIGHTHESIS	')'
#define LEX_PLUS		'+'
#define LEX_MINUS		'-'
#define LEX_STAR		'*'
#define LEX_DIRSLASH	'/'



namespace LT {
	struct Entry {
		char lexema[LEXEMA_FIXSIZE];
		int sn;
		int lineInTxt;
		int idxTI;
		int priority;
		Entry* next = nullptr;
	};

	struct LexTable {
		int maxsize;
		int size;
		Entry* table;
		Entry* head;
	};


	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry* GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
	int getSnByPos(LexTable& lex, int pos);
}