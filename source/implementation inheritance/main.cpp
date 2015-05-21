#include <iostream>
#include "classes.h"

using namespace std;

int main()
{
   cout<<"Testing impl1 object:\n";
   impl1 b{2};
   b.f();
   cout<<"\nTesting impl2 object:\n";
   impl2 d{5};
   d.f();

   cout<<"\nTesting assignment:\n";
   b = d;
   d = b;

   return 0;
}
