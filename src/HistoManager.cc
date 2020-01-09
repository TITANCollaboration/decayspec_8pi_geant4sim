//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file analysis/AnaEx02/src/HistoManager.cc
/// \brief Implementation of the HistoManager class
//
// $Id: HistoManager.cc 65827 2012-11-29 10:21:47Z gcosmo $
// GEANT4 tag $Name: geant4-09-04 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
:rootFile(0),ntupl(0)
{

  // histograms
  for (G4int k=0; k<MaxHisto; k++) histo[k] = 0;

  // ntuple
  ntupl = 0;
  pvolName=&volName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  if ( rootFile ) delete rootFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::book()
{
 // Creating a tree container to handle histograms and ntuples.
 // This tree is associated to an output file.
 //
 //G4String fileName = "rebit.root";
  char fntemplate[] = "_rebitXXXXXX";
  rFileName = G4String(mkstemp(fntemplate))+".root"; // jonr changed to mkstemp..
  std::cout << "root file name >> " << rFileName << " << " << std::endl;
 //G4cout << "in book" << G4endl;
  rootFile = new TFile(rFileName.c_str(),"RECREATE");
 //G4cout << "in book 2" << G4endl;
 if(!rootFile) {
   G4cout << " HistoManager::book :"
          << " problem creating the ROOT TFile "
          << G4endl;
   return;
 }
 /*
 histo[1] = new TH1D("1", "Edep in absorber", 100, 0., 800*CLHEP::MeV);
 if (!histo[1]) G4cout << "\n can't create histo 1" << G4endl;
 histo[2] = new TH1D("2", "Edep in gap", 100, 0., 100*CLHEP::MeV);
 if (!histo[2]) G4cout << "\n can't create histo 2" << G4endl;
 histo[3] = new TH1D("3", "trackL in absorber", 100, 0., 1*CLHEP::m);
 if (!histo[3]) G4cout << "\n can't create histo 3" << G4endl;
 histo[4] = new TH1D("4", "trackL in gap", 100, 0., 50*CLHEP::cm);
 if (!histo[4]) G4cout << "\n can't create histo 4" << G4endl;
 */

 // create 1 ntuple in subdirectory "tuples"
 //
 ntupl = new TTree("T", "T");
 ntupl->Branch("nrun", &nrun, "nrun/I");
 ntupl->Branch("nevt", &nevt, "nevt/I");
 ntupl->Branch("npar", &npar, "npar/I");
 ntupl->Branch("nvol", &nvol, "nvol/I");
 ntupl->Branch("nhit", &nhit, "nhit/I");

 ntupl->Branch("volEmeas", &volEmeas, "volEmeas[nvol]/F");
 ntupl->Branch("volEdep", &volEdep, "volEdep[nvol]/F");
 ntupl->Branch("volNhits", &volNhits, "volNhits[nvol]/I");
 ntupl->Branch("volName", &pvolName);
 // string booking according to http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=1657

 ntupl->Branch("hEdep", &hEdep, "hEdep[nhit]/F");
 ntupl->Branch("hx", &hx, "hx[nhit]/F");
 ntupl->Branch("hy", &hy, "hy[nhit]/F");
 ntupl->Branch("hz", &hz, "hz[nhit]/F");
 ntupl->Branch("hTrackId", &hTrackId, "hTrackId[nhit]/I");
 ntupl->Branch("hv", &hVol);

 ntupl->Branch("tId", &tId, "tId[npar]/I");
 ntupl->Branch("tParentId", &tParentId, "tParentId[npar]/I");
 ntupl->Branch("tPdgCode", &tPdgCode, "tPdgCode[npar]/I");


 /*
 ntupl->Branch("Eabs", &Eabs, "Eabs/D");
 ntupl->Branch("Egap", &Egap, "Egap/D");
 ntupl->Branch("Labs", &Labs, "Labs/D");
 ntupl->Branch("Lgap", &Lgap, "Lgap/D");
 */

 G4cout << "\n----> Histogram file is opened in " << rFileName << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::save(G4int runno) {
  std::cout << "entering save" << std::endl;
  std::cout << runno << std::endl;

  if (rootFile) {
    std::cout << "write" << std::endl;
    rootFile->Write();       // Writing the histograms to the file
    std::cout << "close" << std::endl;
    rootFile->Close();        // and closing the tree (and the file)
    //G4cout << "----> Histogram Tree is saved in " << rFileName << G4endl;

    //delete rootFile;
  }

  if (1) {
    std::ostringstream nfn;
    nfn << "rebit_";
    nfn << runno;
    nfn << ".root";
    std::cout << "rename" << std::endl;
    std::cout << rFileName.c_str() << " " << nfn.str().c_str() << std::endl;
    int rc = rename(rFileName.c_str(), nfn.str().c_str());
    if (rc==-1) {
      G4cout << "problem with output files " << rFileName << " and " << nfn.str() << G4endl;
    }
    else {
      G4cout << "----> Histogram Tree is renamed to " << nfn.str() << G4endl;
    }
  }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
  if (ih >= MaxHisto) {
    G4cout << "---> warning from HistoManager::FillHisto() : histo " << ih
           << " does not exist. (xbin=" << xbin << " weight=" << weight << ")"
           << G4endl;
    return;
  }
 if  (histo[ih]) { histo[ih]->Fill(xbin, weight); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Normalize(G4int ih, G4double fac)
{
  if (ih >= MaxHisto) {
    G4cout << "---> warning from HistoManager::Normalize() : histo " << ih
           << " does not exist. (fac=" << fac << ")" << G4endl;
    return;
  }
  if (histo[ih]) histo[ih]->Scale(fac);
}

void HistoManager::SetParticleInfo(std::vector<G4int> trackid,std::vector<G4int> parentid,std::vector<G4int> pdg) {
  G4int N=(G4int)trackid.size();
  if (N>=PARMAX) {
    N=PARMAX;
    G4cout << "WARNING (HistoManager): Too many particles. Truncating." << G4endl;
  }
  for (G4int i=0; i<N; i++) {
    tId[i]=trackid[i];
    tParentId[i]=parentid[i];
    tPdgCode[i]=pdg[i];
  }
  npar=N;
}


void HistoManager::SetHitInfo(std::vector<G4double> e, std::vector<G4String> v,
			      std::vector<G4double> x,std::vector<G4double> y,std::vector<G4double> z,
			      std::vector<G4int> trackid) {

  G4int N=(G4int)e.size();
  if (N>=HITMAX) {
    N=HITMAX;
    G4cout << "WARNING (HistoManager): Too many hits. Truncating." << G4endl;
  }
  hVol.clear();
  for (G4int i=0; i<N; i++) {
    hEdep[i]=e[i];
    hx[i]=x[i];
    hy[i]=y[i];
    hz[i]=z[i];
    hVol.push_back(v[i]);
    hTrackId[i]=trackid[i];
  }
  nhit=N;
}

void HistoManager::SetVolInfo(std::vector<G4String> vn, std::vector<G4double> volem,
			      std::vector<G4double> voled, std::vector<G4int> nvhits) {

  G4int N=(G4int)vn.size();
  if (N>=VOLMAX) {
    N=VOLMAX;
    G4cout << "WARNING (HistoManager): Too many volumes. Truncating." << G4endl;
  }
  pvolName->clear();
  for (G4int i=0; i<N; i++) {
    volEmeas[i]=volem[i];
    volEdep[i]=voled[i];
    volNhits[i]=nvhits[i];
    pvolName->push_back(vn[i].c_str());
  }
  nvol=N;
}

void HistoManager::FillNtuple(G4int nr, G4int ne, G4int np, G4int nv, G4int nh) {
  nrun=nr; nevt=ne;
  //npar=np; nvol=nv; nhit=nh;
  if (ntupl) ntupl->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void HistoManager::PrintStatistic()
{
  if(histo[1]) {
    G4cout << "\n ----> print histograms statistic \n" << G4endl;

    G4cout
    << " EAbs : mean = " << G4BestUnit(histo[1]->GetMean(), "Energy")
            << " rms = " << G4BestUnit(histo[1]->GetRMS(),  "Energy") << G4endl;
    G4cout
    << " EGap : mean = " << G4BestUnit(histo[2]->GetMean(), "Energy")
            << " rms = " << G4BestUnit(histo[2]->GetRMS(),  "Energy") << G4endl;
    G4cout
    << " LAbs : mean = " << G4BestUnit(histo[3]->GetMean(), "Length")
            << " rms = " << G4BestUnit(histo[3]->GetRMS(),  "Length") << G4endl;
    G4cout
    << " LGap : mean = " << G4BestUnit(histo[4]->GetMean(), "Length")
            << " rms = " << G4BestUnit(histo[4]->GetRMS(),  "Length") << G4endl;

  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


