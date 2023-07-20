
#ifndef B4cDetectorConstruction_h
#define B4cDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "B4Target.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In ConstructSDandField() sensitive detectors of B4cCalorimeterSD type
/// are created and associated with the Absorber and Gap volumes.
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class B4cDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B4cDetectorConstruction();
    virtual ~B4cDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    B4Target* GetTarget(){return fTarget;}
     
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
    G4int   fNofLayers;     // number of layers

    B4Target* fTarget;
};

#endif

