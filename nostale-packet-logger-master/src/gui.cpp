#include "packet_logger.h"
#include "Nostale_Entity.h"
#include <string>
#include "gui.h"
using namespace easyBot;
int GuiMain()
{
	/*
	FILE* f;
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);
	SafeQueue qSend, qRecv;
	StartLogger(&qSend, &qRecv);
	while (1)
	{
		if (!qSend.empty())
		{
			cout << (LPCSTR)qSend.front() << endl;
			qSend.pop();
		}
		if(GetAsyncKeyState(VK_NUMPAD0) & 1)
			Collect(21);
	}
	*/
	StartLogger();
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew main_form(MoveTo, AttackMonster, Collect));
	StopLogger();
	return 0;
}