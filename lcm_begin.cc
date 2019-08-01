/*  Designed By ZhangTong
*   2019/07/05
*   file: lcm_begin.cc
*   LCM init program.
*   compile with:
*   $ gcc -o lcm_begin lcm_begin.cc -llcm
*/

#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include "exlcm/example_t.hpp"

using namespace std;
int main(int argc, char ** argv)
{
  
    lcm::LCM lcm;
    cout << "HelloWorld\n" << endl;
    if(!lcm.good())
       return 1; 
     /* Your application goes here */
       return 0;
}