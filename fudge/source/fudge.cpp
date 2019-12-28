#include "fudge/fudge.h"

#include <iostream>

#include "input/source.h"
#include "scanner/scanner.h"
#include "parser/parser.h"

namespace fudge
{

void run_file(const string& filename)
{
	FileSource source(filename);
	Scanner scanner(&source);
	Parser parser(&scanner);
}

}