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
	token.identifier = identifier;
	return token;
}

///////////////////////////////////////////////////////////////////////////////

void Scanner::reportError(string message, uint bufferPos, uint length)
{
	m_errors.push_back(Error{message, bufferPos, length});
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
					vector<uint> openBlockStartPositions;

					// Nestable block comments
					openBlockStartPositions.push_back(inStream.currentPos());
					inStream.advance();
					inStream.advance();
					char c2;
					while (!scanner::isAtEnd(c2 = inStream.peek()))
					{
						if (c2 == '/' && inStream.peekAhead() == '*')
						{
							openBlockStartPositions.push_back(inStream.currentPos());
							inStream.advance();
							inStream.advance();
						}
						else if (c2 == '*' && inStream.peekAhead() == '/')
						{
							openBlockStartPositions.pop_back();
							inStream.advance();
							inStream.advance();
							if (openBlockStartPositions.empty())
								break;
						}
						else
						{
							inStream.advance();
						}
					}
					
					for (uint pos : openBlockStartPositions)
						reportError("Block comment was not closed", pos, 2);
				}
				break;
			}
			case '*':
				if (inStream.peekAhead() == '/')
				{
					reportError("Stray block comment end", inStream.currentPos(), 2);
					inStream.advance();
					inStream.advance();					
				}
				break;
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