#include "ast.h"

namespace fudge
{
namespace AST
{

string toString(NodeType type)
{
	switch (type)
	{
		case NodeType::StatementBody: return "StatementBody";
		case NodeType::BinaryOp: return "BinaryOp";
		case NodeType::StringLiteral: return "StringLiteral";
		default: return "<Unknown AST Node>";				
	}
}

}
}