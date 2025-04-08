#pragma once
#include <string>

class Animal{
  // these can be seen anywhere
public:
  Animal(std::string name) : fName(name), fAge(0) {}
  virtual void Speak() = 0;
  const std::string GetName(){ return fName; }
  // these can be accessed / modified just from this class
  // not even derived classes can!
private:
  int fAge;
  const std::string fName;
  // these can be accessed / modified from this class, and derived classes
protected:
  void SetAge(int age){ this->fAge = age; };
};
