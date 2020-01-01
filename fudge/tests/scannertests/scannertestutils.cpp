#include "scannertestutils.h"

#include "gtest/gtest.h"

void verifyScannedTokens(Scanner* scanner, const TokenType* expectedTokens, int tokenCount)
{
	for (int p = 0; p < tokenCount; ++p)
	{
		Token token = scanner->readToken();
		EXPECT_EQ(token.type, expectedTokens[p]);
	}

	Token token = scanner->readToken();
	EXPECT_EQ(token.type, TokenType::EndOfScan);
}

void scanToEnd(Scanner* scanner)
{
	Token token;
	do
	{
		token = scanner->readToken();
	} while (token.type != TokenType::EndOfScan);
}