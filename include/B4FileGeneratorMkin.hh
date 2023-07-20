#ifndef B4FileGeneratorMkin_h
#define B4FileGeneratorMkin_h 1

#include "Rtypes.h"

#include "B4FileGeneratorTree.hh"

class B4FileGeneratorMkin : public B4FileGeneratorTree
{
	protected:
		Float_t fVertexBr[3];
		Float_t fBeamBr[5];
		G4int fNPart;
		Float_t** fPartPBr;
		Float_t** fPartVBr;

		static const G4int fgMaxParticles;

	public:
		B4FileGeneratorMkin(const char* filename);
		virtual ~B4FileGeneratorMkin();

		virtual G4bool Init();
		virtual G4bool ReadEvent(G4int event);
		virtual G4int GetMaxParticles();
};

#endif
