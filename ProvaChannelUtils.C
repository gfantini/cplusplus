#include <iostream>
#include <QAnalysisPlotsChannelUtils.hh>

using namespace std;

// g++ -std=c++0x `root-config --cflags --glibs` -lRooFit -L${CUORE_EXT_INSTALL}/lib -lQAnalysisPlots -lcof `diana-config --cflags --libs`

int main(){

  double x,y,z;
  QChannelUtils::ChannelPosition(1,x,y,z);
  cout << "Channel 988 is in " << x << " / " << y << " / " << z << " / "  << endl;
  return 1;
}
