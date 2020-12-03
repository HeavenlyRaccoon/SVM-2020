#pragma once
#include "LT.h"
#include "IT.h"
#include <iostream>
#include "Error.h"

namespace Semantic
{
	bool semAnalyzer(LT::LexTable lt, IT::IdTable it);
	//const char* getType(IT::Entry* element);
}