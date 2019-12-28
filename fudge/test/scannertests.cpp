#include "gtest/gtest.h"

#include "input/source.h"
#include "scanner/scanner.h"
#include "scanner/token.h"

using namespace fudge;

TEST(Scanner, EmptyScan) 
{
	BufferSource source("");
	Scanner scanner(&source);

	Token token = scanner.readToken();
	EXPECT_TRUE(token.type == TokenType::EndOfScan);
}

TEST(Scanner, NonEmptyScan) 
{
	BufferSource source(",");
	Scanner scanner(&source);

	Token token = scanner.readToken();
	EXPECT_EQ(token.type, TokenType::Comma);
	token = scanner.readToken();
	EXPECT_EQ(token.type, TokenType::EndOfScan);
}

TEST(Scanner, ScanLineComments) 
{
	BufferSource source(",//,,\n//,,\n,//");
	Scanner scanner(&source);

	TokenType expectedTypes[] = { TokenType::Comma, TokenType::Comma };

	int p = 0;
	while (true)
	{
		Token token = scanner.readToken();
		if (token.type == TokenType::EndOfScan)
			break;
			
		EXPECT_EQ(token.type, expectedTypes[p++]);
	}
}

TEST(Scanner, ScanBlockComments) 
{
	BufferSource source(",/*,,\n*/,/*\n,*/,");
	Scanner scanner(&source);

	TokenType expectedTypes[] = { TokenType::Comma, TokenType::Comma, TokenType::Comma };

	int p = 0;
	while (true)
	{
		Token token = scanner.readToken();
		if (token.type == TokenType::EndOfScan)
			break;
			
		EXPECT_EQ(token.type, expectedTypes[p++]);
	}
}

TEST(Scanner, ScanNestedBlockComments) 
{
	BufferSource source(",/*/*,,\n*/,/*\n,*//*,");
	Scanner scanner(&source);

	TokenType expectedTypes[] = { TokenType::Comma, TokenType::Comma };

	int p = 0;
	while (true)
	{
		Token token = scanner.readToken();
		if (token.type == TokenType::EndOfScan)
			break;
			
		EXPECT_EQ(token.type, expectedTypes[p++]);
	}
}
