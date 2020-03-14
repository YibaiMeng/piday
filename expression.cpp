#include<iostream>
#include<vector>
#include<string>
#include<functional>
#include<cmath>

#include "expression.h"
#include "calc.h"


Expression::~Expression() {
    std::function<void(const Expression*)> l;
    l = [&l](const Expression* e) {
	  if (e->type == NUMBER) {
	      delete e;    
	  } else if(e->type == UNARY) {
	       l(e->leftChild);
	       delete e;
	  } else if(e->type == BINARY) {
	      l(e->leftChild);
	      l(e->rightChild);
	      delete e;
	  }
    };
    l(this);
};

std::ostream& operator<<(std::ostream& os, const Expression* e) {
    static const std::string numberToName[] = {"a", "b", "c", "d"};
    std::function<void(const Expression*)> l;
    l = [&os, &l](const Expression* e) {
	  if (e->type == NUMBER) {
	      os << numberToName[e->number];    
	  } else if(e->type == UNARY) {
              os << OperatorToStr[e->op] << "(";
	      l(e->leftChild);
	      os<<")";
	  } else if(e->type == BINARY) {
              os << OperatorToStr[e->op] << "(";
	      l(e->leftChild);
	      os<<", ";
	      l(e->rightChild);
	      os << ")";
	  }
    };
    l(e);
    return os;
}

/*
 * Search for all possible expressions with the numbers given.
 * Return an array of all possible expressions 
 * Note that an artifical limit of no recursive factorials is imposed, as multiple layers of factorials are probably too big for PI.
 * */
std::vector<Expression*> dfs(std::vector<int> numbers, bool factorialAncestor) {
    std::vector<Expression*> res;
    if (numbers.size() == 1) {
        // The expressioJust a number is a type
	Expression* n = new Expression;
	n->type = NUMBER;
	n->factorialAncestor = factorialAncestor;
	n->number = numbers[0];
	res.push_back(n);
	// If have factorials in the ancestors of the expression, then must not have anymore factorials.
	if (factorialAncestor) return res;
        Expression *m = new Expression;
	m->type = UNARY;
	m->factorialAncestor = true;
	m->op = FACTORIAL;
	n->factorialAncestor = true;	
	Expression* c = new Expression;
	c->type = NUMBER;
	c->factorialAncestor = true;
	c->number = numbers[0];
	m->leftChild = c;
	m->rightChild = NULL;
	res.push_back(m);
	return res;
    } else if (numbers.size() > 4) {
	std::cerr << "Not supported" << std::endl;
        abort();
    } else { 
	if (!factorialAncestor) {
	    auto r = dfs(numbers, true);
            for (auto &e : r) {
                Expression *n = new Expression;
	        n->type = UNARY;
	        n->factorialAncestor = true;
		n->leftChild = e;
	        n->rightChild = NULL;
		n->op = FACTORIAL;
		res.push_back(n);
	    }	        
	} 
           
	auto f = [&res,factorialAncestor](const std::vector<Expression*> & r1, const std::vector<Expression*> & r2) {      
            for(auto& s1 : r1) {
                for(auto& s2 : r2) {
		    for(auto op : {SUM, SUBTRACT, MULTIPLY, DIVIDE, POW, LOG}) { // TODO: loop through all the ops
                            Expression* n1 = new Expression;
                            n1->type = BINARY;
	                    n1->factorialAncestor = factorialAncestor;
	                    n1->op = op;
			    n1->leftChild = s1;
			    n1->rightChild = s2;
			    res.push_back(n1); 
                            Expression* n2 = new Expression;
                            n2->type = BINARY;
	                    n2->factorialAncestor = factorialAncestor;
	                    n2->op = op;
			    n2->leftChild = s2;
			    n2->rightChild = s1;
			    res.push_back(n2); 
	            }
	        }
	   }
	};

	if (numbers.size() == 2) {
            auto r1 = dfs(std::vector<int>{numbers[0]}, factorialAncestor); // slice
            auto r2 = dfs(std::vector<int>{numbers[1]}, factorialAncestor); // slice
	    f(r1, r2);
	} else if(numbers.size() == 3) {
          auto r1_1 = dfs(std::vector<int>{numbers[0]}, factorialAncestor); // slice    
          auto r1_2 = dfs(std::vector<int>{numbers[1]}, factorialAncestor); // slice    
          auto r1_3 = dfs(std::vector<int>{numbers[2]}, factorialAncestor); // slice    
          auto r2_1 = dfs(std::vector<int>{numbers[0], numbers[1]}, factorialAncestor); // slice    
          auto r2_2 = dfs(std::vector<int>{numbers[0], numbers[2]}, factorialAncestor); // slice    
          auto r2_3 = dfs(std::vector<int>{numbers[1], numbers[2]}, factorialAncestor); // slice    
	  f(r1_1, r2_3);
	  f(r1_2, r2_2);
	  f(r1_3, r2_1);
        } else if(numbers.size() == 4) {
          auto r1_1 = dfs(std::vector<int>{numbers[0]}, factorialAncestor); // slice    
          auto r1_2 = dfs(std::vector<int>{numbers[1]}, factorialAncestor); // slice    
          auto r1_3 = dfs(std::vector<int>{numbers[2]}, factorialAncestor); // slice    
          auto r1_4 = dfs(std::vector<int>{numbers[3]}, factorialAncestor); // slice    
          auto r2_1 = dfs(std::vector<int>{numbers[0], numbers[1]}, factorialAncestor); // slice    
          auto r2_2 = dfs(std::vector<int>{numbers[0], numbers[2]}, factorialAncestor); // slice    
          auto r2_3 = dfs(std::vector<int>{numbers[0], numbers[3]}, factorialAncestor); // slice    
          auto r2_4 = dfs(std::vector<int>{numbers[1], numbers[2]}, factorialAncestor); // slice    
          auto r2_5 = dfs(std::vector<int>{numbers[1], numbers[3]}, factorialAncestor); // slice    
          auto r2_6 = dfs(std::vector<int>{numbers[2], numbers[3]}, factorialAncestor); // slice    
          auto r3_1 = dfs(std::vector<int>{numbers[0], numbers[1], numbers[2]}, factorialAncestor); // slice    
          auto r3_2 = dfs(std::vector<int>{numbers[0], numbers[1], numbers[3]}, factorialAncestor); // slice    
          auto r3_3 = dfs(std::vector<int>{numbers[0], numbers[2], numbers[3]}, factorialAncestor); // slice    
          auto r3_4 = dfs(std::vector<int>{numbers[1], numbers[2], numbers[3]}, factorialAncestor); // slice    
          f(r1_1, r3_4);   
          f(r1_2, r3_3);   
          f(r1_3, r3_2);   
          f(r1_4, r3_1);   
          f(r2_1, r2_6);   
          f(r2_2, r2_5);   
          f(r2_3, r2_4);   
	}	
        return res;
    }
    
}


double eval(Expression* e, double* a) {
    std::function<double(const Expression*)> l;
    l = [&l, a](const Expression* e) {
	    if (e->type == NUMBER) return a[e->number];
	    else if(e->type == UNARY) {
	       double res = l(e->leftChild);
               return factorial(res); 
	    } else if(e->type == BINARY) {

               double left = l(e->leftChild);
               double right = l(e->rightChild);
	       return BinaryOperatorFunc[e->op](left, right);
	    }
            abort();
    };
    return l(e);
}
