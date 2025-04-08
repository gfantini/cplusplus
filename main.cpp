#include <iostream>
#include "src/printer.hh"
#include "src/dog.hh"

// shared library "libname.so"
// to compile g++ -o main main.cpp -L./path_to_lib/ -lname
// to execute we need to add the .so path to $LD_LIBRARY_PATH
#include "sl_src/add.hh"

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
  
  // use a shared library
  std::cout << "shared 1+1 makes " << add(1,1) << std::endl;

  return 0;
}
