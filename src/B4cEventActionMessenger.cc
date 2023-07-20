#include "B4cEventActionMessenger.hh"

#include "B4cEventAction.hh"
#include "G4UIdirectory.hh"
//#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
//#include "G4UIcmdWithAnInteger.hh"
//#include "G4UIcmdWithABool.hh"
#include "globals.hh"

B4cEventActionMessenger::B4cEventActionMessenger(B4cEventAction* EvAct)
:feventAction(EvAct)
{
	feventDir = new G4UIdirectory("/G4CATS/event/");
	feventDir->SetGuidance("event control");

	fOutFileCmd = new G4UIcmdWithAString("/G4CATS/event/setOutputFile",this);
	fOutFileCmd->SetGuidance("set the full name and path of the output ROOT file");
	fOutFileCmd->SetParameterName("choice",true);
	fOutFileCmd->AvailableForStates(G4State_Idle);
}

B4cEventActionMessenger::~B4cEventActionMessenger()
{
	delete fOutFileCmd;
	delete feventDir;
}

void B4cEventActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if(command == fOutFileCmd)
	{feventAction->SetOutFileName(newValue.data());}
}
