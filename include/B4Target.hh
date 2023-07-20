
#ifndef B4Target_h
#define B4Target_h 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4ThreeVector.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

class B4Target
{
	public:
		B4Target();
		~B4Target();

		virtual G4VPhysicalVolume* Construct(G4LogicalVolume *MotherLogic, G4double Z0 = 0)=0;

		G4VPhysicalVolume* GetPhysi(){return fMyPhysi;}
		G4LogicalVolume* GetLogic(){return fMyLogic;}
		G4LogicalVolume* GetMotherLogic(){return fMotherLogic;}

		void SetIsInteractive(G4int is){fIsInteractive=is;}
		void SetMaterial(G4Material* mat){fMaterial=mat;}
		void SetLength(G4double l) { fLength = l; }
		void SetRadius(G4double r) { fRadius = r; }

		G4ThreeVector& GetCenter(){return fCenter;}
		G4double GetLength(){return fLength;}
		G4double GetRadius(){return fRadius;}

	protected:
		G4int fVerbose;
		G4int fIsInteractive;

		G4LogicalVolume* fMotherLogic;

		G4LogicalVolume* fMyLogic;
		G4VPhysicalVolume* fMyPhysi;
		G4Material* fMaterial;

		G4NistManager* fNistManager;

		G4ThreeVector fCenter;
		G4double fLength;
		G4double fRadius;
};

#endif
