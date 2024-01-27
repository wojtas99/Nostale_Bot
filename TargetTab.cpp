#include "gui.h"

void easyBot::main_form::InitializeTargetTab(void)
{
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

    saveTarget_GroupBox = gcnew System::Windows::Forms::GroupBox();
    saveTarget_GroupBox->Text = "Save && Load Settings";
    saveTarget_GroupBox->Size = System::Drawing::Size(170, 153);
    saveTarget_GroupBox->Location = Point(300, 191);

    //###################### Combo Boxes ######################
    targetSpell_ComboBox = gcnew System::Windows::Forms::ComboBox();
    targetSpell_ComboBox->Location = Point(120, 20);
    targetSpell_ComboBox->Size = System::Drawing::Size(65, 21);
    targetSpell_ComboBox->DropDownStyle = ComboBoxStyle::DropDownList;
    for (int i = 0; i < 11; ++i)
    {
        targetSpell_ComboBox->Items->Add(i);
    }
    targetSpell_ComboBox->SelectedIndex = 0;
    //######################     ListBoxes     ######################
    targetWhite_Listbox = gcnew System::Windows::Forms::ListBox();
    targetWhite_Listbox->Size = System::Drawing::Size(207, 134);
    targetWhite_Listbox->Location = Point(10, 20);
    targetWhite_Listbox->DoubleClick += gcnew EventHandler(this, &main_form::addMonsterToBlackList);


    targetBlack_Listbox = gcnew System::Windows::Forms::ListBox();
    targetBlack_Listbox->Size = System::Drawing::Size(207, 134);
    targetBlack_Listbox->Location = Point(10, 20);
    targetBlack_Listbox->DoubleClick += gcnew EventHandler(this, &main_form::addMonsterToWhiteList);

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

    loadTarget_Button = gcnew System::Windows::Forms::Button();
    loadTarget_Button->Location = Point(90, 120);
    loadTarget_Button->Size = System::Drawing::Size(70, 25);
    loadTarget_Button->Text = "Load";

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
    attackWhite_CheckBox->Width = 110;
    attackWhite_CheckBox->CheckedChanged += gcnew EventHandler(this, &main_form::checkBox_CheckedChanged);

    attackBlack_CheckBox = gcnew System::Windows::Forms::CheckBox();
    attackBlack_CheckBox->Location = Point(120, 79);
    attackBlack_CheckBox->Text = "Attack Black List";
    attackBlack_CheckBox->Width = 110;
    attackBlack_CheckBox->CheckedChanged += gcnew EventHandler(this, &main_form::checkBox_CheckedChanged);

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
}
void easyBot::main_form::checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
    if (attackWhite_CheckBox->Checked)
    {
        attackBlack_CheckBox->Checked = false;
        attackBlack_CheckBox->Enabled = false;
    }
    else if (attackBlack_CheckBox->Checked)
    {
        attackWhite_CheckBox->Checked = false;
        attackWhite_CheckBox->Enabled = false;
    }
    else
    {
        attackWhite_CheckBox->Enabled = true;
        attackBlack_CheckBox->Enabled = true;
    }
}
void easyBot::main_form::addSpell(System::Object^ sender, System::EventArgs^ e)
{
    if (targetSpell_ComboBox->SelectedItem != nullptr)
        targetSpell_Listbox->Items->Add(targetSpell_ComboBox->SelectedItem->ToString());
}

void easyBot::main_form::addMonsterToWhiteList(System::Object^ sender, System::EventArgs^ e)
{
    bool found = 0;
    if (targetBlack_Listbox->SelectedItem != nullptr)
    {
        for (int i = 0; i < (int)targetBlack_Listbox->Items->Count; ++i)
        {
            if (targetBlack_Listbox->SelectedItem->ToString() == targetWhite_Listbox->Items[i]->ToString())
            {
                found = 1;
            }
        }
        if (!found)
        {
            targetWhite_Listbox->Items->Add(targetBlack_Listbox->SelectedItem->ToString());
            targetBlack_Listbox->Items->Remove(targetBlack_Listbox->SelectedItem);
        }
        found = 0;
    }
}
void easyBot::main_form::addMonsterToBlackList(System::Object^ sender, System::EventArgs^ e)
{
    bool found = 0;
    if (targetWhite_Listbox->SelectedItem != nullptr)
    {
        for (int i = 0; i < (int)targetBlack_Listbox->Items->Count; ++i)
        {
            if (targetWhite_Listbox->SelectedItem->ToString() == targetBlack_Listbox->Items[i]->ToString())
            {
                found = 1;
            }
        }
        if (!found)
        {
            targetBlack_Listbox->Items->Add(targetWhite_Listbox->SelectedItem->ToString());
            targetWhite_Listbox->Items->Remove(targetWhite_Listbox->SelectedItem);
        }
        found = 0;
    }
}


void easyBot::main_form::refreshMonsters(System::Object^ sender, System::EventArgs^ e)
{
    bool found = 0;
    DWORD monster;
    for (int i = 0; i < (int)*(DWORD*)ReadPointer(0x003282C0, { 0x08, 0x04, 0x7C, 0x04, 0x528 }); ++i)
    {
        DWORD entityListPointer = ReadPointer(0x003266D8, { 0xE8C, 0x4, 0x6A4, 0x0 });
        monster = *(DWORD*)(*(DWORD*)(*(DWORD*)(entityListPointer + 0x04 * i) + 0x1BC) + 0x04);
        for (int tmp = 0; tmp < (int)targetBlack_Listbox->Items->Count; ++tmp)
        {
            if (gcnew System::String((const char*)monster) == (targetBlack_Listbox->Items[tmp]->ToString()))
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            targetBlack_Listbox->Items->Add(gcnew System::String((const char*)monster));
        }
        found = 0;
    }
}

void easyBot::main_form::startTargetBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
    string monsterName;

    DWORD myPosPointer = ReadPointer(0x004C4B34, { 0xCC, 0xFC, 0x8, 0x2EC, 0xC });
    DWORD entityListPointer;
    DWORD monsterStatus;

    short int myX;
    short int myY;
    short int entityX;
    short int entityY;

    double timer = 0;

    while (!targetBot_Worker->CancellationPending)
    {
        if (state == 0)
        {
            for (unsigned int i = 0; i < (unsigned int)*(uint32_t*)ReadPointer(0x003282C0, { 0x08, 0x04, 0x7C, 0x04, 0x528 }) - 1; ++i)
            {
                entityListPointer = ReadPointer(0x003266D8, { 0xE8C, 0x4, 0x6A4, 0x0 });
                monsterStatus = *(DWORD*)(entityListPointer + 0x04 * i);
                monsterName = (string)(const char*)*(DWORD*)(*(DWORD*)(monsterStatus + 0x1BC) + 0x04);
                if (attackBlack_CheckBox->Checked)
                {
                    for (int monsterAttack = 0; monsterAttack < (int)targetBlack_Listbox->Items->Count; ++monsterAttack)
                    {
                        if (monsterName == msclr::interop::marshal_as<std::string>(targetBlack_Listbox->Items[monsterAttack]->ToString()))
                        {
                            myX = *(short int*)myPosPointer;
                            myY = *(short int*)(myPosPointer + 0x2);
                            entityX = *(short int*)(monsterStatus + 0x0C);
                            entityY = *(short int*)(monsterStatus + 0x0E);
                            while (abs(myX - entityX) < 9 && abs(myY - entityY) < 9 && !targetBot_Worker->CancellationPending && *(uint32_t*)(monsterStatus + 0x08) != 0xFFFFFFFF)
                            {
                                i = 0;
                                myX = *(short int*)myPosPointer;
                                myY = *(short int*)(myPosPointer + 0x2);
                                entityX = *(short int*)(monsterStatus + 0x0C);
                                entityY = *(short int*)(monsterStatus + 0x0E);
                                for (int spell = 0; spell < (int)targetSpell_Listbox->Items->Count; ++spell)
                                {
                                    AttackMonster(monsterStatus, System::Convert::ToInt32(targetSpell_Listbox->Items[spell]->ToString()->Split(' ')[0]));
                                    Sleep(150);
                                }
                                AttackMonster(monsterStatus, 0);
                                Sleep(150);
                            }
                        }
                    }
                }
                if (attackWhite_CheckBox->Checked)
                {
                    for (int monsterAttack = 0; monsterAttack < (int)targetWhite_Listbox->Items->Count; ++monsterAttack)
                    {
                        if (monsterName == msclr::interop::marshal_as<std::string>(targetWhite_Listbox->Items[monsterAttack]->ToString()))
                        {
                            myX = *(short int*)myPosPointer;
                            myY = *(short int*)(myPosPointer + 0x2);
                            entityX = *(short int*)(monsterStatus + 0x0C);
                            entityY = *(short int*)(monsterStatus + 0x0E);
                            while (abs(myX - entityX) < 9 && abs(myY - entityY) < 9 && !targetBot_Worker->CancellationPending && *(uint32_t*)(monsterStatus + 0x08) != 0xFFFFFFFF)
                            {
                                i = 0;
                                myX = *(short int*)myPosPointer;
                                myY = *(short int*)(myPosPointer + 0x2);
                                entityX = *(short int*)(monsterStatus + 0x0C);
                                entityY = *(short int*)(monsterStatus + 0x0E);
                                for (int spell = 0; spell < (int)targetSpell_Listbox->Items->Count; ++spell)
                                {
                                    AttackMonster(monsterStatus, System::Convert::ToInt32(targetSpell_Listbox->Items[spell]->ToString()->Split(' ')[0]));
                                    Sleep(150);
                                }
                                AttackMonster(monsterStatus, 0);
                                Sleep(150);
                            }
                        }
                    }
                }
            }        
        state = 1;
        }
        Sleep(10);
    }
}