#ifndef RunMessenger_h
#define RunMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class RunAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

class RunMessenger: public G4UImessenger
{
public:
  RunMessenger(RunAction*);
  ~RunMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  RunAction* runAction;
    
  G4UIdirectory*      Dir;       
  G4UIdirectory*      runDir;

  G4UIcmdWithAnInteger * runNoCmd;
};

#endif
