#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventMessenger;
class XrayAnalysis;

class EventAction : public G4UserEventAction
{
public:
  EventAction(XrayAnalysis*);
  ~EventAction();
  
  void BeginOfEventAction(const G4Event*);
  void   EndOfEventAction(const G4Event*);
  
  void SetPrintModulo(G4int val) {printModulo = val;};
  
private:
  G4int printModulo;
  EventMessenger* messenger;
  XrayAnalysis*   XA;
};

#endif
