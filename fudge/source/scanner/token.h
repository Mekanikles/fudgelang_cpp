#pragma once

#include "core/core.h"

namespace fudge
{

enum class TokenType
{
	Comma,
	StringLiteral,
	EndOfScan,
	Count,
	Invalid
};

struct Token
{
	TokenType type;
	// TODO: Don't store identifiers like this
	//	store a pointer to a data block instead of use the 
	//	bufferPos + length to point into the source buffer
	string identifier;
};

}