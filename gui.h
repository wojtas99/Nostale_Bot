#ifndef GUI_H
#define GUI_H
#include "memscan.h"
#include "Nostale_Entity.h"
#include "CallFunction.h"
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
    public ref class main_form : public System::Windows::Forms::Form
    {
    public:
        main_form(void)
        {
            InitializeMainTab();
            InitializeTargetTab();
            InitializeHealingTab();
            InitializeWalkerTab();
        }
        main_form(void(lpMoveTo)(uint32_t), void(lpAttackMonster)(uint32_t, short), void(lpRest)(void), void(lpCollect)(uint32_t))
        {
            InitializeMainTab();
            InitializeTargetTab();
            InitializeHealingTab();
            InitializeWalkerTab();
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
        // Global Variables
        unsigned int waypoint = 0;
        bool atak = 0;
        // Functions
        void(*attackMonster)(uint32_t, short);
        void(*moveTo)(uint32_t);
        void(*rest)(void);
        void(*collect)(uint32_t);
        void InitializeMainTab(void);
        void InitializeTargetTab(void);
        void InitializeHealingTab(void);
        void InitializeWalkerTab(void);
        void ListFilesInFolder(const std::wstring& folderPath);
        void walkerActions_ComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
        void startBot(Object^ sender, EventArgs^ e);
        void saveWalker(System::Object^ sender, System::EventArgs^ e);
        void loadWalker(System::Object^ sender, System::EventArgs^ e);
        void addWaypoint(System::Object^ sender, System::EventArgs^ e);
        void addSpell(System::Object^ sender, System::EventArgs^ e);
        void refreshMonsters(System::Object^ sender, System::EventArgs^ e);
        void startWalkerBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
        void startTargetBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
        void startHealingBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
        void addHealingItem(System::Object^ sender, System::EventArgs^ e);
        // Variables
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
        //###################### Functions       ######################
        //###################### Close Main_Form ######################
        System::Void main_form_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
        {
            targetBot_Worker->CancelAsync();
            healingBot_Worker->CancelAsync();
            walkerBot_Worker->CancelAsync();
        }      
    };
}
#endif // GUI_H