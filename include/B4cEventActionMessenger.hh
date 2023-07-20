
#ifndef B4cEventActionMessenger_h
#define B4cEventActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class B4cEventAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;

class B4cEventActionMessenger: public G4UImessenger
{
	public:
		B4cEventActionMessenger(B4cEventAction*);
		~B4cEventActionMessenger();

		void SetNewValue(G4UIcommand*, G4String);

	private:
		B4cEventAction* feventAction;
		G4UIdirectory* feventDir;
		G4UIcmdWithAString* fOutFileCmd;
};

#endif
