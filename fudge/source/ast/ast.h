#pragma once
#include "core/core.h"

#define FUDGE_DECLARE_AST_NODE(nodeName) \
	virtual NodeType getType() override { return NodeType::nodeName; } \
	virtual void accept(Visitor* v) override { visit(v, static_cast<nodeName*>(this)); }

#define FUDGE_AST_SAFE_CAST(nodeName, node) \
	(node->getType() == NodeType::nodeName) ? static_cast<struct nodeName*>(node) : [](){ assert(!"Invalid cast!"); return nullptr; }()

namespace fudge
{
namespace AST
{

class Visitor;

// Forward declare to solve cyclic dependency between visitor and nodes
template<typename T>
inline void visit(Visitor* v, T* node);

///////////////////////////////////////////////////////////////////////////////

enum class NodeType
{
	StatementBody,
	BinaryOp,
	StringLiteral,
	Count
};

struct Node 
{
	virtual NodeType getType() = 0;
	virtual void accept(interface Visitor* v) = 0;
	virtual void acceptChildren(interface Visitor* v) {}
};

///////////////////////////////////////////////////////////////////////////////

struct Statement : public Node {};
struct Expression : public Statement {};
struct Literal : public Expression {};

///////////////////////////////////////////////////////////////////////////////

struct StatementBody : public Statement
{
	FUDGE_DECLARE_AST_NODE(StatementBody);
	virtual void acceptChildren(Visitor* v) override
	{
		for (auto& s : statements)
			s->accept(v);
	}

	vector<Statement*> statements;
};

///////////////////////////////////////////////////////////////////////////////

struct StringLiteral : public Literal
{
	FUDGE_DECLARE_AST_NODE(StringLiteral);

	StringLiteral(string str)
		: str(str)
	{}

	string str;
};

///////////////////////////////////////////////////////////////////////////////

struct BinaryOp : public Expression
{
	FUDGE_DECLARE_AST_NODE(BinaryOp);

	virtual void acceptChildren(Visitor* v) override
	{
		left->accept(v);
		right->accept(v);
	}	

	Expression* left;
	Expression* right;
};

///////////////////////////////////////////////////////////////////////////////

interface Visitor
{
	virtual void visit(Node* node) { node->acceptChildren(this); }
	virtual void visit(struct Statement* node) { visit(static_cast<Node*>(node)); }
	virtual void visit(struct Expression* node) { visit(static_cast<Statement*>(node)); }
	virtual void visit(struct StatementBody* node) { visit(static_cast<Statement*>(node)); }
	virtual void visit(struct BinaryOp* node) { visit(static_cast<Expression*>(node)); }
};

///////////////////////////////////////////////////////////////////////////////

template<typename T>
void visit(Visitor* v, T* node)
{
	v->visit(node);
}

///////////////////////////////////////////////////////////////////////////////

}
}
