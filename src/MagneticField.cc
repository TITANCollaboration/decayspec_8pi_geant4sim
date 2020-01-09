#include "MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

MagneticField::MagneticField() : G4UniformMagField(G4ThreeVector())
{
  GetGlobalFieldManager()->SetDetectorField(this);
  GetGlobalFieldManager()->CreateChordFinder(this);
  fMainStrength = 0.*tesla;
  SetMagFieldValue(G4ThreeVector(0.,0., fMainStrength));
}

MagneticField::~MagneticField()
{
}

void MagneticField::SetMagFieldValue(G4ThreeVector fieldVector)
{
  G4FieldManager* fieldMgr= GetGlobalFieldManager();

  if(fieldVector!=G4ThreeVector(0.,0.,0.))
  {
    SetFieldValue(fieldVector);
    fieldMgr->SetDetectorField(this);
  } else {
    G4MagneticField* magField = 0;
    fieldMgr->SetDetectorField(magField);
  }
}

/*void MagneticField::GetFieldValue(const G4double Point[3], G4double* Bfield) const
{
  G4double Bx, By;
  G4double Bz = fMainStrength;

  G4double posR = std::sqrt(std::pow(Point[0],2) + std::pow(Point[1],2));
  G4double cos_theta, sin_theta;

  if (posR > 0) {
    cos_theta = Point[0]/(G4double)posR;
    sin_theta = Point[1]/(G4double)posR;
    Bx = 0;
    By = 0;
  } else {
    Bx = 0;
    By = 0;
  }

  Bfield[0] = Bx;
  Bfield[1] = By;
  Bfield[2] = Bz;

  return;
}*/

G4FieldManager* MagneticField::GetGlobalFieldManager()
{
  return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}
