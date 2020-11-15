#include "pch.h"
#include "IT.h"
#include "Error.h"
#pragma warning(disable : 4996)

namespace IT {
	IdTable Create(int size) {
		if (size <= TI_MAXSIZE) {
			IdTable *idtable = new IdTable;
			idtable->maxsize = size;
			idtable->size = 0;
			idtable->table = new Entry;
			idtable->head = idtable->table;
			return *idtable;
		}
		else {
			throw ERROR_THROW(114);
		}
	}
	void Add(IdTable& idtable, Entry entry) {
		if (idtable.table != nullptr) {
			idtable.size++;
			if (idtable.size > idtable.maxsize) {
				throw ERROR_THROW(116);
			}
			strcpy(idtable.table->visibility.function, entry.visibility.function);
			idtable.table->idxfirstLE = entry.idxfirstLE;
			idtable.table->visibility.visible = entry.visibility.visible;
			for (int i = 0; i < ID_MAXSIZE; i++) { idtable.table->id[i] = entry.id[i]; }
			idtable.table->id[ID_MAXSIZE] = '\0';
			idtable.table->iddatatype = entry.iddatatype;
			idtable.table->idtype = entry.idtype;
			idtable.table->value.vint = entry.value.vint;
			idtable.table->value.vstr->len = entry.value.vstr->len;
			strcpy(idtable.table->value.vstr->str, entry.value.vstr->str);
			idtable.table->next = new Entry;
			idtable.table = idtable.table->next;
			idtable.table->next = nullptr;
		}
		else {
			throw ERROR_THROW(115);
		}
	}

	Entry GetEntry(IdTable& idtable, int n) {
		Entry *value = idtable.head;
		int pos = 1;
		while (value) {
			if (pos == n) {
				return *value;
			}
			else {
				value = value->next;
				pos++;
			}
		}
		throw ERROR_THROW(117);
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		Entry *value = idtable.head;
		while (value){
			if (strcmp(value->id, id) == 0) {
				return value->idxfirstLE;
			}
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable) {
		delete &idtable;
	}
}