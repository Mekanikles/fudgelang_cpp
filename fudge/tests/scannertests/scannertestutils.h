#pragma once

#include "scanner/scanner.h"
#include "scanner/token.h"

using namespace fudge;

void verifyScannedTokens(Scanner* scanner, const TokenType* expectedTokens, int tokenCount);

template <size_t tokenCount>
void verifyScannedTokens(Scanner* scanner, const TokenType (&expectedTokens)[tokenCount])
{
	verifyScannedTokens(scanner, &expectedTokens[0], tokenCount);
}

void scanToEnd(Scanner* scanner);
