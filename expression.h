#ifndef EXPRESSION
#define EXPRESSION
#include <functional>
#include <string>
#include <vector>
#include "calc.h"

enum ExpressionType {
   NUMBER,
   UNARY,
   BINARY
};

static std::string ExpressionTypeToStr[] = {"NUMBER", "UNARY", "BINARY"};

enum Operator {
   SUM,
   SUBTRACT,
   MULTIPLY,
   DIVIDE,
   POW,
   LOG,
   FACTORIAL
};

static std::string OperatorToStr[] = {"sum", "subtract", "multiply", "divide", "power", "log", "factorial"};

static std::function<double(double, double)> BinaryOperatorFunc[] = {sum, subtract, multiply, divide, power, myLog};
static std::function<double(double)> UnaryOperatorFunc[] = {factorial};


class Expression {
    public:
        enum ExpressionType type; 
        enum Operator op;
	class Expression* leftChild; 
        class Expression* rightChild;
	int number;
	bool factorialAncestor;
	~Expression();
	friend double eval(Expression* e, double* a); 
        friend std::ostream& operator<<(std::ostream& os, const Expression* e);
};

std::vector<Expression*> dfs(std::vector<int> numbers, bool factorialAncestor);
#endif
