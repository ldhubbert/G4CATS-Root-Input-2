
#ifndef B4PrimaryGeneratorMessenger_h
#define B4PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class B4PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class B4PrimaryGeneratorMessenger: public G4UImessenger
{
	public:
		B4PrimaryGeneratorMessenger(B4PrimaryGeneratorAction*);
		~B4PrimaryGeneratorMessenger();

		void SetNewValue(G4UIcommand*, G4String);

	private:
		B4PrimaryGeneratorAction* B4Action;
		G4UIdirectory* gunDir;

G4UIcmdWithAString* SetInputCmd;
G4UIcmdWithAString* SetInput2Cmd;
G4UIcmdWithAnInteger* SetNTrackCmd;
G4UIcmdWithAnInteger* SetTrackCmd;
G4UIcmdWithAnInteger* SetModeCmd;
G4UIcmdWithAnInteger* SetSeedCmd;
G4UIcmdWithADoubleAndUnit* SetTminCmd;
G4UIcmdWithADoubleAndUnit* SetTmaxCmd;
G4UIcmdWithADoubleAndUnit* SetThetaminCmd;
G4UIcmdWithADoubleAndUnit* SetThetamaxCmd;
G4UIcmdWithADoubleAndUnit* SetBeamEnergyCmd;
G4UIcmdWithADoubleAndUnit* SetBeamXSigmaCmd;
G4UIcmdWithADoubleAndUnit* SetBeamYSigmaCmd;
G4UIcmdWithADoubleAndUnit* SetBeamDiameterCmd;
G4UIcmdWithADoubleAndUnit* SetTargetZ0Cmd;
G4UIcmdWithADoubleAndUnit* SetTargetThickCmd;
G4UIcmdWithADoubleAndUnit* SetTargetRadiusCmd;
G4UIcmdWithADoubleAndUnit* SplitThetaCmd;
};

#endif
