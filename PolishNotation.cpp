#include "LT.h"
#include "IT.h"

#include <iostream>
#include <stack>
#include "PolishNotation.h"

namespace PN
{
	struct polishNotation
	{
		LT::Entry* result;
		LT::Entry* resultHead;
		std::stack <LT::Entry> symbols;

		polishNotation()
		{
			result = nullptr;
			resultHead = nullptr;
		}
	};

	bool isSymbol(LT::Entry* element);
	void addRusult(polishNotation& p, LT::Entry* element);

	bool PolishNotation( // создание польской записи
		int lextable_pos, // позици€ выражени€ в таблице лексем
		LT::LexTable& lexTable, // таблица лексем
		IT::IdTable& idTable // таблица идентификаторов
	)
	{
		polishNotation pol;
		LT::Entry *sourceStr = LT::GetEntry(lexTable, lextable_pos);
		LT::Entry* nextLine = LT::GetEntry(lexTable, lextable_pos + 1);
		LT::Entry* head = sourceStr;

		LT::Entry* beforePN = sourceStr;
		std::cout << "ƒо ѕольской записи:" << std::endl;
		while (beforePN->sn == lextable_pos)
		{
			std::cout << beforePN->lexema[0];
			beforePN = beforePN->next;
		}
		std::cout << std::endl;

		// algorithm

		while (sourceStr->sn == lextable_pos)
		{
			/*if (sourceStr->lexema[0] == 'f') {
				std::cout << "польска€ запись не построена\n";
				lextable_pos++;
				break;
			}*/
			if (!isSymbol(sourceStr))
			{
				if (sourceStr->lexema[0] == ';')
				{
					while (!pol.symbols.empty())
					{
						addRusult(pol, &pol.symbols.top()); // добавл€ем в резалт наши знаки
						pol.symbols.pop(); // убираем эти знаки из стека
					}
				}
				addRusult(pol, sourceStr); // если идентификатор то кидаем в резалт
			}
			else
			{
				if (sourceStr->lexema[0] == LEX_RIGHTHESIS) // если встречаем ), то
				{
					while (pol.symbols.top().lexema[0] != LEX_LEFTHESIS) // пока не встретим (
					{
						addRusult(pol, &pol.symbols.top()); // добавл€ем в резалт наши знаки
						pol.symbols.pop(); // убираем эти знаки из стека
					}
					pol.symbols.pop(); // удал€ем (
				}
				else
				{
					if (!pol.symbols.empty())
					{
						while ((pol.symbols.top().priority >= sourceStr->priority) && sourceStr->priority != 0)
						{
							addRusult(pol, &pol.symbols.top()); // добавл€ем в резалт наши знаки
							pol.symbols.pop(); // убираем эти знаки из стека
							if (pol.symbols.empty()) break;
						}
					}
					pol.symbols.push(*sourceStr); // иначе добавл€ем символ в стек
				}
			}
			sourceStr = sourceStr->next;
		}



		std::cout << "\nѕосле ѕольской записи:" << std::endl;
		LT::Entry* out = pol.resultHead;
		while (out != nullptr)
		{
			std::cout << out->lexema[0];
			out = out->next;
		}
		std::cout << std::endl;


		// ISSUE: утечка пам€ти, удал€ть lextable

		head->idxTI = pol.resultHead->idxTI;
		head->lexema[0] = pol.resultHead->lexema[0];
		head->priority = pol.resultHead->priority;
		head->sn = pol.resultHead->sn;

		head->next = pol.resultHead->next;
		while (head->next != nullptr) head = head->next;
		head->next = nextLine;
		return true;
	}

	void addRusult(polishNotation& p, LT::Entry* element)
	{
		if (p.result == nullptr)
		{
			p.result = new LT::Entry();
			p.resultHead = p.result;
		}
		else
		{
			p.result->next = new LT::Entry();
			p.result = p.result->next;
		}

		p.result->idxTI = element->idxTI;
		p.result->lexema[0] = element->lexema[0];
		p.result->sn = element->sn;
	}

	bool isSymbol(LT::Entry* element)
	{
		const char* s = "(),+-*/"; // ISSUES: add []

		for (int i = 0; i < strlen(s); i++)
		{
			if (element->lexema[0] == s[i]) return true;
		}
		return false;
	}
}
