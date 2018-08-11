#ifndef T_MATH_NODE_H
#define T_MATH_NODE_H

#include "TNode.h"

class TMathNode : public TNode {
public:
	enum TMathNodeOp {
		Add = 0,
		Sub,
		Mul,
		Neg,
		OpCount
	};

	TMathNode(TMathNodeOp op)
		: TNode("Math", 120, 90), op(op)
	{
		addOutput("Out");
		addInput("In 0");
		addInput("In 1");
	}

	void gui() {
		static const char* OPS[] = {
			"Add\0",
			"Subtract\0",
			"Multiply\0",
			"Negate"
		};
		ImGui::Combo("Op", (int*)&op, OPS, OpCount, -1);
	}

	void solve() {
		float a = getInput(0);
		float b = getInput(1);
		float out = 0.0f;
		switch (op) {
			case Add: out = a + b; break;
			case Sub: out = a - b; break;
			case Mul: out = a * b; break;
			case Neg: out = -a; break;
		}
		setOutput(0, out);
	}

	virtual void save(JSON& json) {
		TNode::save(json);
		json["type"] = type();
		json["op"] = (int)op;
	}

	TMathNodeOp op;

	static std::string type() { return "Math"; }
};

#endif // T_MATH_NODE_H