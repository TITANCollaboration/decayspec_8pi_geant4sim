#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
 : Action(Gun)
{
  Dir = new G4UIdirectory("/pga/");
  Dir->SetGuidance("this primary generator action");
    
  selectActionCmd = new G4UIcmdWithAnInteger("/pga/selectGunAction", this);
  selectActionCmd->SetGuidance("Select primary generator action");
  selectActionCmd->SetGuidance(" id = 1 : General particle source");
  selectActionCmd->SetGuidance(" id = 2 : Particle gun");
  selectActionCmd->SetParameterName("id", false);
  selectActionCmd->SetRange("id>0 && id<3");
  selectActionCmd->AvailableForStates(G4State_Idle);
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete selectActionCmd;
  delete Dir;
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if (command == selectActionCmd)
    { Action->SelectAction(selectActionCmd->GetNewIntValue(newValue)); }
}
