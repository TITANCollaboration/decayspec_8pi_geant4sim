#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <vector>

class G4Step;
class DetectorConstruction;
//class XrayAnalysis;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
    
    SteppingAction(DetectorConstruction*, EventAction*);
    
    ~SteppingAction();
    std::vector<std::string> split(std::string const& str, std::string const& delim);

    void UserSteppingAction(const G4Step*);
    
private:
    //    DetectorConstruction* DC;
    //  XrayAnalysis* XA;
    //G4int totalParticles = 0;
    DetectorConstruction* fDetector;
    EventAction*          fEventAction;

    // Griffin
    void SetDetAndCryNumberForGriffinComponent( G4String );
    void SetDetAndCryNumberForDeadLayerSpecificGriffinCrystal(G4String);
    void SetDetNumberForGenericDetector( G4String );
    void SetDetNumberForAncillaryBGODetector( G4String );
    void SetDetAndCryNumberForSpiceDetector( G4String ); //to get 10 total detectors

    G4int FindTrueGriffinDetector(G4int);

    G4int fStepNumber;
    G4int fDet;
    G4int fCry;
    G4int fTrueGriffinDetectorMap[16];
    G4bool fGriffinDetectorMapSet;

    G4int fNumberOfAssemblyVols;

    //G4String G4intToG4String(G4int value);
    //G4String GetCrystalColour(G4int value);
};

#endif


