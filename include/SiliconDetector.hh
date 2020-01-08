#ifndef SiliconDetector_h
#define SiliconDetector_h 1

#include "globals.hh"

class SiliconDetector
{
public:
  SiliconDetector();
  ~SiliconDetector();
  
  void SetResponse(G4bool val) { response = val; };
  void SetA(G4double val) { A = val; };
  void SetB(G4double val) { B = val; };
  void SetC(G4double val) { C = val; };
  G4double DetectorResponse(G4double);
  
private:
  G4bool response;
  G4double A, B, C;
};

#endif
