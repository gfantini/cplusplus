#include <string>
#include <iostream>

using namespace std;

int main()
{
  string a = "Il cane";
  string b = " caga.";
  string c = a+b;
  cout << c.c_str() << endl;

  return 0;
}

