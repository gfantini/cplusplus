#include <iostream> // cout & co

using namespace std;

// parte nel .hh
class QLanguage
{
public: 
  char* languagename;
  virtual int speak() = 0;// any language should be "speakable"
};

class QEnglish : public QLanguage
{
public:
  int speak(); // <-- override
};

class QFrench : public QLanguage
{
public:
  int speak(); // <-- override
};


// this should be in the .cc
 
int QEnglish::speak() 
{ // overrides the QLanguage::speak() virtual class
  cout << "Hello world." << endl; 
  return 0;
};

int QFrench::speak()
{ // overrides the QLanguage::speak() virtual class
  cout << "Salut monde." << endl;
  return 0;
};

int main(void)
{
  QLanguage *l; // you NEED to define a pointer when you have virtual base class or g++ complains
  QFrench french;
  QEnglish eng;
  
  l = &french;
  l->speak();
  eng.speak();
  return 0;
}
