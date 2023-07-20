
#ifndef B4cEventAction_h
#define B4cEventAction_h 1

#include "G4UserEventAction.hh"

#include "B4cCalorHit.hh"

#include "globals.hh"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

/// Event action class
///
/// In EndOfEventAction(), it prints the accumulated quantities of the energy 
/// deposit and track lengths of charged particles in Absober and Gap layers 
/// stored in the hits collections.

class B4PrimaryGeneratorAction;
class B4cEventActionMessenger;

class B4cEventAction : public G4UserEventAction
{
public:
  B4cEventAction();
  virtual ~B4cEventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);

public:

  void SetReqEvents(G4int ev) { fReqEvents = ev; }

  void SetOutFileName(TString name){fOutFileName=name;}
  G4int PrepareOutput();
  void CloseOutput();
    
private:
  // methods
  B4cCalorHitsCollection* GetHitsCollection(G4int hcID,
                                            const G4Event* event) const;
  void PrintEventStatistics(G4double coreEdep, G4double coreTrackLength,
		  	    G4double ann2Edep,
			    G4double ann3Edep,
			    G4double ann4Edep,
			    G4double ann5Edep,
			    G4double ann6Edep,
                            G4double ann1Edep, G4double ann1TrackLength) const;
  
  // data members                   
 // G4int  fAbsHCID;
 // G4int  fGapHCID;
 G4int	fCoreHCID;
 G4int	fAnn1HCID;
 G4int  fAnn2HCID;
 G4int  fAnn3HCID;
 G4int  fAnn4HCID;
 G4int  fAnn5HCID;
 G4int  fAnn6HCID;

 B4cEventActionMessenger* feventMessenger;

 TFile* fOutFile;
 TTree* fOutTree;
 TString fOutFileName;

 TString fDuration;
 G4double fEventRate;
 G4int fReqEvents;

};

#endif

    
