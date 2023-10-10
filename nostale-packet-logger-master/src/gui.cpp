#include "packet_logger.h"
#include "Nostale_Entity.h"
#include <string>
#include "gui.h"
using namespace easyBot;
int GuiMain()
{
	/*FILE* f;
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);*/
	StartLogger();
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew main_form(MoveTo, AttackMonster, Collect));
	StopLogger();
	return 0;
}