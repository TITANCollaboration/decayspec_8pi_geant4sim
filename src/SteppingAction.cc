#include "SteppingAction.hh"
#include "G4Step.hh"

#include "DetectorConstruction.hh"
//#include "XrayAnalysis.hh"
#include "EventAction.hh"
#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include <sstream>
#include <vector>
#include <regex>	

SteppingAction::SteppingAction(DetectorConstruction* detCon, EventAction* event) : G4UserSteppingAction(), fDetector(detCon), fEventAction(event)
    //DC(detCon), XA(event)
{
}

SteppingAction::~SteppingAction()
{
}

// JonR: Why can't C++ have a decent way to split strings build into it!?!? just why...
// All this function does is split a string into a vector based on a deliminator
// this way I can get the actual detector number from av_2_impr_?_8piGermaniumBlockLog_pv_0
// where ? is the # of the detector.  Using  volume->GetCopyNo() does not work well for this
// so don't use it.  It'll give you some random(ish?) numbers
std::vector<std::string> SteppingAction::split(std::string const& str, std::string const& delim)
{
   using std::string;
   string::size_type start(0);
   string::size_type end(string::npos);
   std::vector<string> sub;

   while( (end = str.find(delim,start)) != string::npos)
   {
      sub.push_back(str.substr(start, end - start));
      start = end + delim.size();
   }
   if(start < str.size() )sub.push_back(str.substr(start, str.size() - start));
   return sub;
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
    // get volume of the current step
    G4VPhysicalVolume* volume;  
    G4int detnum, trackID, parentID, particlePDGenc;
    //  G4double edep;
    G4String volName, particleName, processName;
    G4int particleType = 0, processType = 0;
    G4ThreeVector pos;
    size_t found;

    //****JonR: Go through these later
    G4bool trackSteps   = false;
    G4int systemID      = 9999;
    G4int evntNb;
    fDet = 0;
    fCry = 0;
    G4String mnemonic = "ebit";
    G4int targetZ = -1;
    //G4int evntNb;
    evntNb =  fEventAction->GetEventNumber();
    //****
    
    volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    volName = volume->GetName();

    //detno = (volume->GetCopyNo() * 2) + 2;
    // detnum = volume->GetCopyNo();  //JonR: This goes weird, don't use it.. 
    //  G4cout << "VolName: " << volName << "\t DetNum: "<< detnum << "\n";
    //    volName = volume->GetName(); //std::to_string(detno); 
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
		processName = theTrack->GetCreatorProcess()->GetProcessName();
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
    G4double time2 = point2->GetGlobalTime();
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

        // JonR: we just get the detector # here
        detnum = std::stoi(split(volName.c_str(), "_")[3]);  // JonR: Why can't C++ have a decent way to split strings build into it!?!? just why... 
        // G4cout << "VolName: " << volName << "\t DetNum: "<< detnum << "\n";
        // JonR: Throw the data into ROOT
        fEventAction->AddHitTracker(mnemonic, evntNb, trackID, parentID, fStepNumber, particleType, processType, systemID, fCry-1, detnum, edep, pos2.x(), pos2.y(), pos2.z(), time2, targetZ);
  
    }
}
