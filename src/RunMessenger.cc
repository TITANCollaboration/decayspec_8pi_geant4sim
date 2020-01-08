#include "RunMessenger.hh"
#include "RunAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

RunMessenger::RunMessenger(RunAction* RAct)
 :runAction(RAct)
{   
  Dir = new G4UIdirectory("/ebit/");
  Dir->SetGuidance("this example");

  runDir = new G4UIdirectory("/ebit/run/");
  runDir ->SetGuidance("run control");

  runNoCmd = new G4UIcmdWithAnInteger("/ebit/run/runnumber",this);
  runNoCmd->SetGuidance("set run number");
  runNoCmd->SetParameterName("verbose",false);
  runNoCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}

RunMessenger::~RunMessenger()
{
  delete runDir;
  delete Dir;     
  delete runNoCmd;
}

void RunMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {

  if (command == runNoCmd ) {
    runAction->SetRunNumber(runNoCmd->GetNewIntValue(newValue));
  }
}
