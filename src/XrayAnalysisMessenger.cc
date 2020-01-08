#include "XrayAnalysisMessenger.hh"
#include "XrayAnalysis.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"

XrayAnalysisMessenger::XrayAnalysisMessenger(XrayAnalysis* xray)
  :XA(xray)
{   
  Dir = new G4UIdirectory("/ebit/");
  Dir->SetGuidance("this application");

  xaDir = new G4UIdirectory("/ebit/xa/");
  xaDir ->SetGuidance("xray analysis control");
  
  DirectoryCmd = new G4UIcmdWithAString("/ebit/xa/directory", this);
  DirectoryCmd->SetGuidance("Set output directory");
  DirectoryCmd->SetParameterName("choice", false);
  DirectoryCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  
  FileNameCmd = new G4UIcmdWithAString("/ebit/xa/filename", this);
  FileNameCmd->SetGuidance("Set output name");
  FileNameCmd->SetParameterName("choice", false);
  FileNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  
  FileTypeCmd = new G4UIcmdWithAString("/ebit/xa/filetype", this);
  FileTypeCmd->SetGuidance("Set output type");
  FileTypeCmd->SetParameterName("choice", false);
  FileTypeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  
  PrintOptionCmd = new G4UIcmdWithAnInteger("/ebit/xa/printopt", this);
  PrintOptionCmd->SetGuidance("set print options");
  PrintOptionCmd->SetParameterName("option", true);
  PrintOptionCmd->SetRange("option>=0");
  PrintOptionCmd->SetDefaultValue(0);
  PrintOptionCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XrayAnalysisMessenger::~XrayAnalysisMessenger()
{
  delete PrintOptionCmd;
  delete DirectoryCmd;
  delete FileTypeCmd;
  delete FileNameCmd;
  delete xaDir;
  delete Dir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XrayAnalysisMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if (command == DirectoryCmd)
    { XA->SetDirectory(newValue); }
  if (command == FileNameCmd)
    { XA->SetFileName(newValue); }
  if (command == FileTypeCmd)
    { XA->SetFileType(newValue); }
  if (command == PrintOptionCmd)
    { XA->SetPrintOption(PrintOptionCmd->GetNewIntValue(newValue)); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
