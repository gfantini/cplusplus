#include <map>
#include <iostream>

using namespace std;

int main()
{
  map<int,double> mappa;
  mappa[1]=3.1415;
  std::_Rb_tree_iterator<std::pair<const int, double> > found;
  double res;
  found = mappa.find(1);
  if(found != mappa.end())res = found->second;
  cout << res << endl;
  return 0;
}
