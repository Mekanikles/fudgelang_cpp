#include "scanner.h"

#include "input/source.h"
#include "scanner/token.h"

namespace fudge
{

namespace scanner
{
	static void skipWhitespaceAndComments(BufferedInputStream* inStream)
	{
		bool foundWhitespace = false;
		while (true)
		{
			const char c = inStream->peek();
			switch (c) 
			{
				case ' ':
				case '\r':
				case '\t':
				case '\n':
				{
					inStream->advance();
					foundWhitespace = true;
					break;
				}
				case '/':
				{
					char n = inStream->peekAhead();
					if (n == '/')
					{
						// Line comments
						inStream->advance();
						inStream->advance();
						char c;
						while ((c = inStream->peek()) != EOF && c != '\n')
							inStream->advance();
					}
					else if (n == '*')
					{
						// Nestable block comments
						inStream->advance();
						inStream->advance();
						int blockLevel = 1;
						char c;
						while ((c = inStream->peek()) != EOF)
						{
							if (c == '/' && inStream->peek() == '*')
							{
								inStream->advance();
								inStream->advance();
								++blockLevel;
							}
							else if (c == '*' && inStream->peek() == '/')
							{
								inStream->advance();
								inStream->advance();
								--blockLevel;
								if (blockLevel == 0)
									break;
							}
							else
							{
								inStream->advance();
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
}

Scanner::Scanner(const Source* source)
	: m_inStream(source->createStream())
{
}

Token Scanner::createToken(TokenType type)
{
	Token token;
	token.type = type;
	return token;
}

Token Scanner::readToken()
{
	scanner::skipWhitespaceAndComments(&m_inStream);

	char c;
	while ((c = m_inStream.peek()) != EOF)
	{
		switch (c)
		{
			case ',':
				m_inStream.advance();
				return createToken(TokenType::Comma);
		}

		// TODO: Error reporting
		m_inStream.advance();
		return createToken(TokenType::Invalid);
	}
	
	return createToken(TokenType::EndOfScan);
}

}