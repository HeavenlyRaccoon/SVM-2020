#pragma once
#include "IT.h"
#include <stack>

#define LEXEMA_FIXSIZE	1			//���� ������ �������
#define FUNCTIONSIZE	20
#define LT_MAXSIZE		4096		//���� ���������� ����� � ������� ������
#define LT_TI_NULLIDX	0xffffffff	// ��� �������� ������� ���������������
#define LEX_INTEGER		't' //������� ��� integer
#define LEX_STRING		't'	//������� ��� string
#define LEX_ID			'i' //������� ��� ��������������
#define LEX_LITERAL		'l' //������� ��� ��������
#define MAIN_LITERAL	'm' //������� ��� ����� �����
#define LEX_FUNCTION	'f'	//������� ��� function
#define LEX_DECLARE		'd'	//������� ��� declare
#define LEX_RETURN		'r'	//������� ��� return
#define LEX_PRINT		'p' //������� ��� print
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