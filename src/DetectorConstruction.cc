#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4EllipticalTube.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4UserLimits.hh"
#include "G4RunManager.hh"

#include "MagneticField.hh"
#include "MaterialsList.hh"
#include "DetectorMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"
//#include "DetectionSystemSiLi.hh"
#include "DetectionSystem8pi.hh"

DetectorConstruction::DetectorConstruction()
{
#include "DetectorParameters.input"

  // materials
  field = new MagneticField();
  DefineEbitMaterials();
  mlist = 0;
  messenger = new DetectorMessenger(this);
  checkOverlaps=1;
}

DetectorConstruction::~DetectorConstruction()
{
  //DestroyMaterials();
  if (mlist) delete mlist;
  if (messenger) delete messenger;
}

void DetectorConstruction::CleanGeometry()
{
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  G4GeometryManager::GetInstance()->CloseGeometry();
}

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructAll());
}

void DetectorConstruction::DefineEbitMaterials()
{
  // Use outside class to define materials
  
  mlist = new MaterialsList();
  mlist->Construct();
  
  WorldMater = mlist->GetMaterial("Galactic");
  BdiscMater = mlist->GetMaterial("Aluminium");
  
  //SideDetectorMater = mlist->GetMaterial("Silicon"); 
  //CanisterMater = mlist->GetMaterial("Silicon");
  //CanisterMater = mlist->GetMaterial("BGO");

  //ShieldingCopperMater = mlist->GetMaterial("Copper");
  //ShieldingLeadMater = mlist->GetMaterial("Lead");
  //ShieldingCopperMater = mlist->GetMaterial("BGO");

  // SiLi Material 
  // Al2O3Mater = mlist->GetMaterial("Al2O3");
  // SSteelMater = mlist->GetMaterial("SSteel");
  // CarbonMater = mlist->GetMaterial("Carbon");
  // CopperMater = mlist->GetMaterial("Copper");
  // LeadMater = mlist->GetMaterial("Lead");
  
  
  // Be material
  WindowMater = mlist->GetMaterial("Beryllium");
  // EBIT
  //SSteelMater = mlist->GetMaterial("SSteel");
  
  EbitTubeMater = mlist->GetMaterial("Galactic");
  ElectrodeMater = mlist->GetMaterial("Copper");
  CutMater = mlist->GetMaterial("Galactic");
  HelmholtzCoilMater = mlist->GetMaterial("Nb3Sn");
  InsulatorMater = mlist->GetMaterial("Al2O3");
  MacorRingMater = mlist->GetMaterial("Macor");
  HousingMater = mlist->GetMaterial("SSteel");
  CoilHolderMater = mlist->GetMaterial("SSteel");
  
  delete mlist;
}
/*  Doesn't seem to be used...
void DetectorConstruction::SetWindowMaterial(G4String material)
{
  //MaterialsList* mlist = new MaterialsList();
  mlist = new MaterialsList();
  mlist->Construct();
  WindowMater = mlist->GetMaterial(material);
  delete mlist;
}
*/


void DetectorConstruction::SetVisualization()
{
  // Invisible volumes
  lvWorld->SetVisAttributes(G4VisAttributes::Invisible);
  lvEbitTube->SetVisAttributes(G4VisAttributes::Invisible);
  // colours
  G4Colour white(1.,1.,1.), red(1.,0.,0.), green(0.,1.,0.), blue(0.,0.,1.),
    yellow(1.,1.,0.), cyan(0.,1.,1.), magenta(1.,0.,1.), black(0.,0.,0.),
    orange(1.,.5,0.), pink(1.,.5,.5);
  
  G4VisAttributes* redVis = new G4VisAttributes(red);
  G4VisAttributes* pinkVis = new G4VisAttributes(pink);
  G4VisAttributes* cyanVis = new G4VisAttributes(cyan);
  G4VisAttributes* yellowVis = new G4VisAttributes(yellow);
  G4VisAttributes* blueVis = new G4VisAttributes(blue);
  G4VisAttributes* whiteVis = new G4VisAttributes(white);
  G4VisAttributes* orangeVis = new G4VisAttributes(orange);
  redVis->SetVisibility(true);
  pinkVis->SetVisibility(true);
  cyanVis->SetVisibility(true);
  yellowVis->SetVisibility(true);
  whiteVis->SetVisibility(true);
  orangeVis->SetVisibility(true);
  blueVis->SetVisibility(true);

  /* Getting rid of the following two as they break the sim when not using the SiLi's

  lvSideDeadlayer->SetVisAttributes(whiteVis);
  lvSideDetector->SetVisAttributes(redVis);
  */

  //lvSideDeadlayer->SetVisAttributes(yellow);
  //lvSideCanister->SetVisAttributes(white);
  //lvSideCanister1->SetVisAttributes(white);
  // lvShieldingCopper->SetVisAttributes(yellow);
  // lvShieldingLead->SetVisAttributes(orange);
  //lvShieldingCopper->SetVisAttributes(yellow);
  
  lvSideInnerWindow->SetVisAttributes(cyanVis);
  lvSideOuterWindow->SetVisAttributes(cyanVis);
  lvElectrodeMid->SetVisAttributes(yellowVis);
  lvElectrodeEnd->SetVisAttributes(yellowVis);
  
  lvElectrodeGuard->SetVisAttributes(yellowVis);
  lvElectrodeCone->SetVisAttributes(yellowVis);
  lvInnerInsulator->SetVisAttributes(cyanVis);
  lvOuterInsulator->SetVisAttributes(cyanVis);
  
  lvHelmholtzCoil->SetVisAttributes(blueVis);
  lvInnerMacorRing->SetVisAttributes(whiteVis);
  lvOuterMacorRing->SetVisAttributes(whiteVis);
  
  lvHousing->SetVisAttributes(orangeVis);
  lvCHMid->SetVisAttributes(orangeVis);
  lvCHCoil->SetVisAttributes(orangeVis);
  lvCHEnd->SetVisAttributes(orangeVis);
}
 
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructAll();
}
/*----------------------------------------------------*/
void DetectorConstruction::ConstructTrap() {
  /*----------------------------------------------------*/

  // placement coordinates
  //  //

  
  G4double x1 = 0, y1 = 0, z1 = 0, phi=0., r1 = 0;

  // Be window
  
   G4EllipticalTube* svSideInnerWindow = new G4EllipticalTube(WindowName, SideInnerWindowRadius, SideInnerWindowRadius, SideInnerWindowThick);
  lvSideInnerWindow = new G4LogicalVolume(svSideInnerWindow, WindowMater, WindowName);
  for (int i=-1; i<6; i++) {
    int j = -i;
    phi = 45*deg * j;
    G4RotationMatrix rotWin;
    rotWin.rotateX(0*deg);rotWin.rotateY(270*deg); rotWin.rotateZ(phi);
    r1 = 418.*mm;//SideInnerWindowDist + SideInnerWindowThick;
    x1 = cos(phi)*r1;
    y1 = sin(phi)*r1;
    z1 = 0;
    G4Transform3D transWin(rotWin, G4ThreeVector(x1,y1,z1));
    pvSideInnerWindow = new G4PVPlacement(transWin, lvSideInnerWindow, WindowName, lvWorld, 0, i,checkOverlaps);
  }
  
  
  // Outer Windows
  //
  G4EllipticalTube* svSideOuterWindow = new G4EllipticalTube(WindowName, SideOuterWindowRadius, SideOuterWindowRadius, SideOuterWindowThick);
  lvSideOuterWindow = new G4LogicalVolume(svSideOuterWindow, WindowMater, WindowName);
    for (int i=-1; i<6; i++) {
    int j = -i;
    phi = 45*deg * j;
    G4RotationMatrix rotWin;
    rotWin.rotateX(0*deg);rotWin.rotateY(270*deg); rotWin.rotateZ(phi);
    r1 = 455.163*mm;//SideOuterWindowDist + SideOuterWindowThick;
    x1 = cos(phi)*r1;
    y1 = sin(phi)*r1;
    z1 = 0;
    G4Transform3D transWin(rotWin, G4ThreeVector(x1,y1,z1));
    pvSideOuterWindow = new G4PVPlacement(transWin, lvSideOuterWindow, WindowName, lvWorld, 0, i,checkOverlaps);
    }

  // EBIT
   G4Tubs* svEbitTube = new G4Tubs(EbitTubeName, EbitTubeMinR, EbitTubeMaxR,
				  EbitTubeLength, EbitTubeStartPhi, EbitTubeSweepPhi);
   lvEbitTube = new G4LogicalVolume(svEbitTube, EbitTubeMater, EbitTubeName);
  //
  //pvEbitTube = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), lvEbitTube, EbitTubeName, lvWorld, 0, 0);
  //
   G4double maxStep = 15.*cm, maxLength = 100.*m;
   lvEbitTube->SetUserLimits(new G4UserLimits(maxStep, maxLength));

   
   
   // Electrode
  //
  // central electrode, middle piece
  G4Tubs* svElectrodeMid = new G4Tubs(ElectrodeName, ElectrodeMidMinR, ElectrodeMidMaxR,
				      ElectrodeMidLength, ElectrodeMidStartPhi, ElectrodeMidSweepPhi);
  lvElectrodeMid = new G4LogicalVolume(svElectrodeMid, ElectrodeMater, ElectrodeName);
  
  for (int i=0; i<8; i++) {
    phi = (45*i - 2.5*(1 - pow(-1, i))) * deg;
    G4RotationMatrix rotElec;
    rotElec.rotateZ(phi);
    x1 = 0; y1 = 0; z1 = 0;
    G4Transform3D transElec(rotElec, G4ThreeVector(x1,y1,z1));

    pvElectrodeMid = new G4PVPlacement(transElec, lvElectrodeMid, ElectrodeName, lvWorld, 0, i, checkOverlaps);
  }
  
  // end pieces and cuts
  x1 = 0; y1 = 0; phi = 45*deg;
  z1 = ElectrodeMidLength + ElectrodeEndLength;
  G4Tubs* svElectrodeEnd = new G4Tubs(CutName, ElectrodeEndMinR, ElectrodeEndMaxR,
				      ElectrodeEndLength, ElectrodeStartPhi, ElectrodeSweepPhi);
  G4VSolid* svEndCut = new G4Box(CutName, ElectrodeEndMaxR, CutThickness, ElectrodeEndLength);
  G4RotationMatrix rotCut;
  G4ThreeVector vecCut(0,0,0);
  G4SubtractionSolid* svEndSub1 = new G4SubtractionSolid("", svElectrodeEnd, svEndCut, G4Transform3D(rotCut,vecCut));
  rotCut.rotateZ(phi);
  G4SubtractionSolid* svEndSub2 = new G4SubtractionSolid("", svEndSub1, svEndCut, G4Transform3D(rotCut,vecCut));
  rotCut.rotateZ(phi);
  G4SubtractionSolid* svEndSub3 = new G4SubtractionSolid("", svEndSub2, svEndCut, G4Transform3D(rotCut,vecCut));
  rotCut.rotateZ(phi);
  G4SubtractionSolid* svEndSub4 = new G4SubtractionSolid(ElectrodeName, svEndSub3, svEndCut, G4Transform3D(rotCut,vecCut));
  lvElectrodeEnd = new G4LogicalVolume(svEndSub4, ElectrodeMater, ElectrodeName);
  pvElectrodeEnd = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvElectrodeEnd,
  				     ElectrodeName, lvWorld, 0, 0);
  pvElectrodeEnd = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvElectrodeEnd,
  				     ElectrodeName, lvWorld, 0, 0);
   
  // guard electrodes
  
  x1 = 0; y1 = 0; phi = 0;
  z1 = ElectrodeMidLength + 2*ElectrodeEndLength + 2*InsulatorLength + ElectrodeGuardLength;
  G4Tubs* svElectrodeGuard = new G4Tubs(ElectrodeName, ElectrodeGuardMinR, ElectrodeGuardMaxR,
					ElectrodeGuardLength, ElectrodeStartPhi, ElectrodeSweepPhi);
  lvElectrodeGuard = new G4LogicalVolume(svElectrodeGuard, ElectrodeMater, ElectrodeName);
  pvElectrodeGuard = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvElectrodeGuard,
  				       ElectrodeName, lvWorld, 0, 0);
  pvElectrodeGuard = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvElectrodeGuard, 
  				       ElectrodeName, lvWorld, 0, 1);
  
  // cone electrodes
  x1 = 0; y1 = 0; phi = 180*deg;
  z1 = ElectrodeMidLength + 2*ElectrodeEndLength + 2*InsulatorLength +
    2*ElectrodeGuardLength + 2*InsulatorLength + ElectrodeConeLength;
  G4Cons* svElectrodeCone = new G4Cons(ElectrodeName, ElectrodeConeMinR1, ElectrodeConeMaxR1,
				       ElectrodeConeMinR2, ElectrodeConeMaxR2,
				       ElectrodeConeLength, ElectrodeStartPhi, ElectrodeSweepPhi);
  lvElectrodeCone = new G4LogicalVolume(svElectrodeCone, ElectrodeMater, ElectrodeName);
  pvElectrodeCone = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvElectrodeCone,
  			      ElectrodeName, lvWorld, 0, 0);
  G4RotationMatrix rotCone;
  rotCone.rotateX(phi);
  pvElectrodeCone = new G4PVPlacement(G4Transform3D(rotCone, G4ThreeVector(x1,y1,-z1)), lvElectrodeCone,
  			      ElectrodeName, lvWorld, 0, 1);   

 // Helmholtz Coils
  //
  x1 = 0; y1 = 0; phi = 0;
  z1 = HelmholtzCoilDistance;
  G4Tubs* svHelmholtzCoil = new G4Tubs(HelmholtzCoilName, HelmholtzCoilMinR, HelmholtzCoilMaxR,
				       HelmholtzCoilLength, HelmholtzCoilStartPhi, HelmholtzCoilSweepPhi);
  lvHelmholtzCoil = new G4LogicalVolume(svHelmholtzCoil, HelmholtzCoilMater, HelmholtzCoilName);
  pvHelmholtzCoil = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvHelmholtzCoil,
  				      HelmholtzCoilName, lvWorld, 0, 0);
  pvHelmholtzCoil = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvHelmholtzCoil,
  				      HelmholtzCoilName, lvWorld, 0, 0);
  
  // Insulating disks
  //
  
  x1 = 0; y1 = 0; phi = 0;
  z1 = ElectrodeMidLength + 2*ElectrodeEndLength + InsulatorLength;
  G4Tubs* svInnerInsulator = new G4Tubs(InsulatorName, InsulatorInnerMinR, InsulatorMaxR,
					InsulatorLength, InsulatorStartPhi, InsulatorSweepPhi);
  lvInnerInsulator = new G4LogicalVolume(svInnerInsulator, InsulatorMater, InsulatorName);
  pvInnerInsulator = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvInnerInsulator,
  				       InsulatorName, lvWorld, 0, 0);
  pvInnerInsulator = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvInnerInsulator,
  			       InsulatorName, lvWorld, 0, 1);
  
  z1 = ElectrodeMidLength + 2*ElectrodeEndLength + 2*InsulatorLength + 2*ElectrodeGuardLength + InsulatorLength;
  G4Tubs* svOuterInsulator = new G4Tubs(InsulatorName, InsulatorOuterMinR, InsulatorMaxR,
					InsulatorLength, InsulatorStartPhi, InsulatorSweepPhi);
  lvOuterInsulator = new G4LogicalVolume(svOuterInsulator, InsulatorMater, InsulatorName);
  pvOuterInsulator = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvOuterInsulator,
  				       InsulatorName, lvWorld, 0, 0);
  pvOuterInsulator = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvOuterInsulator,
  				       InsulatorName, lvWorld, 0, 1);
  
  // Macor rings
  // set one
  
  x1 = 0; y1 = 0; phi = 0;
  z1 = ElectrodeMidLength + 2*ElectrodeEndLength + MacorRingInnerLength;
  G4Tubs* svInnerMacorRing = new G4Tubs(MacorRingName, MacorRingMinR, MacorRingMidR,
					MacorRingInnerLength, MacorRingStartPhi, MacorRingSweepPhi);
  lvInnerMacorRing = new G4LogicalVolume(svInnerMacorRing, MacorRingMater, MacorRingName);
  pvInnerMacorRing = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvInnerMacorRing,
  				       MacorRingName, lvWorld, 0, 0);
  pvInnerMacorRing = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvInnerMacorRing,
  				       MacorRingName, lvWorld, 0, 1);
  G4Tubs* svOuterMacorRing = new G4Tubs(MacorRingName, MacorRingMidR, MacorRingMaxR,
					MacorRingOuterLength, MacorRingStartPhi, MacorRingSweepPhi);
  lvOuterMacorRing = new G4LogicalVolume(svOuterMacorRing, MacorRingMater, MacorRingName);
  pvOuterMacorRing = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvOuterMacorRing,
  				       MacorRingName, lvWorld, 0, 0);
  pvOuterMacorRing = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvOuterMacorRing,
  			       MacorRingName, lvWorld, 0, 1);
  // set two
  z1 = ElectrodeMidLength + 2*ElectrodeEndLength + 2*MacorRingInnerLength +
    2*ElectrodeGuardLength + MacorRingOuterLength;
  pvInnerMacorRing = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvInnerMacorRing,
  			       MacorRingName, lvWorld, 0, 2);
  pvInnerMacorRing = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvInnerMacorRing,
  				       MacorRingName, lvWorld, 0, 3);
  pvOuterMacorRing = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvOuterMacorRing,
  				       MacorRingName, lvWorld, 0, 2);
  pvOuterMacorRing = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvOuterMacorRing,
  				       MacorRingName, lvWorld, 0, 3);
  
  
  // Housing
  //
  
  x1 = 0; y1 = 0; z1 = 0; phi = 90*deg;
  G4Tubs* svHousing = new G4Tubs(HousingName, HousingMinR, HousingMaxR,
				 HousingLength, HousingStartPhi, HousingSweepPhi);
  // cuts
  G4Tubs* svHousingCut3 = new G4Tubs(CutName, HousingMinR-1.*mm, HousingMaxR+1.*mm,
				    HousingCutLength3, HousingCutStartPhi3, HousingCutSweepPhi3);
  G4Tubs* svHousingCut4 = new G4Tubs(CutName, HousingMinR-1.*mm, HousingMaxR+1.*mm,
				    HousingCutLength4, HousingCutStartPhi4, HousingCutSweepPhi4);
  G4RotationMatrix rotHouse;
  G4ThreeVector vecHouse(0,0,0);
  G4SubtractionSolid* svHouse1 = new G4SubtractionSolid("", svHousing, svHousingCut3, G4Transform3D(rotHouse,vecHouse));
  rotHouse.rotateZ(phi);
  G4SubtractionSolid* svHouse2 = new G4SubtractionSolid("", svHouse1, svHousingCut3, G4Transform3D(rotHouse,vecHouse));
  rotHouse.rotateZ(phi);
  G4SubtractionSolid* svHouse3 = new G4SubtractionSolid("", svHouse2, svHousingCut3, G4Transform3D(rotHouse,vecHouse));
  rotHouse.rotateZ(phi);
  G4SubtractionSolid* svHouse4 = new G4SubtractionSolid("", svHouse3, svHousingCut3, G4Transform3D(rotHouse,vecHouse));
  rotHouse.rotateZ(phi);
  G4SubtractionSolid* svHouse5 = new G4SubtractionSolid("", svHouse4, svHousingCut4, G4Transform3D(rotHouse,vecHouse));
  rotHouse.rotateZ(phi);
  G4SubtractionSolid* svHouse6 = new G4SubtractionSolid("", svHouse5, svHousingCut4, G4Transform3D(rotHouse,vecHouse));
  rotHouse.rotateZ(phi);
  G4SubtractionSolid* svHouse7 = new G4SubtractionSolid("", svHouse6, svHousingCut4, G4Transform3D(rotHouse,vecHouse));
  rotHouse.rotateZ(phi);
  G4SubtractionSolid* svHouse8 = new G4SubtractionSolid(HousingName, svHouse7, svHousingCut4, G4Transform3D(rotHouse,vecHouse));
  lvHousing = new G4LogicalVolume(svHouse8, HousingMater, HousingName);
  pvHousing = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvHousing,
  				HousingName, lvWorld, 0, 0);
  
  // Coil Holder
  //
  
  x1 = 0; y1 = 0; z1 = 0; phi = 45*deg;
  G4Tubs* svCHMid = new G4Tubs(CoilHolderName, CHInnerRadius, CHMidRadius, CHMidLength, CHStartPhi, CHSweepPhi);
  G4EllipticalTube* svCHCut3 = new G4EllipticalTube("", CHCutRadius3, CHCutRadius3, CHMidRadius);
  G4EllipticalTube* svCHCut4 = new G4EllipticalTube("", CHCutRadius4, CHCutRadius4, CHMidRadius);
  G4RotationMatrix rotCH;
  rotCH.rotateY(90*deg);
  G4ThreeVector vecCH(0,0,0);
  G4SubtractionSolid* svCHMid1 = new G4SubtractionSolid("", svCHMid, svCHCut3, G4Transform3D(rotCH,vecCH));
  rotCH.rotateZ(phi);
  G4SubtractionSolid* svCHMid2 = new G4SubtractionSolid("", svCHMid1, svCHCut4, G4Transform3D(rotCH,vecCH));
  rotCH.rotateZ(phi);
  G4SubtractionSolid* svCHMid3 = new G4SubtractionSolid("", svCHMid2, svCHCut3, G4Transform3D(rotCH,vecCH));
  rotCH.rotateZ(phi);
  G4SubtractionSolid* svCHMid4 = new G4SubtractionSolid(CoilHolderName, svCHMid3, svCHCut4, G4Transform3D(rotCH,vecCH));
  lvCHMid = new G4LogicalVolume(svCHMid4, CoilHolderMater, CoilHolderName);
  pvCHMid = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvCHMid, CoilHolderName, lvWorld, 0, 0);
  
  G4Tubs* svCHCoil = new G4Tubs(CoilHolderName, CHInnerRadius, CHCoilRadius, CHCoilLength, CHStartPhi, CHSweepPhi);
  G4Tubs* svCHEnd = new G4Tubs(CoilHolderName, CHInnerRadius, CHEndRadius, CHEndLength, CHStartPhi, CHSweepPhi);
  lvCHCoil = new G4LogicalVolume(svCHCoil, CoilHolderMater, CoilHolderName);
  lvCHEnd = new G4LogicalVolume(svCHEnd, CoilHolderMater, CoilHolderName);
  z1 = CHMidLength + CHCoilLength;
  pvCHCoil = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvCHCoil, CoilHolderName, lvWorld, 0, 0);
  pvCHCoil = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvCHCoil, CoilHolderName, lvWorld, 0, 0);
  z1 = CHMidLength + CHCoilLength + CHEndLength;
  pvCHEnd = new G4PVPlacement(0, G4ThreeVector(x1,y1,z1), lvCHEnd, CoilHolderName, lvWorld, 0, 0);
  pvCHEnd = new G4PVPlacement(0, G4ThreeVector(x1,y1,-z1), lvCHEnd, CoilHolderName, lvWorld, 0, 0);

}


G4VPhysicalVolume* DetectorConstruction::ConstructAll()
{
  G4double x1, y1, z1, phi=0.;

  CleanGeometry();
  
  // world

  G4Box* boxWorld = new G4Box(WorldName, WorldSize, WorldSize, WorldSize);
  lvWorld = new G4LogicalVolume(boxWorld, WorldMater, WorldName);
  pvWorld = new G4PVPlacement(0, G4ThreeVector(), lvWorld, WorldName, 0, 0, 0);
  
  DetectionSystem8pi* my8pidet = new DetectionSystem8pi();
  //DetectionSystemSiLi* mySiLiDet = new DetectionSystemSiLi();
  //ConstructSiLi();
  // JonR: SiLi's do not work right now, need to refactor code to
  // be more like the 8pi definition
  // G4LogicalVolume* mylvSiLi;
  // mylvSiLi = mySiLiDet->Build();
  my8pidet->Build();

  ConstructTrap();
  // JonR: Outer beryllium window - 1/2 the Ge crystal length as it uses that for the origin
  G4double r1 = 455.136*mm - (my8pidet->fCrystalLength / 2);


  for (int i=-1; i<6;i++){
    int j = -i;
    phi = 45*deg * j;

    G4RotationMatrix* rotate8pi = new G4RotationMatrix(0*deg, 0*deg, 0*deg);
    rotate8pi->rotateX(0*deg);
    rotate8pi->rotateY(90*deg);
    rotate8pi->rotateZ(phi);

    x1 = cos(phi)*r1;
    y1 = sin(phi)*r1;
    z1 = 0.0;
    
    my8pidet->PlaceDetector(lvWorld, G4ThreeVector(x1,y1,z1), rotate8pi, i);
  }
  
  SetVisualization();
  
  return pvWorld;
}



