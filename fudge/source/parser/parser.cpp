#include "parser.h"

#include "scanner/scanner.h"

namespace fudge
{

static Token s_invalidToken(TokenType::Invalid);

///////////////////////////////////////////////////////////////////////////////

Parser::Parser(Scanner* scanner)
	: m_scanner(scanner)
{
	advance();
}

///////////////////////////////////////////////////////////////////////////////

void Parser::advance()
{
	auto& scanner = *m_scanner;
	m_lastToken = m_currentToken;
	while (!(m_currentToken = scanner.readToken()))
	{}
}

///////////////////////////////////////////////////////////////////////////////

const Token& Parser::peek(TokenType type)
{
	if (m_currentToken.type == type)
		return m_currentToken;
	return s_invalidToken;
}

///////////////////////////////////////////////////////////////////////////////

bool Parser::accept(TokenType type)
{
	if (peek(type))
	{
		advance();
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////

bool Parser::parseStatementBody(AST::StatementBody** out)
{
	auto body = makeASTNode<AST::StatementBody>();
	AST::Statement* stmnt;
	while (parseStatement(&stmnt))
		body->statements.push_back(stmnt);
	*out = body;

	return true;
}

///////////////////////////////////////////////////////////////////////////////

bool Parser::parseStatement(AST::Statement** out)
{
	AST::Expression* expr;
	if (parseExpression(&expr))
	{
		*out = expr;
		return true;
	}

	return false;	
}

///////////////////////////////////////////////////////////////////////////////
	
bool Parser::parseExpression(AST::Expression** out)
{
	AST::Literal* literal;
	if (parseLiteral(&literal))
	{
		*out = literal;
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////

bool Parser::parseLiteral(AST::Literal** out)
{
	if (accept(TokenType::StringLiteral))
	{
		*out = makeASTNode<AST::StringLiteral>(lastToken().data);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////

}