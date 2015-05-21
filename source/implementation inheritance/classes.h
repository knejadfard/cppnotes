#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED

#include <iostream>

class impl1
{
public:

   impl1();
   impl1(int);
   impl1(impl1 const&);
   impl1(impl1&&);

   impl1& operator=(impl1 const&);
   impl1& operator=(impl1&&);

   int get() const;
   void set(int const&);
   virtual void f();

protected:
   int _a;
};

class impl2 final: public impl1
{
public:
   using impl1::impl1;
   using impl1::operator=;
   void f();
};

void impl2::f()
{
   std::cout<<"impl2::f() was called"<<std::endl;
}

impl1::impl1(): impl1::impl1(0)
{
   std::cout<<"impl1::impl1() was called -> initialize _a to 0"<<std::endl;
}

impl1::impl1(int a): _a {a}
{
   std::cout<<"impl1::impl1(int) was called -> initialize _a to "<<a<<std::endl;
}

impl1::impl1(impl1 const& rhs): impl1::impl1(rhs._a)
{
   std::cout<<"impl1::impl1(impl1 const&) was called -> initialize _a to "<<_a<<std::endl;
}

impl1::impl1(impl1&& rhs)
{
   _a = std::move(rhs._a);
   std::cout<<"impl1::impl1(impl1&&) was called -> initialize _a to "<<_a<<std::endl;
}

impl1& impl1::operator=(impl1 const& rhs)
{
   _a = rhs._a;
   std::cout<<"impl1::operator=(&) was called"<<std::endl;
   return *this;
}

impl1& impl1::operator=(impl1&& rhs)
{
   _a = std::move(rhs._a);
   std::cout<<"impl1::operator=(&&) was called"<<std::endl;
   return *this;
}

int impl1::get() const
{
   return _a;
}

void impl1::set(int const& a) {
   _a = a;
}

void impl1::f()
{
   std::cout<<"impl1::f() was called"<<std::endl;
}

#endif // CLASSES_H_INCLUDED
