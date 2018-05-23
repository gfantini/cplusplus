#include <iostream>
#include <fstream>
#include <QAnalysisPlotsChannelUtils.hh>

using namespace std;

// compile with this
// you need -L${CUORE_EXT_INSTALL}/lib/
// g++ -std=c++0x `root-config --cflags --glibs` -lRooFit -L${CUORE_EXT_INSTALL}/lib -lQAnalysisPlots -lcof `diana-config --cflags --libs`

int main(){

  ofstream ofile;
  ofile.open("/nfs/cuore1/scratch/gfantini/cplusplus/ChannelPosition.dat");

  double x,y,z;
  cout << "#Channel \t x [mm] \t y [mm] \t z [mm]"<< endl;
  for(int i=1;i<=988;i++)
    {
      QChannelUtils::ChannelPosition(i,x,y,z);
      ofile << i << "\t" << x << "\t" << y << "\t" << z << endl;
    }
  ofile.close();
  
  return 1;
}
