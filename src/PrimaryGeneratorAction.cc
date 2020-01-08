#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorGun.hh"
#include "PrimaryGeneratorSource.hh"
#include "PrimaryGeneratorMessenger.hh"

#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  gpsGun = new G4GeneralParticleSource();
  
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
  
  actionSource = new PrimaryGeneratorSource(gpsGun);
  actionGun = new PrimaryGeneratorGun(particleGun);
  
  selectedAction = 1;
  messenger = new PrimaryGeneratorMessenger(this);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete actionGun;
  delete actionSource;
  delete particleGun;
  delete gpsGun;
  delete messenger;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  switch(selectedAction)
    {
    case 1:
      actionSource->GeneratePrimaries(anEvent);
      break;
    case 2:
      actionGun->GeneratePrimaries(anEvent);
      break;
    default:
      G4cerr << "Invalid generator action" << G4endl;
    }
}


