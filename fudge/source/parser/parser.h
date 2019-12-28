#pragma once
#include "core/core.h"

namespace fudge
{

class Scanner;

class Parser
{
public:	
	Parser(Scanner* scanner)
		: m_scanner(scanner)
	{}

private:
	Scanner* const m_scanner;
};

}