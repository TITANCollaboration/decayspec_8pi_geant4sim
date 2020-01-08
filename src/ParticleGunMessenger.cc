#include "ParticleGunMessenger.hh"
#include "PrimaryGeneratorGun.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

ParticleGunMessenger::ParticleGunMessenger(PrimaryGeneratorGun* Gun)
 : Action(Gun)
{
  Dir = new G4UIdirectory("/particleGun/");
  Dir->SetGuidance("this particle gun");
  
  atomicNumberCmd = new G4UIcmdWithAnInteger("/particleGun/setAtomicNumber", this);
  atomicNumberCmd->SetGuidance("Set atomic number");
  atomicNumberCmd->SetParameterName("atn", false);
  atomicNumberCmd->SetRange("atn>0");
  atomicNumberCmd->AvailableForStates(G4State_Idle);
  
  elementNameCmd = new G4UIcmdWithAString("/particleGun/setElementName", this);
  elementNameCmd->SetGuidance("Set element name");
  elementNameCmd->SetParameterName("eName", false);
  elementNameCmd->AvailableForStates(G4State_Idle);
  
  spinStateCmd = new G4UIcmdWithAString("/particleGun/setSpinState", this);
  spinStateCmd->SetGuidance("Set spin state");
  spinStateCmd->SetParameterName("sState", false);
  spinStateCmd->AvailableForStates(G4State_Idle);
  
  minAngleCmd = new G4UIcmdWithADoubleAndUnit("/particleGun/setMinAngle", this);
  minAngleCmd->SetGuidance("Set z-dir minimum angle spread");
  minAngleCmd->SetParameterName("angle", false);
  minAngleCmd->SetRange("angle>=0");
  minAngleCmd->AvailableForStates(G4State_Idle);
  
  maxAngleCmd = new G4UIcmdWithADoubleAndUnit("/particleGun/setMaxAngle", this);
  maxAngleCmd->SetGuidance("Set z-dir maximum angle spread");
  maxAngleCmd->SetParameterName("angle", false);
  maxAngleCmd->SetRange("angle>=0");
  maxAngleCmd->AvailableForStates(G4State_Idle);

  radiusCmd = new G4UIcmdWithADoubleAndUnit("/particleGun/setCloudRadius", this);
  radiusCmd->SetGuidance("Set cloud radius with unit");
  radiusCmd->SetParameterName("radius", false);
  radiusCmd->SetRange("radius>=0");
  radiusCmd->AvailableForStates(G4State_Idle);
  
  radiiCmd = new G4UIcmdWith3VectorAndUnit("/particleGun/setRadii", this);
  radiiCmd->SetGuidance("Set radii in 3 vector with unit");
  radiiCmd->SetParameterName("x", "y", "z", false, false);
  radiiCmd->AvailableForStates(G4State_Idle);
  
  positionCmd = new G4UIcmdWith3VectorAndUnit("/particleGun/setPosition", this);
  positionCmd->SetGuidance("Set position in 3 vector with unit");
  positionCmd->SetParameterName("x", "y", "z", false, false);
  positionCmd->AvailableForStates(G4State_Idle);
  
  directionCmd = new G4UIcmdWith3Vector("/particleGun/setDirection", this);
  directionCmd->SetGuidance("Set direction in 3 vector with unit");
  directionCmd->SetParameterName("x", "y", "z", false, false);
  directionCmd->AvailableForStates(G4State_Idle);

  updateGunCmd = new G4UIcmdWithoutParameter("/particleGun/updateGun", this);
  updateGunCmd->SetGuidance("Update gun to read from file");
  updateGunCmd->AvailableForStates(G4State_Idle);
  
  toggleGaussCmd = new G4UIcmdWithoutParameter("/particleGun/toggleGauss", this);
  toggleGaussCmd->SetGuidance("Toggle position randomizer");
  toggleGaussCmd->AvailableForStates(G4State_Idle);
}

ParticleGunMessenger::~ParticleGunMessenger()
{
  delete toggleGaussCmd;
  delete updateGunCmd;
  delete directionCmd;
  delete positionCmd;
  delete radiusCmd;
  delete radiiCmd;
  delete minAngleCmd;
  delete maxAngleCmd;
  delete spinStateCmd;
  delete elementNameCmd;
  delete atomicNumberCmd;
  delete Dir;
}

void ParticleGunMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if (command == atomicNumberCmd)
    { Action->SetAtomicNumber(atomicNumberCmd->GetNewIntValue(newValue)); }
  if (command == elementNameCmd)
    { Action->SetElementName(newValue); }
  if (command == spinStateCmd)
    { Action->SetSpinState(newValue); }
  if (command == minAngleCmd)
    { Action->SetMinAngle(minAngleCmd->GetNewDoubleValue(newValue)); }
  if (command == maxAngleCmd)
    { Action->SetMaxAngle(maxAngleCmd->GetNewDoubleValue(newValue)); }
  if (command == radiusCmd) {
    G4double radius = radiusCmd->GetNewDoubleValue(newValue);
    Action->SetXRad(radius);
    Action->SetYRad(radius);
    Action->SetZRad(radius);
  }
  if (command == radiiCmd) {
    G4ThreeVector radii = radiiCmd->GetNew3VectorValue(newValue);
    Action->SetXRad(radii.getX());
    Action->SetYRad(radii.getY());
    Action->SetZRad(radii.getZ());
  }
  if (command == positionCmd) {
    G4ThreeVector position = positionCmd->GetNew3VectorValue(newValue);
    Action->SetXPos(position.getX());
    Action->SetYPos(position.getY());
    Action->SetZPos(position.getZ());
  }
  if (command == directionCmd) {
    G4ThreeVector direction = directionCmd->GetNew3VectorValue(newValue);
    Action->SetXDir(direction.getX());
    Action->SetYDir(direction.getY());
    Action->SetZDir(direction.getZ());
  }
  if (command == updateGunCmd)
    { Action->ReadFromFile(); }
  if (command == toggleGaussCmd)
    { Action->ToggleGauss(); }
}
