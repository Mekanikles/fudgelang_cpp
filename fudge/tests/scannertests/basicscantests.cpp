#include "gtest/gtest.h"

#include "input/source.h"
#include "scanner/scanner.h"
#include "scanner/token.h"

#include "scannertests/scannertestutils.h"

using namespace fudge;

TEST(Scanner, EmptyScan) 
{
	BufferSource source("");
	Scanner scanner(&source);

	verifyScannedTokens(&scanner, (TokenType*)nullptr, 0);
}

TEST(Scanner, NonEmptyScan) 
{
	BufferSource source(",");
	Scanner scanner(&source);

	verifyScannedTokens(&scanner, { TokenType::Comma });
}

TEST(Scanner, StringLiteralScan) 
{
	BufferSource source("\"A String\"");
	Scanner scanner(&source);

	verifyScannedTokens(&scanner, { TokenType::StringLiteral });
}
