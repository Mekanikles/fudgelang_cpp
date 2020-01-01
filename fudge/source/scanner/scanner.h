#pragma once
#include "core/core.h"

#include "input/bufferedinputstream.h"
#include "scanner/token.h"

namespace fudge
{
class Source;
struct Token;

class Scanner
{
public:
	Scanner(const Source* source);

	Token readToken();

	struct Error
	{
		string message;
		uint bufferPos;
		uint length;
	};

	uint getErrorCount() { return m_errors.size(); }
	const vector<Error>& getErrors() { return m_errors; }
	
protected:
	Token createToken(TokenType type, string identifier = string());

	void reportError(string message, uint bufferPos, uint length = 1);

	void skipWhitespaceAndComments();
	Token scanStringLiteral();

private:
	BufferedInputStream m_inStream;

	vector<Error> m_errors;
};

}
