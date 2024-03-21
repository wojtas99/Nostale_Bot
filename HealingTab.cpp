#include "gui.h"

void easyBot::main_form::InitializeHealingTab(void)
{
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
    //refreshHealingItems_Button->Click += gcnew EventHandler(this, &main_form::refreshHealingItem);

    addHealingItem_Button = gcnew System::Windows::Forms::Button();
    addHealingItem_Button->Location = Point(138, 17);
    addHealingItem_Button->Size = System::Drawing::Size(42, 23);
    addHealingItem_Button->Text = "Add";
    addHealingItem_Button->Click += gcnew EventHandler(this, &main_form::addHealingItem);

    refreshHealingSpells_Button = gcnew System::Windows::Forms::Button();
    refreshHealingSpells_Button->Location = Point(186, 17);
    refreshHealingSpells_Button->Size = System::Drawing::Size(82, 23);
    refreshHealingSpells_Button->Text = "Refresh";
    refreshHealingSpells_Button->Click += gcnew EventHandler(this, &main_form::refreshHealingSkill);

    addHealingSpell_Button = gcnew System::Windows::Forms::Button();
    addHealingSpell_Button->Location = Point(138, 17);
    addHealingSpell_Button->Size = System::Drawing::Size(42, 23);
    addHealingSpell_Button->Text = "Add";
    addHealingSpell_Button->Click += gcnew EventHandler(this, &main_form::addHealingSkill);

    saveHealing_Button = gcnew System::Windows::Forms::Button();
    saveHealing_Button->Location = Point(10, 120);
    saveHealing_Button->Size = System::Drawing::Size(70, 25);
    saveHealing_Button->Text = "Save";

    loadHealing_Button = gcnew System::Windows::Forms::Button();
    loadHealing_Button->Location = Point(90, 120);
    loadHealing_Button->Size = System::Drawing::Size(70, 25);
    loadHealing_Button->Text = "Load";

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
    myHealth_ProgressBar->Minimum = 0;


    myMana_ProgressBar = gcnew System::Windows::Forms::ProgressBar();
    myMana_ProgressBar->Location = Point(22, 99);
    myMana_ProgressBar->Size = System::Drawing::Size(235, 23);
    myMana_ProgressBar->Minimum = 0;

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
//###################### Refresh healing Skill ######################
void easyBot::main_form::refreshHealingSkill(System::Object^ sender, System::EventArgs^ e)
{
    healingSpells_ComboBox->Items->Clear();
    DWORD skillList = ReadPointer(0x004F4DD0, { 0x158, 0X4, 0X4, 0X0, 0X8, 0X14 });
    DWORD spell = skillList;
    for (int i = 0; i < (int)*(DWORD*)skillCount - 1; ++i)
    {
        healingSpells_ComboBox->Items->Add(gcnew System::String((const char*)*(DWORD*)(spell + i * 0x2A0)));
    }
    healingSpells_ComboBox->SelectedIndex = 0;
}
//###################### Start Healer ######################
void easyBot::main_form::startHealingBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
    string healName;
    DWORD myMAXMP = myStats;
    DWORD myMP = myStats + 0x4;
    DWORD myMAXHP = myStats + 0xF0;
    DWORD myHP = myStats + 0xF4;
    DWORD monsterStatus;

    while (!healingBot_Worker->CancellationPending)
    {
        myHealth_ProgressBar->Maximum = (int)*(DWORD*)myMAXHP;
        myHealth_ProgressBar->Value = (int)*(DWORD*)myHP;
        myMana_ProgressBar->Maximum = (int)*(DWORD*)myMAXMP;
        myMana_ProgressBar->Value = (int)*(DWORD*)myMP;
        for (int i = 0; i < (int)healing_Listbox->Items->Count; ++i)
        {
            if (healing_Listbox->Items[i]->ToString()->Contains("|"))
            {
                if (System::Convert::ToString(healing_Listbox->Items[i]->ToString()->Split('%')[0]) == "MP")
                {
                    if ((int)*(DWORD*)myMP <= ((int)*(DWORD*)myMAXMP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[1]) * 0.01) &&
                        (int)*(DWORD*)myMP >= ((int)*(DWORD*)myMAXMP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[2]->Substring(1)) * 0.01))
                    {
                        for (int spell2 = 0; spell2 < (int)healingSpells_ComboBox->Items->Count; ++spell2)
                        {
                            if ((System::Convert::ToString(healing_Listbox->Items[i]->ToString()->Split('| ')[1]) == healingSpells_ComboBox->Items[spell2]->ToString()) && ((int)*(DWORD*)(skillCD + spell2 * 0x120)) == 1)
                            {
                                monsterStatus = *(DWORD*)(monsterList + 0x04 * i);
                                AttackMonster(monsterStatus, (spell2 + 1));
                                Sleep(500);
                                break;
                            }
                        }
                    }
                }
                else
                {
                    if ((int)*(DWORD*)myHP <= ((int)*(DWORD*)myMAXHP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[1]) * 0.01) &&
                        (int)*(DWORD*)myHP >= ((int)*(DWORD*)myMAXHP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[2]->Substring(1)) * 0.01))
                    {
                        for (int spell2 = 0; spell2 < (int)healingSpells_ComboBox->Items->Count; ++spell2)
                        {
                            if ((System::Convert::ToString(healing_Listbox->Items[i]->ToString()->Split('| ')[1]) == healingSpells_ComboBox->Items[spell2]->ToString()) && ((int)*(DWORD*)(skillCD + spell2 * 0x48)) == 0)
                            {
                                monsterStatus = *(DWORD*)(monsterList + 0x04 * i);
                                AttackMonster(monsterStatus, (spell2 + 1));
                                Sleep(500);
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                if (System::Convert::ToString(healing_Listbox->Items[i]->ToString()->Split('%')[0]) == "MP")
                {
                    if ((int)*(DWORD*)myMP <= ((int)*(DWORD*)myMAXMP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[1]) * 0.01) &&
                        (int)*(DWORD*)myMP >= ((int)*(DWORD*)myMAXMP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[2]->Substring(1)) * 0.01))
                    {
                        SendMessage(FindWindow(NULL, L"Nostale"), WM_KEYDOWN, 0x31, 0x20001);
                        SendMessage(FindWindow(NULL, L"Nostale"), WM_KEYUP, 0x31, 0xC0020001);
                        Sleep(500);
                    }
                }
                else
                {
                    if ((int)*(DWORD*)myHP <= ((int)*(DWORD*)myMAXHP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[1]) * 0.01) &&
                        (int)*(DWORD*)myHP >= ((int)*(DWORD*)myMAXHP * System::Convert::ToInt32(healing_Listbox->Items[i]->ToString()->Split('%')[2]->Substring(1)) * 0.01))
                    {
                        SendMessage(FindWindow(NULL, L"Nostale"), WM_KEYDOWN, 0x32, 0x20001);
                        SendMessage(FindWindow(NULL, L"Nostale"), WM_KEYUP, 0x32, 0xC0020001);
                        Sleep(500);
                    }
                }
            }
            Sleep(500);
        }
        Sleep(500);
    }
}
void easyBot::main_form::addHealingItem(System::Object^ sender, System::EventArgs^ e)
{
    if (healingOptionItems_ComboBox != nullptr && healingItemFrom_TextBox->Text != "" && healingItemTo_TextBox->Text != "")
        healing_Listbox->Items->Add(healingOptionItems_ComboBox->SelectedItem->ToString() + " "
            + healingItemFrom_TextBox->Text + "%-" + healingItemTo_TextBox->Text + "% ");
}
void easyBot::main_form::addHealingSkill(System::Object^ sender, System::EventArgs^ e)
{
    if (healingSpells_ComboBox->SelectedItem != nullptr)
        healing_Listbox->Items->Add(healingOptionSpells_ComboBox->SelectedItem->ToString() + " "
            + healingSpellFrom_TextBox->Text + "%-" + healingSpellTo_TextBox->Text + "% | " + healingSpells_ComboBox->SelectedItem->ToString());
}

/*
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
*/
