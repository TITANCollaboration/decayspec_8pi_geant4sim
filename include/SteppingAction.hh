#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4Step;
class DetectorConstruction;
class XrayAnalysis;

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(DetectorConstruction*, XrayAnalysis*);
  ~SteppingAction();
  
  void UserSteppingAction(const G4Step*);
  
private:
  DetectorConstruction* DC;
  XrayAnalysis* XA;
};

#endif
