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
#define LEX_OUTPUT		'o' //������� ��� output
#define LEX_OUTPUTLINE	'n' //������� ��� outputline
#define LEX_LOOP		'p' //������� ��� loop
#define LEX_LENGTH		'c'
#define LEX_CONVERT		'q'
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
#define LEX_ASIGN		'='
#define LEX_MODULO		'%'
#define LEX_FUNCPARM	'@'
#define LEX_INC			'x'
#define LEX_DEC			'z'
#define LEX_MORE		'>'
#define LEX_LESS		'<'
#define LEX_EQUAL		'&'
#define LEX_DIFFERENT	'!'
#define LEX_IF			'w'
#define LEX_ELSE		'e'
#define LEX_LEFTSQUARE	'['
#define LEX_RIGHTSQUARE	']'
#define LT_FUNCTION_MAX_PARMS 3



namespace LT {
	struct Entry {
		char lexema[LEXEMA_FIXSIZE];
		int sn;
		int lineInTxt;
		int idxTI;
		int priority;
		Entry* next = nullptr;
		int numIf;
		int numLoop;
		struct funcParms
		{
			char* funcName;
			int count;
			int idx[LT_FUNCTION_MAX_PARMS];
		} func;
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