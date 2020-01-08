#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "XrayAnalysis.hh"
#include "HistoManager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main(int argc, char** argv)
{
  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheSeed(42); // time(0));
  
  // create run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // set mandatory initialization classes
  //
  DetectorConstruction* detector = new DetectorConstruction;
  PhysicsList* physics = new PhysicsList;
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(physics);
  
  // set user custom classes
  XrayAnalysis* xrayAnal = new XrayAnalysis();
  HistoManager*  histo = new HistoManager();
  xrayAnal->SetHistoManager(histo);
  histo->book();

  // set user action classes
  //
  PrimaryGeneratorAction* genAction = new PrimaryGeneratorAction();
  RunAction* runAction = new RunAction(xrayAnal);
  EventAction* eventAction = new EventAction(xrayAnal);
  SteppingAction* steppingAction = new SteppingAction(detector, xrayAnal);
  runManager->SetUserAction(genAction);
  runManager->SetUserAction(runAction);
  runManager->SetUserAction(eventAction);
  runManager->SetUserAction(steppingAction);
  
  // Initialize G4 kernel
  //
  runManager->Initialize();
  
  // get the pointer to the User Interface manager
  //
  G4UImanager* UI = G4UImanager::GetUIpointer();
  
  if (argc!=1) { // batch mode
    
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI->ApplyCommand(command+fileName);
    
  } else { // define visualization and UI terminal for interactive mode
    
#ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    UI->ApplyCommand("/control/execute vis.mac");
#endif
    
#ifdef G4UI_USE
    G4UIExecutive * ui = new G4UIExecutive(argc, argv);
    ui->SessionStart();
    delete ui;
#endif
    
#ifdef G4VIS_USE
    delete visManager;
#endif
  }

  histo->save(runAction->GetRunNumber());
  // job termination
  //
  if (runManager) delete runManager;
  if (xrayAnal) delete xrayAnal;
  
  return 0;
}
