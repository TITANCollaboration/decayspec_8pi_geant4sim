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


DetectorConstruction::DetectorConstruction()
{
#include "DetectorParameters.input"
  
  // materials
  field = new MagneticField();
  DefineMaterials();
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

void DetectorConstruction::DefineMaterials()
{
  // Use outside class to define materials

  MaterialsList* mlist = new MaterialsList();
  mlist->Construct();
  
  WorldMater = mlist->GetMaterial("Galactic");
  SideDetectorMater = mlist->GetMaterial("Silicon"); 
  //CanisterMater = mlist->GetMaterial("Silicon");
  CanisterMater = mlist->GetMaterial("BGO");
  BdiscMater = mlist->GetMaterial("Aluminium");
  //ShieldingCopperMater = mlist->GetMaterial("Copper");
  //ShieldingLeadMater = mlist->GetMaterial("Lead");
  //ShieldingCopperMater = mlist->GetMaterial("BGO");
  Al2O3Mater = mlist->GetMaterial("Al2O3");
  SSteelMater = mlist->GetMaterial("SSteel");
  CarbonMater = mlist->GetMaterial("Carbon");
  CopperMater = mlist->GetMaterial("Copper");
  LeadMater = mlist->GetMaterial("Lead");
  
// Be material
  WindowMater = mlist->GetMaterial("Beryllium");
// EBIT
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

void DetectorConstruction::SetWindowMaterial(G4String material)
{
  MaterialsList* mlist = new MaterialsList(); mlist->Construct();
  WindowMater = mlist->GetMaterial(material);
  delete mlist;
}


void DetectorConstruction::SetSideDetectorMaterial(G4String material)
{
  MaterialsList* mlist = new MaterialsList(); mlist->Construct();
  SideDetectorMater = mlist->GetMaterial(material);
  delete mlist;
}

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
  
  lvSideDetector->SetVisAttributes(redVis);
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
  lvSideDeadlayer->SetVisAttributes(whiteVis);
  
  
  lvHousing->SetVisAttributes(orangeVis);
  lvCHMid->SetVisAttributes(orangeVis);
  lvCHCoil->SetVisAttributes(orangeVis);
  lvCHEnd->SetVisAttributes(orangeVis);
}
 
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructAll();
}

G4VPhysicalVolume* DetectorConstruction::ConstructAll()
{
  CleanGeometry();
  
  // world
  //
  G4Box* boxWorld = new G4Box(WorldName, WorldSize, WorldSize, WorldSize);
  lvWorld = new G4LogicalVolume(boxWorld, WorldMater, WorldName);
  pvWorld = new G4PVPlacement(0, G4ThreeVector(), lvWorld, WorldName, 0, 0, 0);
  
  ConstructSiLi();
  ConstructTrap();
  SetVisualization();
  
  return pvWorld;
}


/*----------------------------------------------------*/
void DetectorConstruction::ConstructSiLi() {
/*----------------------------------------------------*/

  // this ought to be a box that contains all elements of one detector
  G4double x1, y1, z1, phi;
  G4int placeBGO = 0;
  G4int placeCuPb = 1;

  G4Box* boxSiLi = new G4Box("SiLi", 50*cm/2, 25*cm/2, 25*cm/2);
  lvSiLi = new G4LogicalVolume(boxSiLi, WorldMater, "SiLi");
  //pvSiLi = new G4PVPlacement(0, G4ThreeVector(), lvSiLi, WorldName, 0, 0, 0);

  //  G4EllipticalTube* svSideDetector = new G4EllipticalTube(SideDetectorName, SideDetectorRadius, SideDetectorRadius, SideDetectorThick);
  G4Tubs* svSideDetector = new G4Tubs(SideDetectorName,0,SideDetectorRadius, SideDetectorThick,0,360*deg);
  lvSideDetector = new G4LogicalVolume(svSideDetector, SideDetectorMater, SideDetectorName);
  phi = 90*deg * 0;
  G4RotationMatrix rotDet;
  rotDet.rotateY(270*deg); rotDet.rotateZ(phi);
  //G4double r1 = SideDetectorDist + SideDetectorThick;
  //x1 = r1;
  x1 = 0;
  y1 = 0;
  z1 = 0;
  G4Transform3D transDet(rotDet, G4ThreeVector(x1,y1,z1));
  pvSideDetector = new G4PVPlacement(transDet, lvSideDetector, SideDetectorName, lvSiLi, 1, 0, checkOverlaps);

    // Dead layers
  //G4EllipticalTube* svSideDeadlayerFront = new G4EllipticalTube("deadlayer", SideDetectorRadius, SideDetectorRadius, SideDeadlayerFrontThick);

  G4Tubs* svSideDeadLayerFront = new G4Tubs("deadlayer",0,SideDetectorRadius, SideDeadlayerFrontThick ,0,360*deg);
  lvSideDeadlayer = new G4LogicalVolume(svSideDeadLayerFront, SideDetectorMater, SideDeadlayerName);
  
  phi = 90*deg * 0;
  G4RotationMatrix rotDL;
  rotDL.rotateY(270*deg); rotDL.rotateZ(phi);
  x1 = -SideDetectorThick-SideDeadlayerFrontThick; //don't have it overlap
  y1 = 0;
  z1 = 0;
  G4Transform3D transDL(rotDL, G4ThreeVector(x1,y1,z1));
  pvSideDeadlayer = new G4PVPlacement(transDL, lvSideDeadlayer, SideDeadlayerName, lvSiLi, 1, 0, checkOverlaps);
  
  // Canisters
  if (placeBGO) {
    G4Tubs* svSideCanister1 = new G4Tubs(CanisterName1, SideCanisterInnerRadius1,SideCanisterOuterRadius1, SideCanisterThick1,0.*deg,360.*deg);
    lvSideCanister1 = new G4LogicalVolume(svSideCanister1, CanisterMater, CanisterName1);
    phi = 90*deg * 0;
    G4RotationMatrix rotWin1;
    rotWin1.rotateY(270*deg); rotWin1.rotateZ(phi);
    //x1 = 25.*mm-(2.5+.001)*mm;
    x1 = 40+75/2.;
    y1 = 0;
    z1 = 0;
    G4Transform3D transWin1(rotWin1, G4ThreeVector(x1,y1,z1));
    pvSideCanister1 = new G4PVPlacement(transWin1, lvSideCanister1, CanisterName1, lvSiLi, 1, 0, checkOverlaps);


    //G4EllipticalTube* svSideCanister = new G4EllipticalTube(CanisterName, SideCanisterInnerRadius,SideCanisterOuterRadius, SideCanisterThick);
    G4Tubs* svSideCanister = new G4Tubs(CanisterName, 34*mm/2, 95*mm/2, 10*mm/2,0,360*deg);
    lvSideCanister = new G4LogicalVolume(svSideCanister, CanisterMater, CanisterName);
    phi = 90*deg * 0;
    G4RotationMatrix rotWin;
    rotWin.rotateY(270*deg); rotWin.rotateZ(phi);
    //x1 = SideDetectorThick*2 + SideDeadlayerFrontThick*2 +25.*mm;
    x1 = 85+75+5+5+1;
    y1 = 0;
    z1 = 0;
    G4Transform3D transWin(rotWin, G4ThreeVector(x1,y1,z1));
    pvSideCanister = new G4PVPlacement(transWin, lvSideCanister, CanisterName, lvSiLi, 1, 0, checkOverlaps);
  }

  if (placeCuPb) {
    // make it 2mm thick Cu and Pb
    G4Tubs* cushield8 = new G4Tubs("cuShield8",75*mm/2.,78*mm/2,175*mm/2,0,360*deg);
    lvcu8 = new G4LogicalVolume(cushield8, CopperMater, "cuShield8");
    G4Transform3D trans_cushield8(rotDL, G4ThreeVector(40+75/2,0,0));
    pvcu8 = new G4PVPlacement(trans_cushield8, lvcu8, "cuShield8", lvSiLi, 1, 0, checkOverlaps);

    G4Tubs* pbshield8 = new G4Tubs("pbShield8",78*mm/2.,82*mm/2,175*mm/2,0,360*deg);
    lvpb8 = new G4LogicalVolume(pbshield8, LeadMater, "pbShield8");
    G4Transform3D trans_pbshield8(rotDL, G4ThreeVector(40+75/2,0,0));
    pvpb8 = new G4PVPlacement(trans_pbshield8, lvpb8, "pbShield8", lvSiLi, 1, 0, checkOverlaps);
      
  }

    G4double spaceroversize=0.5*mm;
    // carbon window
    G4double cWindowZ = 0.5*mm;
    G4Tubs* cWindow = new G4Tubs("cWindow",0 ,68*mm/2,cWindowZ/2.,0,360*deg);
    lv_cWindow = new G4LogicalVolume(cWindow, CarbonMater, "cWindow");
    G4Transform3D trans_cWindow(rotDL, G4ThreeVector(-2.5-spaceroversize-2-3-1-cWindowZ/2.,0,0));
    pv_cWindow = new G4PVPlacement(trans_cWindow, lv_cWindow, "cWindow", lvSiLi, 1, 0, checkOverlaps);

  if (1) {
    // Al back 'disc'
    G4Tubs* bdisc = new G4Tubs("bdisc", 0*mm, 63*mm/2, 25*mm/2, 0*deg, 360*deg);
					 
    //subtract unwanted stuff
    G4Tubs* bdiscR0 = new G4Tubs("bdiscR0", 0*mm, (63-12)*mm/2, 25*mm/2, 0*deg, 360*deg);
    G4SubtractionSolid* bdisc2 =
      new G4SubtractionSolid("bdisc2",bdisc,bdiscR0,NULL,G4ThreeVector(0,0,3.));

    G4Tubs* bdiscR1 = new G4Tubs("bdiscR1", 0*mm, (63-8)*mm/2, 9*mm/2, 0*deg, 360*deg);
    G4SubtractionSolid* bdisc3 =
      new G4SubtractionSolid("bdisc3",bdisc2,bdiscR1,NULL,G4ThreeVector(0,0,-5));

    G4Tubs* bdiscR2 = new G4Tubs("bdiscR2", 0*mm, (63-4)*mm/2, 12*mm/2, 0*deg, 360*deg);
    G4SubtractionSolid* bdisc4 =
      new G4SubtractionSolid("bdisc4",bdisc3,bdiscR2,NULL,G4ThreeVector(0,0,5.5));

    lvbdisc = new G4LogicalVolume(bdisc4, BdiscMater, "bdisc4");
    phi = 90*deg * 0;
    G4RotationMatrix rotBdisc;
    rotBdisc.rotateY(270*deg); rotBdisc.rotateZ(phi);
    //G4double r1 = SideDetectorDist + SideDetectorThick;
    //x1 = r1;
    G4double bdisc_x0=8*mm-spaceroversize;  //this is the lower edge of the bdisc
    x1 = bdisc_x0; // 8 = 12.5-2.5-2
    y1 = 0;
    z1 = 0;
    G4Transform3D transBdisc(rotBdisc, G4ThreeVector(x1,y1,z1));
    pvbdisc = new G4PVPlacement(transBdisc, lvbdisc, "bdisc", lvSiLi, 1, 0, checkOverlaps);


    // the 'alumina' spacer ring
    G4Tubs* c_spacer = new G4Tubs("c_spacer", (59-8)*mm/2, 59*mm/2, 4*mm/2, 0*deg, 360*deg);
    G4Tubs* c_spacerR1 = new G4Tubs("c_spacerR1", 0., (59-2)*mm/2, 4*mm/2, 0*deg, 360*deg);
    G4SubtractionSolid* c_spacer2 =
      new G4SubtractionSolid("c_spacer2",c_spacer,c_spacerR1,NULL,G4ThreeVector(0,0,-1.));
    
    lvcspacer = new G4LogicalVolume(c_spacer2, Al2O3Mater, "c_spacer2");
    phi = 90*deg * 0;
    G4RotationMatrix rotcspacer;
    rotcspacer.rotateY(270*deg); rotcspacer.rotateZ(phi);
    G4Transform3D transcspacer(rotcspacer, G4ThreeVector(-1.5-spaceroversize,0,0));
    pvcspacer = 
      new G4PVPlacement(transcspacer, lvcspacer, "c_spacer", lvSiLi, 1, 0, checkOverlaps);


    // outer housing
    G4Tubs* c_housing = new G4Tubs("c_housing", (70-19)*mm/2, 70*mm/2, 100*mm/2, 0*deg, 360*deg);
    G4Tubs* chR0 = new G4Tubs("chR0", 0*mm/2, 66*mm/2, 100*mm/2, 0*deg, 360*deg);
    G4SubtractionSolid* c_housing1 =
      new G4SubtractionSolid("c_housing1",c_housing,chR0,NULL,G4ThreeVector(0,0,-1.6));

    G4double cwindow_retreat = 0.6*mm;
    G4Tubs* chR1 = new G4Tubs("chR1", 0*mm/2, 68*mm/2, cwindow_retreat*mm/2, 0*deg, 360*deg);
    G4SubtractionSolid* c_housing2 =
      new G4SubtractionSolid("c_housing2",c_housing1,chR1,NULL,G4ThreeVector(0,0,50-cwindow_retreat/2));

    G4double housing_x=10+22.9+8-spaceroversize;
    lvchousing = new G4LogicalVolume(c_housing2, BdiscMater, "c_housing2");
    G4Transform3D transchousing(rotcspacer, G4ThreeVector(housing_x,0,0));
    pvchousing = 
      new G4PVPlacement(transchousing, lvchousing, "c_housing", lvSiLi, 1, 0, checkOverlaps);

    // cold finger
    G4Cons* cf_cone = new G4Cons("cf_cone",10*mm/2,10*mm/2,10*mm/2,40*mm/2,10*mm/2,0,360*deg);
    lv_cf_cone = new G4LogicalVolume(cf_cone, BdiscMater, "cf_cone");
    G4Transform3D trans_cf_cone(rotcspacer, G4ThreeVector(bdisc_x0+12.5+5+23+5,0,0));
    pv_cf_cone = 
      new G4PVPlacement(trans_cf_cone, lv_cf_cone, "cf_cone", lvSiLi, 1, 0, checkOverlaps);

    G4double cf_tube_length=70*mm;
    G4Tubs* cf_tube = new G4Tubs("cf_tube",0,10*mm/2.,cf_tube_length/2,0,360*deg);
    lv_cf_tube = new G4LogicalVolume(cf_tube, BdiscMater, "cf_tube");
    G4Transform3D trans_cf_tube(rotcspacer, G4ThreeVector(bdisc_x0+12.5+cf_tube_length/2.,0,0));
    pv_cf_tube = 
      new G4PVPlacement(trans_cf_tube, lv_cf_tube, "cf_tube", lvSiLi, 1, 0, checkOverlaps);

    G4Tubs* cf_tube2 = new G4Tubs("cf_tube2",10*mm/2.,40*mm/2,23*mm/2,0,360*deg);
    lv_cf_tube2 = new G4LogicalVolume(cf_tube2, BdiscMater, "cf_tube2");
    G4Transform3D trans_cf_tube2(rotcspacer, G4ThreeVector(bdisc_x0+12.5+5+23/2.,0,0));
    pv_cf_tube2 = 
      new G4PVPlacement(trans_cf_tube2, lv_cf_tube2, "cf_tube2", lvSiLi, 1, 0, checkOverlaps);
    

    // stuff behind the crystal compartment
    G4double housing_x0 = housing_x+50*mm; // this is where it all starts

    // steel(?) separator disc
    G4double sep1z = 7*mm;
    G4Tubs* sep1 = new G4Tubs("sep1",0,70*mm/2,sep1z/2.,0,360*deg);
    lv_sep1 = new G4LogicalVolume(sep1, SSteelMater, "sep1");
    G4Transform3D trans_sep1(rotcspacer, G4ThreeVector(housing_x0+sep1z/2,0,0));
    pv_sep1 = new G4PVPlacement(trans_sep1, lv_sep1, "sep1", lvSiLi, 1, 0, checkOverlaps);
    
    // 2nd cold finger d=34mm,
    // length= 60+8+12 to the start of the cone part behind the preamp housing
    // probably SSteel?
    G4double cf2z=(60+8+18)*mm;
    G4Tubs* cf2 = new G4Tubs("cf2",0,34*mm/2,cf2z/2.,0,360*deg);
    lv_cf2 = new G4LogicalVolume(cf2, SSteelMater, "cf2");
    G4Transform3D trans_cf2(rotcspacer, G4ThreeVector(housing_x0+sep1z+cf2z/2,0,0));
    pv_cf2 = new G4PVPlacement(trans_cf2, lv_cf2, "cf2", lvSiLi, 1, 0, checkOverlaps);
    
    // another separator disc (Al?)
    G4double sep2z = 8*mm;
    G4Tubs* sep2 = new G4Tubs("sep2",34*mm/2.,73*mm/2,sep2z/2.,0,360*deg);
    lv_sep2 = new G4LogicalVolume(sep2, BdiscMater, "sep2");
    G4Transform3D trans_sep2(rotcspacer, G4ThreeVector(housing_x0+sep1z+60+sep2z/2,0,0));
    pv_sep2 = new G4PVPlacement(trans_sep2, lv_sep2, "sep2", lvSiLi, 1, 0, checkOverlaps);

    // pre-amp cover
    G4double paCoverZ = 90*mm;
    G4Tubs* paCover = new G4Tubs("paCover",73*mm/2.,75*mm/2,paCoverZ/2.,0,360*deg);
    lv_paCover = new G4LogicalVolume(paCover, BdiscMater, "paCover");
    G4Transform3D trans_paCover(rotcspacer, G4ThreeVector(housing_x0+sep1z+60+sep2z-paCoverZ/2,0,0));
    pv_paCover = new G4PVPlacement(trans_paCover, lv_paCover, "paCover", lvSiLi, 1, 0, checkOverlaps);
    



    // insensitive ring around the sili, extending it from d=50 to d=57
    G4Tubs* siRing = new G4Tubs("siRing",50*mm/2 ,57*mm/2,5*mm/2.,0,360*deg);
    lv_siRing = new G4LogicalVolume(siRing, SideDetectorMater, "siRing");
    G4Transform3D trans_siRing(rotcspacer, G4ThreeVector(0,0,0));
    pv_siRing = new G4PVPlacement(trans_siRing, lv_siRing, "siRing", lvSiLi, 1, 0, checkOverlaps);
  }
    

}

/*----------------------------------------------------*/
void DetectorConstruction::ConstructTrap() {
  /*----------------------------------------------------*/

  // placement coordinates
  //
  G4double x1, y1, z1, phi=0.;
  G4int ONFLOORTESTS=0;

  // Be window
   G4EllipticalTube* svSideInnerWindow = new G4EllipticalTube(WindowName, SideInnerWindowRadius, SideInnerWindowRadius, SideInnerWindowThick);
  lvSideInnerWindow = new G4LogicalVolume(svSideInnerWindow, WindowMater, WindowName);
  for (int i=-1; i<6; i++) {
    int j = -i;
    phi = 45*deg * j;
    G4RotationMatrix rotWin;
    rotWin.rotateX(0*deg);rotWin.rotateY(270*deg); rotWin.rotateZ(phi);
    G4double r1 = 418.*mm;//SideInnerWindowDist + SideInnerWindowThick;
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
    G4double r1 = 455.163*mm;//SideOuterWindowDist + SideOuterWindowThick;
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
    pvElectrodeMid = new G4PVPlacement(transElec, lvElectrodeMid, ElectrodeName, lvWorld, 0, i);
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


  
  //pvSiLi = new G4PVPlacement(0, G4ThreeVector(), lvSiLi, "SiLi", lvWorld, 1, 0, checkOverlaps);

  if (0) {
    //perhaps also place a stell vessel
    G4Tubs* vessel = new G4Tubs("vessel",40*cm,41*cm,80*cm/2,0,360*deg);
    lvVessel = new G4LogicalVolume(vessel, SSteelMater, "vessel");
    G4RotationMatrix rotvessel;
    phi=90*deg;
    rotvessel.rotateY(270*deg); rotvessel.rotateZ(phi);
    G4Transform3D trans_vessel(rotvessel, G4ThreeVector(-460*mm,0,0));
    pvVessel = new G4PVPlacement(trans_vessel, lvVessel, "vessel", lvWorld, 1, 0, checkOverlaps);

    // and a steel port ring
    G4Tubs* port8 = new G4Tubs("port8",4.75*2.53*cm/2,8*2.54*cm/2,2*cm/2,0,360*deg);
    lvPort8 = new G4LogicalVolume(port8, SSteelMater, "port8");
    G4RotationMatrix rotport8;
    phi=0;
    rotport8.rotateY(270*deg); rotport8.rotateZ(phi);
    G4Transform3D trans_port8(rotport8, G4ThreeVector(-10*mm,0,0));
    pvPort8 = new G4PVPlacement(trans_port8, lvPort8, "port8", lvWorld, 1, 0, checkOverlaps);
  }


  if (ONFLOORTESTS) {
    /* this assumes a base plate and a back(/end) plate.
       the usual setup is:
       the end plate (with the source)is 130mm in front of the crystal.
       the rods are 330mm long.
       the base plate is on the other end of the rods
       a modified setup for the ba133 calib 4/2013 is:
       the end plate is an additional 155 farther away from the crystal.
       (detector pulled back a little)
       a 3rd (and eventually nominal setup for the strong R600 Ba133)
       two sets of rods instead of one, so distance 130+330 
    */
    //perhaps a steel floor of sorts?
    G4Box* floor = new G4Box("floor", WorldSize, WorldSize, 0.5*cm/2);
    lvFloor = new G4LogicalVolume(floor, SSteelMater, "floor");
    pvFloor = new G4PVPlacement(0, G4ThreeVector(0,0,-150*mm), lvFloor, "floor", lvWorld, 1, 0, checkOverlaps);

    // create a virtual box for the support structure
    //G4Box* boxSuSt = new G4Box("SupporStruct", 49*cm/2, 24*cm/2, 24*cm/2);
    //lvSupportStruct = new G4LogicalVolume(boxSuSt, WorldMater, "SupporStructure");

    // base plate
    G4double baplZ=20*mm;
    G4Box* baplBase = new G4Box("bapl", 200*mm/2,200*mm/2,baplZ/2);
    G4Tubs* baplHole = new G4Tubs("bapl",0,100*mm/2,baplZ,0,360*deg);
    G4SubtractionSolid* baPl =
      new G4SubtractionSolid("baPl",baplBase,baplHole,NULL,G4ThreeVector(0,0,0));
    lv_baPl = new G4LogicalVolume(baPl, BdiscMater, "baPl");
    G4RotationMatrix rotbapl;
    phi=0;
    rotbapl.rotateY(270*deg); rotbapl.rotateZ(phi);
    G4Transform3D trans_bapl(rotbapl, G4ThreeVector(200*mm+baplZ/2,0,0));
    pv_baPl = new G4PVPlacement(trans_bapl, lv_baPl, "baPl", lvSiLi, 1, 0, checkOverlaps);

    // end plate
    G4double endplZ=13*mm;
    G4Box* endplBase = new G4Box("endpl", 200*mm/2,200*mm/2,endplZ/2);
    G4Tubs* endplHole = new G4Tubs("endpl",0,125*mm/2,endplZ,0,360*deg);
    G4SubtractionSolid* endpl =
      new G4SubtractionSolid("endpl",endplBase,endplHole,NULL,G4ThreeVector(0,0,0));
    lv_endPl = new G4LogicalVolume(endpl, BdiscMater, "endPl");
    G4RotationMatrix rotendpl;
    phi=0;
    rotendpl.rotateY(270*deg); rotendpl.rotateZ(phi);
    G4Transform3D trans_endpl(rotendpl, G4ThreeVector(-130*mm-endplZ/2,0,0));
    pv_endPl = new G4PVPlacement(trans_endpl, lv_endPl, "endPl", lvSiLi, 1, 0, checkOverlaps);


    //rods
    G4double rodZ=330*mm;
    G4Tubs* rod = new G4Tubs("rod",0,20*mm/2,rodZ/2,0,360*deg);
    lvRod = new G4LogicalVolume(rod, BdiscMater, "rod");

    G4RotationMatrix rotrod;
    phi=0;
    rotrod.rotateY(270*deg); rotrod.rotateZ(phi);
    G4Transform3D trans_rod0(rotrod, G4ThreeVector(35*mm,90*mm,90*mm));
    pvRod0 = new G4PVPlacement(trans_rod0, lvRod, "rod", lvSiLi, 1, 0, checkOverlaps);

    //ok, what the hell, just place it by hand 3 more times, copy&paste FTW!
    G4Transform3D trans_rod1(rotrod, G4ThreeVector(35*mm,-90*mm,90*mm));
    pvRod1 = new G4PVPlacement(trans_rod1, lvRod, "rod", lvSiLi, 1, 1, 1);
    G4Transform3D trans_rod2(rotrod, G4ThreeVector(35*mm,90*mm,-90*mm));
    pvRod2 = new G4PVPlacement(trans_rod2, lvRod, "rod", lvSiLi, 1, 2, 1);
    G4Transform3D trans_rod3(rotrod, G4ThreeVector(35*mm,-90*mm,-90*mm));
    pvRod3 = new G4PVPlacement(trans_rod3, lvRod, "rod", lvSiLi, 1, 3, 1);


    
    //pvSupportStruct = new G4PVPlacement(0, G4ThreeVector(), 
    //					lvSupportStruct, "SupportStruct", lvSiLi, 1, 0, checkOverlaps);

  }
  
//pvSiLi = new G4PVPlacement(0, G4ThreeVector(), lvSiLi, "SiLi", lvWorld, 1, 0, checkOverlaps);
for (int i=-1; i<6;i++){
    int j = -i;
    phi = 45*deg * j;
    G4RotationMatrix rotWin;
    rotWin.rotateX(90*deg);rotWin.rotateY(0*deg); rotWin.rotateZ(phi);
    G4double r1 = 459.805*mm;//SideCanisterDist + SideCanisterThick;
    int x1 = cos(phi)*r1;
    int y1 = sin(phi)*r1;
    int z1 = 0;
    G4Transform3D transWin(rotWin, G4ThreeVector(x1,y1,z1));  
    pvSiLi = new G4PVPlacement(transWin, lvSiLi, "SiLi", lvWorld, 1, i, checkOverlaps);
    //pvSideCanister = new G4PVPlacement(transWin, lvSideCanister, CanisterName, lvWorld, 0, i);

  //pvSiLi = new G4PVPlacement(0, G4ThreeVector(), lvSiLi, "SiLi", lvWorld, 1, 0, checkOverlaps);
}
  
}