#include <iostream>
#include "src/printer.hh"
#include "src/dog.hh"

int main()
{
  // I'd better use local variables, rather than ptrs but..
  Printer* p = new Printer();
  try{
    p->HelloWorld();
    p->Divide(1,10);
    p->Divide(1,0);
    delete p;
  }catch(std::invalid_argument exc){
    std::cout << exc.what() << std::endl;
    delete p;
  }catch(...){
    std::cout << "Some Other Exception caught!" << std::endl;
    delete p;
  }

  
  // Animal a("Rajah"); // breaks at compile time: virtual class
  Dog d("rajah");
  d.Speak();
  
  return 0;
}
