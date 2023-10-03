#pragma once
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
        main_form(void(*lpMoveTo)(uint32_t), void(lpAttackMonster(uint32_t, short)))
        {
            InitializeComponent();
            this->Width = 700;
            this->Height = 700;
            this->Text = "KrawczorBot";
            this->attackMonster = lpAttackMonster;
            this->moveTo = lpMoveTo;
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

        DWORD monsterCountPointer = ReadPointer(0x7212D8, { 0x248 });
        DWORD myPosPointer = ReadPointer(0x008BDD80, { 0xAC, 0x00, 0x08, 0x68, 0x840, 0xFC4 });
        DWORD entityListPointer = ReadPointer(0x008B4F88, { 0x93C, 0x7AC, 0x204, 0x00 });
        DWORD attackStatusPointer = ReadPointer(0x008BD9E8, { 0x784, 0x178, 0x5BC, 0xE64, 0xD88 });

        System::Windows::Forms::TabControl^ tabView;

        System::ComponentModel::BackgroundWorker^ attackWorker;
        System::ComponentModel::BackgroundWorker^ waypointWorker;

        System::ComponentModel::Container^ components; //Required designer variable.

        System::Windows::Forms::ListBox^ monsterList;
        System::Windows::Forms::ListBox^ attackMonsterList;
        System::Windows::Forms::ListBox^ waypointList;

        System::Windows::Forms::Button^ refreshMonsterList;
        System::Windows::Forms::Button^ startBot;
        System::Windows::Forms::Button^ addWaypoint;

        System::Windows::Forms::Label^ labelMonsterList;
        System::Windows::Forms::Label^ labelMonsterAttack;

        System::Windows::Forms::TabPage^ mainTab;
        System::Windows::Forms::TabPage^ waypointTab;
        System::Windows::Forms::TabPage^ targetTab;


        void InitializeComponent(void)
        {
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

            //###################### StartButton ########################
            startBot = gcnew System::Windows::Forms::Button();
            startBot->Location = Point(0, 500);
            startBot->Width = 75;
            startBot->Height = 25;
            startBot->Text = "Start Bot";
            startBot->BackColor = Color::Green;
            startBot->Click += gcnew EventHandler(this, &main_form::startEasyBot);
            mainTab->Controls->Add(startBot);

            //###################### MainTab ########################
            tabView = gcnew System::Windows::Forms::TabControl();
            tabView->Dock = System::Windows::Forms::DockStyle::Fill;
            tabView->TabPages->Add(mainTab);
            tabView->TabPages->Add(waypointTab);
            tabView->TabPages->Add(targetTab);
            Controls->Add(tabView);
            
        }
        System::Void main_form_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) 
        {
            this->attackWorker->CancelAsync();
            this->waypointWorker->CancelAsync();
        }
        //###################### Refresh Monster List Button ######################
        System::Void refreshList(System::Object^ sender, System::EventArgs^ e)
        {

            uint32_t x;
            bool found = 0;

            EntityList* monsters[18];
            monsters[0] = (EntityList*)entityListPointer;
            for (int i = 1; i < 18; ++i)
            {
               monsters[i] = (EntityList*)(*monsters + i);
            }
            for (int i = 0; i < 18; ++i)
            {
                x = monsters[i]->monsterID;
                x = *(uint32_t*)(x + 0x1BC);
                x = *(uint32_t*)(x + 0x04);

                for (int tmp = 0; tmp < (int)this->monsterList->Items->Count; ++tmp)
                {
                    if (gcnew System::String(((const char*)x)) == (this->monsterList->Items[tmp]->ToString()))
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    this->monsterList->Items->Add(gcnew System::String(((const char*)x)));
                }
                found = 0;
            }
        }
        System::Void addWaypoints(System::Object^ sender, System::EventArgs^ e)
        {
            if (*(uint32_t*)myPosPointer != 0)
                waypointList->Items->Add(*(uint32_t*)myPosPointer);
        }
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
        System::Void startEasyBot(Object^ sender, EventArgs^ e)
        {
            startBot->BackColor = Color::Red;
            startBot->Text = "Stop Bot";
            this->waypointWorker->RunWorkerAsync();
            this->attackWorker->RunWorkerAsync();
        }    
        System::Void startWaypointWorker(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            uint32_t myPos = *(uint32_t*)myPosPointer;
            uint32_t waypointPos;
            uint32_t attackStatus = *(uint32_t*)attackStatusPointer;
            while (!this->waypointWorker->CancellationPending)
            {
                for (int i = 0; i < (int)this->waypointList->Items->Count; ++i)
                {
                    this->waypointList->SetSelected(i, TRUE);
                    waypointPos = (uint32_t)this->waypointList->Items[i];
                    while (myPos != waypointPos)
                    {
                        attackStatus = *(uint32_t*)attackStatusPointer;
                        while (attackStatus != 0)
                        {
                            System::Threading::Thread::Sleep(3000);
                            attackStatus = *(uint32_t*)attackStatusPointer;
                        }
                        MoveTo(waypointPos);
                        System::Threading::Thread::Sleep(2000);
                        myPos = *(uint32_t*)myPosPointer;
                    }
                }
                System::Threading::Thread::Sleep(100);
            }
        }
        System::Void startAttackWorker(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            uint32_t monsterPosX;
            uint32_t monsterPosY;
            uint32_t myPosX;
            uint32_t myPosY;
            uint32_t myPos;

            uint32_t monsterCount = *(uint32_t*)monsterCountPointer;
            EntityList** monsters = (EntityList**)malloc(monsterCount * sizeof(EntityList*));
            for (int i = 0; i < monsterCount; ++i)
            {
                *(monsters + i)  = (EntityList*)*((uint32_t*)(entityListPointer) + i);
                (*(monsters + i))->monsterNamePointer = (uint32_t)(((uint32_t*)(*(monsters + i))) + 0x6F);
                (*(monsters + i))->monsterNamePointer = (*(uint32_t*)((*(monsters + i))->monsterNamePointer)) + 0x04;
                (*(monsters + i))->monsterNamePointer = *(uint32_t*)((*(monsters + i))->monsterNamePointer);
            }
            while (!this->attackWorker->CancellationPending)
            {
                for (int i = 0; i < monsterCount; ++i)
                {
                    myPos = *(uint32_t*)myPosPointer;
                    myPosX = (myPos >> 16) & 0xFFFF;
                    myPosY = myPos & 0xFFFF;
                    
                    monsterPosX = ((*(monsters + i))->monsterPos >> 16) & 0xFFFF;
                    monsterPosY = (*(monsters + i))->monsterPos & 0xFFFF;

                    while (abs(int(myPosX - monsterPosX)) <= 9 && abs(int(myPosY - monsterPosY)) <= 9 && (*(monsters +i))->monsterID != 0xFFFFFFFF)
                    {
                        myPos = *(uint32_t*)myPosPointer;
                        if (myPos != (uint32_t)this->waypointList->SelectedItem)
                        {
                            myPos = *(uint32_t*)myPosPointer;
                            System::Threading::Thread::Sleep(100);
                        }
                        AttackMonster(*(uint32_t*)(monsters + i), 0);
                        System::Threading::Thread::Sleep(910);
                    }
                }
            }
        }
        
    };
}
