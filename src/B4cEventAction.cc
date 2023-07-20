
#include "B4cEventAction.hh"
#include "B4cCalorimeterSD.hh"
#include "B4cCalorHit.hh"
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

#include "B4cEventActionMessenger.hh"
#include "B4FileGenerator.hh"
#include "B4RunAction.hh"
#include "B4Version.hh"

using namespace CLHEP;

B4cEventAction::B4cEventAction()
: G4UserEventAction(),
	fCoreHCID(-1),
	fAnn1HCID(-1),
	fAnn2HCID(-1),
	fAnn3HCID(-1),
	fAnn4HCID(-1),
	fAnn5HCID(-1),
	fAnn6HCID(-1)
{
   fEventRate = 0;
   fReqEvents = 0;
   feventMessenger = new B4cEventActionMessenger(this);
   fOutFile=NULL;
   fOutTree=NULL;
   fOutFileName=TString("");
}

B4cEventAction::~B4cEventAction()
{}

B4cCalorHitsCollection* 
B4cEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const

{
  B4cCalorHitsCollection* hitsCollection 
    = static_cast<B4cCalorHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4cEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    


void B4cEventAction::PrintEventStatistics(
                              G4double coreEdep, G4double coreTrackLength,
			      G4double ann2Edep,
			      G4double ann3Edep,
			      G4double ann4Edep,
			      G4double ann5Edep,
			      G4double ann6Edep,
                              G4double ann1Edep, G4double ann1TrackLength) const
{
  // print event statistics
  G4cout
     << "   Core: total energy: " 
     << std::setw(1) << G4BestUnit(coreEdep, "Energy")
     << "       total track length: " 
     << std::setw(1) << G4BestUnit(coreTrackLength, "Length")
     << G4endl
     << "        Annulus Piece 1: total energy: " 
     << std::setw(2) << G4BestUnit(ann1Edep, "Energy")
     << "       total track length: " 
     << std::setw(2) << G4BestUnit(ann1TrackLength, "Length")
     << "        Annulus Piece 2: total energy: "
     << std::setw(3) << G4BestUnit(ann2Edep, "Energy")
     << "        Annulus Piece 3: total energy: "
     << std::setw(4) << G4BestUnit(ann3Edep, "Energy")
     << "        Annulus Piece 4: total energy: "
     << std::setw(5) << G4BestUnit(ann4Edep, "Energy")     
     << "        Annulus Piece 5: total energy: "
     << std::setw(6) << G4BestUnit(ann5Edep, "Energy")     
     << "        Annulus Piece 6: total energy: "
     << std::setw(7) << G4BestUnit(ann6Edep, "Energy")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cEventAction::BeginOfEventAction(const G4Event* /*event*/)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cEventAction::EndOfEventAction(const G4Event* event)
{  
  // Get hits collections IDs (only once)
  if ( fCoreHCID == -1 ) {
    fCoreHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("CoreHitsCollection");
    fAnn1HCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece1HitsCollection");//was: CoreHitsCollection
    fAnn2HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece2HitsCollection");
    fAnn3HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece3HitsCollection"); 
    fAnn4HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece4HitsCollection");
    fAnn5HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece5HitsCollection");
    fAnn6HCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("AnnulusPiece6HitsCollection");
  }

  // Get hits collections
  auto CoreHC = GetHitsCollection(fCoreHCID, event);
  auto Ann1HC = GetHitsCollection(fAnn1HCID, event);
  auto Ann2HC = GetHitsCollection(fAnn2HCID, event);
  auto Ann3HC = GetHitsCollection(fAnn3HCID, event);
  auto Ann4HC = GetHitsCollection(fAnn4HCID, event);
  auto Ann5HC = GetHitsCollection(fAnn5HCID, event);
  auto Ann6HC = GetHitsCollection(fAnn6HCID, event);
  // Get hit with total values
  auto CoreHit = (*CoreHC)[CoreHC->entries()-1];
  auto Ann1Hit = (*Ann1HC)[Ann1HC->entries()-1];
  auto Ann2Hit = (*Ann2HC)[Ann2HC->entries()-1];
  auto Ann3Hit = (*Ann3HC)[Ann3HC->entries()-1];
  auto Ann4Hit = (*Ann4HC)[Ann4HC->entries()-1];
  auto Ann5Hit = (*Ann5HC)[Ann5HC->entries()-1];
  auto Ann6Hit = (*Ann6HC)[Ann6HC->entries()-1];
  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     

    PrintEventStatistics(
      CoreHit->GetEdep(), CoreHit->GetTrackLength(),
      Ann2Hit->GetEdep(),
      Ann3Hit->GetEdep(),
      Ann4Hit->GetEdep(),
      Ann5Hit->GetEdep(),
      Ann6Hit->GetEdep(),
      Ann1Hit->GetEdep(), Ann1Hit->GetTrackLength());
 
      }  
  
  // Fill histograms, ntuple
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
 
  // fill histograms
  analysisManager->FillH1(0, CoreHit->GetEdep());
  analysisManager->FillH1(1, Ann1Hit->GetEdep());
  analysisManager->FillH1(2, CoreHit->GetTrackLength());
  analysisManager->FillH1(3, Ann1Hit->GetTrackLength());

  analysisManager->FillH1(4, Ann2Hit->GetEdep());
  analysisManager->FillH1(5, Ann3Hit->GetEdep());
  analysisManager->FillH1(6, Ann4Hit->GetEdep());
  analysisManager->FillH1(7, Ann5Hit->GetEdep());
  analysisManager->FillH1(8, Ann6Hit->GetEdep());
  
  // fill ntuple
  analysisManager->FillNtupleDColumn(0, CoreHit->GetEdep());
  analysisManager->FillNtupleDColumn(1, Ann1Hit->GetEdep());
  analysisManager->FillNtupleDColumn(2, CoreHit->GetTrackLength());
  analysisManager->FillNtupleDColumn(3, Ann1Hit->GetTrackLength());
  
  analysisManager->FillNtupleDColumn(4, Ann2Hit->GetEdep());
  analysisManager->FillNtupleDColumn(5, Ann3Hit->GetEdep());
  analysisManager->FillNtupleDColumn(6, Ann4Hit->GetEdep());
  analysisManager->FillNtupleDColumn(7, Ann5Hit->GetEdep());
  analysisManager->FillNtupleDColumn(8, Ann6Hit->GetEdep());
  
  analysisManager->AddNtupleRow();  
}  

G4int B4cEventAction::PrepareOutput(){
	fOutFile=new TFile(fOutFileName,"CREATE");

	return 1;

}

/*

void B4cEventAction::CloseOutput(){
if(!fCBOut) return;
  fCBOut->WriteTree();
  delete fCBOut;

  // write metadata
#if defined(__clang__)
    TString compiler("clang ");
    compiler += __clang_version__;
#elif defined(__GNUC__)
    TString compiler("gcc ");
    compiler += __VERSION__;
#else
    TString compiler("unknown");
#endif
  TString version(G4Version.c_str());
  version.ReplaceAll("$", "");
  version.ReplaceAll(" ", "");
  version.ReplaceAll("Name:", "");
  SysInfo_t sysInfo;
  gSystem->GetSysInfo(&sysInfo);
  struct utsname unameBuffer;
  uname(&unameBuffer);
  TDatime date;
  TString inputFile("none");
  if (fPGA->GetFileGen())
    inputFile = fPGA->GetFileGen()->GetFileName().c_str();
  TString trackedPart("unknown");
  if (fPGA->GetFileGen())
  {
    trackedPart = "";
    if (fPGA->GetFileGen()->GetType() == A2FileGenerator::kPlutoCocktail)
      trackedPart = "all stable (Pluto cocktail)";
    else if (fPGA->GetFileGen()->GetType() == A2FileGenerator::kGiBUU)
      trackedPart = "all (GiBUU)";
    else
    {
      for (G4int i = 0; i < fPGA->GetFileGen()->GetNParticles(); i++)
      {
        if (fPGA->GetFileGen()->IsParticleTrack(i))
        {
            if (trackedPart != "")
              trackedPart += ", ";
            trackedPart += TString::Format("%d (%s)", i+1, fPGA->GetFileGen()->GetParticleDefinition(i)->GetParticleName().c_str());
	}
      }
    }
  }


 TNamed meta("A2Geant4 Metadata", TString::Format("\n"
              "       Version            : %s\n"
              "       Geant4 Version     : %s\n"
              "       Compiler           : %s\n"
              "       Hostname           : %s\n"
              "       System model       : %s\n"
              "       OS name            : %s\n"
              "       OS release         : %s\n"
              "       OS version         : %s\n"
              "       OS architecture    : %s\n"
              "       Command            : %s\n"
              "       Detector setup     : %s"
              "       Input file         : %s\n"
              "       Output file        : %s\n"
              "       Tracked particles  : %s\n"
              "       Start time         : %s\n"
              "       Stop time          : %s\n"
              "       Tracking time      : %s\n"
              "       Tracked events     : %d\n"
              "       Average events/sec : %.2f",
              B4_VERSION,
              version.Data(),
              compiler.Data(),
              unameBuffer.nodename,
              sysInfo.fModel.Data(),
              unameBuffer.sysname,
              unameBuffer.release,
              unameBuffer.version,
              unameBuffer.machine,
              fInvokeCmd.Data(),
              fDetSetup.Data(),
              inputFile.Data(),
              fOutFile->GetName(),
              trackedPart.Data(),
              fStartTime.Data(),
              date.AsString(),
              fDuration.Data(),
              fReqEvents,
              fEventRate
              ).Data());
  meta.Write();

  fOutFile->Close();
//  if(fOutFile)delete fOutFile;

}

*/
