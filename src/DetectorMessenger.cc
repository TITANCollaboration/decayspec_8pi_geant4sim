#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
//#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* det)
  :Detector(det)
{   
  Dir = new G4UIdirectory("/ebit/");
  Dir->SetGuidance("this application");

  dcDir = new G4UIdirectory("/ebit/dc/");
  dcDir ->SetGuidance("detector construction control");
  
  
  sideDetectorDir = new G4UIdirectory("/ebit/dc/detectorSide/");
  sideDetectorDir ->SetGuidance("side detector settings");
  
  
  SideDetectorMatCmd = new G4UIcmdWithAString("/ebit/dc/detectorSide/material", this);
  SideDetectorMatCmd->SetGuidance("Set side detector material");
  SideDetectorMatCmd->SetParameterName("choice", false);
  SideDetectorMatCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  
  
  UpdateCmd = new G4UIcmdWithoutParameter("/ebit/dc/update", this);
  UpdateCmd->SetGuidance("Update detector geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
  delete UpdateCmd;
  delete SideDetectorMatCmd;
  delete sideDetectorDir;
  delete dcDir;
  delete Dir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  
  if (command == SideDetectorMatCmd)
    { Detector->SetSideDetectorMaterial(newValue); }
  
  if (command == UpdateCmd)
    { Detector->UpdateGeometry(); }
}
