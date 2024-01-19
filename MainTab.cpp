#include "gui.h"

void easyBot::main_form::InitializeMainTab(void)
{
    //################ TabPages  ####################
    mainTab = gcnew System::Windows::Forms::TabPage();
    mainTab->Text = "Main";
    targetTab = gcnew System::Windows::Forms::TabPage();
    targetTab->Text = "Skill&Target";
    waypointTab = gcnew System::Windows::Forms::TabPage();
    waypointTab->Text = "Cavebot";
    healingTab = gcnew System::Windows::Forms::TabPage();
    healingTab->Text = "Healing";
    tabView = gcnew System::Windows::Forms::TabControl();
    tabView->Dock = System::Windows::Forms::DockStyle::Fill;
    tabView->TabPages->Add(mainTab);
    tabView->TabPages->Add(waypointTab);
    tabView->TabPages->Add(targetTab);
    tabView->TabPages->Add(healingTab);
    Controls->Add(tabView);
    //################ Background Workers ####################
    walkerBot_Worker = gcnew System::ComponentModel::BackgroundWorker();
    walkerBot_Worker->WorkerSupportsCancellation = true;
    walkerBot_Worker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &main_form::startWalkerBot_thread);
    targetBot_Worker = gcnew System::ComponentModel::BackgroundWorker();
    targetBot_Worker->WorkerSupportsCancellation = true;
    targetBot_Worker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &main_form::startTargetBot_thread);
    healingBot_Worker = gcnew System::ComponentModel::BackgroundWorker();
    healingBot_Worker->WorkerSupportsCancellation = true;
    healingBot_Worker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &main_form::startHealingBot_thread);
    //######################   Main Tab    ##########################
    startBot_Button = gcnew System::Windows::Forms::Button();
    startBot_Button->Location = Point(0, 250);
    startBot_Button->Text = "Start Bot";
    startBot_Button->BackColor = Color::Red;
    startBot_Button->Click += gcnew EventHandler(this, &main_form::startBot);
    mainTab->Controls->Add(startBot_Button);
}
void easyBot::main_form::startBot(Object^ sender, EventArgs^ e)
{
    if (startBot_Button->BackColor == Color::Red)
    {
        startBot_Button->BackColor = Color::Green;
        startBot_Button->Text = "Stop Bot";
        walkerBot_Worker->RunWorkerAsync();
        targetBot_Worker->RunWorkerAsync();
        healingBot_Worker->RunWorkerAsync();
    }
    else
    {
        startBot_Button->BackColor = Color::Red;
        startBot_Button->Text = "Start Bot";
        targetBot_Worker->CancelAsync();
        walkerBot_Worker->CancelAsync();
        healingBot_Worker->CancelAsync();
    }
}