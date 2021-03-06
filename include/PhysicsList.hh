#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"

#include "globals.hh"

class PhysicsList: public G4VModularPhysicsList
//G4VUserPhysicsList
{
public:
  PhysicsList();
  ~PhysicsList();

protected:
  void ConstructParticle();
  void ConstructProcess();
  void ConstructEM();
  void ConstructRD();
  void SetCuts();
};

#endif







