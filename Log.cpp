#include "pch.h"
#include "Log.h"
#include <ctime>
namespace Log {
	LOG getlog(char logfile[]) {
		LOG log;
		log.stream = new std::ofstream(logfile);
		if (!log.stream->is_open()) {
			throw ERROR_THROW(112);
		}
		for (int i = 0, size = strlen(logfile); i < size; i++) {
			log.logfile[i] = logfile[i];
		}
		log.logfile[strlen(log.logfile)] = '\0';
		return log;
	}

	void WriteLine(LOG log, const char* c, ...) {
		const char** pc = &c;
		while (*pc != "") {
			*log.stream << *pc;
			pc++;
		}
		*log.stream << '\n';
	}

	void WriteLine(LOG log, const wchar_t* c, ...) {
		const wchar_t** pc = &c;
		while (*pc != L"") {
			const int SIZE = 10;
			char buff[SIZE];
			size_t tsize = 0;
			wcstombs_s(&tsize, buff, *pc, SIZE);
			*log.stream << buff;
			pc++;
		}
		*log.stream << '\n';
	}

	void WriteLog(LOG log) {
		char date[100];
		tm local; //��������� ���������
		time_t currentTime;
		currentTime = time(NULL); //��������� ������� �����
		localtime_s(&local, &currentTime); //����������� �����, � ��������� ���������
		strftime(date, 100, "%d.%m.%Y %H:%M:%S", &local);//���������� �� ��������� ������, ����������� �� ������� � ������ � date
		*log.stream << "--- �������� --- ����: " << date << '\n';
	}

	void WriteParm(LOG log, Parm::PARM parm) {
		*log.stream << "--- ��������� --- " << '\n';
		*log.stream << "-in : " << parm.in << '\n';
		*log.stream << "-out: " << parm.out << '\n';
		*log.stream << "-log: " << parm.log << '\n';
	}

	void WriteIn(LOG log, In::IN in) {

		*log.stream << "--- �������� ������ --- " << endl;
		*log.stream << "���������� �������� : " << in.size << endl;
		*log.stream << "���������� �����    : " << in.lines << endl;
		*log.stream << "���������������     : " << in.ignor << endl;
	}
	void WriteError(LOG log, Error::ERROR error) {

		*log.stream << "������ " << error.id << ":" << error.message << endl;

		if (error.inext.line != -1&&error.inext.col==-1) {
			*log.stream << "������ " << error.inext.line << endl << endl;
		}
		else if (error.inext.line != -1 && error.inext.col != -1) {
			*log.stream << "������ " << error.inext.line << " �������: " << error.inext.col << endl << endl;
		}
	}
	void Close(LOG log) {
		log.stream->close();
		delete log.stream;
	}
}