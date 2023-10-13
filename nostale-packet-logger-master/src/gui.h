#pragma once
#include <msclr/marshal_cppstd.h> // Library to convert String^ to string
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
        DWORD myPosPointer = ReadPointer(0x00729E34, { 0x0C });
        DWORD entityListPointer = ReadPointer(0x008B4F88, { 0x93C, 0x7AC, 0x204, 0x00 });
        DWORD attackStatusPointer = ReadPointer(0x008BD9E8, { 0x784, 0x178, 0x5BC, 0xE64, 0xD88 });
        DWORD groundItems = ReadPointer(0x00721634, { 0x26C, 0xE84, 0x04, 0x724, 0x00 });
        DWORD skillListPointer = ReadPointer(0x008BDAB4, { 0x90, 0x08, 0x5F0, 0x50});

        System::Windows::Forms::TabControl^ tabView;

        System::ComponentModel::BackgroundWorker^ attackWorker;
        System::ComponentModel::BackgroundWorker^ waypointWorker;

        System::ComponentModel::Container^ components; //Required designer variable.

        System::Windows::Forms::ListBox^ attackMonsterList;
        System::Windows::Forms::ListBox^ waypointList;
        System::Windows::Forms::ListBox^ useSkillList;

        System::Windows::Forms::Button^ refreshMonsterList;
        System::Windows::Forms::Button^ startTargeting;
        System::Windows::Forms::Button^ startWalking;
        System::Windows::Forms::Button^ addWaypoint;
        System::Windows::Forms::Button^ addMonster;
        System::Windows::Forms::Button^ addSkill;
        System::Windows::Forms::Button^ refreshSkillList;

        System::Windows::Forms::Label^ labelMonsterList;
        System::Windows::Forms::Label^ labelMonsterAttack;
        System::Windows::Forms::Label^ labelSkillList;
        System::Windows::Forms::Label^ labelSkillUse;

        System::Windows::Forms::TabPage^ mainTab;
        System::Windows::Forms::TabPage^ waypointTab;
        System::Windows::Forms::TabPage^ targetTab;

        System::Windows::Forms::ComboBox^ monsterList;
        System::Windows::Forms::ComboBox^ skillList;

        bool walkingOn = false;


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
            labelMonsterList->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(238)));
            labelMonsterList->Size = System::Drawing::Size(67, 17);
            labelMonsterList->Location = Point(179, 29);
            labelMonsterList->Text = "Monster :";
            targetTab->Controls->Add(labelMonsterList);

            //###################### LabelMonsterAttack #####################
            labelMonsterAttack = gcnew System::Windows::Forms::Label();
            labelMonsterAttack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(238)));
            labelMonsterAttack->Size = System::Drawing::Size(61, 17);
            labelMonsterAttack->Location = Point(59, 12);
            labelMonsterAttack->Text = "Whitelist";
            targetTab->Controls->Add(labelMonsterAttack);

            //###################### LabelSkillList #####################
            labelSkillList = gcnew System::Windows::Forms::Label();
            labelSkillList->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(238)));
            labelSkillList->Size = System::Drawing::Size(59, 17);
            labelSkillList->Location = Point(59, 237);
            labelSkillList->Text = "Skill List";
            targetTab->Controls->Add(labelSkillList);

            //###################### Label Skill Use #####################
            labelSkillUse = gcnew System::Windows::Forms::Label();
            labelSkillUse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(238)));
            labelSkillUse->Size = System::Drawing::Size(41, 17);
            labelSkillUse->Location = Point(205, 241);
            labelSkillUse->Text = "Skill :";
            targetTab->Controls->Add(labelSkillUse);

            //###################### ComboBoxes ######################
            //###################### ComboBox MonsterList ######################
            monsterList = gcnew System::Windows::Forms::ComboBox();
            monsterList->Size = System::Drawing::Size(140, 21);
            monsterList->Location = Point(252, 27);
            targetTab->Controls->Add(monsterList);

            //###################### ComboBox SkillList ######################
            skillList = gcnew System::Windows::Forms::ComboBox();
            skillList->Size = System::Drawing::Size(140, 21);
            skillList->Location = Point(252, 237);
            targetTab->Controls->Add(skillList);

            //######################     ListBoxes     ######################
            //###################### AttackMonsterList ######################
            attackMonsterList = gcnew System::Windows::Forms::ListBox();
            attackMonsterList->Size = System::Drawing::Size(160, 134);
            attackMonsterList->Location = Point(12, 39);
            attackMonsterList->DoubleClick += gcnew EventHandler(this, &main_form::removeMonsterFromList);
            targetTab->Controls->Add(this->attackMonsterList);

            //###################### WaypointList ######################
            waypointList = gcnew System::Windows::Forms::ListBox();
            waypointList->Size = System::Drawing::Size(150, 300);
            waypointList->Location = Point(500, 300);
            waypointTab->Controls->Add(waypointList);

            //###################### SkillsList ######################
            useSkillList = gcnew System::Windows::Forms::ListBox();
            useSkillList->Size = System::Drawing::Size(160, 134);
            useSkillList->Location = Point(12, 265);
            useSkillList->DoubleClick += gcnew EventHandler(this, &main_form::removeSkillFromList);
            targetTab->Controls->Add(useSkillList);


            //######################    Buttons    ########################
            //#################### AddWaypointButton ######################
            addWaypoint = gcnew System::Windows::Forms::Button();
            addWaypoint->Location = Point(500, 600);
            addWaypoint->Width = 100;
            addWaypoint->Height = 30;
            addWaypoint->Text = "AddWaypoint";
            addWaypoint->Click += gcnew EventHandler(this, &main_form::addWaypoints);
            waypointTab->Controls->Add(addWaypoint);

            //#################### AddMonstertButton ######################
            addMonster = gcnew System::Windows::Forms::Button();
            addMonster->Location = System::Drawing::Point(252, 55);
            addMonster->Size = System::Drawing::Size(140, 23);
            addMonster->Text = "Add Monster to Whitelist";
            addMonster->Click += gcnew EventHandler(this, &main_form::addTarget);
            targetTab->Controls->Add(addMonster);

            //#################### AddSkillButton ######################
            addSkill = gcnew System::Windows::Forms::Button();
            addSkill->Location = System::Drawing::Point(252, 265);
            addSkill->Size = System::Drawing::Size(140, 23);
            addSkill->Text = "Add Skill To Skill List";
            addSkill->Click += gcnew EventHandler(this, &main_form::addSpell);
            targetTab->Controls->Add(addSkill);

            //###################### RefreshTargetListButton ########################
            refreshMonsterList = gcnew System::Windows::Forms::Button();
            refreshMonsterList->Size = System::Drawing::Size(75, 25);
            refreshMonsterList->Location = Point(400, 25);
            refreshMonsterList->Text = "Refresh";
            refreshMonsterList->Click += gcnew EventHandler(this, &main_form::refreshTargetList);
            targetTab->Controls->Add(refreshMonsterList);

            //###################### RefreshSkillList ########################
            refreshSkillList = gcnew System::Windows::Forms::Button();
            refreshSkillList->Size = System::Drawing::Size(75, 21);
            refreshSkillList->Location = Point(397, 237);
            refreshSkillList->Text = "Refresh";
            refreshSkillList->Click += gcnew EventHandler(this, &main_form::refreshSkillsList);
            targetTab->Controls->Add(refreshSkillList);

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
        //###################### Refresh Skill List Button ######################
        System::Void refreshSkillsList(System::Object^ sender, System::EventArgs^ e)
        {
            this->skillList->Items->Clear();
            uint32_t skill = *(uint32_t*)skillListPointer;
            skill -= 0xA6C;
            for (int i = 0; i < 11; ++i)
            {
                this->skillList->Items->Add(gcnew System::String((const char*)*(uint32_t*)(skill + 0x2A0 * i)));
            }
            this->skillList->SelectedIndex = 0;
        }
        //###################### Refresh Monster List Button ######################
        System::Void refreshTargetList(System::Object^ sender, System::EventArgs^ e)
        {
            this->monsterList->Items->Clear();
            bool found = 0;
            uint32_t monsterCount = *(uint32_t*)monsterCountPointer;
            EntityList** monsters = (EntityList**)malloc(monsterCount * sizeof(EntityList*));
            for (int i = 0; i < monsterCount; ++i)
            {
                *(monsters + i) = (EntityList*)*((uint32_t*)(entityListPointer)+i);
                (*(monsters + i))->monsterNamePointer = (uint32_t*)((uint32_t) * (monsters + i) + 0x1BC);
                (*(monsters + i))->monsterNamePointer = (uint32_t*)((*(uint32_t*)((*(monsters + i))->monsterNamePointer)) + 0x04);
                for (int tmp = 0; tmp < (int)this->monsterList->Items->Count; ++tmp)
                {
                    if (gcnew System::String((const char*)*(uint32_t*)((*(monsters + i))->monsterNamePointer)) == (this->monsterList->Items[tmp]->ToString()))
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    this->monsterList->Items->Add(gcnew System::String((const char*)*(uint32_t*)((*(monsters + i))->monsterNamePointer)));
                }
                found = 0;
            }
            this->monsterList->SelectedIndex = 0;
            free(monsters);
        }
        //###################### Add Waypoint Button ######################
        System::Void addWaypoints(System::Object^ sender, System::EventArgs^ e)
        {
            if (*(uint32_t*)myPosPointer != 0)
                waypointList->Items->Add(*(uint32_t*)myPosPointer);
        }
        //###################### Add Target Button ######################
        System::Void addTarget(System::Object^ sender, System::EventArgs^ e)
        {
            attackMonsterList->Items->Add(this->monsterList->SelectedItem->ToString());
        }
        //###################### Add Spell Button ######################
        System::Void addSpell(System::Object^ sender, System::EventArgs^ e)
        {
            useSkillList->Items->Add(this->skillList->SelectedItem->ToString());
        }
        //###################### Remove Monster ######################
        System::Void removeMonsterFromList(Object^ sender, EventArgs^ e)
        {
            if (this->attackMonsterList->SelectedItem != nullptr)
            {
                this->attackMonsterList->Items->Remove(attackMonsterList->SelectedItem);
            }
        }
        //###################### Remove Skill ######################
        System::Void removeSkillFromList(Object^ sender, EventArgs^ e)
        {
            if (this->useSkillList->SelectedItem != nullptr)
            {
                this->useSkillList->Items->Remove(useSkillList->SelectedItem);
            }
        }
        //###################### StartWalker ######################
        System::Void startWaypointWorker(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            unsigned int waypointPos = (unsigned int)this->waypointList->Items[0];
            unsigned int myPos = *(uint32_t*)myPosPointer;
            unsigned int items = *(uint32_t*)groundItems;
            unsigned int tmp = (int)this->waypointList->Items->Count;
            unsigned int i = 0;
            float timer = 0;
            this->waypointList->SetSelected(i, TRUE);
            MoveTo(waypointPos);
            while (!this->waypointWorker->CancellationPending)
            {
                myPos = *(uint32_t*)myPosPointer;
                if (myPos == waypointPos)
                {
                    this->walkingOn = false;
                    while (!this->walkingOn)
                        Sleep(100);
                    if (i < tmp - 1)
                    {
                        ++i;
                        this->waypointList->SetSelected(i, TRUE);
                        waypointPos = (unsigned int)this->waypointList->Items[i];
                        MoveTo(waypointPos);
                        timer = 0;
                    }
                    else
                    {
                        i = 0;
                        this->waypointList->SetSelected(i, TRUE);
                        waypointPos = (unsigned int)this->waypointList->Items[i];
                        MoveTo(waypointPos);
                        timer = 0;
                    }
                }
                Sleep(100);
                timer += 0.1;
                if (timer > 10)
                {
                    waypointPos = (unsigned int)this->waypointList->Items[i];
                    MoveTo(waypointPos);
                    timer = 0;
                }
            }
        }

        //###################### StartAttackWalker ######################
        System::Void startAttackWorker(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            unsigned int monsterPos = 0;
            int monsterPosX = 0;
            int monsterPosY = 0;
            unsigned int myPos = 0;
            int myPosX = 0;
            int myPosY = 0;
            unsigned register int distanceX = 0;
            unsigned register int distanceY = 0;
            unsigned register int monsterStatus = 0;
            unsigned int monsterCount = *(uint32_t*)monsterCountPointer;
            
            vector<int> skillPriority;
            for (int i = 0; i < (int)this->useSkillList->Items->Count; ++i)
            {
                for (int j = 0; j < (int)this->skillList->Items->Count; ++j)
                {
                    if (this->useSkillList->Items[i]->ToString() == this->skillList->Items[j]->ToString())
                    {
                        skillPriority.push_back(j);
                        break;
                    }
                }
            }
            EntityList** monsters = (EntityList**)malloc(monsterCount * sizeof(EntityList*));
            vector<string> monsterName;
            unsigned int spells[11];
            uint32_t spell = skillListPointer;
            spell -= 0x108;
            spells[1] = spell;
            spells[0] = spell + 0x48;
            for (int i = 2; i < 11; ++i)
            {
                spells[i] = spell + 0x48 *i;
            }
            for(int i = 0; i < monsterCount; ++i)
            {
                *(monsters + i) = (EntityList*)*((uint32_t*)(entityListPointer)+i);
                (*(monsters + i))->monsterNamePointer = (uint32_t*)((uint32_t) * (monsters + i) + 0x1BC);
                (*(monsters + i))->monsterNamePointer = (uint32_t*)((*(uint32_t*)((*(monsters + i))->monsterNamePointer)) + 0x04);
                monsterName.push_back((string)(const char*)*(uint32_t*)(*(monsters + i))->monsterNamePointer);
            }
            while (!this->attackWorker->CancellationPending)
            {
                if (!this->walkingOn)
                {
                    for (int i = 0; i < monsterCount; ++i)
                    {
                        for (int j = 0; j < (int)this->attackMonsterList->Items->Count; ++j)
                        {
                            if (monsterName.at(i) == msclr::interop::marshal_as<std::string>(attackMonsterList->Items[j]->ToString()))
                            {
                                myPos = *(uint32_t*)myPosPointer;
                                myPosX = myPos & 0xFF;
                                myPosY = (myPos >> 16) & 0xFF;
                                monsterPos = (*(monsters + i))->monsterPos;
                                monsterPosX = monsterPos & 0xFF;
                                monsterPosY = (monsterPos >> 16) & 0xFF;
                                distanceX = abs(myPosX - monsterPosX);
                                distanceY = abs(myPosY - monsterPosY);
                                monsterStatus = (*(monsters + i))->monsterID;
                                while (distanceX < 9 && distanceY < 9 && monsterStatus != 0xFFFFFFFF)
                                {
                                    if (this->attackWorker->CancellationPending)
                                    {
                                        free(monsters);
                                        return;
                                    }
                                    monsterStatus = (*(monsters + i))->monsterID;
                                    for (int k = 0; k < this->useSkillList->Items->Count; ++k)
                                    {
                                        if (*(uint32_t*)spells[skillPriority.at(k)] < 15)
                                        {
                                            AttackMonster((uint32_t)(*(monsters + i)), skillPriority.at(k));
                                            break;
                                        }
                                    }
                                    Sleep(1000);
                                }
                            }
                            else
                            {
                                continue;
                                Sleep(100);
                            }
                        }
                    }
                    //this->walkingOn = true;
                }
            }
            free(monsters);
        }
    };
}
