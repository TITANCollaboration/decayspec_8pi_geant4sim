#include "SteppingAction.hh"
#include "G4Step.hh"

#include "DetectorConstruction.hh"
#include "XrayAnalysis.hh"

#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include <sstream>

SteppingAction::SteppingAction(DetectorConstruction* detCon, XrayAnalysis* event) : DC(detCon), XA(event)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
    // get volume of the current step
    G4VPhysicalVolume* volume;  
    G4int detno, trackID, parentID, particlePDGenc;
    //  G4double edep;
    G4String volName, particleName, processName;
    G4int particleType = 0, processType = 0;
    G4ThreeVector pos;
    size_t found;

    volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    volName = volume->GetName();
    
    //detno = (volume->GetCopyNo() * 2) + 2;
    detno = volume->GetCopyNo();

    volName  =volume->GetName(); //std::to_string(detno); 
    //    G4String volname = volume->GetName();

    G4Track* theTrack = aStep->GetTrack();

    // collect energy and track length step by step
    // As it's called more than once, get the Track and assign to variable
    G4double edep = aStep->GetTotalEnergyDeposit();
    G4double ekin = aStep->GetPreStepPoint()->GetKineticEnergy();
    //  edep = 0 ;
    //edep = aStep->GetTotalEnergyDeposit();
    //  if (edep <= 0.) return;
    
    trackID  = theTrack->GetTrackID();
    parentID = theTrack->GetParentID();

    //JonR: Adding a lot of stuff from the Griffin detectorSimulations_v10 code, thank you!!  The previous code was a bit dated
    
    particleName = theTrack->GetParticleDefinition()->GetParticleName();
    
    if (particleName == "gamma")         particleType = 1;
    else if (particleName == "e-")       particleType = 2;
    else if (particleName == "e+")       particleType = 3;
    else if (particleName == "proton")   particleType = 4;
    else if (particleName == "neutron")  particleType = 5;
    else if (particleName == "deuteron") particleType = 6;
    else if (particleName == "C12")      particleType = 7;
    else particleType = 0;

    // this can be modified to add more processes
    if(theTrack->GetCreatorProcess() != NULL) {
		G4String processName = theTrack->GetCreatorProcess()->GetProcessName();
		//G4cout<<"found secondary, particle "<<particleName<<", creation process "<<process<<G4endl;
        if (processName == "RadioactiveDecay")      processType = 1;
        else if (processName == "eIoni")            processType = 2;
        else if (processName == "msc")              processType = 3;
        else if (processName == "Scintillation")    processType = 4;
        else if (processName == "Cerenkov")         processType = 5;
        else  processType = 0;
    } else {
		processType = -1;
    }

    G4StepPoint* point1 = aStep->GetPreStepPoint();
    G4StepPoint* point2 = aStep->GetPostStepPoint();

    G4ThreeVector pos1 = point1->GetPosition();
    G4ThreeVector pos2 = point2->GetPosition();

    //G4double time1 = point1->GetGlobalTime();
    //G4double time2 = point2->GetGlobalTime();
    G4double timePostStepPoint = point2->GetGlobalTime();
    
    particlePDGenc = aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
    
    //adding for position
    pos = aStep->GetPostStepPoint()->GetPosition();
    // retrieve process name when available
    if (parentID == 0) {
        //process = "initStep";
        processName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    } else if (aStep->GetPostStepPoint()->GetProcessDefinedStep() != 0) {
        processName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    } else {
        processName = "UserLimit";
    }
    
    // 8PI energy deposits ////////////////////////////////////////////////////////////////////////////////
    found = volName.find("8piGermaniumBlockLog");
    if (edep != 0 && found!=G4String::npos) {
        //SetDetNumberForGenericDetector(volname);
        //mnemonic.replace(0,3,"8PI");
        //mnemonic.replace(3,2,G4intToG4String(fDet));
        //mnemonic.replace(5,1,GetCrystalColour(fCry));
        //systemID = 6000;
        //        fEventAction->AddHitTracker(mnemonic, evntNb, trackID, parentID, fStepNumber, particleType, processType, systemID, fCry-1, fDet-1, edep, pos2.x(), pos2.y(), pos2.z(), time2, targetZ);
        XA->CreateHit(detno, trackID, parentID, edep, volName, particleName, processName, pos, particlePDGenc);
    }
}
