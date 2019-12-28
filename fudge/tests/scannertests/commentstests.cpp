#include "gtest/gtest.h"

#include "input/source.h"
#include "scanner/scanner.h"
#include "scanner/token.h"

#include "scannertests/scannertestutils.h"

using namespace fudge;

TEST(Scanner, ScanLineComments) 
{
	BufferSource source(",//,,\n//,,\n,//");
	Scanner scanner(&source);

	verifyScannedTokens(&scanner, { TokenType::Comma, TokenType::Comma });
}

TEST(Scanner, ScanBlockComments) 
{
	BufferSource source(",/*,,\n*/,/*\n,*/,");
	Scanner scanner(&source);

	verifyScannedTokens(&scanner, { TokenType::Comma, TokenType::Comma, TokenType::Comma });
}

TEST(Scanner, ScanNestedBlockComments) 
{
	BufferSource source(",/*/*,,\n*/,/*\n,*/*/,");
	Scanner scanner(&source);

	verifyScannedTokens(&scanner, { TokenType::Comma, TokenType::Comma });
}
