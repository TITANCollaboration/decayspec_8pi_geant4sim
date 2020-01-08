#ifndef XrayAnalysis_h
#define XrayAnalysis_h 1

#include "globals.hh"
#include <map>
#include <vector>
#include "G4ThreeVector.hh"
#include "HistoManager.hh"

class SiliconDetector;
class XrayAnalysisMessenger;
struct PartialHit {
  G4int detno;
  G4int trackID;
  G4int parentID;
  G4double edep;
  G4String volume;
  G4String particle;
  G4int particleID;
  G4String process;
  G4ThreeVector pos;
};
struct FullHit {
  G4int evtNb;
  G4int detno;
  G4int trackID;
  G4double edep;
  G4String volume;
  G4String particle;
  G4String process;
  G4ThreeVector pos;
};

class XrayAnalysis
{
public:
  XrayAnalysis();
  ~XrayAnalysis();
  
  void CreateHit(G4int, G4int, G4int, G4double, G4String, G4String, G4String, G4ThreeVector, G4int);
  void ProcessEvent(int);
  void ProcessRun();
  
  void SetDirectory(G4String str) { outdirectory = str; };
  void SetFileName(G4String str) { filename = str; };
  void SetFileType(G4String str) { filetype = str; };
  void SetPrintOption(G4int opt) { printopt = opt; };
  void SetHistoManager(HistoManager* hm) { histo = hm; };

private:
  std::vector<PartialHit> currHits;
  std::vector<FullHit> totalHits;
  SiliconDetector* siliDetector;
  XrayAnalysisMessenger* messenger;
  HistoManager* histo;
  
  G4String outdirectory;
  G4String filename;
  G4String filetype;
  G4int printopt;
  
  std::vector< std::vector<PartialHit> > FindPartialHits();
  FullHit MakeFullHit(std::vector<PartialHit>);
  void PrintFile();
  void PrintEdepOnly(std::map<G4int, std::vector<G4double> >);
};

#endif
