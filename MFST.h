#pragma once
#include <iostream>
#include <stack>
#include "Greibach.h"
#include "LT.h"

// MFST TRACES
#include <iomanip>

#define MFST_TRACE_START		{std::cout << std::endl						\
								<< std::setw( 4) << std::left << "���" << ":"	\
								<< std::setw(30) << std::left << " �������"		\
								<< std::setw(40) << std::left << "������� �����"\
								<< std::setw(20) << std::left << "����"			\
								<< std::endl;}								

#define MFST_TRACE1				{std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": "\
								<< std::setw(30) << std::left << rule.getCRule(rbuf,nrulechain)	\
								<< std::setw(40) << std::left << getCLenta(lbuf, lenta_position)\
								<< std::setw(20) << std::left << getCSt(sbuf)					\
								<< std::endl;}													

#define MFST_TRACE2				{std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": "\
								<< std::setw(30) << std::left << " "							\
								<< std::setw(40) << std::left << getCLenta(lbuf, lenta_position)\
								<< std::setw(20) << std::left << getCSt(sbuf)					\
								<< std::endl;}													

#define MFST_TRACE3				{std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": "\
								<< std::setw(30) << std::left << " "							\
								<< std::setw(40) << std::left << getCLenta(lbuf, lenta_position)\
								<< std::setw(20) << std::left << getCSt(sbuf)					\
								<< std::endl;}

#define MFST_TRACE4(c)			std::cout << std::setw(4) << std::left << ++ FST_TRACE_n << ": " << std::setw(20) << std::left << c << std::endl;

#define MFST_TRACE5(c)			std::cout << std::setw(4) << std::left <<    FST_TRACE_n << ": " << std::setw(20) << std::left << c <<std::endl;

#define MFST_TRACE6(c,k)		std::cout << std::setw(4) << std::left <<    FST_TRACE_n << ": " << std::setw(20) << std::left << c << k <<  std::endl;

#define MFST_TRACE7				std::cout << std::setw(4) << std::left << state.lenta_position  << ": " \
								<< std::setw(30) << std::left << rule.getCRule(rbuf,state.nrulechain)	\
								<< std::endl;

#define MFST_DIAGN_NUMBER 10
#define MFST_DIAGN_MAXSIZE 255*2
#define ERROR_MAXSIZE_MESSAGE 255

class my_stack_SHORT :public std::stack<short> {
public:
	using std::stack<short>::c; // ���������
};

typedef my_stack_SHORT MFSTSTSTACK;			// ���� ��������

namespace MFST
{
	struct MfstState							// ��������� �������� (��� ����������)
	{
		short lenta_position;					// ������� �� �����
		short nrule;							// ����� �������
		short nrulechain;						// ����� ������� �������, �������� �������
		MFSTSTSTACK st;							// ���� ��������
		MfstState();
		MfstState(
			short pposition,					// ������� �� �����
			MFSTSTSTACK pst,					// ���� ��������
			short pnrulechain					// ����� ������� �������, �������� �������
		);
		MfstState(
			short pposition,					// ������� �� �����
			MFSTSTSTACK pst,					// ���� ��������
			short pnrule,						// ����� �������� �������
			short pnrulechain					// ����� ������� �������, �������� �������
		);
	};

	struct Mfst									// ���������� �������
	{
		enum RC_STEP							// ��� �������� ������� step
		{
			NS_OK,								// ������� ������� � �������, ������� �������� � ����
			NS_NORULE,							// �� ������� ������� � ���������� (������ � ����������)
			NS_NORULECHAIN,						// �� ������� ���������� ������� ������ (������ � �������� ����)
			NS_ERROR,							// ����������� �������������� ������ ����������
			TS_OK,								// �����. ������ ����� == ������� �����, ����� ������������, pop �����
			TS_NOK,								// �����. ������ ����� != ������� �����, �������������� ���������
			LENTA_END,							// ������� ������� ����� >= lenta_size
			SURPRISE							// ����������� ��� �������� (������ � step) xaxax
		};

		struct MfstDiagnosis					// �����������
		{
			short lenta_position;				// ������� �� �����
			RC_STEP rc_step;					// ��� ���������� ����
			short nrule;						// ����� �������
			short nrule_chain;					// ����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(
				short plenta_position,				// ������� �� �����
				RC_STEP prc_step,					// ��� ���������� ����
				short pnrule,						// ����� �������
				short pnrule_chain					// ����� ������� �������
			);
		} diagnosis[MFST_DIAGN_NUMBER];			// ��������� ����� �������� ���������

		class my_stack_MfstState :public std::stack<MfstState> {
		public:
			using std::stack<MfstState>::c; // container
		};

		GRBALPHABET* lenta;						// ���������������� (TS,NS) ����� �� LEX
		short lenta_position;					// ������� ������� �� �����
		short nrule;							// ����� �������� �������
		short nrulechain;						// ����� ������� ������� �������� �������
		short lenta_size;						// ������ �����
		GRB::Greibach greibach;					// ���������� �������
		LT::LexTable lex;						// ��������� ������ ������������ �����������
		LT::Entry* element = lex.head;			// ��������� �� ��������� �������
		MFSTSTSTACK st;							// ���� ��������
		my_stack_MfstState storestate;		// ���� ��� ���������� ���������
		Mfst();
		Mfst(
			LT::LexTable plex,					// ��������� ������ ������������ �����������
			GRB::Greibach pgreibach				// ���������� �������
		);
		char* getCSt(char* buf);				// �������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25); // �����: n �������� � pos
		char* getDiagnosis(short n, char* buf); // �������� n-�� ������ ����������� ��� 0�00
		bool savestate();						// ��������� ��������� ��������
		bool reststate();						// ������������ ��������� ��������
		bool push_chain(						// ��������� ������� ������� � ����
			GRB::Rule::Chain chain				// ������� �������
		);
		RC_STEP step();							// ��������� ��� ��������
		bool start();							// ��������� �������
		bool savediagnosis(
			RC_STEP pprc_step					// ��� ���������� ����
		);
		void printrules();

		struct Deducation
		{
			short size;
			short* nrules;
			short* nrulechains;
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;
		bool savededucation();
	};
}