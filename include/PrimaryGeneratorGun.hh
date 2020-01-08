#ifndef PrimaryGeneratorGun_h
#define PrimaryGeneratorGun_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include <vector>

class ParticleGunMessenger;
class G4ParticleGun;
class G4Event;

class PrimaryGeneratorGun : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorGun(G4ParticleGun*);    
  ~PrimaryGeneratorGun();

public:
  void GeneratePrimaries(G4Event*);
  
  void ReadFromFile();
  void SetAtomicNumber(G4int val)   { atomicNumber = val; };
  void SetElementName(G4String val) { elementName = val; };
  void SetSpinState(G4String val) { spinState = val; };
  void SetXRad(G4double val) { xRad = val; };
  void SetYRad(G4double val) { yRad = val; };
  void SetZRad(G4double val) { zRad = val; };
  void SetXPos(G4double val) { xPos = val; };
  void SetYPos(G4double val) { yPos = val; };
  void SetZPos(G4double val) { zPos = val; };
  void SetXDir(G4double val) { xDir = val; };
  void SetYDir(G4double val) { yDir = val; };
  void SetZDir(G4double val) { zDir = val; };
  void SetMinAngle(G4double val) { minAngle = val; };
  void SetMaxAngle(G4double val) { maxAngle = val; };
  void ToggleGauss();
//
//
//
//

private:
  G4ParticleGun* particleGun;
  G4String       elementName;
  G4int          atomicNumber;
  G4String       spinState;
  
  G4double xRad, yRad, zRad;
  G4double xPos, yPos, zPos;
  G4double xDir, yDir, zDir;
  G4double minAngle, maxAngle;
  G4double maxIntensity, sumIntensity;
  G4bool   gausstrig;
//
//
  FILE *fp;
//
//
  
  std::vector <G4String> gunParticle;
  std::vector <G4double> gunIntensity;
  std::vector <G4double> gunEnergy;
  
  ParticleGunMessenger* messenger;
};

#endif
