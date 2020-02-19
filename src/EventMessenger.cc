#include "EventMessenger.hh"
#include "EventAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

EventMessenger::EventMessenger(EventAction* EvAct) : eventAction(EvAct)
{   
  Dir = new G4UIdirectory("/ebit/");
  Dir->SetGuidance("this example");

  eventDir = new G4UIdirectory("/ebit/event/");
  eventDir ->SetGuidance("event control");
      
  PrintCmd = new G4UIcmdWithAnInteger("/ebit/event/printModulo", this);
  PrintCmd->SetGuidance("Print events modulo n");
  PrintCmd->SetParameterName("EventNb", false);
  PrintCmd->SetRange("EventNb>0");
  PrintCmd->AvailableForStates(G4State_Idle);
}

EventMessenger::~EventMessenger()
{
  delete PrintCmd;
  delete eventDir;
  delete Dir;     
}

void EventMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
    //  if (command == PrintCmd)
    //{eventAction->SetPrintModulo(PrintCmd->GetNewIntValue(newValue));}
}
