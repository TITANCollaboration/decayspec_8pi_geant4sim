#include "RunAction.hh"
#include "RunMessenger.hh"
#include "XrayAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

RunAction::RunAction(XrayAnalysis* xAnal)
  : XA(xAnal), runno(0)
{
  messenger = new RunMessenger(this);
}

RunAction::~RunAction()
{
  if (messenger) delete messenger;
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4int runNb = aRun->GetRunID();
  G4cout << "Beginning of run number: " << runNb << "." << G4endl;
  G4cout << "even though our own run number is " << runno << G4endl;
  // set random numbers to something related to runno
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  CLHEP::HepRandom::setTheSeed(runno); // time(0));
 
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;
  G4cout << "End of run, number of events: " << NbOfEvents << "." << G4endl;
  // process xrays
  XA->ProcessRun();
}
