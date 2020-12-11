#include "Semantic.h"

namespace Semantic {
	struct flag
	{
		bool convert = false;
		bool func = false;
		bool ret = false;
		int funcType = NULL;
		int idtype = NULL;
		bool asign = false;
		bool checkIf = false;
		bool checkLoop = false;
		bool leng = false;
	};

	bool semAnalyzer(LT::LexTable lt, IT::IdTable it) {
		LT::Entry *lextable = lt.head;
		IT::Entry idtable;
		flag f;
		while (lextable->next) {
			switch (lextable->lexema[0])
			{
			case LEX_ID: {
				idtable = IT::GetEntry(it, lextable->idxTI);
				if (!idtable.declared) {
					throw ERROR_THROW_LINE(123, lextable->sn);
					std::cout << "Переменная не инициализирована!";
				}
				if (f.func) {
					f.funcType = idtable.iddatatype;
					f.func = false;
				}
				if (f.ret) {
					if (f.funcType != idtable.iddatatype) {
						throw ERROR_THROW_LINE(124, lextable->sn);
					}
					else { f.ret = false; }
				}
				if (lextable->next->lexema[0] == LEX_ID) {
					if (idtable.iddatatype != IT::GetEntry(it, lextable->next->idxTI).iddatatype) {
						throw ERROR_THROW_LINE(125, lextable->sn);
					}
				}
				if (f.leng||f.convert) {
					if (f.idtype == 2) throw ERROR_THROW_LINE(126, lextable->sn)
					else if (idtable.iddatatype == 1) throw ERROR_THROW_LINE(126, lextable->sn)
					else f.leng = false; f.convert = false;
					break;
				}
				if (f.asign) {
					if (f.idtype != idtable.iddatatype) {
						throw ERROR_THROW_LINE(125, lextable->sn);
					}
					else
					{
						f.asign = false;
					}
				}
				if (f.checkLoop) {
					if (idtable.iddatatype == 2) {
						throw ERROR_THROW_LINE(126, lextable->sn);
					}
				}
				if (f.checkIf) {
					if (idtable.iddatatype == 2) {
						throw ERROR_THROW_LINE(126, lextable->sn);
					}
				}
				
				f.idtype = idtable.iddatatype;
				break;
			}
			case LEX_LITERAL: {
				idtable = IT::GetEntry(it, lextable->idxTI);
				if (f.leng||f.convert) {
					if (f.idtype == 2) throw ERROR_THROW_LINE(126, lextable->sn)
					else if (idtable.iddatatype == 1) throw ERROR_THROW_LINE(126, lextable->sn)
					else f.leng = false; f.convert = false;
					break;
				}
				if (f.asign) {
					if (f.idtype != idtable.iddatatype) {
						throw ERROR_THROW_LINE(125, lextable->sn);
					}
					else
					{
						f.asign = false;
					}
				}
				if (f.checkLoop) {
					if (idtable.iddatatype == 2) {
						throw ERROR_THROW_LINE(126, lextable->sn);
					}
				}
				if (f.checkIf) {
					if (idtable.iddatatype == 2) {
						throw ERROR_THROW_LINE(126, lextable->sn);
					}
				}
				
				break;
			}
			case LEX_FUNCPARM: {
				idtable = IT::GetEntry(it, lextable->idxTI);
				if (f.asign) {
					if (f.idtype != idtable.iddatatype) {
						throw ERROR_THROW_LINE(125, lextable->sn);
					}
					else
					{
						f.asign = false;
					}
				}
				break;
			}
			case LEX_FUNCTION: {
				f.func = true;
				break;
			}
			case LEX_LENGTH: {
				f.leng = true;
				break;
			}
			case LEX_CONVERT: {
				f.convert = true;
				break;
			}
			case LEX_RETURN: {
				f.ret = true;
				break;
			}
			case LEX_ASIGN: {
				f.asign = true;
				break;
			}
			case LEX_DIRSLASH:
			case LEX_MINUS:
			case LEX_MODULO:
			case LEX_INC:
			case LEX_DEC:
			case LEX_STAR: {
				if (f.idtype == 2) {
					throw ERROR_THROW_LINE(126, lextable->sn);
				}
				break;
			}
			case LEX_IF: {
				f.checkIf = true;
				break;
			}
			case LEX_LOOP: {
				f.checkLoop = true;
				break;
			}
			case LEX_RIGHTHESIS: {
				if (f.checkIf) {
					f.checkIf = false;
				}
				if (f.checkLoop) {
					f.checkLoop = false;
				}
				break;
			}
			default:
				break;
			}
			lextable = lextable->next;
		}
		return true;
	}
}