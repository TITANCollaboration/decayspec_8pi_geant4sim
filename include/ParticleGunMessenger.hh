#ifndef ParticleGunMessenger_h
#define ParticleGunMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorGun;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter;

class ParticleGunMessenger : public G4UImessenger
{
public:
  ParticleGunMessenger(PrimaryGeneratorGun*);
  ~ParticleGunMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  PrimaryGeneratorGun* Action;
    
  G4UIdirectory*             Dir;
  G4UIcmdWithAnInteger*      atomicNumberCmd;
  G4UIcmdWithAString*        elementNameCmd;
  G4UIcmdWithAString*        spinStateCmd;
  G4UIcmdWithADoubleAndUnit* minAngleCmd;
  G4UIcmdWithADoubleAndUnit* maxAngleCmd;
  G4UIcmdWithADoubleAndUnit* radiusCmd;
  G4UIcmdWith3VectorAndUnit* radiiCmd;
  G4UIcmdWith3VectorAndUnit* positionCmd;
  G4UIcmdWith3Vector*        directionCmd;
  G4UIcmdWithoutParameter*   updateGunCmd;
  G4UIcmdWithoutParameter*   toggleGaussCmd;
};

#endif
