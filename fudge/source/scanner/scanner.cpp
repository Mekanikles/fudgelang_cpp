#include "scanner.h"

#include "input/source.h"
#include "scanner/token.h"

namespace fudge
{

///////////////////////////////////////////////////////////////////////////////

namespace scanner
{
	inline bool isAtEnd(char c)
	{
		return c == EOF;	
	}
}

///////////////////////////////////////////////////////////////////////////////

Scanner::Scanner(const Source* source)
	: m_inStream(source->createStream())
{
}

///////////////////////////////////////////////////////////////////////////////

Token Scanner::createToken(TokenType type, string identifier)
{
	Token token;
	token.type = type;
	token.bufferPos = m_inStream.currentPos();
	token.identifier = identifier;
	return token;
}

///////////////////////////////////////////////////////////////////////////////

void Scanner::skipWhitespaceAndComments()
{
	auto& inStream = m_inStream;
	bool foundWhitespace = false;
	while (true)
	{
		const char c = inStream.peek();
		switch (c) 
		{
			case ' ':
			case '\r':
			case '\t':
			case '\n':
			{
				inStream.advance();
				foundWhitespace = true;
				break;
			}
			case '/':
			{
				char n = inStream.peekAhead();
				if (n == '/')
				{
					// Line comments
					inStream.advance();
					inStream.advance();
					char c;
					while (!scanner::isAtEnd(c = inStream.peek()) && c != '\n')
						inStream.advance();
				}
				else if (n == '*')
				{
					// Nestable block comments
					inStream.advance();
					inStream.advance();
					int blockLevel = 1;
					char c2;
					while (!scanner::isAtEnd(c2 = inStream.peek()))
					{
						if (c2 == '/' && inStream.peekAhead() == '*')
						{
							inStream.advance();
							inStream.advance();
							++blockLevel;
						}
						else if (c2 == '*' && inStream.peekAhead() == '/')
						{
							inStream.advance();
							inStream.advance();
							--blockLevel;
							if (blockLevel == 0)
								break;
						}
						else
						{
							inStream.advance();
						}
					}
					// TODO: Add warning on blockLevel != 0
				}
				break;
			}
			default:
				return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

Token Scanner::scanStringLiteral()
{
	auto& inStream = m_inStream;

	assert(inStream.peek() == '\"');
	inStream.advance();

	string str;

	char c;
	while (!scanner::isAtEnd(c = inStream.peek()))
	{
		inStream.advance();
		if (c == '\"')
			break;

		str += c;	
	}

	return createToken(TokenType::StringLiteral, str);
}

///////////////////////////////////////////////////////////////////////////////

Token Scanner::readToken()
{
	auto& inStream = m_inStream;	
	skipWhitespaceAndComments();

	char c;
	while (!scanner::isAtEnd(c = inStream.peek()))
	{
		switch (c)
		{
			case ',':
				inStream.advance();
				return createToken(TokenType::Comma);
			case '"': 
				return scanStringLiteral();
		}

		// TODO: Error reporting
		inStream.advance();
		return createToken(TokenType::Invalid);
	}
	
	return createToken(TokenType::EndOfScan);
}

///////////////////////////////////////////////////////////////////////////////

}