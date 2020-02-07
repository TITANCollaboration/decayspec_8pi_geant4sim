#include "PrimaryGeneratorSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

PrimaryGeneratorSource::PrimaryGeneratorSource(G4GeneralParticleSource* gun) : gpsGun(gun)
{}

PrimaryGeneratorSource::~PrimaryGeneratorSource()
{}

void PrimaryGeneratorSource::GeneratePrimaries(G4Event* anEvent)
{
    //JonR: Had thought I was going to code in a way for geant to read in a file that contained ion intensities over time
    //but after talking to Connor N. it seems that the better approach may be to have the EBIT python simulator just output
    //a GEANT macro file which is probably easier.  Will need to stitch together a bunch of ROOT files in the end.
    
    //G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    //G4ParticleDefinition* particle = particleTable->FindParticle("ion");
    //gpsGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle(particle));
    //gpsGun->SetParticleEnergy(0);
    gpsGun->GeneratePrimaryVertex(anEvent);
}
