#include "PrimaryGeneratorGun.hh"
#include "PrimaryGeneratorAction.hh"
#include "ParticleGunMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"


#include <iostream>
#include <fstream>
#include <sstream>

PrimaryGeneratorGun::PrimaryGeneratorGun(G4ParticleGun* gun)
  : particleGun(gun)
{
  elementName = "Ba";
  atomicNumber = 133;
  spinState = "";
  xRad = 0.*mm; yRad = 0.*mm; zRad = 0.*mm;
  xPos = 0.*mm; yPos = 0.*mm; zPos = 0.*mm;
  xDir = 0.; yDir = 0.; zDir = 0.;
  minAngle = 0.*deg; maxAngle = 180.*deg;
  gausstrig = false;
  maxIntensity = 0.;
  sumIntensity = 0.;

  fp= fopen("testfile.txt","w");
  
  ReadFromFile();
  
  messenger = new ParticleGunMessenger(this);
}

PrimaryGeneratorGun::~PrimaryGeneratorGun()
{
  delete messenger;
}

void PrimaryGeneratorGun::ReadFromFile()
{
  // clear the vectors
  if (!gunParticle.empty())  gunParticle.clear();
  if (!gunIntensity.empty()) gunIntensity.clear();
  if (!gunEnergy.empty())    gunEnergy.clear();
  maxIntensity = 0.;
  sumIntensity = 0.;
  
  G4cout << "Reading from file..." << G4endl;
  
  // determine file name to read
  std::string atn;
  std::stringstream ss;
  ss << atomicNumber;
  atn = ss.str();
  G4String fileType = ".ion";
  G4String fileName = elementName + atn + spinState + fileType;
  
  std::ifstream inFile;
  inFile.open(fileName);
  
  if(!inFile) {
    G4cout << "Failed to open file " << fileName << G4endl;
    return;
  }
  
  // HEADER FORMAT: number of datasets \n lines per dataset
  G4int nSets;
  inFile >> nSets;
  if (nSets <= 0) {
    G4cout << "Faulty header in file." << G4endl;
    return;
  }
  std::vector<G4int> setLines;
  std::vector<G4double> setModeI;
  G4int nLines = 0;
  for (G4int i=0; i<nSets; i++) {
    G4int line; G4double mode;
    inFile >> line >> mode;
    G4cout << line << mode << G4endl;
    setLines.push_back(line);
    setModeI.push_back(mode);
    nLines += line;
  }
  
  // FORMAT: PARTICLE \t ENERGY \t INTENSITY
  G4String particle;
  G4double intensity, energy;
  
  // read the file
  while (!inFile.eof()) {
    inFile >> particle >> energy >> intensity;
    G4cout << particle << energy << intensity << G4endl;
    gunParticle.push_back(particle);
    gunIntensity.push_back(intensity);
    gunEnergy.push_back(energy);
  }
  
  // temporary fix of duplicate last item
  gunParticle.pop_back();
  gunIntensity.pop_back();
  gunEnergy.pop_back();
  
  // error checking
  if (gunParticle.size() != gunIntensity.size() ||
      gunParticle.size() != gunEnergy.size() ||
      gunIntensity.size() != gunEnergy.size() ||
      (G4int)gunIntensity.size() != nLines) {
    G4cout << "Uneven number of parameters in file, aborting..." << G4endl;
    gunParticle.clear();
    gunIntensity.clear();
    gunEnergy.clear();
    return;
  }
  
  // normalize for each mode
  G4int linecount = 0;
  for (G4int i=0; i<nSets; i++) {
    // sum up the intensities first
    G4double tempInt = 0.;
    for (G4int j=linecount; j<(linecount+setLines[i]); j++)
      tempInt += gunIntensity[j];
    // change the intensities
    for (G4int j=linecount; j<(linecount+setLines[i]); j++)
      gunIntensity[j] *= setModeI[i] / tempInt;
    linecount += setLines[i];
  }
  setLines.clear();
  setModeI.clear();
  
  // normalize to maximum intensity
  for (G4int i=0; i<(G4int)gunIntensity.size(); i++) {
    sumIntensity += gunIntensity[i];
    if (maxIntensity < gunIntensity[i]) maxIntensity = gunIntensity[i];
  }
  
  G4cout << "Read file " << fileName << " successfully!" << G4endl;
  inFile.close();
}

void PrimaryGeneratorGun::GeneratePrimaries(G4Event* anEvent)
{
  G4int n_decaytypes = gunEnergy.size();
  G4double energy;
  G4String particle;
  G4double cumSum1 = 0.;
  G4double cumSum2 = 0.;
  G4double randomNum = G4UniformRand() * sumIntensity;

  for (G4int i=0; i<n_decaytypes; i++) {
    // test for intensity first
    cumSum2 += gunIntensity[i];
    if (randomNum >= cumSum1 && randomNum <= cumSum2) {
      // success!
      // set energy
      particle = gunParticle[i];
      energy = gunEnergy[i] * keV;
      particleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle(particle));
      particleGun->SetParticleEnergy(energy);
      // set random position (within ellipsoid cloud)
      //
      G4double rx, ry, rz;
      //
      //G4double rx=0.*mm, ry=0.*mm, rz=0.*mm;
      if (!gausstrig) {
	rx = xRad*G4UniformRand();
	ry = yRad*G4UniformRand();
	rz = zRad*G4UniformRand();
      } else {
	rx = xRad*G4RandGauss::shoot(1,1)/3.; if (rx > xRad) rx = xRad;
	ry = yRad*G4RandGauss::shoot(1,1)/3.; if (ry > yRad) ry = yRad;
	rz = zRad*G4RandGauss::shoot(1,1)/3.; if (rz > zRad) rz = zRad;
      }
      G4double theta = twopi*G4UniformRand();
      G4double phi = twopi*G4UniformRand() / 2.;
      G4double px = xPos + (rx * std::cos(phi) * std::sin(theta));
      G4double py = yPos + (ry * std::sin(phi) * std::sin(theta));
      G4double pz = zPos + (rz * std::cos(theta));
      particleGun->SetParticlePosition(G4ThreeVector(px,py,pz));
      //  WRITING POSITIONS OF PARTICLE GUN

      fprintf(fp,"%f\t%f\t%f\n",px,py,pz);


      G4double cosTheta = -1.0 + 2.0*G4UniformRand();
      G4double phi_1 = twopi*G4UniformRand();
      G4double sinTheta = sqrt(1. - cosTheta*cosTheta);
      G4double alpha = (maxAngle - minAngle)*G4UniformRand() + minAngle;
      G4double uz = std::cos(alpha);
      //  isotropic particle direction (within angle spread)
      particleGun -> SetParticleMomentumDirection(G4ThreeVector(sinTheta*cos(phi_1),
							    sinTheta*sin(phi_1),
							    uz));//cosTheta));

      
      if (xDir != 0. || yDir != 0. || zDir != 0.) {
	// specified direction
	G4double ux = xDir; G4double uy = yDir; uz = zDir;
        particleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
      }
      
      // shoot a decay event
      particleGun->GeneratePrimaryVertex(anEvent);
      break;
    }
    cumSum1 += gunIntensity[i];
  }
}

void PrimaryGeneratorGun::ToggleGauss() {
  if (!gausstrig) gausstrig = true;
  else gausstrig = false;
  return;
}
