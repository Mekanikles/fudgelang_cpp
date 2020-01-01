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

TEST(Scanner, ScanMismatchedBlockComments) 
{
	BufferSource source("*//*/**//*/**/");
	Scanner scanner(&source);

	scanToEnd(&scanner);
	
	ASSERT_EQ(scanner.getErrorCount(), 3);
	// Mismatched block close
	EXPECT_EQ(scanner.getErrors()[0].bufferPos, 0);

	// Mismatched block open
	EXPECT_EQ(scanner.getErrors()[1].bufferPos, 2);

	// Mismatched block open
	EXPECT_EQ(scanner.getErrors()[2].bufferPos, 8);	
}