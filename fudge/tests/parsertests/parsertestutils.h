#pragma once
#include "core/core.h"

#include "gtest/gtest.h"

#include "input/source.h"
#include "scanner/scanner.h"
#include "parser/parser.h"
#include "ast/ast.h"

using namespace fudge;

void verifyAST(AST::Node* root, const AST::NodeType* expectedNodes, int nodeCount);

template <size_t nodeCount>
void verifyAST(AST::Node* root, const AST::NodeType (&expectedNodes)[nodeCount])
{
	verifyAST(root, &expectedNodes[0], nodeCount);
}

template <size_t nodeCount>
void verifyParsedAST(const char* buffer, const AST::NodeType (&expectedNodes)[nodeCount])
{
	BufferSource source(buffer);
	Scanner scanner(&source);
	Parser parser(&scanner);

	AST::StatementBody* body;
	ASSERT_TRUE(parser.parseStatementBody(&body));

	verifyAST(body, expectedNodes);
}
