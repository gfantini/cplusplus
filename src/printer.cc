#include "printer.hh"
#include <iostream>
#include <string>
#include <stdexcept>
/*-- exceptions handled by std library C++
  namespace std {
    class logic_error;
    class domain_error;
    class invalid_argument;
    class length_error;
    class out_of_range;
    class runtime_error;
    class range_error;
    class overflow_error;
    class underflow_error;
}
*/

Printer::Printer()
{
  fValid = true;
}

void Printer::Print(std::string s){
  std::cout << "[Printer] " << s << std::endl;
}

void Printer::HelloWorld()
{
  std::cout << "[Printer] HelloWorld" << std::endl;
}

double Printer::Divide(int num, int den)
{
  // unsure if this is best practice
  if( den == 0 )
    throw std::invalid_argument("[Printer::Divide] divided by 0");
  this->Print( std::to_string(num/(double)den) );
  return num/den;
}
