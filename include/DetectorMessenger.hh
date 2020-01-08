#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
//class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class DetectorMessenger: public G4UImessenger
{
public:
  DetectorMessenger(DetectorConstruction*);
  ~DetectorMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  DetectorConstruction* Detector;
    
  G4UIdirectory* Dir;
  G4UIdirectory* dcDir;
  G4UIdirectory* windowDir;
  G4UIdirectory* sideDetectorDir;
  G4UIdirectory* diagDetectorDir;
  G4UIcmdWithAString* WindowMatCmd;
  G4UIcmdWithAString* SideDetectorMatCmd;
  G4UIcmdWithAString* DiagDetectorMatCmd;
  G4UIcmdWithoutParameter* UpdateCmd;
};

#endif
