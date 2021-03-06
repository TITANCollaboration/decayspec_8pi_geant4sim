#include "HistoMessenger.hh"
#include "HistoManager.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"


HistoMessenger::HistoMessenger(HistoManager* histEvt) : hist(histEvt)//G4UImessenger()
{
 
  Dir = new G4UIdirectory("/histo/");
  Dir->SetGuidance("Controls aspects of ROOT histograms");

  FileNameCmd = new G4UIcmdWithAString("/histo/filename", this);
  FileNameCmd->SetGuidance("Set output name");
  FileNameCmd->SetParameterName("choice", false);
  FileNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  /*  selectActionCmd = new G4UIcmdWithAnInteger("/pga/selectGunAction", this);
  selectActionCmd->SetGuidance("Select primary generator action");
  selectActionCmd->SetGuidance(" id = 1 : General particle source");
  selectActionCmd->SetGuidance(" id = 2 : Particle gun");
  selectActionCmd->SetParameterName("id", false);
  selectActionCmd->SetRange("id>0 && id<3");
  selectActionCmd->AvailableForStates(G4State_Idle);*/
}

HistoMessenger::~HistoMessenger()
{
    //  delete selectActionCmd;
  delete Dir;
}

void HistoMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
       if (command == FileNameCmd)
            {
                hist->setMyFileName(newValue);
            }
       /*  if (command == selectActionCmd)
        { Action->SelectAction(selectActionCmd->GetNewIntValue(newValue)); } */
}
