#pragma once

namespace fudge
{

enum class TokenType
{
	Comma,
	EndOfScan,
	Count,
	Invalid
};

struct Token
{
	TokenType type;
};

}