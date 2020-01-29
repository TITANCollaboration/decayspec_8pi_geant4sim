#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class MagneticField;
class MaterialsList;
class DetectorMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction();
  
public:
  G4VPhysicalVolume* Construct();
  G4VPhysicalVolume* ConstructAll();
  const G4VPhysicalVolume* GetWorld()          {return pvWorld;};
  // const G4VPhysicalVolume* GetSideDetector()   {return pvSideDetector;};
  const G4VPhysicalVolume* GetElectrodeMid()   {return pvElectrodeMid;};
  const G4VPhysicalVolume* GetElectrodeEnd()   {return pvElectrodeEnd;};
  const G4VPhysicalVolume* GetElectrodeGuard() {return pvElectrodeGuard;};
  const G4VPhysicalVolume* GetElectrodeCone()  {return pvElectrodeCone;};

  // Lets add in the ability to add in the 8pi's
  void AddDetectionSystem8pi(G4int ndet);
  void AddDetectionSystem8piDetector(G4int ndet);

  void CleanGeometry();
  void UpdateGeometry();
  
  void DefineEbitMaterials();
  //void DestroyMaterials();
  void SetVisualization();
  void ConstructTrap();
  void ConstructSiLi();
  
  void SetWindowMaterial(G4String);
  // void SetSideDetectorMaterial(G4String);
  void DefineSuppressedParameters();
  void DefineMaterials();
 

private:
  G4int checkOverlaps;

  // Magnetic Field
  MagneticField* field;
  MaterialsList* mlist;
  DetectorMessenger* messenger;
  
  // World
  G4LogicalVolume*   fLogicWorld;    //pointer to the logical World, this is for 8pi, should probably meld into lvWoorld at some point
  G4LogicalVolume* lvWorld;
  G4VPhysicalVolume* pvWorld;
  G4Material* WorldMater;
  G4String WorldName;
  G4double WorldSize;
  
  G4LogicalVolume* lvSiLi;
  /*  G4VPhysicalVolume* pvSiLi;*/

  G4LogicalVolume* lvSupportStruct;
  G4VPhysicalVolume* pvSupportStruct;

  G4LogicalVolume* lvVessel;
  G4VPhysicalVolume* pvVessel;
  G4LogicalVolume* lvPort8;
  G4VPhysicalVolume* pvPort8;
  G4LogicalVolume* lvFloor;
  G4VPhysicalVolume* pvFloor;
  
  /*
  // Detectors
  G4LogicalVolume* lvSideDetector;
  G4VPhysicalVolume* pvSideDetector;
  G4Material* SideDetectorMater;
  G4String SideDetectorName;
  G4double SideDetectorRadius;
  G4double SideDetectorDist;
  G4double SideDetectorThick;
  */
  G4Material* BdiscMater;
  G4Material* Al2O3Mater;
  G4Material* SSteelMater;
  G4Material* CarbonMater;
  G4Material* CopperMater;
  G4Material* LeadMater;


  /* G4LogicalVolume* lvbdisc;
  G4VPhysicalVolume* pvbdisc;

  // shields
  G4LogicalVolume* lvcu8;
  G4VPhysicalVolume* pvcu8;
  G4LogicalVolume* lvpb8;
  G4VPhysicalVolume* pvpb8;
  */

  /*
  // Dead layers
  G4LogicalVolume* lvSideDeadlayer;
  G4VPhysicalVolume* pvSideDeadlayer;
  G4String SideDeadlayerName;
  G4double SideDeadlayerFrontThick;
  */
  /* //Canister
  G4LogicalVolume* lvSideCanister;
  G4VPhysicalVolume* pvSideCanister;
  G4LogicalVolume* lvSideCanister1;
  G4VPhysicalVolume* pvSideCanister1;
  G4Material* CanisterMater;
  G4String CanisterName;
  G4String CanisterName1;
  G4double SideCanisterInnerRadius;
  G4double SideCanisterOuterRadius;
  G4double SideCanisterDist;
  G4double SideCanisterThick;
  G4double SideCanisterInnerRadius1;
  G4double SideCanisterOuterRadius1;
  G4double SideCanisterThick1;

  G4LogicalVolume* lvcspacer;
  G4VPhysicalVolume* pvcspacer;
  G4LogicalVolume* lvchousing;
  G4VPhysicalVolume* pvchousing;
  G4LogicalVolume* lv_cf_tube;
  G4VPhysicalVolume* pv_cf_tube;
  G4LogicalVolume* lv_cf_cone;
  G4VPhysicalVolume* pv_cf_cone;
  G4LogicalVolume* lv_cf_tube2;
  G4VPhysicalVolume* pv_cf_tube2;

  G4LogicalVolume* lv_sep1;
  G4VPhysicalVolume* pv_sep1;
  G4LogicalVolume* lv_cf2;
  G4VPhysicalVolume* pv_cf2;
  G4LogicalVolume* lv_sep2;
  G4VPhysicalVolume* pv_sep2;
  G4LogicalVolume* lv_paCover;
  G4VPhysicalVolume* pv_paCover;

  G4LogicalVolume* lv_cWindow;
  G4VPhysicalVolume* pv_cWindow;

  G4LogicalVolume* lv_siRing;
  G4VPhysicalVolume* pv_siRing;
  */
  G4LogicalVolume* lv_baPl;
  G4VPhysicalVolume* pv_baPl;
  G4LogicalVolume* lv_endPl;
  G4VPhysicalVolume* pv_endPl;

  G4LogicalVolume* lvRod;
  G4VPhysicalVolume *pvRod0, *pvRod1, *pvRod2, *pvRod3;

  /*// SHEILDING LAYERS
  G4LogicalVolume* lvShieldingCopper;
  //G4LogicalVolume* lvShieldingLead;
  G4VPhysicalVolume* pvShieldingCopper;
  //G4VPhysicalVolume* pvShieldingLead;
  G4Material* ShieldingCopperMater;
 // G4Material* ShieldingLeadMater;
  G4String ShieldingCopperName;
  //G4String ShieldingLeadName;
  G4double ShieldingCopperOuterRadius;
  G4double ShieldingCopperInnerRadius;
  //G4double ShieldingLeadOuterRadius;
  //G4double ShieldingLeadInnerRadius;
  G4double ShieldingCopperDist;
  //G4double ShieldingLeadDist;
  G4double ShieldingCopperThick;
  //G4double ShieldingLeadThick;
  */

  // Inner Windows
  G4LogicalVolume* lvSideInnerWindow;
  G4VPhysicalVolume* pvSideInnerWindow;
  G4Material* WindowMater;
  G4String WindowName;
  G4double SideInnerWindowRadius;
  G4double SideInnerWindowDist;
  G4double SideInnerWindowThick;
  
  // Outer Windows
  G4LogicalVolume* lvSideOuterWindow;
  G4VPhysicalVolume* pvSideOuterWindow;
  G4double SideOuterWindowRadius;
  G4double SideOuterWindowDist;
  G4double SideOuterWindowThick;

  // Ebit Tube
  G4LogicalVolume* lvEbitTube;
  G4VPhysicalVolume* pvEbitTube;
  G4Material* EbitTubeMater;
  G4String EbitTubeName;
  G4double EbitTubeMinR;
  G4double EbitTubeMaxR;
  G4double EbitTubeLength;
  G4double EbitTubeStartPhi;
  G4double EbitTubeSweepPhi;
 
  // Electrode
  G4Material* ElectrodeMater;
  G4String ElectrodeName;
  
  // Electrode Mid
  G4LogicalVolume* lvElectrodeMid;
  G4VPhysicalVolume* pvElectrodeMid;
  G4double ElectrodeMidMinR;
  G4double ElectrodeMidMaxR;
  G4double ElectrodeMidLength;
  G4double ElectrodeMidStartPhi;
  G4double ElectrodeMidSweepPhi;
  
  // Electrode Ends
  G4LogicalVolume* lvElectrodeEnd;
  G4VPhysicalVolume* pvElectrodeEnd;
  G4double ElectrodeEndMinR;
  G4double ElectrodeEndMaxR;
  G4double ElectrodeEndLength;
  G4double ElectrodeStartPhi;
  G4double ElectrodeSweepPhi;
  
  // Electrode EndCut
  G4LogicalVolume* lvEndCut;
  G4VPhysicalVolume* pvEndCut;
  G4Material* CutMater;
  G4String CutName;
  G4double CutThickness;
  
  // Electrode Guard
  G4LogicalVolume* lvElectrodeGuard;
  G4VPhysicalVolume* pvElectrodeGuard;
  G4double ElectrodeGuardMinR;
  G4double ElectrodeGuardMaxR;
  G4double ElectrodeGuardLength;
  
  // Electrode Cone
  G4LogicalVolume* lvElectrodeCone;
  G4VPhysicalVolume* pvElectrodeCone;
  G4double ElectrodeConeMinR1;
  G4double ElectrodeConeMaxR1;
  G4double ElectrodeConeMinR2;
  G4double ElectrodeConeMaxR2;
  G4double ElectrodeConeLength;
 
  // Helmholtz Coils
  G4LogicalVolume* lvHelmholtzCoil;
  G4VPhysicalVolume* pvHelmholtzCoil;
  G4Material* HelmholtzCoilMater;
  G4String HelmholtzCoilName;
  G4double HelmholtzCoilMinR;
  G4double HelmholtzCoilMaxR;
  G4double HelmholtzCoilLength;
  G4double HelmholtzCoilDistance;
  G4double HelmholtzCoilStartPhi;
  G4double HelmholtzCoilSweepPhi;
  
  // Insulator
  G4LogicalVolume* lvInnerInsulator;
  G4LogicalVolume* lvOuterInsulator;
  G4VPhysicalVolume* pvInnerInsulator;
  G4VPhysicalVolume* pvOuterInsulator;
  G4Material* InsulatorMater;
  G4String InsulatorName;
  G4double InsulatorInnerMinR;
  G4double InsulatorOuterMinR;
  G4double InsulatorMaxR;
  G4double InsulatorLength;
  G4double InsulatorStartPhi;
  G4double InsulatorSweepPhi;
  
  // Macor Ring
  G4LogicalVolume* lvInnerMacorRing;
  G4LogicalVolume* lvOuterMacorRing;
  G4VPhysicalVolume* pvInnerMacorRing;
  G4VPhysicalVolume* pvOuterMacorRing;
  G4Material* MacorRingMater;
  G4String MacorRingName;
  G4double MacorRingMinR;
  G4double MacorRingMidR;
  G4double MacorRingMaxR;
  G4double MacorRingInnerLength;
  G4double MacorRingOuterLength;
  G4double MacorRingStartPhi;
  G4double MacorRingSweepPhi;
  
  // Housing
  G4LogicalVolume* lvHousing;
  G4VPhysicalVolume* pvHousing;
  G4Material* HousingMater;
  G4String HousingName;
  G4double HousingMinR;
  G4double HousingMaxR;
  G4double HousingLength;
  G4double HousingStartPhi;
  G4double HousingSweepPhi;
  
  // Housing cut
  G4LogicalVolume* lvHousingCut;
  G4VPhysicalVolume* pvHousingCut;
  G4double HousingCutLength3;
  G4double HousingCutStartPhi3;
  G4double HousingCutSweepPhi3;
  G4double HousingCutLength4;
  G4double HousingCutStartPhi4;
  G4double HousingCutSweepPhi4;
  
  // Coil Holder
  G4LogicalVolume* lvCHMid;
  G4LogicalVolume* lvCHCoil;
  G4LogicalVolume* lvCHEnd;
  G4VPhysicalVolume* pvCHMid;
  G4VPhysicalVolume* pvCHCoil;
  G4VPhysicalVolume* pvCHEnd;
  G4Material* CoilHolderMater;
  G4String CoilHolderName;
  G4double CHInnerRadius;
  G4double CHMidRadius;
  G4double CHMidLength;
  G4double CHCoilRadius;
  G4double CHCoilLength;
  G4double CHEndRadius;
  G4double CHEndLength;
  G4double CHStartPhi;
  G4double CHSweepPhi;
  
  // Holder mid cuts
  G4double CHCutRadius3;
  G4double CHCutRadius4;

};

#endif

