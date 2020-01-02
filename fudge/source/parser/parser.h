#pragma once
#include "core/core.h"

#include "scanner/token.h"
#include "ast/ast.h"

namespace fudge
{

class Scanner;

class Parser
{
public:	
	Parser(Scanner* scanner);

	bool parseStatementBody(AST::StatementBody** out);
	bool parseStatement(AST::Statement** out);
	bool parseExpression(AST::Expression** out);
	bool parseLiteral(AST::Literal** out);

private:
	template<typename T, typename... Args>
	T* makeASTNode(Args&&... args) { return new T(std::forward<Args>(args)...); }

	void advance();
	const Token& peek(TokenType type);
	const Token& lastToken() { return m_lastToken; }

	bool accept(TokenType type);

	Scanner* const m_scanner;
	Token m_currentToken;
	Token m_lastToken;
};

}