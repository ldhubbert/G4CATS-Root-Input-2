#include "B4PrimaryGeneratorMessenger.hh"

#include "B4PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

B4PrimaryGeneratorMessenger::B4PrimaryGeneratorMessenger(B4PrimaryGeneratorAction* B4Gun)
:B4Action(B4Gun)
{
	gunDir = new G4UIdirectory("/G4CATS/generator/");
	gunDir->SetGuidance("PrimaryGenerator control");

	SetInputCmd = new G4UIcmdWithAString("/G4CATS/generator/InputFile",this);
	SetInputCmd->SetGuidance("Set the file with the input ROOT ntuple");
	SetInputCmd->SetParameterName("inputfile",false);
	SetInputCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	SetInput2Cmd = new G4UIcmdWithAString("/G4CATS/generator/PrepareInout",this);
	SetInput2Cmd->SetGuidance("Prepare the file with the input ROOT ntuple");
	SetInput2Cmd->SetParameterName("Ntrack",false);
	SetInput2Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	SetNTrackCmd = new G4UIcmdWithAnInteger("/G4CATS/generator/NToBeTracked",this);
	SetNTrackCmd->SetGuidance("Set the number of generated particles to be tracked");
	SetNTrackCmd->SetParameterName("Ntrack",false);
	SetNTrackCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	SetTrackCmd = new G4UIcmdWithAnInteger("/G4CATS/generator/Track",this);
	SetTrackCmd->SetGuidance("Set the index of the particles to be tracked, this comes from the ntuple branch name.");
	SetTrackCmd->SetParameterName("Track",false);
	SetTrackCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	SetModeCmd = new G4UIcmdWithAnInteger("/G4CATS/generator/Mode",this);
	SetModeCmd->SetGuidance("Set the mode of the generator, command line, phase space, or ROOT");
	SetModeCmd->SetParameterName("Mode",false);
	SetModeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

//	SetSeedCmd = new G4UIcmdWithAnInteger("/G4CATS/generator/Seed",this);
//	SetSeedCmd->SetGuidance("Set the random seed of the generator");
//	SetSeedCmd->SetParameterName("Seed",false);
//	SetSeedCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	SetTminCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetTMin",this);
	SetTminCmd->SetGuidance("Set the minimum particle energy for the phase space generator");
	SetTminCmd->SetParameterName("Tmin",false);
	SetTminCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetTminCmd->SetUnitCategory("Energy");

	SetTmaxCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetTMax",this);
	SetTmaxCmd->SetGuidance("Set the maximum particle energy for the pase space generator");
	SetTmaxCmd->SetParameterName("Tmax",false);
	SetTmaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetTmaxCmd->SetUnitCategory("Energy");

	SetThetaminCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetThetaMin",this);
	SetThetaminCmd->SetGuidance("Set the minimum particle theta for the pase space generator");
	SetThetaminCmd->SetParameterName("Tmin",false);
	SetThetaminCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetThetaminCmd->SetUnitCategory("Angle");

	SetThetamaxCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetThetaMax",this);
	SetThetamaxCmd->SetGuidance("Set the maximum particle theta for the pase space generator");
	SetThetamaxCmd->SetParameterName("Tmax",false);
	SetThetamaxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetThetamaxCmd->SetUnitCategory("Angle");

	SetBeamEnergyCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetBeamEnergy",this);
	SetBeamEnergyCmd->SetGuidance("Set the energy of the photon beam");
	SetBeamEnergyCmd->SetParameterName("BeamEnergy",false);
	SetBeamEnergyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetBeamEnergyCmd->SetUnitCategory("Energy");

	SetBeamXSigmaCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetBeamXSigma",this);
	SetBeamXSigmaCmd->SetGuidance("Set the X wdith of the photon beam");
	SetBeamXSigmaCmd->SetParameterName("BeamXSigma",false);
	SetBeamXSigmaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetBeamXSigmaCmd->SetUnitCategory("Length");

	SetBeamYSigmaCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetBeamYSigma",this);
	SetBeamYSigmaCmd->SetGuidance("Set the Y width of the photon beam");
	SetBeamYSigmaCmd->SetParameterName("BeamYSigma",false);
	SetBeamYSigmaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetBeamYSigmaCmd->SetUnitCategory("Length");

	SetBeamDiameterCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetBeamDiameter",this);
	SetBeamDiameterCmd->SetGuidance("Set the diameter of the photon beam");
	SetBeamDiameterCmd->SetParameterName("BeamDiameter",false);
	SetBeamDiameterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetBeamDiameterCmd->SetUnitCategory("Length");

	SetTargetZ0Cmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetTargetZ0",this);
	SetTargetZ0Cmd->SetGuidance("Set the target Z0 position");
	SetTargetZ0Cmd->SetParameterName("TargetZ0",false);
	SetTargetZ0Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetTargetZ0Cmd->SetUnitCategory("Length");

	SetTargetThickCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetTargetThick",this);
	SetTargetThickCmd->SetGuidance("Set the target thickness");
	SetTargetThickCmd->SetParameterName("TargetThick",false);
	SetTargetThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetTargetThickCmd->SetUnitCategory("Length");

	SetTargetRadiusCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetTargetRadius",this);
	SetTargetRadiusCmd->SetGuidance("Set the x-y radius of the target");
	SetTargetRadiusCmd->SetParameterName("TargetRadius",false);
	SetTargetRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SetTargetRadiusCmd->SetUnitCategory("Length");

	SplitThetaCmd = new G4UIcmdWithADoubleAndUnit("/G4CATS/generator/SetSplitTheta",this);
	SplitThetaCmd->SetGuidance("Set the splitoff angle in the overlap generator");
	SplitThetaCmd->SetParameterName("SplitTheta",false);
	SplitThetaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
	SplitThetaCmd->SetUnitCategory("Angle");
}

B4PrimaryGeneratorMessenger::~B4PrimaryGeneratorMessenger()
{
	delete gunDir;
	delete SetInputCmd;
	delete SetInput2Cmd;
	delete SetNTrackCmd;
	delete SetTrackCmd;
	delete SetTminCmd;
	delete SetTmaxCmd;
	delete SetThetaminCmd;
	delete SetThetamaxCmd;
	delete SetModeCmd;
//	delete SetSeedCmd;
	delete SetBeamEnergyCmd;
	delete SetBeamXSigmaCmd;
	delete SetBeamYSigmaCmd;
	delete SetBeamDiameterCmd;
	delete SetTargetZ0Cmd;
	delete SetTargetThickCmd;
	delete SetTargetRadiusCmd;
	delete SplitThetaCmd;
}

void B4PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if (command == SetInputCmd)
	{ B4Action->SetInputFile(static_cast<TString>(newValue)); }

	if (command == SetInput2Cmd)
	{ B4Action->SetInputFile(static_cast<TString>(newValue)); B4Action->SetUpFileInput(); }

	if (command == SetNTrackCmd)
	{ B4Action->SetNParticlesToBeTracked(SetNTrackCmd->GetNewIntValue(newValue)); }

	if (command == SetTrackCmd)
	{ B4Action->SetParticlesToBeTracked(SetTrackCmd->GetNewIntValue(newValue)); }

	if (command == SetModeCmd)
	{ B4Action->SetMode(SetModeCmd->GetNewIntValue(newValue)); }

//	if (command == SetSeedCmd)
//	{ CLHEP::HepRandom::setTheSeed(SetSeedCmd->GetNewIntValue(newValue)); }

	if (command == SetTminCmd)
	{ B4Action->SetTmin(SetTminCmd->GetNewDoubleValue(newValue)); }

	if (command == SetTmaxCmd)
	{ B4Action->SetTmax(SetTmaxCmd->GetNewDoubleValue(newValue)); }

	if (command == SetThetaminCmd)
	{ B4Action->SetThetamin(SetThetaminCmd->GetNewDoubleValue(newValue)); }

	if (command == SetThetamaxCmd)
	{ B4Action->SetThetamax(SetThetamaxCmd->GetNewDoubleValue(newValue)); }

	if (command == SetBeamEnergyCmd)
	{ B4Action->SetBeamEnergy(SetBeamEnergyCmd->GetNewDoubleValue(newValue)); }

	if (command == SetBeamXSigmaCmd)
	{ B4Action->SetBeamXSigma(SetBeamXSigmaCmd->GetNewDoubleValue(newValue)); }

	if (command == SetBeamYSigmaCmd)
	{ B4Action->SetBeamYSigma(SetBeamYSigmaCmd->GetNewDoubleValue(newValue)); }

	if (command == SetBeamDiameterCmd)
	{ B4Action->SetBeamDiameter(SetBeamDiameterCmd->GetNewDoubleValue(newValue)); }

	if (command == SetTargetZ0Cmd)
	{ B4Action->SetTargetZ0(SetTargetZ0Cmd->GetNewDoubleValue(newValue)); }

	if (command == SetTargetThickCmd)
	{ B4Action->SetTargetThick(SetTargetThickCmd->GetNewDoubleValue(newValue)); }

	if (command == SetTargetRadiusCmd)
	{ B4Action->SetTargetRadius(SetTargetRadiusCmd->GetNewDoubleValue(newValue)); }

	if (command == SplitThetaCmd)
	{ B4Action->SetSplitTheta(SplitThetaCmd->GetNewDoubleValue(newValue)); }
}
