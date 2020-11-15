#include "pch.h"
#include <locale>
#include <cwchar>
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "IT.h"
#include "LT.h"
#include "PolishNotation.h"
#include "MFST.h"
#include "CreateT.h"

using namespace std;
int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log = Log::INITLOG;
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		cout << "-in:" << parm.in << endl;
		cout << "-out:" << parm.out << endl;
		cout << "-log:" << parm.log << endl;
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест:", "без ошибок", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);

		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);

		In::IN in = In::getin(parm.in, parm.out);
		CreateT::fillTable(in.text, lextable, idtable);

		MFST_TRACE_START;								// отладка
		MFST::Mfst mfst(lextable, GRB::getGreibach()); 	// автомат

		mfst.start();
		mfst.savededucation();
		mfst.printrules();

		bool a = PN::PolishNotation(3, lextable, idtable);
		CreateT::makeOutLt(lextable);

		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e) {
		cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
		if (e.inext.line != -1) {
			cout << "строка " << e.inext.line << " позиция " << e.inext.col << endl << endl;
		}
		Log::WriteError(log, e);
	}
}

