#include <string>
#include "CallFunction.h"
#include "Nostale_Entity.h"
#include "gui.h"
int GuiMain()
{
	FILE* f;
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);
	StartBot();
	easyBot::Application::EnableVisualStyles();
	easyBot::Application::SetCompatibleTextRenderingDefault(false);
	easyBot::Application::Run(gcnew easyBot::main_form(MoveTo, AttackMonster));
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, GetCurrentProcessId());
	TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);
	return 0;
}