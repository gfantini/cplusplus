#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

using namespace std;

const int gNbin = 1000;
const double gEmin = 2000;
const double gEmax = 3000;

void ProduceJagsM2spectrum()
{
  // File with result from bkg model
  string InputFile_b2g = "/nfs/cuore1/scratch/gfantini/spacebased/input/b2g_3018_3021.dat";
  string InputMcFolder = "/nfs/cuore1/data/simulation/CUORE/2017/ntp/";
  string OutputRootFile = "/nfs/cuore1/scratch/gfantini/spacebased/out/ProduceJagsM2Spectrum.root";
  ifstream IF;
  IF.open(InputFile_b2g.c_str());
  
  // do some printout (test)
  string Filename;
  string FunctionName;
  double Mu,Sigma; // gauss fit function
  double ReducedChi2,Pvalue,MinGauss,MaxGauss;
  string line;
  vector<string> McFileNames;
  vector<string> McFilePaths;
  vector<double> N;
  
  Mu=0.; Sigma=0.; ReducedChi2=0.; Pvalue=0.; MinGauss=0.; MaxGauss=0.; // init variables
  
  std::getline(IF,line); // throw away the 1st line
  int counter = 0;
  while(IF.good())
    {
      // read file and fill the vectors of MC files and normalization factors
      IF >> Filename >> FunctionName >> ReducedChi2 >> Mu >> Sigma >> Pvalue >> MinGauss >> MaxGauss;
      
      McFileNames.push_back(Filename);
      McFilePaths.push_back(InputMcFolder+Filename+".root");
      cout << "Added " << McFilePaths[counter] << endl;
      if(FunctionName == "gaus_n"){// the gaussian fit of the posterior converges --> contamination present!
	N.push_back(Mu);
      }else{ // the gaussian fit is inappropriate --> contamination absent (upper limit) --> set to 0.
	N.push_back(0.);
      }
      counter++;
      
      // print to screen what you just retrieved
      cout << "Filename:\t" << Filename << endl;
      cout << "FunctionName:\t" << FunctionName << endl;
      cout << "Mu:\t\t" << Mu << endl;
      cout << "Sigma:\t\t" << Sigma << endl;
      cout << "ReducedChi2:\t" << ReducedChi2 << endl;
      cout << "Pvalue:\t\t" << Pvalue << endl;
      cout << "MinGauss:\t"<< MinGauss << endl;
      cout << "MaxGauss:\t"<< MaxGauss << endl;
      cout << "************************************************************************" << endl;
    }

  // once the loop over the sources is done..
  if(N.size() != McFilePaths.size()){// consistency check
    cerr << "FATAL! Number of MC files is different from number of normalization coefficients." << endl;
    exit(1);
  }
  // file existence check  
  TFile *pMcFile;
  for(unsigned int i=0; i<N.size(); i++)
    {
      pMcFile = new TFile(McFilePaths[i].c_str(),"read");
      if(!pMcFile->IsOpen()){
	cerr << "FATAL! Could not open " << McFilePaths[i] << endl;
	exit(2);
      }else{
	cout << "[INFO] File " << McFilePaths[i] << " found and readable." << endl;
      }
      pMcFile->Close();
    }

  // compute sum of normalization factors (I assume this is correlated to the MC statistics..)
  double Nsum = 0.;
  for(unsigned int i=0; i<N.size(); i++)Nsum+=N[i];
  cout << "Nsum: \t " << Nsum << endl;

  vector<TH1D*> HistoM2;
  TH1D* HistoTmp;
  // the true final loop over MC files to load events and produce distributions
  for(unsigned int i=0; i<N.size(); i++)
    {
      HistoTmp = new TH1D(McFileNames[i].c_str(),McFileNames[i].c_str(),gNbin,gEmin,gEmax);
      HistoM2.push_back(HistoTmp);
      if(N[i] != 0.)
	{ // if the contamination is relevant
	  cout << "[INFO] Processing "<< McFilePaths[i] << endl;
	  pMcFile = new TFile(McFilePaths[i].c_str(),"read");
	  if(pMcFile->IsZombie() || !pMcFile->IsOpen()){
	    cerr << "FATAL! Could not open " << McFilePaths[i] << endl; 
	    exit(2);
	  }
	  // set the relevant variables
	  TTree *OutTree = 0;
	  Int_t Detector; // Channel number in DAQ numbering
	  Double_t Ener2; // Energy corrected by quenching and ...
	  Double_t Esum2; // TotalEnergy of the multiplet corrected by quenching etc..
	  Double_t Multiplicity; // self-explaining..
	  Short_t MultipletIndex; // index of the main event in the multiplet array
	  Int_t Multiplet[988]; // array filled every time from 0..Multiplicity-1 with the Detector number of coincident channels
	  
	  // get the tree of g4cuore and the variables I am looking for
	  pMcFile->GetObject("outTree",OutTree);
	  cout << "[DEBUG] Checkpoint 1" << endl;
	  if(OutTree != 0){
	    cout << "[DEBUG] Checkpoint 2" << endl;
	  }else{
	    cerr << "FATAL! Could not read outTree!" << endl;
	    exit(4);
	  }
	  OutTree->Show(0);
	  cout << "[DEBUG] Checkpoint 3" << endl;
	  // FIXME DEBUG
	  /*
Error in <TTree::SetBranchAddress>: The pointer type given "Short_t" (2) does not correspond to the type needed "Int_t" (3) by the branch: Detector
Error in <TTree::SetBranchAddress>: unknown branch -> Esum2
Error in <TTree::SetBranchAddress>: The pointer type given "Double_t" (8) does not correspond to the type needed "Short_t" (2) by the branch: Multiplicity
	  */
	  OutTree->SetBranchAddress("Detector",&Detector);
	  OutTree->SetBranchAddress("Ener2",&Ener2);
	  OutTree->SetBranchAddress("Esum2",&Esum2);
	  OutTree->SetBranchAddress("Multiplicity",&Multiplicity);
	  OutTree->SetBranchAddress("MultipletIndex",&MultipletIndex);
	  OutTree->SetBranchAddress("Multiplet",Multiplet);
	  for(unsigned int j=0; j<OutTree->GetEntries(); j++)
	    { // loop over MC file "i" and fill the histogram
	      OutTree->GetEntry(j);
	      if(Multiplicity == 2)HistoM2[i]->Fill(Esum2);
	    }
	  pMcFile->Close();
	  // <---- normalize the histogram 
	}else{
	HistoM2[i]->Fill(gEmin - .5*gEmin); // fill only 1 underflow event, so that histo is not empty
      }
    }
  
  // put together all the histograms into the sum histogram
  TH1D* HistoM2all = new TH1D("M2spectrum","M2 spectrum (MC normalized)",gNbin,gEmin,gEmax);
  for(unsigned int i=0;i<HistoM2.size();i++)(*HistoM2all)=(*HistoM2all)+N[i]*(*HistoM2[i]);
  // open a ROOT file for output and dump everything inside
  TFile *RootFileOutput = new TFile(OutputRootFile.c_str(),"recreate");
  for(unsigned int i=0;i<HistoM2.size();i++)HistoM2[i]->Write();
  HistoM2all->Write();
  RootFileOutput->Close();
  cout << "[INFO] Written output into " << OutputRootFile << endl;
}


int main()
{

  ProduceJagsM2spectrum();
  return 0;
}

