#pragma once
#include <msclr/marshal_cppstd.h> // Library to convert String^ to string
using namespace std;
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
        main_form(void(lpMoveTo)(uint32_t), void(lpAttackMonster)(uint32_t, short))
        {
            InitializeComponent();
            this->Width = 500;
            this->Height = 400;
            this->Text = "KrawczorBot";
            this->attackMonster = lpAttackMonster;
            this->moveTo = lpMoveTo;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
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
        System::ComponentModel::Container^ components; //Required designer variable.

        System::Windows::Forms::TabControl^ tabView;

        System::Windows::Forms::TabPage^ mainTab;
        System::Windows::Forms::TabPage^ waypointTab;
        System::Windows::Forms::TabPage^ targetTab;

        System::ComponentModel::BackgroundWorker^ mainBot_Worker;

        System::Windows::Forms::ListBox^ waypoints_ListBox;
        System::Windows::Forms::ListBox^ monsters_ListBox;
        System::Windows::Forms::ListBox^ skills_Listbox;

        System::Windows::Forms::Button^ startBot_Button;
        System::Windows::Forms::Button^ addWaypoint_Button;
        System::Windows::Forms::Button^ refreshMonsters_Button;
        System::Windows::Forms::Button^ addMonster_Button;
        System::Windows::Forms::Button^ addSkill_Button;
        System::Windows::Forms::Button^ refreshSkills_Button;

        System::Windows::Forms::ComboBox^ monsters_ComboBox;
        System::Windows::Forms::ComboBox^ skills_ComboBox;

        bool walkingOn = false;
        //################ GRAPHIC USER INTERFACE ##############
        void InitializeComponent(void)
        {
            //################ TabPages  ####################
            //################  MainTab  ####################
            mainTab = gcnew System::Windows::Forms::TabPage();
            mainTab->Text = "Main";
            //################ TargetTab ####################
            targetTab = gcnew System::Windows::Forms::TabPage();
            targetTab->Text = "Skill&Target";

            //################ WaypointTab ####################
            waypointTab = gcnew System::Windows::Forms::TabPage();
            waypointTab->Text = "Cavebot";

            //################   TabView   ####################
            tabView = gcnew System::Windows::Forms::TabControl();
            tabView->Dock = System::Windows::Forms::DockStyle::Fill;
            tabView->TabPages->Add(mainTab);
            tabView->TabPages->Add(waypointTab);
            tabView->TabPages->Add(targetTab);
            Controls->Add(tabView);

            //################ Background Workers ####################
            mainBot_Worker = gcnew System::ComponentModel::BackgroundWorker();
            mainBot_Worker->WorkerSupportsCancellation = true;
            mainBot_Worker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &main_form::startBot_thread);

            //######################   Main Tab    ##########################
            //######################    Buttons    ##########################
            startBot_Button = gcnew System::Windows::Forms::Button();
            startBot_Button->Location = Point(0, 250);
            startBot_Button->Text = "Start Bot";
            startBot_Button->BackColor = Color::Red;
            startBot_Button->Click += gcnew EventHandler(this, &main_form::startBot);

            //##################### Add to Main Tab ######################
            mainTab->Controls->Add(startBot_Button);


            //######################   Cabebot Tab     ##########################         
            //######################    Buttons    ########################
            addWaypoint_Button = gcnew System::Windows::Forms::Button();
            addWaypoint_Button->Location = Point(0, 200);
            addWaypoint_Button->Width = 150;
            addWaypoint_Button->Text = "Add Waypoint";
            addWaypoint_Button->Click += gcnew EventHandler(this, &main_form::addWaypoint);

            //######################     ListBoxes     ######################
            waypoints_ListBox = gcnew System::Windows::Forms::ListBox();
            waypoints_ListBox->Size = System::Drawing::Size(150, 200);
            waypoints_ListBox->Location = Point(0, 0);

            //##################### Add to Cavebot Tab ######################
            waypointTab->Controls->Add(addWaypoint_Button);
            waypointTab->Controls->Add(waypoints_ListBox);


            //######################   Target&Skill Tab ######################
            //######################     List Boxes     ######################

            monsters_ListBox = gcnew System::Windows::Forms::ListBox();
            monsters_ListBox->Size = System::Drawing::Size(150, 200);
            monsters_ListBox->DoubleClick += gcnew EventHandler(this, &main_form::removeMonsterFromList);

            skills_Listbox = gcnew System::Windows::Forms::ListBox();
            skills_Listbox->Size = System::Drawing::Size(150, 200);
            skills_Listbox->Location = Point(180, 0);
            skills_Listbox->DoubleClick += gcnew EventHandler(this, &main_form::removeSkillFromList);
            //###################### Combo Boxes ######################
            monsters_ComboBox = gcnew System::Windows::Forms::ComboBox();
            monsters_ComboBox->Location = Point(0, 200);

            skills_ComboBox = gcnew System::Windows::Forms::ComboBox();
            skills_ComboBox->Location = Point(180, 200);

            //######################    Buttons    ########################
            addMonster_Button = gcnew System::Windows::Forms::Button();
            addMonster_Button->Location = System::Drawing::Point(100, 240);
            addMonster_Button->Text = "Add Monster";
            addMonster_Button->Click += gcnew EventHandler(this, &main_form::addMonster);

            addSkill_Button = gcnew System::Windows::Forms::Button();
            addSkill_Button->Location = System::Drawing::Point(280, 240);
            addSkill_Button->Text = "Add Skill";
            addSkill_Button->Click += gcnew EventHandler(this, &main_form::addSkill);

            refreshMonsters_Button = gcnew System::Windows::Forms::Button();
            refreshMonsters_Button->Location = Point(0, 240);
            refreshMonsters_Button->Text = "Refresh";
            refreshMonsters_Button->Click += gcnew EventHandler(this, &main_form::refreshMonsters);

            refreshSkills_Button = gcnew System::Windows::Forms::Button();
            refreshSkills_Button->Location = Point(180, 240);
            refreshSkills_Button->Text = "Refresh";
            refreshSkills_Button->Click += gcnew EventHandler(this, &main_form::refreshSkills);
            targetTab->Controls->Add(refreshSkills_Button);

            //##################### Add to Target&Skill Tab ######################
            targetTab->Controls->Add(monsters_ComboBox);
            targetTab->Controls->Add(skills_ComboBox);
            targetTab->Controls->Add(monsters_ListBox);
            targetTab->Controls->Add(skills_Listbox);
            targetTab->Controls->Add(addMonster_Button);
            targetTab->Controls->Add(addSkill_Button);
            targetTab->Controls->Add(refreshMonsters_Button);
        }
#pragma endregion
        //###################### Functions       ######################
        //###################### Close Main_Form ######################
        System::Void main_form_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
        {
            mainBot_Worker->CancelAsync();
        }
        //###################### Button Functions ######################
        //###################### StartBot ######################
        System::Void startBot(Object^ sender, EventArgs^ e)
        {
            if (startBot_Button->BackColor == Color::Red)
            {
                startBot_Button->BackColor = Color::Green;
                startBot_Button->Text = "Stop Bot";
                mainBot_Worker->RunWorkerAsync();
            }
            else
            {
                startBot_Button->BackColor = Color::Red;
                startBot_Button->Text = "Start Bot";
                mainBot_Worker->CancelAsync();
            }
        }
        //###################### Add Waypoint Button ######################
        System::Void addWaypoint(System::Object^ sender, System::EventArgs^ e)
        {
            DWORD myPosPointer = ReadPointer(0x004C4E4C, { 0x560, 0x1C, 0x10, 0xB60, 0x0C });
            if (*(uint32_t*)myPosPointer != 0)
                waypoints_ListBox->Items->Add(*(uint32_t*)myPosPointer);
        }
        //###################### Add Target Button ######################
        System::Void addMonster(System::Object^ sender, System::EventArgs^ e)
        {
            if (monsters_ComboBox->SelectedItem != nullptr)
                monsters_ListBox->Items->Add(monsters_ComboBox->SelectedItem->ToString());
        }
        //###################### Add Spell Button ######################
        System::Void addSkill(System::Object^ sender, System::EventArgs^ e)
        {
            if (skills_ComboBox->SelectedItem != nullptr)
                skills_Listbox->Items->Add(skills_ComboBox->SelectedIndex + " " + skills_ComboBox->SelectedItem->ToString());
        }
        //###################### Remove Monster ######################
        System::Void removeMonsterFromList(Object^ sender, EventArgs^ e)
        {
            if (monsters_ListBox->SelectedItem != nullptr)
            {
                monsters_ListBox->Items->Remove(monsters_ListBox->SelectedItem);
            }
        }
        //###################### Remove Skill ######################
        System::Void removeSkillFromList(Object^ sender, EventArgs^ e)
        {
            if (skills_Listbox->SelectedItem != nullptr)
            {
                skills_Listbox->Items->Remove(skills_Listbox->SelectedItem);
            }
        }
        //###################### Refresh Skill List Button ######################
        System::Void refreshSkills(System::Object^ sender, System::EventArgs^ e)
        {
            DWORD skillListPointer = ReadPointer(0x004C3E5C, { 0x1BC, 0xF0, 0x0, 0x170, 0x7F4 });
            skills_ComboBox->Items->Clear();
            uint32_t skill = (uint32_t)skillListPointer - 0x2A0 * 3;
            for (int i = 0; i < 11; ++i)
            {
                skills_ComboBox->Items->Add(gcnew System::String((const char*)*(uint32_t*)(skill + 0x2A0 * i)));
            }
            skills_ComboBox->SelectedIndex = 0;
        }
        //###################### Refresh Monsters List Button ######################
        System::Void refreshMonsters(System::Object^ sender, System::EventArgs^ e)
        {
            DWORD entityListPointer = ReadPointer(0x003266D8, { 0xE8C, 0x4, 0x6A4, 0x0 });
            DWORD monsterCountPointer = ReadPointer(0x003282C0, { 0x08, 0x04, 0x7C, 0x04, 0x528 });
            monsters_ComboBox->Items->Clear();
            bool found = 0;
            int monsterCount = *(uint32_t*)monsterCountPointer;
            EntityList** monsters = (EntityList**)malloc(monsterCount * sizeof(EntityList*));
            for (int i = 0; i < monsterCount; ++i)
            {
                *(monsters + i) = (EntityList*)*((uint32_t*)(entityListPointer)+i);
                (*(monsters + i))->monsterNamePointer = (uint32_t*)((uint32_t) * (monsters + i) + 0x1BC);
                (*(monsters + i))->monsterNamePointer = (uint32_t*)((*(uint32_t*)((*(monsters + i))->monsterNamePointer)) + 0x04);
                for (int tmp = 0; tmp < (int)monsters_ComboBox->Items->Count; ++tmp)
                {
                    if (gcnew System::String((const char*)*(uint32_t*)((*(monsters + i))->monsterNamePointer)) == (monsters_ComboBox->Items[tmp]->ToString()))
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    monsters_ComboBox->Items->Add(gcnew System::String((const char*)*(uint32_t*)((*(monsters + i))->monsterNamePointer)));
                }
                found = 0;
            }
            monsters_ComboBox->SelectedIndex = 0;
            free(monsters);
        }
        //###################### StartWalker ######################
        System::Void startBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            string monsterName;
            int myPos;
            int monsterInRange;
            int myX;
            int myY;
            int monsterX;
            int monsterY;
            int distanceX;
            int distanceY;
            int skill;
            int value;
            int waypoint = 0;
            double timer = 0;
            DWORD monsterCountPointer;
            DWORD monsterID;
            DWORD monsterPos;
            DWORD monsterStatus;
            DWORD entityListPointer;
            DWORD myPosPointer = ReadPointer(0x004C4E4C, { 0x560, 0x1C, 0x10, 0xB60, 0x0C });
            waypoints_ListBox->SetSelected(0, TRUE);
            MoveTo((uint32_t)waypoints_ListBox->Items[0]);
            while (!mainBot_Worker->CancellationPending)
            {
                if ((uint32_t)*(uint32_t*)myPosPointer == (uint32_t)waypoints_ListBox->Items[waypoint])
                {                     
                    monsterCountPointer = ReadPointer(0x003282C0, { 0x08, 0x04, 0x7C, 0x04, 0x528 });
                    for (int monster = 0; monster < (int)*(uint32_t*)monsterCountPointer; ++monster)
                    {
                        Sleep(10);
                        entityListPointer = ReadPointer(0x003266D8, { 0xE8C, 0x4, 0x6A4, 0x0 });
                        monsterID = *((uint32_t*)(entityListPointer) + monster);
                        monsterName = (string)(const char*)*(uint32_t*)((*(uint32_t*)(monsterID + 0x1BC)) + 0x04);
                        for (int monsterAttack = 0; monsterAttack < (int)monsters_ListBox->Items->Count; ++monsterAttack)
                        {
                            Sleep(10);
                            monsterInRange = (monsterID + 0x8C);
                            monsterInRange = *(uint32_t*)monsterInRange;
                            if (monsterInRange != 0)
                            {
                                if (monsterName == msclr::interop::marshal_as<std::string>(monsters_ListBox->Items[monsterAttack]->ToString()))
                                {
                                    monsterPos = monsterID + 0x0C;
                                    myPos = *(uint32_t*)myPosPointer;
                                    myX = myPos & 0xFF;
                                    myY = (myPos >> 16) & 0xFF;
                                    monsterPos = *(uint32_t*)monsterPos;
                                    monsterX = monsterPos & 0xFF;
                                    monsterY = (monsterPos >> 16) & 0xFF;
                                    distanceX = abs(myX - monsterX);
                                    distanceY = abs(myY - monsterY);
                                    monsterStatus = monsterID + 0x08;
                                    DWORD skillCooldown = ReadPointer(0x004C46DC, { 0x3A8, 0xFB4 });
                                    while (distanceX < 9 && distanceY < 9 && *(uint32_t*)monsterStatus != 0xFFFFFFFF)
                                    {
                                        for (int tmp = 0; tmp < (int)skills_Listbox->Items->Count; ++tmp)
                                        {
                                            skill = System::Convert::ToInt32(skills_Listbox->Items[tmp]->ToString()->Split(' ')[0]);
                                            value = *(int*)(skillCooldown + (0x120 * skill));
                                            if (value == 1)
                                            {
                                                AttackMonster(monsterID, skill);
                                                break;
                                            }
                                        }
                                        AttackMonster(monsterID, 0);
                                    }
                                }
                            }
                        }
                    }
                    if (waypoint < (int)waypoints_ListBox->Items->Count - 1)
                    {
                        ++waypoint;
                    }
                    else
                    {
                        waypoint = 0;
                    }
                    Sleep(900);
                    waypoints_ListBox->SetSelected(waypoint, TRUE);
                    MoveTo((uint32_t)waypoints_ListBox->Items[waypoint]);
                    timer = 0;
                }
                timer += 0.05;
                if (timer > 5.0)
                {
                    waypoints_ListBox->SetSelected(waypoint, TRUE);
                    MoveTo((uint32_t)waypoints_ListBox->Items[waypoint]);
                    timer = 0;
                }
                Sleep(50);
            }
        }
    };
}
