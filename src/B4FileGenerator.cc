#include "TMath.h"

#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

#include "B4FileGenerator.hh"

B4FileGenerator::B4FileGenerator(const char* filename, EFileGenType type)
{
	fType = type;
	fFileName = filename;
	fNEvents = 0;
	fWeight = 1;
}

void B4FileGenerator::B4GenParticle_t::SetCorrectMass(G4bool usePDG)
{
	if (usePDG && fDef)
	{
		fM = fDef->GetPDGMass();
		G4double p_old = fP.mag();
		G4double p_new = TMath::Sqrt(fE*fE - fM*fM);
		fP.set(fP.x()/p_old*p_new, fP.y()/p_old*p_new, fP.z()/p_old*p_new);
	}
	else
	{
		if (fDef && fDef->GetPDGMass() == 0)
			fM = 0;
		else
			fM = TMath::Sqrt(fE*fE - fP.mag2());
	}
}

void B4FileGenerator::SetParticleIsTrack(G4int p, G4bool t)
{
	if (t && !fPart[p].fDef)
		return;
	fPart[p].fIsTrack = t ;
}


void B4FileGenerator::GenerateVertexCylinder(G4double t_length, G4double t_center, G4double b_diam)
{
	Double_t vX = 1e10;
	Double_t vY = 1e10;
	Double_t beamRad = b_diam / 2.;
	while (vX*vX+vY*vY > beamRad*beamRad)
	{
		vX = beamRad * (2. * G4UniformRand() - 1.);
		vY = beamRad * (2. * G4UniformRand() - 1.);
	}
	Double_t vZ = t_length / 2. * (2. * G4UniformRand() - 1.) + t_center;
	fVertex.set(vX, vY, vZ);
}
