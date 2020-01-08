#ifndef MagneticField_h
#define MagneticField_h 1

#include "G4UniformMagField.hh"
#include "globals.hh"

class G4FieldManager;

class MagneticField : public G4UniformMagField
{
public:
  MagneticField();
  ~MagneticField();

  void SetMagFieldValue(G4ThreeVector fieldVector);
  //void GetFieldValue(const G4double Point[3], G4double* Bfield) const;

private:
  G4double fMainStrength;

protected:
  G4FieldManager* GetGlobalFieldManager();
};

#endif
