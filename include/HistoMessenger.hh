#ifndef HISTOMESSENGER_HH
#define HISTOMESSENGER_HH

#include "globals.hh"
#include "G4UImessenger.hh"
#include "HistoManager.hh"

class HistoManager;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithABool;

class HistoMessenger : public G4UImessenger
{
public:
  HistoMessenger(HistoManager*);
  ~HistoMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
    
    G4UIdirectory*             Dir;
    /*  G4UIcmdWithAnInteger*      atomicNumberCmd;
  G4UIcmdWithAString*        elementNameCmd;
  G4UIcmdWithAString*        spinStateCmd;
  G4UIcmdWithADoubleAndUnit* minAngleCmd;
  G4UIcmdWithADoubleAndUnit* maxAngleCmd;
  G4UIcmdWithADoubleAndUnit* radiusCmd;
  G4UIcmdWith3VectorAndUnit* radiiCmd;
  G4UIcmdWith3VectorAndUnit* positionCmd;
  G4UIcmdWith3Vector*        directionCmd;
  G4UIcmdWithoutParameter*   updateGunCmd;
  G4UIcmdWithoutParameter*   toggleGaussCmd;*/
};

#endif
