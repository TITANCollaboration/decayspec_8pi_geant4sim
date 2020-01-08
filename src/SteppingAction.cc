#include "SteppingAction.hh"
#include "G4Step.hh"

#include "DetectorConstruction.hh"
#include "XrayAnalysis.hh"

#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include <sstream>

SteppingAction::SteppingAction(DetectorConstruction* dc, XrayAnalysis* xa)
  : DC(dc), XA(xa)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // get volume of the current step
  G4VPhysicalVolume* testVolume  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4int detno, trackID, parentID, particlePDGenc;
  G4double edep;
  G4String volume, particle, process;
//
  G4ThreeVector pos;
// adding for BGO data
  //G4double d_edep;
//
   

   volume = testVolume->GetName();
   //if (volume == DC->GetSideDetector()->GetName() ) {
   detno = (testVolume->GetCopyNo() * 2) + 2;
   detno = testVolume->GetCopyNo();
   std::ostringstream blah;
   blah << detno;
   volume+=blah.str();

   //G4cout << "Hit in detector " << detno << G4endl;
   //}
    //G4cout << "Hit in detector " << detno << G4endl;
  
   //else {
    //G4cout << "No hit detected." << G4endl;
    //return;
   //}
  edep = 0 ;
  edep = aStep->GetTotalEnergyDeposit();
  if (edep <= 0.) return;
  
  trackID  = aStep->GetTrack()->GetTrackID();
  parentID = aStep->GetTrack()->GetParentID();
  particle = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
  particlePDGenc = aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding();

//adding for position
  pos = aStep->GetPostStepPoint()->GetPosition();
  // retrieve process name when available
  if (parentID == 0) {
    //process = "initStep";
    process = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  } else if (aStep->GetPostStepPoint()->GetProcessDefinedStep() != 0) {
    process = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  } else {
    process = "UserLimit";
  }
  
  // // adding for BGO data
   //if (volume == "SideDetector") {
    //process = "test";
    //}
  XA->CreateHit(detno, trackID, parentID, edep, volume, particle, process, pos, particlePDGenc);
}
