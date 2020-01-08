#include "XrayAnalysis.hh"
#include "XrayAnalysisMessenger.hh"
#include "SiliconDetector.hh"
#include "G4ThreeVector.hh"
#include <climits>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Randomize.hh"

XrayAnalysis::XrayAnalysis()
{
  siliDetector = new SiliconDetector();
  messenger = new XrayAnalysisMessenger(this);
  
  outdirectory = "";
  filename = "xray";
  filetype = ".dat";
  printopt = 0;
}

XrayAnalysis::~XrayAnalysis()
{
  currHits.clear();
  totalHits.clear();
  if (siliDetector) delete siliDetector;
  if (messenger) delete messenger;
  histo->save();
}

void XrayAnalysis::CreateHit(G4int detno, G4int trackID, G4int parentID, G4double edep,  
			     G4String volume, G4String particle, G4String process, 
			     G4ThreeVector pos, G4int particlePDGenc)
{
  PartialHit aHit;
  aHit.detno = detno;
  aHit.trackID = trackID;
  aHit.parentID = parentID;
  aHit.edep = edep;
  aHit.volume = volume;
  aHit.particle = particle;
  aHit.particleID = particlePDGenc;
  aHit.process = process;
//
  aHit.pos= pos;
  currHits.push_back(aHit);
}

void XrayAnalysis::ProcessEvent(int evtNb)
{
  // do the stuff for trees

  // figure out hits
  G4int nhit=currHits.size();
  std::vector<G4double> he(nhit),x(nhit),y(nhit),z(nhit);
  std::vector<G4String> hv(nhit);
  std::vector<G4int> pdg(nhit);
  for (G4int i=0; i<nhit; i++) {
    he[i]=(currHits[i].edep/keV);
    x[i]=(currHits[i].pos[0]);
    y[i]=(currHits[i].pos[1]);
    z[i]=(currHits[i].pos[2]);
    hv[i]=(currHits[i].volume);
    pdg[i]=(currHits[i].particleID);
  }    

  std::vector<G4String> volnames;
  for (G4int i=0; i<(G4int)currHits.size(); i++) {
    if (std::count(volnames.begin(), volnames.end(), currHits[i].volume)==0) { 
      volnames.push_back(currHits[i].volume);
    }
  }
  // figure out volumes
  G4int nvol=volnames.size();
  std::vector<G4double> vedep(nvol), vemeas(nvol);
  std::vector<G4int> nvhits(nvol);
  for (G4int i=0; i<nvol; i++) {
    vedep[i]=0;
    nvhits[i]=0;
    for (G4int j=0; j<nhit; j++) {
      if (currHits[j].volume==volnames[i]) { vedep[i]+=currHits[j].edep/keV; nvhits[i]+=1; }
    }
    G4double reso=sqrt(0.115*0.0038*vedep[i]+0.1936);
    vemeas[i]=G4RandGauss::shoot(vedep[i], reso );
  }

  //histo->SetHitInfo(he,hv,x,y,z,pdg);
  histo->SetVolInfo(volnames, vemeas, vedep, nvhits);
  histo->FillNtuple(0,evtNb,0,volnames.size(),currHits.size());

  // record tree groups
  std::vector< std::vector<PartialHit> > groups = FindPartialHits();
  for (G4int i=0; i<(G4int)groups.size(); i++) {
    // group into full hits and record
    FullHit aHit = MakeFullHit(groups[i]);
    aHit.evtNb = evtNb; // add event number
    totalHits.push_back(aHit);
  }
  currHits.clear();
}

void XrayAnalysis::ProcessRun()
{
  switch(printopt) {
  case 0:
    // regular print out of energies, volume, detector number, particle, process
    PrintFile();
    break;
  case 1:
    // print only energies, individual file for each detector number
    std::map<G4int, std::vector<G4double> > listDetnoEdep;
    for (G4int i=0; i<(G4int)totalHits.size(); i++) {
      G4int detno = totalHits[i].detno;
      G4double edep = totalHits[i].edep;
      if (detno >= 0)
	listDetnoEdep[detno].push_back(edep);
    }
    PrintEdepOnly(listDetnoEdep);
    break;
  }
  currHits.clear();
  totalHits.clear();
  //histo->save();
}

std::vector< std::vector<PartialHit> > XrayAnalysis::FindPartialHits()
{
  // find tree groups for partial hits
  std::vector< std::vector<PartialHit> > groups;
  while (!currHits.empty()) {
    std::vector<PartialHit> newGroup;
    // look for the ROOT, node with lowest parentID
    G4int rootPos = 0, IDcomp = INT_MAX;
    for (G4int i=0; i<(G4int)currHits.size(); i++) {
      PartialHit aNode = currHits[i];
      if (aNode.parentID < IDcomp) {
	IDcomp = aNode.parentID;
	rootPos = i;
      }
    }
    // add this root node to new group
    PartialHit rootNode = currHits[rootPos];
    newGroup.push_back(rootNode);
    currHits.erase(currHits.begin()+rootPos);
    // build the tree from this root node
    std::vector<G4int> groupIDs;
    G4int rootDetno = rootNode.detno;
    G4int removed;
    groupIDs.push_back(rootNode.trackID);
    // find and add child nodes
    do {
      removed = -1;
      for (G4int i=0; i<(G4int)currHits.size(); i++) {
	PartialHit aNode = currHits[i];
	for (G4int j=0; j<(G4int)groupIDs.size(); j++) {
	  if (aNode.parentID == groupIDs[j] && aNode.detno == rootDetno) {
	    newGroup.push_back(aNode);
	    groupIDs.push_back(aNode.trackID);
	    removed = i;
	    break;
	  }
	}
	if (removed >= 0) {
	  currHits.erase(currHits.begin()+removed);
	  break;
	}
      }
    } while (removed > 0);
    // push this group into vector
    groups.push_back(newGroup);
  }
  if (!currHits.empty()) currHits.clear();
  return groups;
}

FullHit XrayAnalysis::MakeFullHit(std::vector<PartialHit> group)
{
  // find root parent of this group; total the energy deposit
  G4int rootPos = 0, IDcomp = INT_MAX;
  G4double edep = 0;
  for (G4int i=0; i<(G4int)group.size(); i++) {
    PartialHit aNode = group[i];
    edep += aNode.edep;
    if (aNode.parentID < IDcomp) {
      IDcomp = aNode.parentID;
      rootPos = i;
    }
  }
  // total results into a full hit
  FullHit aHit;
  aHit.detno = group[rootPos].detno;
  aHit.edep = edep;
  aHit.volume = group[rootPos].volume;
  aHit.particle = group[rootPos].particle;
  aHit.process = group[rootPos].process;
//
  aHit.pos = group[rootPos].pos;
  // G4cout << "Full hit made with detno: " << aHit.detno << "; edep: " << aHit.edep
  //	 << "; volume: " << aHit.volume << "; particle: " << aHit.particle << "; process: " << aHit.process << G4endl;
  return aHit;
}

void XrayAnalysis::PrintFile()
{
  G4cout << "Now writing to files..." << G4endl;
  
  G4int nhits = totalHits.size();
  G4String outname = outdirectory + filename + filetype;
  std::ofstream File(outname, std::ios::out);
  
  for (G4int i=0; i<nhits; i++) {
    std::stringstream ss;
    ss << std::setw( 8) << (totalHits[i].edep / keV) << "\t"
       << std::setw( 8) << totalHits[i].evtNb << "\t"
       << std::setw( 8) << totalHits[i].detno << "\t"
       << std::setw(15) << totalHits[i].volume << "\t"
       << std::setw( 8) << totalHits[i].particle << "\t"
       << std::setw( 8) << totalHits[i].process << "\t"
//
       << std::setw( 8) << totalHits[i].pos;  

    G4String rowstr = ss.str() + "\n";
    File << rowstr;
  }
}

void XrayAnalysis::PrintEdepOnly(std::map<G4int, std::vector<G4double> > listDetnoEdep)
{
  G4cout << "Now writing to files..." << G4endl;
  
  std::map<G4int, std::vector<G4double> >::iterator it;
  for (it = listDetnoEdep.begin(); it != listDetnoEdep.end(); it++) {
    G4int detno = it->first;
    std::vector<G4double> listEdep = it->second;
    std::stringstream ss;
    ss << detno;
    // det{n}.dat: list of edep hits per detector
    //
    filename = "det" + ss.str();
    if (!filename) filename = "test";
    G4String outname = filename + filetype;
    std::ofstream File(outname, std::ios::out);
    G4int hits = listEdep.size();
    // print edep in keV
    //
    for (G4int i=0; i<hits; i++) {
      G4double hitdep = listEdep.back();
      // perform response here
      if (detno >= 0 && detno <= 2)
	hitdep = siliDetector->DetectorResponse(hitdep) / keV;
      else if (detno >= 3 && detno <= 6)
	hitdep = siliDetector->DetectorResponse(hitdep) / keV;
      File << hitdep << G4endl;
      listEdep.pop_back();
    }
  }
}
