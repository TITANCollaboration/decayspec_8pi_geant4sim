#ifndef PrimaryGeneratorSource_h
#define PrimaryGeneratorSource_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

class PrimaryGeneratorSource : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorSource(G4GeneralParticleSource*);    
  ~PrimaryGeneratorSource();

public:
  void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource* gpsGun;
};

#endif
