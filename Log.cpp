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
		tm local; //временная струкутра
		time_t currentTime;
		currentTime = time(NULL); //считываем текущее время
		localtime_s(&local, &currentTime); //преобразуем время, к временной структуре
		strftime(date, 100, "%d.%m.%Y %H:%M:%S", &local);//Вытягиваем из структуры данные, преобразуем по формату и кладем в date
		*log.stream << "--- Протокол --- Дата: " << date << '\n';
	}

	void WriteParm(LOG log, Parm::PARM parm) {
		*log.stream << "--- Параметры --- " << '\n';
		*log.stream << "-in : " << parm.in << '\n';
		*log.stream << "-out: " << parm.out << '\n';
		*log.stream << "-log: " << parm.log << '\n';
	}

	void WriteIn(LOG log, In::IN in) {

		*log.stream << "--- Исходные данные --- " << endl;
		*log.stream << "Количество символов : " << in.size << endl;
		*log.stream << "Количество строк    : " << in.lines << endl;
		*log.stream << "Проигнорировано     : " << in.ignor << endl;
	}
	void WriteError(LOG log, Error::ERROR error) {

		*log.stream << "Ошибка " << error.id << ":" << error.message << endl;

		if (error.inext.line != -1&&error.inext.col==-1) {
			*log.stream << "Строка " << error.inext.line << endl << endl;
		}
		else if (error.inext.line != -1 && error.inext.col != -1) {
			*log.stream << "Строка " << error.inext.line << " позиция: " << error.inext.col << endl << endl;
		}
	}
	void Close(LOG log) {
		log.stream->close();
		delete log.stream;
	}
}