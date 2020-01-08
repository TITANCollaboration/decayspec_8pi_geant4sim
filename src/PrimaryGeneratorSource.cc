#include "PrimaryGeneratorSource.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

PrimaryGeneratorSource::PrimaryGeneratorSource(G4GeneralParticleSource* gun)
  : gpsGun(gun)
{}

PrimaryGeneratorSource::~PrimaryGeneratorSource()
{}

void PrimaryGeneratorSource::GeneratePrimaries(G4Event* anEvent)
{
  gpsGun->GeneratePrimaryVertex(anEvent);
}
