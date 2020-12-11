#pragma once
#include "Greibach.h"
#define GRB_ERROR_SERIES 600

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'),
		9,
		Rule(NS('S'), GRB_ERROR_SERIES + 0, // ошибка в структуре
			4, // S -> m{NrE;}; | tfi(F){NrE;};S | tfi(F){NrE;}; | m{NrE;};S
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1, // ошибка в операторах
			25, // N -> dti; | rE; | i=E; | dti;N | i=E;N | dti=E; | dti=E;N | o/nl; | o/ni; | o/nl;N| o/ni;N | iI; | iI;N | w(B)[N]; | w(B)[N];N |
				// w(B)[N]e[N]; | w(B)[N]e[N];N | p(i)[N]; | p(i)[N];N | p(l)[N]; | p(l)[N];N |
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('o'), TS('l'), TS(';')),
			Rule::Chain(3, TS('o'), TS('i'), TS(';')),
			Rule::Chain(4, TS('o'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(4, TS('o'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(3, TS('n'), TS('l'), TS(';')),
			Rule::Chain(3, TS('n'), TS('i'), TS(';')),
			Rule::Chain(4, TS('n'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(4, TS('n'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(3, TS('i'), NS('I'), TS(';')),
			Rule::Chain(4, TS('i'), NS('I'), TS(';'), NS('N')),
			Rule::Chain(8, TS('w'), TS('('), NS('B'), TS(')'), TS('['), NS('N'), TS(']'), TS(';')),
			Rule::Chain(9, TS('w'), TS('('), NS('B'), TS(')'), TS('['), NS('N'), TS(']'), TS(';'), NS('N')),
			Rule::Chain(12, TS('w'), TS('('), NS('B'), TS(')'), TS('['), NS('N'), TS(']'), TS('e'), TS('['), NS('N'), TS(']'), TS(';')),
			Rule::Chain(13, TS('w'), TS('('), NS('B'), TS(')'), TS('['), NS('N'), TS(']'), TS('e'), TS('['), NS('N'), TS(']'), TS(';'), NS('N')),
			Rule::Chain(8, TS('p'), TS('('), TS('i'), TS(')'), TS('['), NS('N'), TS(']'), TS(';')),
			Rule::Chain(9, TS('p'), TS('('), TS('i'), TS(')'), TS('['), NS('N'), TS(']'), TS(';'), NS('N')),
			Rule::Chain(8, TS('p'), TS('('), TS('l'), TS(')'), TS('['), NS('N'), TS(']'), TS(';')),
			Rule::Chain(9, TS('p'), TS('('), TS('l'), TS(')'), TS('['), NS('N'), TS(']'), TS(';'), NS('N'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, // ошибка в выражении 
			14,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('i'), NS('I')),
			Rule::Chain(4, TS('i'), NS('I'), NS('M')),
			Rule::Chain(4, TS('c'), TS('('), TS('l'), TS(')')),
			Rule::Chain(4, TS('c'), TS('('), TS('i'), TS(')')),
			Rule::Chain(4, TS('q'), TS('('), TS('i'), TS(')')),
			Rule::Chain(4, TS('q'), TS('('), TS('l'), TS(')'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 3, // ошибка в выражении
			5,
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('%'), NS('E')),
			Rule::Chain(2, TS('/'), NS('E'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 4, // ошибка в параметрах функции
			2,		//F -> ti | ti,F
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 5, // ошибка в параметрах вызываемой функции
			4,		//W -> i | l | i,W | l,W
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('B'), GRB_ERROR_SERIES + 6, // ошибка в логическом выражении
			2,		
			Rule::Chain(2, TS('i'), NS('L')),
			Rule::Chain(2, TS('l'), NS('L'))
		),
		Rule(NS('L'), GRB_ERROR_SERIES + 6, // ошибка в логическом выражении
			8,
			Rule::Chain(2, TS('>'), TS('i')),
			Rule::Chain(2, TS('<'), TS('i')),
			Rule::Chain(2, TS('&'), TS('i')),
			Rule::Chain(2, TS('!'), TS('i')),
			Rule::Chain(2, TS('>'), TS('l')),
			Rule::Chain(2, TS('<'), TS('l')),
			Rule::Chain(2, TS('&'), TS('l')),
			Rule::Chain(2, TS('!'), TS('l'))
		),
		Rule(NS('I'), GRB_ERROR_SERIES + 3, // ошибка в выражении
			2,		//W -> i | l | i,W | l,W
			Rule::Chain(1, TS('x')),
			Rule::Chain(1, TS('z'))
		)
	);
}
