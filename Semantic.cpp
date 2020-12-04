#include "Semantic.h"

namespace Semantic {
	struct flag
	{
		bool func = false;
		bool ret = false;
		int funcType = NULL;
		int idtype = NULL;
		bool asign = false;
	};

	bool semAnalyzer(LT::LexTable lt, IT::IdTable it) {
		LT::Entry *lextable = lt.head;
		IT::Entry idtable;
		flag f;
		int position=0;
		while (lextable->next) {
			switch (lextable->lexema[0])
			{
			case LEX_ID: {
				idtable = IT::GetEntry(it, lextable->idxTI);
				if (!idtable.declared) {
					throw ERROR_THROW_IN(123, lextable->sn, position);
					std::cout << "Переменная не инициализирована!";
				}
				if (f.func) {
					f.funcType = idtable.iddatatype;
					f.func = false;
				}
				if (f.ret) {
					if (f.funcType != idtable.iddatatype) {
						throw ERROR_THROW_IN(124, lextable->sn, position);
					}
					else { f.ret = false; }
				}
				if (lextable->next->lexema[0] == LEX_ID) {
					if (idtable.iddatatype != IT::GetEntry(it, lextable->next->idxTI).iddatatype) {
						throw ERROR_THROW_IN(125, lextable->sn, position);
					}
				}
				if (f.asign) {
					if (f.idtype != idtable.iddatatype) {
						throw ERROR_THROW_IN(125, lextable->sn, position);
					}
					else
					{
						f.asign = false;
					}
				}
				f.idtype = idtable.iddatatype;
				break;
			}
			case LEX_LITERAL: {
				idtable = IT::GetEntry(it, lextable->idxTI);
				if (f.asign) {
					if (f.idtype != idtable.iddatatype) {
						throw ERROR_THROW_IN(125, lextable->sn, position);
					}
					else
					{
						f.asign = false;
					}
				}
				break;
			}
			case LEX_FUNCPARM: {
				idtable = IT::GetEntry(it, lextable->idxTI);
				if (f.asign) {
					if (f.idtype != idtable.iddatatype) {
						throw ERROR_THROW_IN(125, lextable->sn, position);
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
					throw ERROR_THROW_IN(126, lextable->sn, position);
				}
				break;
			}
			default:
				break;
			}
			if (lextable->sn != lextable->next->sn) {
				position = 0;
			}
			else {
				position++;
			}
			lextable = lextable->next;
		}
		return true;
	}
}