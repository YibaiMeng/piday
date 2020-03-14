#include <iostream>
#include <cmath>
#include "expression.h"


int main() {
   auto ans = dfs(std::vector<int>{0,1,2}, false);
   int j = 0;
   for(auto e : ans) { 
       for(int i = 1; i <= 20; i++) {
       for(int j = i; j <= 20; j++) {
       for(int k = j; k <= 20; k++) {
	  double d[] = {(double)i,(double)j,(double)k}; 
          double res = eval(e, d); 
          if (!std::isnan(res) and (std::abs(res - 3.14159265358) < 1e-4)) {
              std::cout << res << " " << i << " " << j << " " << k << " " << e << " " << std::endl;
          }
       }}}
       j++;
   }
   return 0;
}
