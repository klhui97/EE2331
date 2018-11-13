//Student name:
//Student ID  :

/* 
	Implement the functions infix_to_postfix() and prefix_to_postfix(). 

	An arithmetic expression may contain 5 binary operators: +, -, *, /, $.
	Operators are delimited by 1 or more white space character.
	Operands in an infix expression can be delimited by space character or bracket.
	Operands in a prefix expression are delimited by space character.

	An operand is a number (may have multiple characters), and it can be negative.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stack>

using namespace std;

bool isOperator(const string& expr, int i)
{
	// return true if the symbol at index i of expr is an operator

	char c = expr[i];

	// the symbol '#' denotes the end_of_expression for infix expression
	if (c == '+' || c == '*' || c == '/' || c == '$' || c == '#')
		return true;

	// not the minus sign of an operand
	if (c == '-' && (i == expr.length()-1 || isspace(expr[i+1])))
		return true;

	return false;
}

string nextOperand(const string& expr, int& i)
{
	// Retrieve the operand starting at index i.
	// i is advanced to the char (white space or bracket) that follows the retrieved operand

	int j = i;
	while (j < expr.length() && !(isspace(expr[j]) || expr[j] == ')' || expr[j] == '('))
		j++;

	string operand = expr.substr(i, j-i);
	i = j;
	return operand;
}

int precNum(char c)
{
	if (c == '#')
		return 1;
	else if (c == '(')
		return 2;
	else if (c == '+' || c == '-')
		return 3;
	else if (c == '*' || c == '/')
		return 4;
	else if (c == '$')
		return 5;
	
	return 0;
}

/*
	The symbol '#' is used to denote the end of the infix expression.
	Operators are separated by space characters.
	An operand is a number (can have multiple digits) and can be negative.

	You can access a character in the string object by the subscript operator, e.g. infix[i].
	Use the string concatenation operator "+" to build the postfix expression.

	You can reference the notes for the infix_to_postfix conversion algoirthm.
	Please note that the end of expression symbol used in this exercise is different
	from the algoirthm in the notes.
*/
string infix_to_postfix(const string& infix)
{
	// Convert the input infix expression to postfix format.

	stack<char> S;
	S.push('@');

	string postfix = "";
	int i = 0;

	while (S.top() != '#')
	{
		if (isspace(infix[i]))
			i++;
		else
		{
			if (isOperator(infix, i))
			{
				char opr = infix[i++];
				while (precNum(S.top()) >= precNum(opr))
				{
					postfix = postfix + " " + S.top();
					S.pop();
				}
				S.push(opr);
			}
			else if (infix[i] == '(') 
				S.push(infix[i++]);
			else if (infix[i] == ')')
			{
				while (S.top() != '(')
				{
					postfix = postfix + " " + S.top();
					S.pop();
				}
				S.pop();
				i++;
			}
			else // operand	
			{
				if (postfix.empty())
					postfix = nextOperand(infix, i);
				else
					postfix = postfix + " " + nextOperand(infix, i);
			}
		}
	}
	return postfix;
}


struct stackItem  // for prefix_to_postfix conversion
{
	char symbol;  // operator
	int count;
};

/*
	You can access a character in the string object by the subscript operator, e.g. prefix[i].
	Use prefix.length() to control the looping until end of string.
	Use the string concatenation operator "+" to build the postfix expression.
*/
string prefix_to_postfix(const string& prefix)
{
	// Convert the input prefix expression to postfix format.

	stack<stackItem> S;
	stackItem x;

	string postfix = "";
	int i = 0;
	while (i < prefix.length())  //scan the prefix expr from left to right
	{
		if (isspace(prefix[i]))
			i++;
		else if (isOperator(prefix, i))
		{
			x.count = 0;
			x.symbol = prefix[i++];  // operator
			S.push(x);
		}
		else
		{
			string operand = nextOperand(prefix, i);
			if (postfix.empty())
				postfix = operand;
			else
				postfix = postfix + " " + operand;

			while (!S.empty())
			{
				S.top().count++;
				if (S.top().count == 2)
				{
					postfix = postfix + " " + S.top().symbol;
					S.pop();
				}
				else
					break;
			}
		}
	}
	return postfix;
}

int main()
{	
	string postfix_expr, prefix_expr, infix_expr;

	cout << "Infix to Postfix conversion\n\n";

	ifstream infile("infix_expr.txt");
	if (!infile.is_open())
	{
		cout << "Error: cannot open data file" << endl;
		system("pause");
		exit(0);
	}

	while (getline(infile, infix_expr))
	{
		postfix_expr = infix_to_postfix(infix_expr);
		cout << "infix_expr   : " << infix_expr << endl;
		cout << "postfix_expr : " << postfix_expr << endl << endl;
	}
	infile.close();

	
	cout << "\n----------------------------------------------------------------\n";
	cout << "Prefix to Postfix conversion\n\n";
	
	infile.open("prefix_expr.txt");
	if (!infile.is_open())
	{
		cout << "Error: cannot open data file" << endl;
		system("pause");
		exit(0);
	}

	while (getline(infile, prefix_expr))
	{
		postfix_expr = prefix_to_postfix(prefix_expr);
		cout << "prefix_expr  : " << prefix_expr << endl;
		cout << "postfix_expr : " << postfix_expr << endl << endl;
	}
	infile.close();
	
	system("pause");
	exit(0);
}