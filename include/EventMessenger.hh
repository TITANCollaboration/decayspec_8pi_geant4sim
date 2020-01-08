#ifndef EventMessenger_h
#define EventMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class EventAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;

class EventMessenger: public G4UImessenger
{
public:
  EventMessenger(EventAction*);
  ~EventMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  EventAction* eventAction;
    
  G4UIdirectory*        Dir;       
  G4UIdirectory*        eventDir;   
  G4UIcmdWithAnInteger* PrintCmd;
};

#endif
