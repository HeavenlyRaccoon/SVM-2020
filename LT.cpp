#include "pch.h"
#include "LT.h";
#include "IT.h";
#include "Error.h";
#include "FST.h"
#pragma warning(disable : 4996)

namespace LT {
	//создание таблицы
	LexTable Create(int size) {
		if (size <= LT_MAXSIZE) {
			LexTable *lextable = new LexTable;
			lextable->maxsize = size;
			lextable->size = 0;
			lextable->table = new Entry;
			lextable->head = lextable->table;
			return *lextable;
		}
		else {
			throw ERROR_THROW(118);
		}
		
	}

	//добавление строки в таблицу
	void Add(LexTable& lextable, Entry entry) {
		if (lextable.table != nullptr) {
			lextable.size++;
			if (lextable.size > lextable.maxsize) {
				throw ERROR_THROW(120);
			}

			lextable.table->lexema[0] = entry.lexema[0];
			lextable.table->sn = entry.sn;
			lextable.table->idxTI = entry.idxTI;
			lextable.table->priority = entry.priority;
			lextable.table->next = new Entry;
			lextable.table = lextable.table->next;
			lextable.table->next = nullptr;
		}
		else {
			throw ERROR_THROW(119);
		}
	}

	//возварщение строки таблицы
	Entry* GetEntry(LexTable& lextable, int n) {
		Entry *value = lextable.head;
		int pos = 0;
		while (value) {
			if (pos == n) {
				return value;
			}
			else {
				value = value->next;
				pos=value->sn;
			}
		}
		throw ERROR_THROW(121);
	}

	//удаление таблицы
	void Delete(LexTable& lextable) {
		delete &lextable;
	}

	int getSnByPos(LexTable& lex, int pos)
	{
		Entry* element = lex.head;
		for (int i = 0; i < pos; i++)
		{
			if (element->next != NULL)
				element = element->next;
		}
		if (element) return element->sn;
		else return 0;
	}
}