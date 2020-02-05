//#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorGun.hh"

#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
//#include "XrayAnalysis.hh"
#include "HistoManager.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"
//#else
#include "G4RunManager.hh"
//#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

/*void MyActionInitialization::Build() : G4VUserActionInitialization
{
  PrimaryGeneratorAction* genAction = new PrimaryGeneratorAction();
  RunAction* runAction = new RunAction(xrayAnal);
  EventAction* eventAction = new EventAction(xrayAnal);
  SteppingAction* steppingAction = new SteppingAction(detector, xrayAnal);
  SetUserAction(genAction);
  SetUserAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(steppingAction);
}*/


int main(int argc, char** argv)
{
  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheSeed(42); // time(0));

 G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // create run manager
  //

//#ifdef G4MULTITHREADED
//  G4MTRunManager* runManager = new G4MTRunManager;
 // runManager->SetNumberOfThreads(2);
//#else
  G4RunManager* runManager = new G4RunManager;
//#endif


  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  // set mandatory initialization classes
  //
  DetectorConstruction* detector = new DetectorConstruction;
  PhysicsList* physics = new PhysicsList;
  physics->SetVerboseLevel(2);
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(physics);

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // set user custom classes
  //  XrayAnalysis* xrayAnal = new XrayAnalysis();
  //  HistoManager*  histo = new HistoManager();
  //  xrayAnal->SetHistoManager(histo);
  // histo->Book();

  // set user action classes
  //
  PrimaryGeneratorAction* genAction = new PrimaryGeneratorAction();
  //  RunAction* runAction = new RunAction(xrayAnal);
  RunAction* runAction = new RunAction();
  EventAction* eventAction = new EventAction(runAction);
  SteppingAction* steppingAction = new SteppingAction(detector, eventAction);
  runManager->SetUserAction(genAction);
  runManager->SetUserAction(runAction);
  runManager->SetUserAction(eventAction);
  runManager->SetUserAction(steppingAction);

  // Initialize G4 kernel
  //
  runManager->Initialize();

  // get the pointer to the User Interface manager
  //
  //G4UImanager* UI = G4UImanager::GetUIpointer();

    if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

    //  histo->Save();
    //histo->Save(runAction->GetRunNumber());
  // job termination
  //
  if (runManager) delete runManager;
  // if (xrayAnal) delete xrayAnal;

  return 0;
}
