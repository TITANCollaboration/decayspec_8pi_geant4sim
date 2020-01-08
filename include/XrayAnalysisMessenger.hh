#ifndef XrayAnalysisMessenger_h
#define XrayAnalysisMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class XrayAnalysis;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

class XrayAnalysisMessenger: public G4UImessenger
{
public:
  XrayAnalysisMessenger(XrayAnalysis*);
  ~XrayAnalysisMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  XrayAnalysis* XA;
    
  G4UIdirectory* Dir;
  G4UIdirectory* xaDir;
  G4UIcmdWithAString* DirectoryCmd;
  G4UIcmdWithAString* FileNameCmd;
  G4UIcmdWithAString* FileTypeCmd;
  G4UIcmdWithAnInteger* PrintOptionCmd;
};

#endif
