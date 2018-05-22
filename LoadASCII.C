

void LoadASCII()
{

  ifstream ifile;
  ifile.open("/nfs/cuore1/scratch/byron/shifter_training/CUORE_work/outfile.csv");
  
  int ch1,ch2;
  double Energy1,TotalEnergy;
  
  TGraph * graph = new TGraph();
  int i = 0;
  while(ifile.good())
    {
      ifile >> ch1 >> Energy1 >> ch2 >> TotalEnergy;
      
      graph->SetPoint(i,Energy1,TotalEnergy-Energy1);
      /*
      cout << "Ch1: \t" << ch1 << endl;
      cout << "Energy1: \t" << Energy1 << endl;
      cout << "Ch2: \t" << ch2 << endl;
      cout << "TotalEnergy: \t" << TotalEnergy << endl;
      */
      if(i%100 == 1)cout << "I've read " << i << " entries from csv." << endl;
      i++;
    }
  
  graph->Draw("AP");
}
