#pragma once
#include <msclr/marshal_cppstd.h> // Library to convert String^ to string
#include <fstream>
#include <tchar.h>
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
        main_form(void(lpMoveTo)(uint32_t), void(lpAttackMonster)(uint32_t, short), void(lpRest)(void), void(lpCollect)(uint32_t))
        {
            InitializeComponent();
            this->Width = 500;
            this->Height = 400;
            this->Text = "KrawczorBot";
            this->attackMonster = lpAttackMonster;
            this->moveTo = lpMoveTo;
            this->rest = lpRest;
            this->collect = lpCollect;
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
        void(*rest)(void);
        void(*collect)(uint32_t);

        System::ComponentModel::Container^ components;

        System::Windows::Forms::TabControl^ tabView;

        System::Windows::Forms::TabPage^ mainTab;

        System::ComponentModel::BackgroundWorker^ targetBot_Worker;
        System::ComponentModel::BackgroundWorker^ walkerBot_Worker;
        System::ComponentModel::BackgroundWorker^ healingBot_Worker;

        System::Windows::Forms::Button^ startBot_Button;
        // Target & Skill Tab
        System::Windows::Forms::TabPage^ targetTab;

        System::Windows::Forms::GroupBox^ targetWhite_GroupBox;
        System::Windows::Forms::GroupBox^ targetBlack_GroupBox;
        System::Windows::Forms::GroupBox^ targetSpell_GroupBox;
        System::Windows::Forms::GroupBox^ saveTarget_GroupBox;

        System::Windows::Forms::ListBox^ targetWhite_Listbox;
        System::Windows::Forms::ListBox^ targetBlack_Listbox;
        System::Windows::Forms::ListBox^ targetSpell_Listbox;
        System::Windows::Forms::ListBox^ saveTarget_Listbox;

        System::Windows::Forms::ComboBox^ targetSpell_ComboBox;

        System::Windows::Forms::Button^ refreshTarget_Button;
        System::Windows::Forms::Button^ addSpell_Button;
        System::Windows::Forms::Button^ loadTarget_Button;
        System::Windows::Forms::Button^ saveTarget_Button;

        System::Windows::Forms::TextBox^ saveTarget_TextBox;

        System::Windows::Forms::Label^ saveTarget_Label;
        System::Windows::Forms::Label^ attackWhite_Label;
        System::Windows::Forms::Label^ attackBlack_Label;

        System::Windows::Forms::CheckBox^ attackWhite_CheckBox;
        System::Windows::Forms::CheckBox^ attackBlack_CheckBox;


        // Walker Tab
        System::Windows::Forms::TabPage^ waypointTab;

        System::Windows::Forms::GroupBox^ walker_GroupBox;
        System::Windows::Forms::GroupBox^ addWaypoint_GroupBox;
        System::Windows::Forms::GroupBox^ currentStatus_GroupBox;
        System::Windows::Forms::GroupBox^ saveWalker_GroupBox;

        System::Windows::Forms::ListBox^ walker_Listbox;
        System::Windows::Forms::ListBox^ saveWalker_Listbox;

        System::Windows::Forms::ComboBox^ walkerActions_ComboBox;

        System::Windows::Forms::Button^ addWaypoint_Button;
        System::Windows::Forms::Button^ saveWalker_Button;
        System::Windows::Forms::Button^ loadWalker_Button;

        System::Windows::Forms::TextBox^ walkerAction_TextBox;
        System::Windows::Forms::TextBox^ saveWalker_TextBox;

        System::Windows::Forms::Label^ saveWalker_Label;
        System::Windows::Forms::Label^ currentPos_Label;
        System::Windows::Forms::Label^ walkerStatus_Label;
        System::Windows::Forms::Label^ targetStatus_Label;


        // Healing Tab
        System::Windows::Forms::TabPage^ healingTab;

        System::Windows::Forms::GroupBox^ healing_GroupBox;
        System::Windows::Forms::GroupBox^ addItem_GroupBox;
        System::Windows::Forms::GroupBox^ addSpell_GroupBox;
        System::Windows::Forms::GroupBox^ saveHealing_GroupBox;
        System::Windows::Forms::GroupBox^ myHealth_GroupBox;

        System::Windows::Forms::ListBox^ healing_Listbox;
        System::Windows::Forms::ListBox^ saveHealing_Listbox;
        System::Windows::Forms::ListBox^ healingAddresses_Listbox;

        System::Windows::Forms::ComboBox^ healingItems_ComboBox;
        System::Windows::Forms::ComboBox^ healingSpells_ComboBox;
        System::Windows::Forms::ComboBox^ healingOptionItems_ComboBox;
        System::Windows::Forms::ComboBox^ healingOptionSpells_ComboBox;

        System::Windows::Forms::Button^ refreshHealingItems_Button;
        System::Windows::Forms::Button^ refreshHealingSpells_Button;
        System::Windows::Forms::Button^ addHealingItem_Button;
        System::Windows::Forms::Button^ addHealingSpell_Button;
        System::Windows::Forms::Button^ saveHealing_Button;
        System::Windows::Forms::Button^ loadHealing_Button;

        System::Windows::Forms::TextBox^ healingItemFrom_TextBox;
        System::Windows::Forms::TextBox^ healingItemTo_TextBox;
        System::Windows::Forms::TextBox^ healingSpellFrom_TextBox;
        System::Windows::Forms::TextBox^ healingSpellTo_TextBox;
        System::Windows::Forms::TextBox^ saveHealing_TextBox;

        System::Windows::Forms::Label^ healingItems_Label;
        System::Windows::Forms::Label^ healingSpells_Label;
        System::Windows::Forms::Label^ saveHealing_Label;
        System::Windows::Forms::Label^ myHealth_Label;
        System::Windows::Forms::Label^ myMana_Label;

        System::Windows::Forms::ProgressBar^ myHealth_ProgressBar;
        System::Windows::Forms::ProgressBar^ myMana_ProgressBar;


        // Global Variables
        unsigned int waypoint = 0;
        bool atak = 0;
        //################ GRAPHIC USER INTERFACE ##############
        void InitializeComponent(void)
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
            //######################   Target & Skill Tab     ##########################      
            //######################     GroupBoxes    ######################   
            targetWhite_GroupBox = gcnew System::Windows::Forms::GroupBox();
            targetWhite_GroupBox->Text = "White List";
            targetWhite_GroupBox->Size = System::Drawing::Size(223, 173);
            targetWhite_GroupBox->Location = Point(12, 12);

            targetBlack_GroupBox = gcnew System::Windows::Forms::GroupBox();
            targetBlack_GroupBox->Text = "Black List";
            targetBlack_GroupBox->Size = System::Drawing::Size(223, 173);
            targetBlack_GroupBox->Location = Point(247, 12);

            targetSpell_GroupBox = gcnew System::Windows::Forms::GroupBox();
            targetSpell_GroupBox->Text = "Spell List";
            targetSpell_GroupBox->Size = System::Drawing::Size(282, 153);
            targetSpell_GroupBox->Location = Point(12, 191);

            walker_GroupBox = gcnew System::Windows::Forms::GroupBox();
            walker_GroupBox->Text = "Save && Load settings";
            walker_GroupBox->Size = System::Drawing::Size(170, 153);
            walker_GroupBox->Location = Point(300, 191);

            //###################### Combo Boxes ######################
            targetSpell_ComboBox = gcnew System::Windows::Forms::ComboBox();
            targetSpell_ComboBox->Location = Point(6, 22);
            targetSpell_ComboBox->Size = System::Drawing::Size(87, 21);
            targetSpell_ComboBox->DropDownStyle = ComboBoxStyle::DropDownList;
            for (int i = 0; i < 10; ++i)
            {
                targetSpell_ComboBox->Items->Add(i);
            }
            targetSpell_ComboBox->SelectedIndex = 0;

            //######################     ListBoxes     ######################
            targetWhite_Listbox = gcnew System::Windows::Forms::ListBox();
            targetWhite_Listbox->Size = System::Drawing::Size(207, 134);
            targetWhite_Listbox->Location = Point(10, 20);

            targetBlack_Listbox = gcnew System::Windows::Forms::ListBox();
            targetBlack_Listbox->Size = System::Drawing::Size(207, 134);
            targetBlack_Listbox->Location = Point(10, 10);

            targetSpell_Listbox = gcnew System::Windows::Forms::ListBox();
            targetSpell_Listbox->Size = System::Drawing::Size(104, 121);
            targetSpell_Listbox->Location = Point(10, 20);

            saveTarget_Listbox = gcnew System::Windows::Forms::ListBox();
            saveTarget_Listbox->Size = System::Drawing::Size(150, 69);
            saveTarget_Listbox->Location = Point(10, 19);

            //######################    Buttons    ########################
            addSpell_Button = gcnew System::Windows::Forms::Button();
            addSpell_Button->Location = Point(191, 19);
            addSpell_Button->Size = System::Drawing::Size(75, 24);
            addSpell_Button->Text = "Add Spell";
            addSpell_Button->Click += gcnew EventHandler(this, &main_form::addSpell);

            refreshTarget_Button = gcnew System::Windows::Forms::Button();
            refreshTarget_Button->Location = Point(120, 49);
            refreshTarget_Button->Size = System::Drawing::Size(146, 24);
            refreshTarget_Button->Text = "Refresh Monsters";
            refreshTarget_Button->Click += gcnew EventHandler(this, &main_form::refreshMonsters);

            saveTarget_Button = gcnew System::Windows::Forms::Button();
            saveTarget_Button->Location = Point(10, 120);
            saveTarget_Button->Size = System::Drawing::Size(70, 25);
            saveTarget_Button->Text = "Save";
            //saveTarget_Button->Click += gcnew EventHandler(this, &main_form::saveTarget);

            loadTarget_Button = gcnew System::Windows::Forms::Button();
            loadTarget_Button->Location = Point(90, 120);
            loadTarget_Button->Size = System::Drawing::Size(70, 25);
            loadTarget_Button->Text = "Load";
            //loadTarget_Button->Click += gcnew EventHandler(this, &main_form::loadWalker);

            //######################   Text Boxes  ########################
            saveTarget_TextBox = gcnew System::Windows::Forms::TextBox();
            saveTarget_TextBox->Location = Point(52, 94);
            saveTarget_TextBox->Size = System::Drawing::Size(108, 20);

            //######################   Labels  ########################
            saveTarget_Label = gcnew System::Windows::Forms::Label();
            saveTarget_Label->Location = Point(7, 94);
            saveTarget_Label->Text = "Name";
            saveTarget_Label->Width = 45;
            saveTarget_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Regular);

            //######################  CheckBoxes  ########################
            attackWhite_CheckBox = gcnew System::Windows::Forms::CheckBox();
            attackWhite_CheckBox->Location = Point(120, 102);
            attackWhite_CheckBox->Text = "Attack White List";

            attackBlack_CheckBox = gcnew System::Windows::Forms::CheckBox();
            attackBlack_CheckBox->Location = Point(120, 79);
            attackBlack_CheckBox->Text = "Attack Black List";

            //##################### Add to GroupBoxes ######################
            targetWhite_GroupBox->Controls->Add(targetWhite_Listbox);

            targetBlack_GroupBox->Controls->Add(targetBlack_Listbox);

            targetSpell_GroupBox->Controls->Add(targetSpell_Listbox);
            targetSpell_GroupBox->Controls->Add(targetSpell_ComboBox);
            targetSpell_GroupBox->Controls->Add(addSpell_Button);
            targetSpell_GroupBox->Controls->Add(refreshTarget_Button);
            targetSpell_GroupBox->Controls->Add(attackWhite_CheckBox);
            targetSpell_GroupBox->Controls->Add(attackBlack_CheckBox);

            saveTarget_GroupBox->Controls->Add(saveTarget_Listbox);
            saveTarget_GroupBox->Controls->Add(saveTarget_Button);
            saveTarget_GroupBox->Controls->Add(loadTarget_Button);
            saveTarget_GroupBox->Controls->Add(saveTarget_Label);
            saveTarget_GroupBox->Controls->Add(saveTarget_TextBox);

            //##################### Add to Target & Skill Tab ######################
            targetTab->Controls->Add(targetWhite_GroupBox);
            targetTab->Controls->Add(targetBlack_GroupBox);
            targetTab->Controls->Add(targetSpell_GroupBox);
            targetTab->Controls->Add(saveTarget_GroupBox);

            //######################   Cabebot Tab     ##########################      
            //######################     GroupBoxes    ######################   
            walker_GroupBox = gcnew System::Windows::Forms::GroupBox();
            walker_GroupBox->Text = "Waypoint List";
            walker_GroupBox->Size = System::Drawing::Size(160, 332);
            walker_GroupBox->Location = Point(12, 12);

            addWaypoint_GroupBox = gcnew System::Windows::Forms::GroupBox();
            addWaypoint_GroupBox->Text = "Add Action";
            addWaypoint_GroupBox->Size = System::Drawing::Size(292, 173);
            addWaypoint_GroupBox->Location = Point(178, 12);

            currentStatus_GroupBox = gcnew System::Windows::Forms::GroupBox();
            currentStatus_GroupBox->Text = "Current Status";
            currentStatus_GroupBox->Size = System::Drawing::Size(116, 153);
            currentStatus_GroupBox->Location = Point(178, 191);

            saveWalker_GroupBox = gcnew System::Windows::Forms::GroupBox();
            saveWalker_GroupBox->Text = "Save && Load Settings";
            saveWalker_GroupBox->Size = System::Drawing::Size(170, 153);
            saveWalker_GroupBox->Location = Point(300, 191);

            //###################### Combo Boxes ######################
            walkerActions_ComboBox = gcnew System::Windows::Forms::ComboBox();
            walkerActions_ComboBox->Location = Point(6, 22);
            walkerActions_ComboBox->Size = System::Drawing::Size(87, 21);
            walkerActions_ComboBox->DropDownStyle = ComboBoxStyle::DropDownList;
            walkerActions_ComboBox->Items->Add("Walk");
            walkerActions_ComboBox->Items->Add("Wait");
            walkerActions_ComboBox->Items->Add("Lure");
            walkerActions_ComboBox->Items->Add("Use Skill");
            walkerActions_ComboBox->Items->Add("Use Item");
            walkerActions_ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &main_form::walkerActions_ComboBox_SelectedIndexChanged);

            //######################     ListBoxes     ######################
            walker_Listbox = gcnew System::Windows::Forms::ListBox();
            walker_Listbox->Size = System::Drawing::Size(140, 303);
            walker_Listbox->Location = Point(10, 20);

            saveWalker_Listbox = gcnew System::Windows::Forms::ListBox();
            saveWalker_Listbox->Size = System::Drawing::Size(150, 69);
            saveWalker_Listbox->Location = Point(10, 19);

            //######################    Buttons    ########################
            addWaypoint_Button = gcnew System::Windows::Forms::Button();
            addWaypoint_Button->Location = Point(179, 20);
            addWaypoint_Button->Size = System::Drawing::Size(103, 23);
            addWaypoint_Button->Text = "Add Action";
            addWaypoint_Button->Click += gcnew EventHandler(this, &main_form::addWaypoint);

            saveWalker_Button = gcnew System::Windows::Forms::Button();
            saveWalker_Button->Location = Point(10, 120);
            saveWalker_Button->Size = System::Drawing::Size(70, 25);
            saveWalker_Button->Text = "Save";
            saveWalker_Button->Click += gcnew EventHandler(this, &main_form::saveWalker);

            loadWalker_Button = gcnew System::Windows::Forms::Button();
            loadWalker_Button->Location = Point(90, 120);
            loadWalker_Button->Size = System::Drawing::Size(70, 25);
            loadWalker_Button->Text = "Load";
            loadWalker_Button->Click += gcnew EventHandler(this, &main_form::loadWalker);

            //######################   Text Boxes  ########################
            saveWalker_TextBox = gcnew System::Windows::Forms::TextBox();
            saveWalker_TextBox->Location = Point(52, 94);
            saveWalker_TextBox->Size = System::Drawing::Size(108, 20);

            walkerAction_TextBox = gcnew System::Windows::Forms::TextBox();
            walkerAction_TextBox->Location = Point(99, 22);
            walkerAction_TextBox->Size = System::Drawing::Size(74, 20);

            //######################   Labels  ########################
            saveWalker_Label = gcnew System::Windows::Forms::Label();
            saveWalker_Label->Location = Point(7, 94);
            saveWalker_Label->Text = "Name";
            saveWalker_Label->Width = 45;
            saveWalker_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Regular);

            currentPos_Label = gcnew System::Windows::Forms::Label();
            currentPos_Label->Location = Point(10, 20);
            currentPos_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25, FontStyle::Regular);
            currentPos_Label->Text = "Current Position" + System::Environment::NewLine + "X = 100 | Y = 200";
            currentPos_Label->Height = 40;

            walkerStatus_Label = gcnew System::Windows::Forms::Label();
            walkerStatus_Label->Location = Point(10, 60);
            walkerStatus_Label->Text = "Walker Status" + System::Environment::NewLine + "OFF";
            walkerStatus_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25, FontStyle::Regular);
            walkerStatus_Label->Height = 40;

            targetStatus_Label = gcnew System::Windows::Forms::Label();
            targetStatus_Label->Location = Point(10, 100);
            targetStatus_Label->Text = "Target Status" + System::Environment::NewLine + "OFF";
            targetStatus_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25, FontStyle::Regular);
            targetStatus_Label->Height = 40;

            //##################### Add to GroupBoxes ######################
            walker_GroupBox->Controls->Add(walker_Listbox);
            ListFilesInFolder(L"Waypoints");
            addWaypoint_GroupBox->Controls->Add(addWaypoint_Button);
            addWaypoint_GroupBox->Controls->Add(walkerActions_ComboBox);
            addWaypoint_GroupBox->Controls->Add(walkerAction_TextBox);

            saveWalker_GroupBox->Controls->Add(saveWalker_Listbox);
            saveWalker_GroupBox->Controls->Add(saveWalker_Button);
            saveWalker_GroupBox->Controls->Add(loadWalker_Button);
            saveWalker_GroupBox->Controls->Add(saveWalker_Label);
            saveWalker_GroupBox->Controls->Add(saveWalker_TextBox);

            currentStatus_GroupBox->Controls->Add(currentPos_Label);
            currentStatus_GroupBox->Controls->Add(walkerStatus_Label);
            currentStatus_GroupBox->Controls->Add(targetStatus_Label);

            //##################### Add to Waypoint Tab ######################
            waypointTab->Controls->Add(walker_GroupBox);
            waypointTab->Controls->Add(addWaypoint_GroupBox);
            waypointTab->Controls->Add(saveWalker_GroupBox);
            waypointTab->Controls->Add(currentStatus_GroupBox);

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

            //######################   Healing Tab ######################
            //######################     GroupBoxes    ######################
            healing_GroupBox = gcnew System::Windows::Forms::GroupBox();
            healing_GroupBox->Text = "Healing List";
            healing_GroupBox->Size = System::Drawing::Size(165, 176);
            healing_GroupBox->Location = Point(12, 12);

            addItem_GroupBox = gcnew System::Windows::Forms::GroupBox();
            addItem_GroupBox->Text = "Add Healing Item";
            addItem_GroupBox->Size = System::Drawing::Size(278, 85);
            addItem_GroupBox->Location = Point(192, 12);

            addSpell_GroupBox = gcnew System::Windows::Forms::GroupBox();
            addSpell_GroupBox->Text = "Add Healing Spell";
            addSpell_GroupBox->Size = System::Drawing::Size(278, 85);
            addSpell_GroupBox->Location = Point(192, 103);

            saveHealing_GroupBox = gcnew System::Windows::Forms::GroupBox();
            saveHealing_GroupBox->Text = "Save && Load Settings";
            saveHealing_GroupBox->Size = System::Drawing::Size(170, 153);
            saveHealing_GroupBox->Location = Point(300, 191);

            myHealth_GroupBox = gcnew System::Windows::Forms::GroupBox();
            myHealth_GroupBox->Text = "My Health && Mana";
            myHealth_GroupBox->Size = System::Drawing::Size(280, 150);
            myHealth_GroupBox->Location = Point(12, 194);


            //######################     ListBoxes     ######################

            healing_Listbox = gcnew System::Windows::Forms::ListBox();
            healing_Listbox->Size = System::Drawing::Size(147, 134);
            healing_Listbox->Location = Point(6, 21);

            saveHealing_Listbox = gcnew System::Windows::Forms::ListBox();
            saveHealing_Listbox->Size = System::Drawing::Size(150, 69);
            saveHealing_Listbox->Location = Point(10, 19);

            //###################### Combo Boxes ######################
            healingItems_ComboBox = gcnew System::Windows::Forms::ComboBox();
            healingItems_ComboBox->Location = Point(6, 17);
            healingItems_ComboBox->Size = System::Drawing::Size(126, 21);
            healingItems_ComboBox->DropDownStyle = ComboBoxStyle::DropDownList;

            healingOptionItems_ComboBox = gcnew System::Windows::Forms::ComboBox();
            healingOptionItems_ComboBox->Location = Point(6, 46);
            healingOptionItems_ComboBox->Size = System::Drawing::Size(45, 21);
            healingOptionItems_ComboBox->Items->Add("HP%");
            healingOptionItems_ComboBox->Items->Add("MP%");
            healingOptionItems_ComboBox->SelectedIndex = 0;
            healingOptionItems_ComboBox->DropDownStyle = ComboBoxStyle::DropDownList;

            healingSpells_ComboBox = gcnew System::Windows::Forms::ComboBox();
            healingSpells_ComboBox->Location = Point(6, 17);
            healingSpells_ComboBox->Size = System::Drawing::Size(126, 21);
            healingSpells_ComboBox->DropDownStyle = ComboBoxStyle::DropDownList;

            healingOptionSpells_ComboBox = gcnew System::Windows::Forms::ComboBox();
            healingOptionSpells_ComboBox->Location = Point(6, 46);
            healingOptionSpells_ComboBox->Size = System::Drawing::Size(45, 21);
            healingOptionSpells_ComboBox->Items->Add("HP%");
            healingOptionSpells_ComboBox->Items->Add("MP%");
            healingOptionSpells_ComboBox->SelectedIndex = 0;
            healingOptionSpells_ComboBox->DropDownStyle = ComboBoxStyle::DropDownList;

            //######################    Buttons    ########################
            refreshHealingItems_Button = gcnew System::Windows::Forms::Button();
            refreshHealingItems_Button->Location = Point(186, 17);
            refreshHealingItems_Button->Size = System::Drawing::Size(82, 23);
            refreshHealingItems_Button->Text = "Refresh";
            refreshHealingItems_Button->Click += gcnew EventHandler(this, &main_form::refreshHealingItem);

            addHealingItem_Button = gcnew System::Windows::Forms::Button();
            addHealingItem_Button->Location = Point(138, 17);
            addHealingItem_Button->Size = System::Drawing::Size(42, 23);
            addHealingItem_Button->Text = "Add";
            addHealingItem_Button->Click += gcnew EventHandler(this, &main_form::addHealingItem);

            refreshHealingSpells_Button = gcnew System::Windows::Forms::Button();
            refreshHealingSpells_Button->Location = Point(186, 17);
            refreshHealingSpells_Button->Size = System::Drawing::Size(82, 23);
            refreshHealingSpells_Button->Text = "Refresh";
            refreshHealingSpells_Button->Click += gcnew EventHandler(this, &main_form::refreshHealingSpell);

            addHealingSpell_Button = gcnew System::Windows::Forms::Button();
            addHealingSpell_Button->Location = Point(138, 17);
            addHealingSpell_Button->Size = System::Drawing::Size(42, 23);
            addHealingSpell_Button->Text = "Add";
            addHealingSpell_Button->Click += gcnew EventHandler(this, &main_form::addHealingSpell);

            saveHealing_Button = gcnew System::Windows::Forms::Button();
            saveHealing_Button->Location = Point(10, 120);
            saveHealing_Button->Size = System::Drawing::Size(70, 25);
            saveHealing_Button->Text = "Save";
            //saveHealing_Button->Click += gcnew EventHandler(this, &main_form::saveHealing);

            loadHealing_Button = gcnew System::Windows::Forms::Button();
            loadHealing_Button->Location = Point(90, 120);
            loadHealing_Button->Size = System::Drawing::Size(70, 25);
            loadHealing_Button->Text = "Load";
            //loadHealing_Button->Click += gcnew EventHandler(this, &main_form::loadHealing);

            //######################   Text Boxes  ########################
            healingItemFrom_TextBox = gcnew System::Windows::Forms::TextBox();
            healingItemFrom_TextBox->Location = Point(57, 46);
            healingItemFrom_TextBox->Size = System::Drawing::Size(42, 20);

            healingItemTo_TextBox = gcnew System::Windows::Forms::TextBox();
            healingItemTo_TextBox->Location = Point(138, 46);
            healingItemTo_TextBox->Size = System::Drawing::Size(42, 20);

            healingSpellFrom_TextBox = gcnew System::Windows::Forms::TextBox();
            healingSpellFrom_TextBox->Location = Point(57, 46);
            healingSpellFrom_TextBox->Size = System::Drawing::Size(42, 20);

            healingSpellTo_TextBox = gcnew System::Windows::Forms::TextBox();
            healingSpellTo_TextBox->Location = Point(138, 46);
            healingSpellTo_TextBox->Size = System::Drawing::Size(42, 20);

            saveHealing_TextBox = gcnew System::Windows::Forms::TextBox();
            saveHealing_TextBox->Location = Point(52, 94);
            saveHealing_TextBox->Size = System::Drawing::Size(108, 20);

            //######################   Labels  ########################
            healingItems_Label = gcnew System::Windows::Forms::Label();
            healingItems_Label->Location = Point(105, 48);
            healingItems_Label->Text = "to";
            healingItems_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 11, FontStyle::Regular);

            healingSpells_Label = gcnew System::Windows::Forms::Label();
            healingSpells_Label->Location = Point(105, 48);
            healingSpells_Label->Size = System::Drawing::Size(21, 18);
            healingSpells_Label->Text = "to";
            healingSpells_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 11, FontStyle::Regular);

            saveHealing_Label = gcnew System::Windows::Forms::Label();
            saveHealing_Label->Location = Point(7, 94);
            saveHealing_Label->Text = "Name";
            saveHealing_Label->Width = 45;
            saveHealing_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Regular);

            myHealth_Label = gcnew System::Windows::Forms::Label();
            myHealth_Label->Location = Point(109, 16);
            myHealth_Label->Text = "Health";
            myHealth_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12, FontStyle::Regular);

            myMana_Label = gcnew System::Windows::Forms::Label();
            myMana_Label->Location = Point(109, 75);
            myMana_Label->Text = "Mana";
            myMana_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12, FontStyle::Regular);

            //######################   Progress Bars  ######################
            myHealth_ProgressBar = gcnew System::Windows::Forms::ProgressBar();
            myHealth_ProgressBar->Location = Point(22, 43);
            myHealth_ProgressBar->Size = System::Drawing::Size(235, 23);

            myMana_ProgressBar = gcnew System::Windows::Forms::ProgressBar();
            myMana_ProgressBar->Location = Point(22, 99);
            myMana_ProgressBar->Size = System::Drawing::Size(235, 23);


            //##################### Add to GroupBoxes ######################
            healing_GroupBox->Controls->Add(healing_Listbox);

            addItem_GroupBox->Controls->Add(healingItems_ComboBox);
            addItem_GroupBox->Controls->Add(refreshHealingItems_Button);
            addItem_GroupBox->Controls->Add(addHealingItem_Button);
            addItem_GroupBox->Controls->Add(healingItemFrom_TextBox);
            addItem_GroupBox->Controls->Add(healingItemTo_TextBox);
            addItem_GroupBox->Controls->Add(healingOptionItems_ComboBox);
            addItem_GroupBox->Controls->Add(healingItems_Label);

            addSpell_GroupBox->Controls->Add(healingSpells_ComboBox);
            addSpell_GroupBox->Controls->Add(refreshHealingSpells_Button);
            addSpell_GroupBox->Controls->Add(addHealingSpell_Button);
            addSpell_GroupBox->Controls->Add(healingSpellFrom_TextBox);
            addSpell_GroupBox->Controls->Add(healingSpellTo_TextBox);
            addSpell_GroupBox->Controls->Add(healingOptionSpells_ComboBox);
            addSpell_GroupBox->Controls->Add(healingSpells_Label);

            saveHealing_GroupBox->Controls->Add(saveHealing_Listbox);
            saveHealing_GroupBox->Controls->Add(saveHealing_Button);
            saveHealing_GroupBox->Controls->Add(loadHealing_Button);
            saveHealing_GroupBox->Controls->Add(saveHealing_Label);
            saveHealing_GroupBox->Controls->Add(saveHealing_TextBox);

            myHealth_GroupBox->Controls->Add(myHealth_Label);
            myHealth_GroupBox->Controls->Add(myMana_Label);
            myHealth_GroupBox->Controls->Add(myHealth_ProgressBar);
            myHealth_GroupBox->Controls->Add(myMana_ProgressBar);

            //##################### Add to Healing Tab ######################
            healingTab->Controls->Add(healing_GroupBox);
            healingTab->Controls->Add(addItem_GroupBox);
            healingTab->Controls->Add(addSpell_GroupBox);
            healingTab->Controls->Add(saveHealing_GroupBox);
            healingTab->Controls->Add(myHealth_GroupBox);
        }
#pragma endregion
        void ListFilesInFolder(const std::wstring& folderPath) {
            WIN32_FIND_DATA findFileData;
            HANDLE hFind = FindFirstFile((folderPath + L"\\*").c_str(), &findFileData);

            if (hFind == INVALID_HANDLE_VALUE) {
                std::wcerr << L"Nie mo¿na znaleŸæ plików w folderze: " << folderPath << std::endl;
                return;
            }

            do {
                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    saveWalker_Listbox->Items->Add(msclr::interop::marshal_as<String^>(findFileData.cFileName));
                }
            } while (FindNextFile(hFind, &findFileData) != 0);

            FindClose(hFind);
        }
        //###################### Functions       ######################
        //###################### Close Main_Form ######################
        System::Void main_form_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
        {
            targetBot_Worker->CancelAsync();
            healingBot_Worker->CancelAsync();
            walkerBot_Worker->CancelAsync();
        }
        System::Void walkerActions_ComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
            if (walkerActions_ComboBox->SelectedItem != nullptr && walkerActions_ComboBox->SelectedItem->ToString() == "Walk")
            {
                walkerAction_TextBox->Enabled = false;
            }
            else 
            {
                walkerAction_TextBox->Enabled = true;
            }
        }
        //###################### Button Functions ######################
        //###################### StartBot ######################
        System::Void startBot(Object^ sender, EventArgs^ e)
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
        //###################### Save Waypoint Button ######################g
        System::Void saveWalker(System::Object^ sender, System::EventArgs^ e)
        {
            if (saveWalker_TextBox->Text != "")
            {
               string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveWalker_TextBox->Text->ToString()));
               ofstream saveWpt("Waypoints/"+fileName);
               for (int i = 0; i < (int)walker_Listbox->Items->Count; ++i)
               {
                   saveWpt << msclr::interop::marshal_as<string>(walker_Listbox->Items[i]->ToString()) << endl;;
               }
               saveWalker_Listbox->Items->Add(saveWalker_TextBox->Text);
               saveWpt.close();
            }
        }
        //###################### Load Waypoint Button ######################
        System::Void loadWalker(System::Object^ sender, System::EventArgs^ e)
        {
            if (saveWalker_TextBox->Text != "")
            {
                string myText;
                string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveWalker_TextBox->Text->ToString()));
                ifstream saveWpt("Waypoints/" + fileName);
                walker_Listbox->Items->Clear();
                while (getline(saveWpt, myText)) 
                {
                    walker_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
                }
                waypoint = 0;
            }
            else if (saveWalker_Listbox->SelectedIndex != -1)
            {
                string myText;
                string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveWalker_Listbox->Items[saveWalker_Listbox->SelectedIndex]->ToString()));
                ifstream saveWpt("Waypoints/" + fileName);
                walker_Listbox->Items->Clear();
                while (getline(saveWpt, myText))
                {
                    walker_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
                }
                waypoint = 0;
            }
        }
        //###################### Add Waypoint Button ######################
        System::Void addWaypoint(System::Object^ sender, System::EventArgs^ e)
        {
            DWORD myPosPointer = ReadPointer(0x004C4E4C, { 0x560, 0x1C, 0x10, 0xB60, 0x0C });
            short int myX = (short int)*(short int*)myPosPointer;
            short int myY = (short int)*(short int*)(myPosPointer + 0x02);
            if (*(uint32_t*)myPosPointer != 0)
                walker_Listbox->Items->Add("X = "+ myX + " Y = " + myY);
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
                skills_Listbox->Items->Add(skills_ComboBox->SelectedItem->ToString());
        }
        //###################### Add add Healing Item Button ######################
        System::Void addHealingItem(System::Object^ sender, System::EventArgs^ e)
        {
            if (healingOptionItems_ComboBox != nullptr && healingItemFrom_TextBox->Text != "" && healingItemTo_TextBox->Text != "")
                healing_Listbox->Items->Add(healingOptionItems_ComboBox->SelectedItem->ToString() + " " 
                    + healingItemFrom_TextBox->Text + "%-" + healingItemTo_TextBox->Text + "% | ");
        }
        //###################### Add add Healing SpellButton ######################
        System::Void addHealingSpell(System::Object^ sender, System::EventArgs^ e)
        {
            if (healingSpells_ComboBox->SelectedItem != nullptr && healingOptionSpells_ComboBox != nullptr && healingSpellFrom_TextBox->Text != "" && healingSpellTo_TextBox->Text != "")
                healing_Listbox->Items->Add(healingSpells_ComboBox->SelectedIndex);
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
            DWORD skillListPointer = ReadPointer(0X004C3E5C, { 0x1bc, 0xF0, 0x0, 0x170, 0x7F4 });
            skills_ComboBox->Items->Clear();
            uint32_t skill = (uint32_t)skillListPointer - 0x2A0 * 4;
            for (int i = 0; i < 11; ++i)
            {
                //gcnew System::String((const char*)*(uint32_t*)(skill + 0x2A0 * i
                skills_ComboBox->Items->Add(i);
            }
            skills_ComboBox->SelectedIndex = 0;
        }
        //###################### Refresh Healing Spell List Button ######################
        System::Void refreshHealingSpell(System::Object^ sender, System::EventArgs^ e)
        {
            DWORD skillListPointer = ReadPointer(0x004C3E5C, { 0x1BC, 0xF0, 0x0, 0x170, 0x7F4 });
            healingSpells_ComboBox->Items->Clear();
            uint32_t skill = (uint32_t)skillListPointer - 0x2A0 * 3;
            for (int i = 0; i < 11; ++i)
            {
                healingSpells_ComboBox->Items->Add(gcnew System::String((const char*)*(uint32_t*)(skill + 0x2A0 * i)));
            }
            healingSpells_ComboBox->SelectedIndex = 0;
        }
        //###################### Refresh Healing Item List Button ######################
        System::Void refreshHealingItem(System::Object^ sender, System::EventArgs^ e)
        {
            DWORD healingListPointer = ReadPointer(0x004C4DF8, { 0xEC, 0x220, 0x4, 0xF0, 0x988 });
            DWORD tmpPointer;
            DWORD itemToAdd;
            healingItems_ComboBox->Items->Clear();
            for (int i = 0; i < 84; ++i)
            {
                tmpPointer = healingListPointer;
                tmpPointer += i * 0x28;
                tmpPointer = *(DWORD*)tmpPointer;
                if ((int)tmpPointer == 0)
                    continue;
                itemToAdd = tmpPointer;
                tmpPointer += 0x08;
                tmpPointer = *(DWORD*)tmpPointer;
                if ((int)*(DWORD*)(tmpPointer + 0x0C) > 10)
                {
                    tmpPointer += 0x38;
                    healingItems_ComboBox->Items->Add(gcnew System::String((const char*)*(uint32_t*)(tmpPointer)));
                    healingAddresses_Listbox->Items->Add(itemToAdd);
                }
            }
            healingListPointer = ReadPointer(0x004C463C, { 0x21C, 0x04, 0xF0, 0x960 });
            for (int i = 0; i < 84; ++i)
            {
                tmpPointer = healingListPointer;
                tmpPointer += i * 0x28;
                tmpPointer = *(DWORD*)tmpPointer;
                if ((int)tmpPointer == 0)
                    continue;
                itemToAdd = tmpPointer;
                tmpPointer += 0x08;
                tmpPointer = *(DWORD*)tmpPointer;
                if ((int)*(DWORD*)(tmpPointer + 0x0C) > 10)
                {
                    tmpPointer += 0x38;
                    healingItems_ComboBox->Items->Add(gcnew System::String((const char*)*(uint32_t*)(tmpPointer)));
                    healingAddresses_Listbox->Items->Add(itemToAdd);
                }
            }
            healingItems_ComboBox->SelectedIndex = 0;
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
        System::Void startWalkerBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            DWORD myPosPointer = ReadPointer(0x004C4E4C, { 0x560, 0x1C, 0x10, 0xB60, 0x0C });
            double timer = 0;
            short int myX;
            short int myY;
            short int mapY;
            short int mapX;
            walker_Listbox->SetSelected(waypoint, TRUE);
            mapX = System::Convert::ToInt32(walker_Listbox->Items[waypoint]->ToString()->Split('Y')[0]->Substring(3));
            mapY = System::Convert::ToInt32(walker_Listbox->Items[waypoint]->ToString()->Split('Y')[1]->Substring(2));            
            MoveTo(mapY*65536 + mapX);
            while (!walkerBot_Worker->CancellationPending)
            {
                while (!atak && !walkerBot_Worker->CancellationPending)
                {
                    walker_Listbox->SetSelected(waypoint, TRUE);
                    mapX = System::Convert::ToInt32(walker_Listbox->Items[waypoint]->ToString()->Split('Y')[0]->Substring(3));
                    mapY = System::Convert::ToInt32(walker_Listbox->Items[waypoint]->ToString()->Split('Y')[1]->Substring(2));
                    myX = (short int)*(short int*)myPosPointer;
                    myY = (short int)*(short int*)(myPosPointer + 0x02);
                    Sleep(100);
                    MoveTo(mapY * 65536 + mapX);
                    MoveTo(mapY * 65536 + mapX);
                    MoveTo(mapY * 65536 + mapX);
                    timer = 0;
                    while (myX != mapX && myY != mapY && !atak && !walkerBot_Worker->CancellationPending)
                    {
                        myX = (short int)*(short int*)myPosPointer;
                        myY = (short int)*(short int*)(myPosPointer + 0x02);
                        if (timer > 2)
                        {
                            MoveTo(mapY * 65536 + mapX);
                            timer = 0;
                        }
                        timer += 0.05;
                        Sleep(50);
                    }
                    if (myX == mapX && myY == mapY && !atak)
                    {
                        if (waypoint < (unsigned int)walker_Listbox->Items->Count - 1)
                        {
                            ++waypoint;
                        }
                        else
                        {
                            waypoint = 0;
                        }
                    }
                }
                Sleep(10);
            }
        }
        System::Void startTargetBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            string monsterName;

            DWORD entityListPointer;
            DWORD monsterID;
            DWORD monsterCountPointer = ReadPointer(0x003282C0, { 0x08, 0x04, 0x7C, 0x04, 0x528 });
            DWORD myPosPointer = ReadPointer(0x004C4E4C, { 0x560, 0x1C, 0x10, 0xB60, 0x0C });

            short int myX;
            short int myY;
            short int entityX;
            short int entityY;

            double timer = 0;

            bool tmps = 0;

            int ilosc = 0;

            while (!targetBot_Worker->CancellationPending)
            {
                for (int ss = 0; ss < 2; ++ss)
                {
                    for (int monster = 0; monster < (int)*(uint32_t*)monsterCountPointer; ++monster)
                    {
                        entityListPointer = ReadPointer(0x003266D8, { 0xE8C, 0x4, 0x6A4, 0x0 });
                        monsterID = *((uint32_t*)(entityListPointer)+monster);
                        monsterName = (string)(const char*)*(uint32_t*)((*(uint32_t*)(monsterID + 0x1BC)) + 0x04);
                        for (int monsterAttack = 0; monsterAttack < (int)monsters_ListBox->Items->Count; ++monsterAttack)
                        {
                            if (monsterName == msclr::interop::marshal_as<std::string>(monsters_ListBox->Items[monsterAttack]->ToString()))
                            {
                                myX = (int)*(short int*)myPosPointer;
                                myY = (int)*(short int*)(myPosPointer + 0x2);
                                entityX = (int)*(short int*)(monsterID + 0x0C);
                                entityY = (int)*(short int*)(monsterID + 0x0E);
                                while (((abs(myX - entityX) < 8 && abs(myY - entityY) < 8)) && (*(uint32_t*)(monsterID + 0x08) != 0xFFFFFFFF) && !targetBot_Worker->CancellationPending)
                                {
                                    myX = (int)*(short int*)myPosPointer;
                                    myY = (int)*(short int*)(myPosPointer + 0x2);
                                    entityX = (int)*(short int*)(monsterID + 0x0C);
                                    entityY = (int)*(short int*)(monsterID + 0x0E);
                                    atak = 1;
                                    for (int tmp = 0; tmp < (int)skills_Listbox->Items->Count; ++tmp)
                                    {
                                        AttackMonster(monsterID, System::Convert::ToInt32(skills_Listbox->Items[tmp]->ToString()->Split(' ')[0]));
                                        Sleep(150);
                                    }
                                    AttackMonster(monsterID, 0);
                                    Sleep(150);
                                }
                            }
                        }
                    }
                }
                Sleep(100);
                while ((int)*(DWORD*)ReadPointer(0x003282D8, { 0x288 }) > 0)
                {              
                    atak = 1;
                    DWORD itemsPointer = ReadPointer(0x004C44C4, { 0x18, 0x4, 0x0, 0x0 });
                    myX = (int)*(short int*)myPosPointer;
                    myY = (int)*(short int*)(myPosPointer + 0x2);
                    entityX = (int)*(short int*)(itemsPointer + 0x0C);
                    entityY = (int)*(short int*)(itemsPointer + 0x0E);
                    Sleep(300);
                    MoveTo(entityY * 65536 + entityX);
                    while (myX != entityX && myY != entityY && (int)*(DWORD*)ReadPointer(0x003282D8, { 0x288 }) > 0)
                    {
                        myX = (int)*(short int*)myPosPointer;
                        myY = (int)*(short int*)(myPosPointer + 0x2);
                        Sleep(50);
                        timer += 0.05;
                        if (timer > 2)
                        {
                            MoveTo((rand() % 3 - 1 + entityY) * 65536 + entityX + rand() % 3 - 1);
                            timer = 0;
                        }
                    }
                    Collect((uint32_t)(itemsPointer));
                }
                if (((int)*(DWORD*)ReadPointer(0x003282D8, { 0x288 }) == 0))
                     atak = 0;
            }
        }
        //###################### Start Healer ######################
        System::Void startHealingBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            string healName;
            while (!healingBot_Worker->CancellationPending)
            {
                for (int i = 0; i < (int)healing_Listbox->Items->Count; ++i)
                {
                    if (System::Convert::ToString(healing_Listbox->Items[i]->ToString()->Split('%')[0]) == "MP")
                    {
                        DWORD myMana = ReadPointer(0X004C482C, { 0xC0, 0xF48, 0xA74, 0xC04, 0x13C });
                        DWORD myMaxMana = ReadPointer(0X004C482C, { 0xC0, 0xF48, 0xA74, 0xC04, 0x138 });
                        if ((int)*(DWORD*)myMana <= ((int)*(DWORD*)myMaxMana * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[1]) * 0.01) &&
                            (int)*(DWORD*)myMana >= ((int)*(DWORD*)myMaxMana * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[2]->Substring(1)) * 0.01))
                        {   
                            SendMessage(FindWindow(NULL, L"Nostale"), WM_KEYDOWN, 0x31, 0x20001);
                            SendMessage(FindWindow(NULL, L"Nostale"), WM_KEYUP, 0x31, 0xC0020001);
                            Sleep(500);
                        }
                    }
                    else
                    {
                        DWORD myHp = ReadPointer(0X004C482C, { 0xC0, 0xF48, 0xA74, 0xC04, 0x22C });
                        DWORD myMaxHP = ReadPointer(0X004C482C, { 0xC0, 0xF48, 0xA74, 0xC04, 0x228 });
                        if ((int)*(DWORD*)myHp <= ((int)*(DWORD*)myMaxHP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[1]) * 0.01) &&
                            (int)*(DWORD*)myHp >= ((int)*(DWORD*)myMaxHP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[2]->Substring(1)) * 0.01))
                        {
                            SendMessage(FindWindow(NULL, L"Nostale"), WM_KEYDOWN, 0x32, 0x20001);
                            SendMessage(FindWindow(NULL, L"Nostale"), WM_KEYUP, 0x32, 0xC0020001);
                            Sleep(500);
                        }
                    }
                    Sleep(500);
                }
                Sleep(500);
            }
        }
    };
}
