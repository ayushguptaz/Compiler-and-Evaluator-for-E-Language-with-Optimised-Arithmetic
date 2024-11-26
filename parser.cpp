/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// Write your code below this line

Parser::Parser()
{
}

bool is_variable(string s)
{
    if (s[0] == '-')
    {
        return false;
    }
    else
    {
        for (long unsigned int i = 0; i < s.size(); i++) // since s.size() was a long unsigned int
        {
            char c = s[i];
            if ((c != '0') && (c != '1') && (c != '2') && (c != '3') && (c != '4') && (c != '5') && (c != '6') && (c != '7') && (c != '8') && (c != '9'))
            {
                return true;
            }
        }
    }
    return false;
}

ExprTreeNode *makeNode(vector<string> code, int start, int end)
// Takes input from which index till which index
{
    // cout << "I am in makeNode" << endl;
    //  code[start] and code[end] will definietly be ( )
    int i = start;
    int j = end;
    // cout << "Start is " << i << endl;
    // cout << "End is " << j << endl;

    if ((code.at(i + 1) == "(") && (code.at(j - 1) == ")"))
    {
        // cout << "I am in ((....) + (....)) case" << endl;
        //  ((....) + (....)) case

        // I will maintain a variable that counts the number of '(' greater than ')'
        int check = 1;
        i = i + 2;
        while (check != 0)
        {
            if (code.at(i) == "(")
            {
                check++;
                i++;
            }
            else if (code.at(i) == ")")
            {
                check--;
                i++;
            }
            else
            {
                i++;
            }
        }
        // cout << "i and j are " << i << " " << j << endl;
        //  now i will be at the operator ((...(..)..) + (.....))

        int temp = int(-1);
        // this node.type is add/sub etc so giving a random int "-1" in the val
        ExprTreeNode *ans = new ExprTreeNode(code.at(i), &temp);

        // now I will recurrsively call make node for left and right child

        ExprTreeNode *right = makeNode(code, i + 1, j - 1);
        ExprTreeNode *left = makeNode(code, start + 1, i - 1);
        ans->right = right;
        ans->left = left;
        return ans;
    }
    else if ((code.at(i + 1) != "(") && (code.at(j - 1) == ")"))
    {
        // cout << "I am in case (a + ())" << endl;
        //  case (a + ())

        int temp = int(-1);
        // this node.type is add/sub etc so giving a random int "-1" in the val
        ExprTreeNode *ans = new ExprTreeNode(code.at(i + 2), &temp);

        // now I will check if a is an int or a variable

        bool check = is_variable(code.at(i + 1));

        if (check)
        {
            ExprTreeNode *left = new ExprTreeNode();
            ans->left = left;
            left->id = code.at(i + 1);
            left->type = "VAR";
        }
        else
        {
            int *a = new int(code.at(i + 1));
            ans->left = new ExprTreeNode();
            ans->left->type = "VAL";
            ans->left->val = new UnlimitedRational(a, new int(1)); // basically make a/1 as rational;
        }

        // now I will recurrsively call make node for right child

        ExprTreeNode *right = makeNode(code, i + 3, j - 1);
        ans->right = right;
        return ans;
    }
    else if ((code.at(i + 1) == "(") && (code.at(j - 1) != ")"))
    {
        // cout << "I am in case (() + a))" << endl;
        //  case (() + a)

        int temp = int(-1);
        // this node.type is add/sub etc so giving a random int "-1" in the val
        ExprTreeNode *ans = new ExprTreeNode(code.at(j - 2), &temp);

        // now I will check if a is an int or a variable

        bool check = is_variable(code.at(j - 1));

        if (check)
        {
            ExprTreeNode *right = new ExprTreeNode();
            ans->right = right;
            right->type = "VAR";
            right->id = code.at(j - 1);
        }
        else
        {
            int *a = new int(code.at(j - 1));
            ans->right = new ExprTreeNode();
            ans->right->type = "VAL";
            ans->right->val = new UnlimitedRational(a, new int(1)); // basically make a/1 as rational;
        }

        // now I will recurrsively call make node for left child

        ExprTreeNode *left = makeNode(code, i + 1, j - 3);
        ans->left = left;
        return ans;
    }
    else if ((code.at(i + 1) != "(") && (code.at(j - 1) != ")"))
    {
        // cout << "I am in case (b + a)" << endl;
        //  case (a+b)

        int temp = int(-1);
        // cout << "Unlim int(-1) created as " << temp.to_string() << endl;
        //  this node.type is add/sub etc so giving a random int "-1" in the val
        ExprTreeNode *ans = new ExprTreeNode(code.at(j - 2), &temp);
        // cout << "ExprTreeNode ans created with type as " << ans->type << endl;

        // check a
        bool check = is_variable(code.at(i + 1));
        // cout << "I checked for variable and got bool check = " << check << endl;
        if (check)
        {
            ExprTreeNode *left = new ExprTreeNode();
            ans->left = left;
            left->id = code.at(i + 1);
            left->type = "VAR";
        }
        else
        {
            int *a = new int(code.at(i + 1));
            // cout << "Unlim a created as " << a->to_string() << endl;
            // cout << "ans.left is " << ans->left << endl;
            ans->left = new ExprTreeNode();
            ans->left->type = "VAL";
            // cout << "ans.left.type is " << ans->left->type << endl;
            ans->left->val = new UnlimitedRational(a, new int(1)); // basically make a/1 as rational;
            // cout << "ans.left.val is " << ans->left->val->get_frac_str() << endl;
        }

        // check b
        check = is_variable(code.at(j - 1));
        // cout << "I checked for variable and got bool check = " << check << endl;

        if (check)
        {
            ExprTreeNode *right = new ExprTreeNode();
            ans->right = right;
            right->type = "VAR";
            right->id = code.at(j - 1);
        }
        else
        {
            int *a = new int(code.at(j - 1));
            // cout << "Unlim a created as " << a->to_string() << endl;
            ans->right = new ExprTreeNode();
            // cout << "ans.left is " << ans->left << endl;
            ans->right->type = "VAL";
            // cout << "ans.left.type is " << ans->left->type << endl;
            ans->right->val = new UnlimitedRational(a, new int(1)); // basically make a/1 as rational;
            // cout << "ans.left.val is " << ans->left->val->get_frac_str() << endl;
        }

        return ans;
    }
    // cout << "I came out of the if else" << endl;
    return new ExprTreeNode();
}

void Parser::parse(vector<string> expression)
{

    if (expression.at(0) == "del")
    {
        ExprTreeNode *left = new ExprTreeNode();
        left->type = "DEL";

        ExprTreeNode *root = new ExprTreeNode();
        root->left = left;
        root->type = "DEL";

        ExprTreeNode *right = new ExprTreeNode();
        right->id = code.at(2);
        right->type = "VAR";
    }

    else if (expression.at(0) == "ret")
    {
        ExprTreeNode *left = new ExprTreeNode();
        left->type = "RET";

        ExprTreeNode *root = new ExprTreeNode();
        root->left = left;
        root->type = "RET";

        ExprTreeNode *right = makeNode(code, 2, code.size() - 1);
        root->right = right;
    }

    if (code.size() == 3)
    {
        ExprTreeNode *left = new ExprTreeNode();
        left->id = code.at(0);
        left->type = "VAR";

        bool check = is_variable(code.at(2));

        ExprTreeNode *root = new ExprTreeNode();
        root->left = left;
        root->type = "EQUAL";

        if (check)
        {
            // RHS is a variable
            ExprTreeNode *right = new ExprTreeNode();
            root->right = right;
            right->type = "VAR";
            right->id = code.at(2);
        }
        else
        {
            // RHS is a number
            int *a = new int(code.at(2));
            root->right = new ExprTreeNode();
            root->right->type = "VAL";
            root->right->val = new UnlimitedRational(a, new int(1)); // basically make a/1 as rational;
        }

        // ExprTreeNode *right = new ExprTreeNode();
        // right->type = "VAL";
        // UnlimitedRational *p = new UnlimitedRational(new int(code.at(2)), new int(1));
        // right->val = p;

        expr_trees.push_back(root);
    }
    // x:=(.....) type
    else
    {
        ExprTreeNode *root = new ExprTreeNode();
        root->type = "EQUAL";
        ExprTreeNode *right = makeNode(code, 2, code.size() - 1);

        ExprTreeNode *left = new ExprTreeNode();
        left->id = code.at(0);
        left->type = "VAR";

        root->left = left;
        root->right = right;

        expr_trees.push_back(root);
    }
}

Parser::~Parser()
{
}