#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class PrimaryGeneratorSource;
class PrimaryGeneratorGun;
class PrimaryGeneratorMessenger;
class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);
  
  G4GeneralParticleSource* GetGPS() { return gpsGun; };
  G4ParticleGun* GetParticleGun()   { return particleGun; };
  void SelectAction(G4int i) { selectedAction = i; };
  G4int GetSelectedAction()  { return selectedAction; };
  PrimaryGeneratorSource* GetActionSource() { return actionSource; };
  PrimaryGeneratorGun*    GetActionGun()    { return actionGun; };

private:
  G4int selectedAction;
  G4GeneralParticleSource*   gpsGun;
  G4ParticleGun*             particleGun;
  PrimaryGeneratorSource*    actionSource;
  PrimaryGeneratorGun*       actionGun;
  PrimaryGeneratorMessenger* messenger;
};

#endif


