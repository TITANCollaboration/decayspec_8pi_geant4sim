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
/// \file analysis/AnaEx02/include/HistoManager.hh
/// \brief Definition of the HistoManager class
//
// $Id: HistoManager.hh 59868 2012-06-20 13:59:51Z gcosmo $
// GEANT4 tag $Name: geant4-09-04 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"
#include "g4root.hh"

#include "G4SystemOfUnits.hh" // new version geant4.10 requires units

const G4int MAXNTCOL            = 15;

///////////////////////////////////////////////////
const G4double MINENERGYTHRES   = 0.001*keV;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TFile;
class TTree;
class TH1D;

const G4int MaxHisto = 5;
const G4int VOLMAX=100;
const G4int HITMAX=1000;
const G4int PARMAX=100;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
public:
  
  HistoManager();
  ~HistoManager();
   
  void book();
  void save(G4int runno=0);

  void FillHisto(G4int id, G4double bin, G4double weight = 1.0);
  void Normalize(G4int id, G4double fac);    

  void FillNtuple(G4double energyAbs, G4double energyGap, G4double trackLAbs, G4double trackLGap);
  void FillNtuple(G4int nrun, G4int nevt, G4int npar, G4int nvol, G4int nhit);
  void SetVolInfo(std::vector<G4String> volNames, std::vector<G4double> volEmeas, std::vector<G4double> volEdep, std::vector<G4int> nvhits);
  void SetHitInfo(std::vector<G4double> e, std::vector<G4String> v, std::vector<G4double> x, std::vector<G4double> y, std::vector<G4double> z, std::vector<G4int> pdg);
  void SetParticleInfo(std::vector<G4int> trackid,std::vector<G4int> parentid,std::vector<G4int> pdg);
  void PrintStatistic();
        
private:
  TFile*   rootFile;
  TH1D*    histo[MaxHisto];            
  TTree*   ntupl;    

  // volumes
  G4float volEmeas[VOLMAX];
  G4float volEdep[VOLMAX];
  G4int volNhits[VOLMAX];
  std::vector<std::string> volName;
  std::vector<std::string>* pvolName;

  //hits
  G4float hEdep[HITMAX];
  G4float hx[HITMAX];
  G4float hy[HITMAX];
  G4float hz[HITMAX];
  G4int hTrackId[HITMAX];
  std::vector<std::string> hVol;
  std::vector<std::string>* phVol;

  //particles
  G4int tId[PARMAX];
  G4int tParentId[PARMAX];
  G4int tPdgCode[PARMAX];

  G4String rFileName;
  G4int nrun,nevt,nvol,npar,nhit;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

