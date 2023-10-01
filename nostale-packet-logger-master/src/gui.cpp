#include "packet_logger.h"
#include "Nostale_Entity.h"
#include <string>
#include "gui.h"
using namespace easyBot;
int GuiMain()
{
	StartLogger();
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew main_form(MoveTo, AttackMonster));
	StopLogger();
	return 0;
}