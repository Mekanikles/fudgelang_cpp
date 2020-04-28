#include "parsertestutils.h"

///////////////////////////////////////////////////////////////////////////////

class ASTVerifier : public AST::Visitor
{
public:
	ASTVerifier(const AST::NodeType* expectedNodes, int nodeCount)
	{
		for (int i = nodeCount - 1; i >= 0; --i)
			m_expectedNodes.push_back(expectedNodes[i]);
	}

	virtual void visit(AST::Node* node) override
	{
		auto type = m_expectedNodes.back(); 
		m_expectedNodes.pop_back();
		EXPECT_EQ(node->getType(), type) << 
			"Mismatched AST Node type. Expected: " << toString(type) <<
			", Found: " << toString(node->getType());
			
		node->acceptChildren(this);
	}

	void verify(AST::Node* node)
	{
		node->accept(this);
		ASSERT_TRUE(m_expectedNodes.empty());
	}

private:
	vector<AST::NodeType> m_expectedNodes;
};

///////////////////////////////////////////////////////////////////////////////

void verifyAST(AST::Node* root, const AST::NodeType* expectedNodes, int nodeCount)
{
	ASTVerifier verifier(expectedNodes, nodeCount);
	verifier.verify(root);
}

///////////////////////////////////////////////////////////////////////////////
