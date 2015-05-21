#include <iostream>

using namespace std;

template <typename T>
T f(T& t) {
   cout<<"General template function was called."<<endl;
   return ++t;
}

template <>
double f(double& s) {
   cout<<"Template function with specialization for double was called."<<endl;
   return s;
}

double f(double& t) {
   cout<<"Non-template function for double was called."<<endl;
   return t+2;
}

int main() {
   int a=2;
   double d=2.1;
   cout<<f(a)<<endl; //calls the general template function
   cout<<f(d)<<endl; //calls the non-template version of f, instead of the specialized overload
   return 0;
}
