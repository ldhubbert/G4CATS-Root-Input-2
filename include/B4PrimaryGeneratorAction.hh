
#ifndef B4PrimaryGeneratorAction_h
#define B4PrimaryGeneratorAction_h 1

#include "TString.h" 

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Types.hh"

#include "globals.hh"

class TLorentzVector;
class G4ParticleGun;
class G4Event;
class B4PrimaryGeneratorMessenger;
class B4cDetectorConstruction;
class B4FileGenerator;

//Event generator mode
enum { EPGA_g4, EPGA_phase_space, EPGA_FILE, EPGA_Overlap };

class B4PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  B4PrimaryGeneratorAction();    
  ~B4PrimaryGeneratorAction();
  
  public:
  void GeneratePrimaries(G4Event*);

  void SetUpFileInput();
  void SetInputFile(TString filename){fInFileName=filename;};
  void SetNParticlesToBeTracked(Int_t n)
  {
  	fNToBeTracked = n;
	fTrackThis = new Int_t[n];
	for (G4int i = 0; i < fNToBeTracked; i++)
		fTrackThis[i] = -99;
  }
  void SetParticlesToBeTracked(Int_t ipart){if(fTrackThis) fTrackThis[fNToBeTcount++]=ipart;}
  Int_t *GetParticlesToBeTracked(){return fTrackThis;}
  Int_t GetNParticlesToBeTracked(){return fNToBeTracked;}
  G4bool IsTracked(Int_t part)
  {
  	for (G4int i = 0; i < fNToBeTracked; i++)
		if (part == fTrackThis[i])
			return true;
	return false;
  }
  G4int GetNEvents();

  Int_t GetNGenParticles(){return fNGenParticles;}
  Int_t GetNGenMaxParticles(){return fNGenMaxParticles;}
  TLorentzVector* GetGenLorentzVec(Int_t i){return fGenLorentzVec[i];}
  TLorentzVector** GetGenLorentzVecs(){return fGenLorentzVec;}
  TLorentzVector* GetBeamLorentzVec(){return fBeamLorentzVec;}
  Float_t* GetVertex(){return fGenPosition;}
  Int_t* GetGenPartType(){return fGenPartType;}
  
  void SetDetCon(B4cDetectorConstruction* det){fDetCon=det;}

private:
  G4ParticleGun* fParticleGun;
  B4PrimaryGeneratorMessenger* fGunMessenger;
  B4cDetectorConstruction* fDetCon;
  TString fInFileName;
  Int_t fNGenParticles;
  Int_t fNGenMaxParticles;
  Float_t fGenPosition[3];
  TLorentzVector ** fGenLorentzVec;
  TLorentzVector* fBeamLorentzVec;
  B4FileGenerator* fFileGen;

  Int_t *fGenPartType;
  Int_t *fTrackThis;
  Int_t fNToBeTracked;
  Int_t fNToBeTcount;
  Int_t fNevent;

  G4int fMode;
public:
  void SetMode(G4int mode);
  G4int GetMode(){return fMode;}
  B4FileGenerator* GetFileGen() const {return fFileGen; }

private:
  void PhaseSpaceGenerator(G4Event* anEvent);
  void OverlapGenerator(G4Event* anEvent);
  G4float fTmin;
  G4float fTmax;
  G4float fThetamin;
  G4float fThetamax;
  G4float fBeamEnergy;
  G4float fBeamXSigma;
  G4float fBeamYSigma;
  G4float fBeamDiameter;
  G4float fTargetZ0;
  G4float fTargetThick;
  G4float fTargetRadius;
  G4float fSplitTheta;

public:
  void SetTmin(G4float min){fTmin=min;}
  void SetTmax(G4float max){fTmax=max;}
  void SetThetamin(G4float min){fThetamin=min;}
  void SetThetamax(G4float max){fThetamax=max;}
  void SetBeamEnergy(G4float energy){fBeamEnergy=energy;}
  void SetBeamXSigma(G4float sigma){fBeamXSigma=sigma;}
  void SetBeamYSigma(G4float sigma){fBeamYSigma=sigma;}
  void SetBeamDiameter(G4float d){fBeamDiameter=d;}
  void SetTargetZ0(G4float z){fTargetZ0=z;}
  void SetTargetThick(G4float z){fTargetThick=z;}
  void SetTargetRadius(G4float z){fTargetRadius=z;}
  void SetSplitTheta(G4float min){fSplitTheta=min;}

};

#endif
