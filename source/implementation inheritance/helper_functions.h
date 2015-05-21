#ifndef HELPER_FUNCTIONS_H_INCLUDED
#define HELPER_FUNCTIONS_H_INCLUDED

#include <iostream>
#include "classes.h"

//Instead of implementing the following two:
/*impl1 operator+(impl1 const& lhs, impl1 const& rhs)
impl2 operator+(impl2 const& lhs, impl1 const& rhs);*/

//One templated definition suffices
template <typename T1, typename T2>
T1 operator+(T1 const& lh, T2 const& rh)
{
   std::cout<<"operator+(T1 const&, T2 const&) was called"<<std::endl;
   return T1{lh.get() + rh.get()};
}

#endif // HELPER_FUNCTIONS_H_INCLUDED
