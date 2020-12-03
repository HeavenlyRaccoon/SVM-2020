#include "LT.h"
#include "IT.h"

#include <iostream>
#include <stack>
#include "PolishNotation.h"
#pragma warning(disable : 4996)
//namespace PN
//{
//	struct polishNotation
//	{
//		LT::Entry* result;
//		LT::Entry* resultHead;
//		std::stack <LT::Entry> symbols;
//
//		polishNotation()
//		{
//			result = nullptr;
//			resultHead = nullptr;
//		}
//	};
//
//	bool isSymbol(LT::Entry* element);
//	void addRusult(polishNotation& p, LT::Entry* element);
//
//	bool PolishNotation( // создание польской записи
//		int lextable_pos, // позици€ выражени€ в таблице лексем
//		LT::LexTable& lexTable, // таблица лексем
//		IT::IdTable& idTable // таблица идентификаторов
//	)
//	{
//		polishNotation pol;
//		LT::Entry *sourceStr = LT::GetEntry(lexTable, lextable_pos);
//		LT::Entry* nextLine = LT::GetEntry(lexTable, lextable_pos + 1);
//		LT::Entry* head = sourceStr;
//
//		LT::Entry* beforePN = sourceStr;
//		std::cout << "ƒо ѕольской записи:" << std::endl;
//		while (beforePN->sn == lextable_pos)
//		{
//			std::cout << beforePN->lexema[0];
//			beforePN = beforePN->next;
//		}
//		std::cout << std::endl;
//
//		// algorithm
//
//		while (sourceStr->sn == lextable_pos)
//		{
//			/*if (sourceStr->lexema[0] == 'f') {
//				std::cout << "польска€ запись не построена\n";
//				lextable_pos++;
//				break;
//			}*/
//			if (!isSymbol(sourceStr))
//			{
//				if (sourceStr->lexema[0] == ';')
//				{
//					while (!pol.symbols.empty())
//					{
//						addRusult(pol, &pol.symbols.top()); // добавл€ем в резалт наши знаки
//						pol.symbols.pop(); // убираем эти знаки из стека
//					}
//				}
//				addRusult(pol, sourceStr); // если идентификатор то кидаем в резалт
//			}
//			else
//			{
//				if (sourceStr->lexema[0] == LEX_RIGHTHESIS) // если встречаем ), то
//				{
//					while (pol.symbols.top().lexema[0] != LEX_LEFTHESIS) // пока не встретим (
//					{
//						addRusult(pol, &pol.symbols.top()); // добавл€ем в резалт наши знаки
//						pol.symbols.pop(); // убираем эти знаки из стека
//					}
//					pol.symbols.pop(); // удал€ем (
//				}
//				else
//				{
//					if (!pol.symbols.empty())
//					{
//						while ((pol.symbols.top().priority >= sourceStr->priority) && sourceStr->priority != 0)
//						{
//							addRusult(pol, &pol.symbols.top()); // добавл€ем в резалт наши знаки
//							pol.symbols.pop(); // убираем эти знаки из стека
//							if (pol.symbols.empty()) break;
//						}
//					}
//					pol.symbols.push(*sourceStr); // иначе добавл€ем символ в стек
//				}
//			}
//			sourceStr = sourceStr->next;
//		}
//
//
//
//		std::cout << "\nѕосле ѕольской записи:" << std::endl;
//		LT::Entry* out = pol.resultHead;
//		while (out != nullptr)
//		{
//			std::cout << out->lexema[0];
//			out = out->next;
//		}
//		std::cout << std::endl;
//
//
//		// ISSUE: утечка пам€ти, удал€ть lextable
//
//		head->idxTI = pol.resultHead->idxTI;
//		head->lexema[0] = pol.resultHead->lexema[0];
//		head->priority = pol.resultHead->priority;
//		head->sn = pol.resultHead->sn;
//
//		head->next = pol.resultHead->next;
//		while (head->next != nullptr) head = head->next;
//		head->next = nextLine;
//		return true;
//	}
//
//	void addRusult(polishNotation& p, LT::Entry* element)
//	{
//		if (p.result == nullptr)
//		{
//			p.result = new LT::Entry();
//			p.resultHead = p.result;
//		}
//		else
//		{
//			p.result->next = new LT::Entry();
//			p.result = p.result->next;
//		}
//
//		p.result->idxTI = element->idxTI;
//		p.result->lexema[0] = element->lexema[0];
//		p.result->sn = element->sn;
//	}
//
//	bool isSymbol(LT::Entry* element)
//	{
//		const char* s = "(),+-*/"; // ISSUES: add []
//
//		for (int i = 0; i < strlen(s); i++)
//		{
//			if (element->lexema[0] == s[i]) return true;
//		}
//		return false;
//	}
//}
namespace PN
{
	void addResult(LT::Entry& result, LT::Entry& lentaElement, IT::IdTable& idTable);
	void addResult(LT::Entry& result, LT::Entry& lentaElement, bool memory = false);
	void addToStack(std::stack<LT::Entry*>& stack, LT::Entry* result, LT::Entry* element);

	void PolishNotation( // создание польской записи
		LT::LexTable& lexTable, // таблица лексем
		IT::IdTable& idTable, // таблица идентификаторов
		bool debug // вывод польской записи
	)
	{
		LT::Entry *lenta = LT::GetEntry(lexTable, 0);
		std::stack<LT::Entry*> stack;

		while (lenta->next != NULL)
		{
			if (lenta->lexema[0] == LEX_ASIGN || lenta->lexema[0] == LEX_RETURN)
			{
				// обработка польской записи
				LT::Entry* result = new LT::Entry();
				LT::Entry* resultHead = new LT::Entry();
				LT::Entry* unionChain = lenta->next;	// символ после равно, который мы потом заменим на resultHead 
														// чтобы сцепить цепочки

				bool saved = false;

				while (lenta->lexema[0] != LEX_SEMICOLON)
				{
					if (result->lexema[0] != NULL && saved) result = result->next;


					lenta = lenta->next;
					switch (lenta->lexema[0])
					{
					case LEX_ID:
					case LEX_LITERAL:
						addResult(*result, *lenta, idTable);
						if (!saved)
						{
							resultHead = result;	// сохран€ю начало цепочки
							saved = true;
						}
						result = result->next;
						break;
					case LEX_RIGHTHESIS:
					case LEX_LEFTHESIS:
					case LEX_PLUS:
					case LEX_MINUS:
					case LEX_STAR:
					case LEX_MODULO:
					case LEX_DIRSLASH:
					case LEX_SEMICOLON:
						addToStack(stack, result, lenta);
						if (result->lexema[0] != NULL) result = result->next;
						break;
					}
				}
				*unionChain = *resultHead;
				*lenta = *unionChain;
			}
			lenta = lenta->next; // следующее выражение
		}
	}

	void addResult(LT::Entry& result, LT::Entry& lentaElement, IT::IdTable& idTable)
	{
		switch (lentaElement.lexema[0])
		{
		case(LEX_ID):
			if (/*IT::GetEntry(idTable, lentaElement.idxTI)->idtype*/ IT::GetEntry(idTable,lentaElement.idxTI).idtype== IT::F)
			{
				result.func.funcName = new char();
				strcpy(result.func.funcName, IT::GetEntry(idTable, lentaElement.idxTI).id);
				int parms = 0;
				result.idxTI = lentaElement.idxTI;
				result.sn = lentaElement.sn;
				while (lentaElement.lexema[0] != LEX_RIGHTHESIS)
				{
					lentaElement = *lentaElement.next;
					if (lentaElement.lexema[0] == LEX_ID || lentaElement.lexema[0] == LEX_LITERAL)
					{
						result.func.idx[parms] = lentaElement.idxTI;
						parms++;
					}
				}
				result.func.count = parms;
				
				result.lexema[0] = '@';
				result.next = new LT::Entry();
				result.priority = 0;
				break;
			}
		case(LEX_LITERAL):
			result.idxTI = lentaElement.idxTI;
			result.lexema[0] = lentaElement.lexema[0];
			result.priority = lentaElement.priority;
			result.sn = lentaElement.sn;
			result.next = new LT::Entry();
			break;
		}
	}

	void addResult(LT::Entry& result, LT::Entry& lentaElement, bool memory)
	{
		result.idxTI = lentaElement.idxTI;
		result.lexema[0] = lentaElement.lexema[0];
		result.priority = lentaElement.priority;
		result.sn = lentaElement.sn;
		if (!memory) result.next = new LT::Entry();
		else result.next = lentaElement.next;
	}

	void addToStack(std::stack<LT::Entry*>& stack, LT::Entry* result, LT::Entry* element)
	{
		switch (element->lexema[0])
		{
		case LEX_LEFTHESIS:
			stack.push(element);
			break;
		case LEX_RIGHTHESIS:
			while (!stack.empty())
			{
				if (stack.top()->lexema[0] == LEX_LEFTHESIS)
				{
					stack.pop();
					break;
				}
				else
				{
					addResult(*result, *stack.top());
					result = result->next;
					stack.pop();
				}
			}
			break;
		case LEX_PLUS:
		case LEX_MINUS:
			if (stack.empty() || element->priority > stack.top()->priority)
				stack.push(element);
			else
			{
				addResult(*result, *stack.top());
				stack.pop();
				stack.push(element);
			}
			break;
		case LEX_STAR:
		case LEX_DIRSLASH:
		case LEX_MODULO:
			if (stack.empty() || element->priority > stack.top()->priority)
				stack.push(element);
			else
			{
				addResult(*result, *stack.top());
				stack.pop();
				stack.push(element);
			}
			break;
		case LEX_SEMICOLON:
			while (!stack.empty())
			{
				addResult(*result, *stack.top());
				result = result->next;
				stack.pop();
			}
			addResult(*result, *element, true); // св€зываем ; с цепочкой. ќстаЄтс€ св€зать только голову
			break;
		}
	}
}
