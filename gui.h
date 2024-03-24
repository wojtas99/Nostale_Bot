#ifndef GUI_H
#define GUI_H
#include "memscan.h"
#include "CallFunction.h"
#include <msclr/marshal_cppstd.h>
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
    public ref class main_form : public System::Windows::Forms::Form
    {
    public:
        main_form(void)
        {
        }
        main_form(void(lpMoveTo)(uint32_t), void(lpAttackMonster)(uint32_t, short), void(lpRest)(void), void(lpCollect)(uint32_t), void(lpMovePetPartner)(uint32_t, bool), void(lpAttackMonsterPet)(uint32_t, bool))
        {
            InitializeMainTab();
            InitializeTargetTab();
            InitializeHealingTab();
            InitializeWalkerTab();
            InitializeLootTab();
            ListFilesInFolder(L"Waypoints");
            ListFilesInFolder(L"Target");
            ListFilesInFolder(L"Loot");
            this->Width = 500;
            this->Height = 400;
            this->Text = "KrawczorBot";
            this->attackMonster = lpAttackMonster;
            this->moveTo = lpMoveTo;
            this->rest = lpRest;
            this->collect = lpCollect;
            this->moveToPet = lpMovePetPartner;
            this->attackMonsterPet = lpAttackMonsterPet;
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
        // Global Variables
        unsigned int waypoint = 0;
        unsigned int state = 0; // 0 - Attack, 1 - Loot, 2 - Walk
        // Functions
        void(*attackMonster)(uint32_t, short);
        void(*moveTo)(uint32_t);
        void(*rest)(void);
        void(*collect)(uint32_t);
        void(*moveToPet)(uint32_t, bool);
        void(*attackMonsterPet)(uint32_t, bool);
        void InitializeMainTab(void);
        void InitializeTargetTab(void);
        void InitializeHealingTab(void);
        void InitializeWalkerTab(void);
        void InitializeLootTab(void);
        void ListFilesInFolder(const std::wstring& folderPath);
        void startBot(Object^ sender, EventArgs^ e);
        void saveWalker(System::Object^ sender, System::EventArgs^ e);
        void loadWalker(System::Object^ sender, System::EventArgs^ e);
        void addWaypoint(System::Object^ sender, System::EventArgs^ e);
        void addSpell(System::Object^ sender, System::EventArgs^ e);
        void refreshMonsters(System::Object^ sender, System::EventArgs^ e);
        void startTargetBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
        void startLootBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
        void startWalkerBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
        void startHealingBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
        void addHealingItem(System::Object^ sender, System::EventArgs^ e);
        void addMonsterToBlackList(System::Object^ sender, System::EventArgs^ e);
        void addMonsterToWhiteList(System::Object^ sender, System::EventArgs^ e);
        void checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        void refreshItems(System::Object^ sender, System::EventArgs^ e);
        void addItem(System::Object^ sender, System::EventArgs^ e);
        void main_form_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
        void saveLoot(System::Object^ sender, System::EventArgs^ e);
        void loadLoot(System::Object^ sender, System::EventArgs^ e);
        void addItemToWhiteList(System::Object^ sender, System::EventArgs^ e);
        void addItemToBlackList(System::Object^ sender, System::EventArgs^ e);
        void checkBoxLoot_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
        void saveTarget(System::Object^ sender, System::EventArgs^ e);
        void loadTarget(System::Object^ sender, System::EventArgs^ e);
        void deleteWaypoint(System::Object^ sender, System::EventArgs^ e);
        void refreshSpell(System::Object^ sender, System::EventArgs^ e);
        void refreshHealingSkill(System::Object^ sender, System::EventArgs^ e);
        void addHealingSkill(System::Object^ sender, System::EventArgs^ e);
        // Main Tab
        System::ComponentModel::Container^ components;
        System::Windows::Forms::TabControl^ tabView;
        System::Windows::Forms::TabPage^ mainTab;
        System::ComponentModel::BackgroundWorker^ targetBot_Worker;
        System::ComponentModel::BackgroundWorker^ lootBot_Worker;
        System::ComponentModel::BackgroundWorker^ walkerBot_Worker;
        System::ComponentModel::BackgroundWorker^ healingBot_Worker;
        System::Windows::Forms::Button^ startBot_Button;
        System::Windows::Forms::CheckBox^ moveAttackPet_CheckBox;
        System::Windows::Forms::CheckBox^ moveAttackPartner_CheckBox;
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
        System::Windows::Forms::Button^ refreshSpell_Button;
        System::Windows::Forms::Button^ loadTarget_Button;
        System::Windows::Forms::Button^ saveTarget_Button;
        System::Windows::Forms::TextBox^ saveTarget_TextBox;
        System::Windows::Forms::Label^ saveTarget_Label;
        System::Windows::Forms::CheckBox^ attackWhite_CheckBox;
        System::Windows::Forms::CheckBox^ attackBlack_CheckBox;
        System::Windows::Forms::CheckBox^ attackEverything_CheckBox;
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
        // Loot Tab
        System::Windows::Forms::TabPage^ lootTab;
        System::Windows::Forms::GroupBox^ lootWhite_GroupBox;
        System::Windows::Forms::GroupBox^ lootBlack_GroupBox;
        System::Windows::Forms::GroupBox^ addLoot_GroupBox;
        System::Windows::Forms::GroupBox^ saveLoot_GroupBox;
        System::Windows::Forms::ListBox^ lootWhite_Listbox;
        System::Windows::Forms::ListBox^ lootBlack_Listbox;
        System::Windows::Forms::ListBox^ saveLoot_Listbox;
        System::Windows::Forms::Button^ addLootItem_Button;
        System::Windows::Forms::Button^ refreshLoot_Button;
        System::Windows::Forms::Button^ saveLoot_Button;
        System::Windows::Forms::Button^ loadLoot_Button;
        System::Windows::Forms::TextBox^ addLootItem_TextBox;
        System::Windows::Forms::TextBox^ saveLoot_TextBox;
        System::Windows::Forms::Label^ itemName_Label;
        System::Windows::Forms::Label^ saveLoot_Label;
        System::Windows::Forms::CheckBox^ lootWhite_CheckBox;
        System::Windows::Forms::CheckBox^ lootBlack_CheckBox;
        System::Windows::Forms::CheckBox^ lootEverything_CheckBox;

        // Pointers
        DWORD myPosition = ReadPointer(0x004F4904, { 0x20, 0x0C});

        DWORD monsterCount = ReadPointer(0x003582C0, { 0x8, 0x4, 0X60, 0X4, 0X608 });
        DWORD monsterList = ReadPointer(0x003566D8, { 0xEA4, 0x4, 0X5E4, 0X0 });

        DWORD itemCount = ReadPointer(0x003582C0, { 0x8, 0X4, 0X7C, 0X4, 0X568 });

        DWORD myStats = ReadPointer(0x00356158, { 0x18, 0XA34, 0XB10 });

        DWORD range = ReadPointer(0x004F4904, { 0x68 });

        DWORD skillCount = ReadPointer(0x004F4C70, { 0X3EC, 0X768 });
        DWORD skillCD = ReadPointer(0x004F4DD0, { 0X158, 0X4, 0X4, 0X0, 0X24 });


    };
}
#endif // GUI_H