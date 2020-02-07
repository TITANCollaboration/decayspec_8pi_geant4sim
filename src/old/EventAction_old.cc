#include "EventAction.hh"
#include "EventMessenger.hh"
#include "XrayAnalysis.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"

EventAction::EventAction(XrayAnalysis* xray)
  : XA(xray)
{
  printModulo = 1;
  messenger = new EventMessenger(this);
}

EventAction::~EventAction()
{
  if (messenger) delete messenger;
}

void EventAction::BeginOfEventAction(const G4Event*)
{
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();
  if (evtNb % printModulo == 0) 
    //G4cout << "end of event " << std::setw(6) << evtNb << G4endl;
  // process xrays
  XA->ProcessEvent(evtNb);
}
