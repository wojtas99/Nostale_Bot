#pragma once
#include <msclr/marshal_cppstd.h> // Library to convert String^ to const char*
#include <msclr/marshal.h>
#include "memscan.h"
namespace easyBot
{

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Summary for main_form
    /// </summary>
    public ref class main_form : public System::Windows::Forms::Form
    {
    public:

        main_form(void)
        {
            InitializeComponent();
        }
        main_form(void(lpMoveTo)(uint32_t), void(lpAttackMonster)(uint32_t, short), void(lpCollect)(uint32_t))
        {
            InitializeComponent();
            this->Width = 700;
            this->Height = 700;
            this->Text = "KrawczorBot";
            this->attackMonster = lpAttackMonster;
            this->moveTo = lpMoveTo;
            this->collectItems = lpCollect;
        }
        ~main_form()
        {
            if (components)
            {
                delete components;
            }
        }
    private:
        void(*attackMonster)(uint32_t, short);
        void(*moveTo)(uint32_t);
        void(*collectItems)(uint32_t);
        DWORD monsterCountPointer = ReadPointer(0x7212D8, { 0x248 });
        DWORD myPosPointer = ReadPointer(0x008BDD80, { 0xAC, 0x00, 0x08, 0x68, 0x840, 0xFC4 });
        DWORD entityListPointer = ReadPointer(0x008B4F88, { 0x93C, 0x7AC, 0x204, 0x00 });
        DWORD attackStatusPointer = ReadPointer(0x008BD9E8, { 0x784, 0x178, 0x5BC, 0xE64, 0xD88 });
        DWORD groundItems = ReadPointer(0x00721634, { 0x26C, 0xE84, 0x04, 0x724, 0x00 });

        System::Windows::Forms::TabControl^ tabView;

        System::ComponentModel::BackgroundWorker^ attackWorker;
        System::ComponentModel::BackgroundWorker^ waypointWorker;

        System::ComponentModel::Container^ components; //Required designer variable.

        System::Windows::Forms::ListBox^ monsterList;
        System::Windows::Forms::ListBox^ attackMonsterList;
        System::Windows::Forms::ListBox^ waypointList;

        System::Windows::Forms::Button^ refreshMonsterList;
        System::Windows::Forms::Button^ startTargeting;
        System::Windows::Forms::Button^ startWalking;
        System::Windows::Forms::Button^ addWaypoint;

        System::Windows::Forms::Label^ labelMonsterList;
        System::Windows::Forms::Label^ labelMonsterAttack;

        System::Windows::Forms::TabPage^ mainTab;
        System::Windows::Forms::TabPage^ waypointTab;
        System::Windows::Forms::TabPage^ targetTab;

        bool walkingOn = false;


        void InitializeComponent(void)
        {
            FILE* f;
            AllocConsole();
            freopen_s(&f, "CONOUT$", "w", stdout);

            //################ TabPages  ####################
            //################  MainTab  ####################
            mainTab = gcnew System::Windows::Forms::TabPage();
            mainTab->Text = "Main";

            //################ TargetTab ####################
            targetTab = gcnew System::Windows::Forms::TabPage();
            targetTab->Text = "Target";

            //################ WaypointTab ####################
            waypointTab = gcnew System::Windows::Forms::TabPage();
            waypointTab->Text = "Waypoint";

            //################   TabView   ####################
            tabView = gcnew System::Windows::Forms::TabControl();
            tabView->Dock = System::Windows::Forms::DockStyle::Fill;
            tabView->TabPages->Add(mainTab);
            tabView->TabPages->Add(waypointTab);
            tabView->TabPages->Add(targetTab);
            Controls->Add(tabView);

            //################ Background Workers ####################
            //################ Attack Worker ########################
            attackWorker = gcnew System::ComponentModel::BackgroundWorker();
            attackWorker->WorkerSupportsCancellation = true;
            attackWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &main_form::startAttackWorker);

            //################ Waypoint Worker ########################
            waypointWorker = gcnew System::ComponentModel::BackgroundWorker();
            waypointWorker->WorkerSupportsCancellation = true;
            waypointWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &main_form::startWaypointWorker);

            //######################   Labels  ##############################
            //###################### LabelMonsterList #######################
            labelMonsterList = gcnew System::Windows::Forms::Label();
            labelMonsterList->Width = 250;
            labelMonsterList->Height = 25;
            labelMonsterList->Location = Point(500, 270);
            labelMonsterList->Text = "Monsters On The Map";
            targetTab->Controls->Add(labelMonsterList);

            //###################### LabelMonsterAttack #####################
            labelMonsterAttack = gcnew System::Windows::Forms::Label();
            labelMonsterAttack->Width = 250;
            labelMonsterAttack->Height = 25;
            labelMonsterAttack->Location = Point(250, 270);
            labelMonsterAttack->Text = "Monsters To Attack";
            targetTab->Controls->Add(labelMonsterAttack);

            //######################     ListBoxes     ######################
            //###################### AttackMonsterList ######################
            attackMonsterList = gcnew System::Windows::Forms::ListBox();
            attackMonsterList->Size = System::Drawing::Size(150, 300);
            attackMonsterList->Location = Point(250, 300);
            attackMonsterList->DoubleClick += gcnew EventHandler(this, &main_form::removeMonsterFromList);
            targetTab->Controls->Add(this->attackMonsterList);

            //###################### MonsterList ######################
            monsterList = gcnew System::Windows::Forms::ListBox();
            monsterList->Size = System::Drawing::Size(150, 300);
            monsterList->Location = Point(500, 300);
            monsterList->DoubleClick += gcnew EventHandler(this, &main_form::addMonsterToList);
            targetTab->Controls->Add(monsterList);

            //###################### WaypointList ######################
            waypointList = gcnew System::Windows::Forms::ListBox();
            waypointList->Size = System::Drawing::Size(150, 300);
            waypointList->Location = Point(500, 300);
            waypointTab->Controls->Add(waypointList);

            //######################    Buttons    ########################
            //#################### AddWaypointButton ######################
            addWaypoint = gcnew System::Windows::Forms::Button();
            addWaypoint->Location = Point(500, 600);
            addWaypoint->Width = 100;
            addWaypoint->Height = 30;
            addWaypoint->Text = "AddWaypoint";
            addWaypoint->Click += gcnew EventHandler(this, &main_form::addWaypoints);
            waypointTab->Controls->Add(addWaypoint);

            //###################### RefreshButton ########################
            refreshMonsterList = gcnew System::Windows::Forms::Button();
            refreshMonsterList->Location = Point(500, 600);
            refreshMonsterList->Width = 100;
            refreshMonsterList->Height = 30;
            refreshMonsterList->Text = "Refresh";
            refreshMonsterList->Click += gcnew EventHandler(this, &main_form::refreshList);
            targetTab->Controls->Add(refreshMonsterList);

            //###################### StartTargeting ########################
            startTargeting = gcnew System::Windows::Forms::Button();
            startTargeting->Location = Point(0, 500);
            startTargeting->Width = 85;
            startTargeting->Height = 25;
            startTargeting->Text = "Targeting Off";
            startTargeting->BackColor = Color::Red;
            startTargeting->Click += gcnew EventHandler(this, &main_form::startAttack);
            mainTab->Controls->Add(startTargeting);

            //######################  StartWalking  ########################
            startWalking = gcnew System::Windows::Forms::Button();
            startWalking->Location = Point(0, 400);
            startWalking->Width = 85;
            startWalking->Height = 25;
            startWalking->Text = "Walking Off";
            startWalking->BackColor = Color::Red;
            startWalking->Click += gcnew EventHandler(this, &main_form::startWalk);
            mainTab->Controls->Add(startWalking);
            
        }
        //###################### Close Main_Form ######################
        System::Void main_form_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) 
        {
            this->attackWorker->CancelAsync();
            this->waypointWorker->CancelAsync();
        }
        //###################### StartTargeting ######################
        System::Void startAttack(Object^ sender, EventArgs^ e)
        {
            if (startTargeting->BackColor == Color::Red)
            {
                startTargeting->BackColor = Color::Green;
                startTargeting->Text = "Targeting On";
                this->attackWorker->RunWorkerAsync();
            }
            else
            {
                startTargeting->BackColor = Color::Red;
                startTargeting->Text = "Targeting Off";
                this->attackWorker->CancelAsync();
            }
        }
        //###################### StartWalking ######################
        System::Void startWalk(Object^ sender, EventArgs^ e)
        {
            if (startWalking->BackColor == Color::Red)
            {
                startWalking->BackColor = Color::Green;
                startWalking->Text = "Walking On";
                this->waypointWorker->RunWorkerAsync();
            }
            else
            {
                startWalking->BackColor = Color::Red;
                startWalking->Text = "Walking Off";
                this->waypointWorker->CancelAsync();
            } 
        }
        //###################### Refresh Monster List Button ######################
        System::Void refreshList(System::Object^ sender, System::EventArgs^ e)
        {
            bool found = 0;
            uint32_t monsterCount = *(uint32_t*)monsterCountPointer;
            EntityList** monsters = (EntityList**)malloc(monsterCount * sizeof(EntityList*));
            /*
            for (int i = 0; i < monsterCount; ++i)
            {
                *(monsters + i) = (EntityList*)*((uint32_t*)(entityListPointer)+i);
                (*(monsters + i))->monsterNamePointer = (uint32_t)(((uint32_t*)(*(monsters + i))) + 0x6F);
                (*(monsters + i))->monsterNamePointer = (*(uint32_t*)((*(monsters + i))->monsterNamePointer)) + 0x04;
                (*(monsters + i))->monsterNamePointer = *(uint32_t*)((*(monsters + i))->monsterNamePointer);
                for (int tmp = 0; tmp < (int)this->monsterList->Items->Count; ++tmp)
                {
                    if (gcnew System::String((const char*)((*(monsters + i))->monsterNamePointer)) == (this->monsterList->Items[tmp]->ToString()))
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    this->monsterList->Items->Add(gcnew System::String((const char*)((*(monsters + i))->monsterNamePointer)));
                }
                found = 0;
            }
            */
            free(monsters);
        }
        //###################### Add Waypoint Button ######################
        System::Void addWaypoints(System::Object^ sender, System::EventArgs^ e)
        {
            if (*(uint32_t*)myPosPointer != 0)
                waypointList->Items->Add(*(uint32_t*)myPosPointer);
        }
        //###################### Add and Remove Monster ######################
        System::Void addMonsterToList(Object^ sender, EventArgs^ e)
        {
            if (monsterList->SelectedItem != nullptr)
            {
                this->attackMonsterList->Items->Add(monsterList->SelectedItem->ToString());
            }
        }
        System::Void removeMonsterFromList(Object^ sender, EventArgs^ e)
        {
            if (this->attackMonsterList->SelectedItem != nullptr)
            {
                this->attackMonsterList->Items->Remove(attackMonsterList->SelectedItem);
            }
        }
        //###################### StartWalker ######################
        System::Void startWaypointWorker(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            uint32_t waypointPos;
            uint32_t myPos = *(uint32_t*)myPosPointer;

            uint32_t items = *(uint32_t*)groundItems;

            uint32_t attackStatus = *(uint32_t*)attackStatusPointer;

            int i = 0;
            int tmp = (int)this->waypointList->Items->Count;
            this->waypointList->SetSelected(i, TRUE);
            while (!this->waypointWorker->CancellationPending)
            {
                while (1)
                {
                    myPos = *(uint32_t*)myPosPointer;
                    waypointPos = (uint32_t)this->waypointList->Items[i];
                    if (myPos == waypointPos)
                    {
                        this->walkingOn = false;
                        Sleep(4000);
                        attackStatus = *(uint32_t*)attackStatusPointer;
                        if (attackStatus)
                            continue;
                        if (i < tmp - 1)
                        {
                            ++i;
                            this->waypointList->SetSelected(i, TRUE);
                            waypointPos = (uint32_t)this->waypointList->Items[i];
                            this->walkingOn = true;
                            MoveTo(waypointPos);
                            Sleep(1000);
                        }
                        else
                        {
                            i = 0;
                            break;
                        }
                    }
                    else
                    {
                        if (!this->walkingOn)
                        {
                            MoveTo(waypointPos);
                            this->walkingOn = true;
                        }
                        Sleep(1000);
                    }
                    Sleep(100);
                }
            }
        }

        //###################### StartAttackWalker ######################
        System::Void startAttackWorker(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            int monsterPos = 0;
            int monsterPosY = 0;
            int myPosX = 0;
            int myPosY = 0;

            uint32_t myPos = 0;

            uint32_t monsterCount = *(uint32_t*)monsterCountPointer;

            EntityList** monsters = (EntityList**)malloc(monsterCount * sizeof(EntityList*));

            for (int i = 0; i < monsterCount; ++i)
            {
                *(monsters + i)  = (EntityList*)*((uint32_t*)(entityListPointer) + i);
                (*(monsters + i))->monsterNamePointer = (uint32_t*)((uint32_t)*(monsters + i) + 0x1BC);
                (*(monsters + i))->monsterNamePointer = (uint32_t*)((*(uint32_t*)((*(monsters + i))->monsterNamePointer)) + 0x04);
            }
            while (!this->attackWorker->CancellationPending)
            {
                for (int i = 0; i < monsterCount; ++i)
                {

                }
            }
        }
    };
}
