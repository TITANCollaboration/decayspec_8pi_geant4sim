#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class RunMessenger;
class XrayAnalysis;

class RunAction : public G4UserRunAction
{
public:
  RunAction(XrayAnalysis*);
  ~RunAction();
  
public:
  void BeginOfRunAction(const G4Run*);
  void   EndOfRunAction(const G4Run*);
  void SetRunNumber(G4int v) { runno=v; }
  G4int GetRunNumber() { return runno; }

private:
  RunMessenger* messenger;
  XrayAnalysis* XA;
  G4int runno;
};

#endif
