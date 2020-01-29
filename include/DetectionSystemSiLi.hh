#ifndef DETECTIONSYSTEMSILI_HH
#define DETECTIONSYSTEMSILI_HH

//#include "DetectionSystem8pi.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "G4AssemblyVolume.hh"

class MaterialsList;

class DetectionSystemSiLi
{
public:
  DetectionSystemSiLi();
  ~DetectionSystemSiLi();
  G4int Build();
  G4int DefineMaterials();
  void SetSideDetectorMaterial(G4String material);
  const G4VPhysicalVolume* GetSideDetector()   {return pvSideDetector;};

private:
  G4Material* WorldMater;

  MaterialsList* mlist;
  G4int checkOverlaps;

  

  // Detectors
  G4LogicalVolume* lvSideDetector;
  G4VPhysicalVolume* pvSideDetector;
  G4Material* SideDetectorMater;
  G4String SideDetectorName;
  G4double SideDetectorRadius;
  G4double SideDetectorDist;
  G4double SideDetectorThick;

  // Dead layers
 
  G4LogicalVolume* lvSideDeadlayer;
  G4VPhysicalVolume* pvSideDeadlayer;
  G4String SideDeadlayerName;
  G4double SideDeadlayerFrontThick;
  
  //Canister
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

  G4LogicalVolume* lvSiLi;
  G4VPhysicalVolume* pvSiLi;

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

  G4LogicalVolume* lv_baPl;
  G4VPhysicalVolume* pv_baPl;
  G4LogicalVolume* lv_endPl;
  G4VPhysicalVolume* pv_endPl;

  G4LogicalVolume* lvRod;
  G4VPhysicalVolume *pvRod0, *pvRod1, *pvRod2, *pvRod3;

  G4LogicalVolume* lvbdisc;
  G4VPhysicalVolume* pvbdisc;

  // shields
  G4LogicalVolume* lvcu8;
  G4VPhysicalVolume* pvcu8;
  G4LogicalVolume* lvpb8;
  G4VPhysicalVolume* pvpb8;
  
  G4Material* BdiscMater;
  G4Material* Al2O3Mater;
  G4Material* SSteelMater;
  G4Material* CarbonMater;
  G4Material* CopperMater;
  G4Material* LeadMater;

};

#endif
