#ifndef MaterialsList_h
#define MaterialsList_h 1

#include "globals.hh"

class G4Element;
class G4Material;

class MaterialsList
{
public:
  MaterialsList();
  ~MaterialsList() {theMaterialsList = NULL;};
  
  void DefineMaterials();
  static MaterialsList* Construct();
  G4Material* GetMaterial(G4String);
  
  static MaterialsList* theMaterialsList;
  
private:
  G4Element *Be, *B, *Bi, *C, *N, *O, *F;
  G4Element *Mg, *Al, *Si, *K, *Cr, *Fe, *Cu, *Ge, *Nb, *Sn, *Pb;
  
  G4Material *Galactic, *Air;
  G4Material *Beryllium, *Aluminium, *Silicon, *Germanium, *Copper, *Lead, *Carbon;
  G4Material *Al2O3, *B2O3, *BGO, *K2O, *MgO, *Nb3Sn, *SiO2;
  G4Material *Macor, *SSteel;
};

#endif
