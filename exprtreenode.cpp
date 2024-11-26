/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

// Write your code below this line

ExprTreeNode::ExprTreeNode()
{
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
    // While creating the Tree I pass Node(t, v)
    // in t I will send the operator +,-,*,/,%
    // if the node is a var I will pass the var name in t --> store in id
    // whatever value I send in v just store in val, It may may not be useful
    left = nullptr;
    right = nullptr;
    if (t == "+")
    {
        type = "ADD";
    }
    else if (t == "-")
    {
        type = "SUB";
    }
    else if (t == "*")
    {
        type = "MUL";
    }
    else if (t == "/")
    {
        type = "DIV";
    }
    else if (t == "%")
    {
        type = "MOD";
    }
    else if (t == "DEL")
    {
        type = "DEL";
    }
    else if (t == "RET")
    {
        type = "RET";
    }
    else
    {
        type = "VAR";
        id = t;
    }
    num = v;
}

ExprTreeNode::~ExprTreeNode()
{
    delete left;
    delete right;
}
