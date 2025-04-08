#pragma once

#include <string>


class Printer
{
public:
  Printer();
  void HelloWorld();
  void Print(std::string s);
  double Divide(int num, int den);
private:
  bool fValid;
};
