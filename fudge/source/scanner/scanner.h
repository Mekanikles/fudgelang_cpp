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

private:
	BufferedInputStream m_inStream;

	Token createToken(TokenType type);
};

}