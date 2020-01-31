#include "DetectorMessenger.hh"

#include "G4Material.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Polyhedra.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4AssemblyVolume.hh"
#include "G4SubtractionSolid.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "DetectionSystemSiLi.hh"
#include "MaterialsList.hh"

#include "G4SystemOfUnits.hh" // new version geant4.10 requires units
#include "DetectorConstruction.hh"

DetectionSystemSiLi::DetectionSystemSiLi() {}



void DetectionSystemSiLi::SetSideDetectorMaterial(G4String material)
{
  //  mlistSiLi = new MaterialsList();
  //mlistSiLi->Construct();
  //SideDetectorMater = mlistSiLi->GetMaterial(material);
  //delete mlistSiLi;
}

/*----------------------------------------------------*/
G4int DetectionSystemSiLi::DefineMaterials() {
    mlistSiLi = new MaterialsList();
  //mlistSiLi->Construct();
  
  WorldMater = mlistSiLi->GetMaterial("Galactic");
  //delete mlistSiLi;
  return 0;
}

/*----------------------------------------------------*/
  
/*----------------------------------------------------*/
G4LogicalVolume* DetectionSystemSiLi::Build() {  // Formally ConstructSiLi
/*----------------------------------------------------*/
#include "DetectorParametersSiLi.input"

  // this ought to be a box that contains all elements of one detector
  G4double x1, y1, z1, phi;
  G4int placeBGO = 0;
  G4int placeCuPb = 1;

  DefineMaterials();

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
  return lvSiLi;
  // return lvSiLi;
}
