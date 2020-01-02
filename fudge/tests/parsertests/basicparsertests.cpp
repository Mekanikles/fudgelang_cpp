#include "gtest/gtest.h"

#include "parser/parser.h"
#include "ast/ast.h"

#include "parsertests/parsertestutils.h"

using namespace fudge;

TEST(Parser, ParseEmptyStatementBody) 
{
	const char* source = "";
	verifyParsedAST(source, { AST::NodeType::StatementBody });
}

TEST(Parser, ParseSimpleStatementBody) 
{
	const char* source = "\"A string\"";
	verifyParsedAST(source, { AST::NodeType::StatementBody, AST::NodeType::StringLiteral });
}
