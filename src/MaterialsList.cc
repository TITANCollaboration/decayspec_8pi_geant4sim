#include "MaterialsList.hh"
#include "globals.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

MaterialsList* MaterialsList::theMaterialsList = NULL;

MaterialsList::MaterialsList()
{
  DefineMaterials();
}

//MaterialsList::~MaterialsList()
//{
//}

void MaterialsList::DefineMaterials()
{
  G4double a, z; // atomic mass and number
  G4double fractionmass, density;
  G4int n, ncomponents, natoms;

  // Nist manager and elements
  //
  G4NistManager* Nman = G4NistManager::Instance();

  Be = Nman->FindOrBuildElement(n=4);
  B  = Nman->FindOrBuildElement(n=5);
  C  = Nman->FindOrBuildElement(n=6);
  N  = Nman->FindOrBuildElement(n=7);
  O  = Nman->FindOrBuildElement(n=8);
  F  = Nman->FindOrBuildElement(n=9);
  Mg = Nman->FindOrBuildElement(n=12);
  Al = Nman->FindOrBuildElement(n=13);
  Si = Nman->FindOrBuildElement(n=14);
  K  = Nman->FindOrBuildElement(n=19);
  Cr = Nman->FindOrBuildElement(n=24);
  Fe = Nman->FindOrBuildElement(n=26);
  Cu = Nman->FindOrBuildElement(n=29);
  Ge = Nman->FindOrBuildElement(n=32);
  Nb = Nman->FindOrBuildElement(n=41);
  Sn = Nman->FindOrBuildElement(n=50);
  // ADDING LEAD
  Pb = Nman->FindOrBuildElement(n=82);
  // ADDING Bi
  Bi = Nman->FindOrBuildElement(n=83);
  Air = Nman->FindOrBuildMaterial("G4_AIR");
  Galactic = Nman->FindOrBuildMaterial("G4_Galactic");

  // materials

  Carbon = new G4Material("Carbon", density=2.267*g/cm3, ncomponents=1);
  Carbon ->AddElement(C, fractionmass=1.);
  Beryllium = new G4Material("Beryllium", density=1.85*g/cm3, ncomponents=1);
  Beryllium ->AddElement(Be, fractionmass=1.);
  Aluminium = new G4Material("Aluminium", density=2.70*g/cm3, ncomponents=1);
  Aluminium ->AddElement(Al, fractionmass=1.);
  Silicon = new G4Material("Silicon", z=Si->GetZ(), a=Si->GetA(),
			   density=2.329*g/cm3, kStateSolid, 77*kelvin);
  //Silicon   = new G4Material("Silicon", density=2.33*g/cm3, ncomponents=1);
  //Silicon   ->AddElement(Si, fractionmass=1.);
  Germanium = new G4Material("Germanium", z=Ge->GetZ(), a=Ge->GetA(),
			   density=5.323*g/cm3, kStateSolid, 77*kelvin);
  //Germanium = new G4Material("Germanium", density=5.323*g/cm3, ncomponents=1);
  //Germanium ->AddElement(Ge, fractionmass=1.);
  Copper    = new G4Material("Copper", density=8.931*g/cm3, ncomponents=1);
  Copper    ->AddElement(Cu, fractionmass=1.);
  // ADDING LEAD PROPERTIES
  Lead = new G4Material("Lead", density=11.34*g/cm3, ncomponents=1);
  Lead      ->AddElement(Pb, fractionmass=1.);
  Al2O3 = new G4Material("Al2O3", density= 3.90*g/cm3, ncomponents=2);
  Al2O3 ->AddElement(Al, natoms=2);
  Al2O3 ->AddElement(O , natoms=3);
  B2O3  = new G4Material("B2O3", density= 1.81*g/cm3, ncomponents=2);
  B2O3  ->AddElement(B, natoms=2);
  B2O3  ->AddElement(O, natoms=3);
  // ADDING BGO
  BGO  = new G4Material("BGO", density= 7.10*g/cm3, ncomponents=3);
  BGO  ->AddElement(O, natoms=12);
  BGO  ->AddElement(Ge, natoms=3);
  BGO  ->AddElement(Bi, natoms=4);
  //
  K2O   = new G4Material("K2O", density= 2.32*g/cm3, ncomponents=2);
  K2O   ->AddElement(K, natoms=2);
  K2O   ->AddElement(O, natoms=1);
  MgO   = new G4Material("MgO", density= 3.58*g/cm3, ncomponents=2);
  MgO   ->AddElement(Mg, natoms=1);
  MgO   ->AddElement(O , natoms=1);
  Nb3Sn = new G4Material("Nb3Sn", density = 8.27*g/cm3, ncomponents=2);
  Nb3Sn ->AddElement(Nb, natoms=3);
  Nb3Sn ->AddElement(Sn, natoms=1);
  SiO2  = new G4Material("SiO2", density= 2.65*g/cm3, ncomponents=2);
  SiO2  ->AddElement(Si, natoms=1);
  SiO2  ->AddElement(O , natoms=2);

  Macor = new G4Material("Macor", density= 2.52*g/cm3, ncomponents=6);
  Macor ->AddMaterial(SiO2 , fractionmass=0.46);
  Macor ->AddMaterial(MgO  , fractionmass=0.17);
  Macor ->AddMaterial(Al2O3, fractionmass=0.16);
  Macor ->AddMaterial(K2O  , fractionmass=0.10);
  Macor ->AddMaterial(B2O3 , fractionmass=0.07);
  Macor ->AddElement (F    , fractionmass=0.04);

  SSteel = new G4Material("Stainless Steel", density=7.79876*g/cm3, ncomponents=2);
  SSteel ->AddElement(Fe, fractionmass=0.89);
  SSteel ->AddElement(Cr, fractionmass=0.11);
}

MaterialsList* MaterialsList::Construct()
{
  if (theMaterialsList == NULL) {
    theMaterialsList = new MaterialsList();
  }
  return theMaterialsList;
}

G4Material* MaterialsList::GetMaterial(G4String material)
{
  //G4Material* pttoMaterial = G4Material::GetMaterial(material);
  //return pttoMaterial;
  G4Material* vMat = 0;
  if      (material == "Air")       { vMat = Air; }
  else if (material == "Galactic")  { vMat = Galactic; }
  else if (material == "Beryllium") { vMat = Beryllium; }
  else if (material == "Aluminium") { vMat = Aluminium; }
  else if (material == "Silicon")   { vMat = Silicon; }
  else if (material == "Germanium") { vMat = Germanium; }
  else if (material == "Copper")    { vMat = Copper; }
  else if (material == "Carbon")    { vMat = Carbon; }
  // ADDING LEAD
  else if (material == "Lead")      { vMat = Lead; }
  else if (material == "Al2O3")     { vMat = Al2O3; }
  else if (material == "B2O3")      { vMat = B2O3; }
  // ADDING BGO
  else if (material == "BGO")       { vMat = BGO; }
  else if (material == "K2O")       { vMat = K2O; }
  else if (material == "MgO")       { vMat = MgO; }
  else if (material == "Nb3Sn")     { vMat = Nb3Sn; }
  else if (material == "SiO2")      { vMat = SiO2; }
  else if (material == "Macor")     { vMat = Macor; }
  else if (material == "SSteel")    { vMat = SSteel; }
  else {
    G4cout << "Cannot find material in list." << G4endl;
  }

  return vMat;
}
