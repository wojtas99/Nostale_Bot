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
    targetSpell_Listbox->Size = System::Drawing::Size(104, 81);
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

    refreshSpell_Button = gcnew System::Windows::Forms::Button();
    refreshSpell_Button->Location = Point(10, 110);
    refreshSpell_Button->Size = System::Drawing::Size(75, 24);
    refreshSpell_Button->Text = "Refresh Spell";
    refreshSpell_Button->Click += gcnew EventHandler(this, &main_form::refreshSpell);

    refreshTarget_Button = gcnew System::Windows::Forms::Button();
    refreshTarget_Button->Location = Point(120, 49);
    refreshTarget_Button->Size = System::Drawing::Size(146, 24);
    refreshTarget_Button->Text = "Refresh Monsters";
    refreshTarget_Button->Click += gcnew EventHandler(this, &main_form::refreshMonsters);

    saveTarget_Button = gcnew System::Windows::Forms::Button();
    saveTarget_Button->Location = Point(10, 120);
    saveTarget_Button->Size = System::Drawing::Size(70, 25);
    saveTarget_Button->Text = "Save";
    saveTarget_Button->Click += gcnew EventHandler(this, &main_form::saveTarget);

    loadTarget_Button = gcnew System::Windows::Forms::Button();
    loadTarget_Button->Location = Point(90, 120);
    loadTarget_Button->Size = System::Drawing::Size(70, 25);
    loadTarget_Button->Text = "Load";
    loadTarget_Button->Click += gcnew EventHandler(this, &main_form::loadTarget);

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

    attackEverything_CheckBox = gcnew System::Windows::Forms::CheckBox();
    attackEverything_CheckBox->Location = Point(120, 125);
    attackEverything_CheckBox->Text = "Attack Everything";
    attackEverything_CheckBox->Width = 110;
    attackEverything_CheckBox->CheckedChanged += gcnew EventHandler(this, &main_form::checkBox_CheckedChanged);

    //##################### Add to GroupBoxes ######################
    targetWhite_GroupBox->Controls->Add(targetWhite_Listbox);

    targetBlack_GroupBox->Controls->Add(targetBlack_Listbox);

    targetSpell_GroupBox->Controls->Add(targetSpell_Listbox);
    targetSpell_GroupBox->Controls->Add(targetSpell_ComboBox);
    targetSpell_GroupBox->Controls->Add(addSpell_Button);
    targetSpell_GroupBox->Controls->Add(refreshSpell_Button);
    targetSpell_GroupBox->Controls->Add(refreshTarget_Button);
    targetSpell_GroupBox->Controls->Add(attackWhite_CheckBox);
    targetSpell_GroupBox->Controls->Add(attackBlack_CheckBox);
    targetSpell_GroupBox->Controls->Add(attackEverything_CheckBox);
    

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
        attackEverything_CheckBox->Checked = false;
        attackEverything_CheckBox->Enabled = false;
    }
    else if (attackBlack_CheckBox->Checked)
    {
        attackWhite_CheckBox->Checked = false;
        attackWhite_CheckBox->Enabled = false;
        attackEverything_CheckBox->Checked = false;
        attackEverything_CheckBox->Enabled = false;
    }
    else if (attackEverything_CheckBox->Checked)
    {
        attackWhite_CheckBox->Checked = false;
        attackWhite_CheckBox->Enabled = false;
        attackBlack_CheckBox->Checked = false;
        attackBlack_CheckBox->Enabled = false;
    }
    else
    {
        attackWhite_CheckBox->Enabled = true;
        attackBlack_CheckBox->Enabled = true;
        attackEverything_CheckBox->Enabled = true;
    }
}
void easyBot::main_form::refreshSpell(System::Object^ sender, System::EventArgs^ e)
{
    targetSpell_ComboBox->Items->Clear();
    DWORD skillList = ReadPointer(0x004F4DD0, { 0x158, 0X4, 0X4, 0X0, 0X8, 0X14 });
    DWORD spell = skillList;
    for(int i = 0; i < (int)*(DWORD*)skillCount - 1; ++i)
    {
        targetSpell_ComboBox->Items->Add(gcnew System::String((const char*)*(DWORD*)(spell + i*0x2A0)));
    }
    targetSpell_ComboBox->SelectedIndex = 0;
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
        for (int i = 0; i < (int)targetWhite_Listbox->Items->Count; ++i)
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
void easyBot::main_form::saveTarget(System::Object^ sender, System::EventArgs^ e)
{
    if (saveTarget_TextBox->Text != "")
    {
        string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveTarget_TextBox->Text->ToString()));
        ofstream save("Target/" + fileName);
        for (int i = 0; i < (int)targetBlack_Listbox->Items->Count; ++i)
        {

            save << msclr::interop::marshal_as<string>(targetBlack_Listbox->Items[i]->ToString()) << endl;
        }
        if ((int)targetWhite_Listbox->Items->Count > 0)
        {
            save << "W" << endl;
        }
        for (int i = 0; i < (int)targetWhite_Listbox->Items->Count; ++i)
        {

            save << msclr::interop::marshal_as<string>(targetWhite_Listbox->Items[i]->ToString()) << endl;
        }
        saveTarget_Listbox->Items->Add(saveTarget_TextBox->Text);
        save.close();
    }
}
void easyBot::main_form::loadTarget(System::Object^ sender, System::EventArgs^ e)
{
    bool addToBlack = 0;
    if (saveTarget_TextBox->Text != "")
    {
        string myText;
        string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveTarget_TextBox->Text->ToString()));
        ifstream save("Target/" + fileName);
        targetWhite_Listbox->Items->Clear();
        targetWhite_Listbox->Items->Clear();
        while (getline(save, myText))
        {
            if (myText == "W")
            {
                addToBlack = 1;
                continue;
            }
            if (!addToBlack)
            {
                targetBlack_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
            }
            else
            {
                targetWhite_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
            }
        }
    }
    else if (saveTarget_Listbox->SelectedIndex != -1)
    {
        string myText;
        string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveTarget_Listbox->Items[saveTarget_Listbox->SelectedIndex]->ToString()));
        ifstream save("Target/" + fileName);
        targetWhite_Listbox->Items->Clear();
        targetWhite_Listbox->Items->Clear();
        while (getline(save, myText))
        {
            if (myText == "W")
            {
                addToBlack = 1;
                continue;
            }
            if (!addToBlack)
            {
                targetBlack_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
            }
            else
            {
                targetWhite_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
            }
        }
    }
}
void easyBot::main_form::refreshMonsters(System::Object^ sender, System::EventArgs^ e)
{
    targetBlack_Listbox->Items->Clear();
    targetWhite_Listbox->Items->Clear();
    bool found = 0;
    DWORD monster;
    for (int i = 0; i < (int)*(DWORD*)monsterCount; ++i)
    {
        monster = *(DWORD*)(*(DWORD*)(*(DWORD*)(monsterList + 0x04 * i) + 0x1BC) + 0x04);
        for (int tmp = 0; tmp < (int)targetBlack_Listbox->Items->Count; ++tmp)
        {
            if (gcnew System::String((const char*)monster) == (targetBlack_Listbox->Items[tmp]->ToString()))
            {
                found = 1;
                break;
            }
        }
        for (int tmp = 0; tmp < (int)targetWhite_Listbox->Items->Count; ++tmp)
        {
            if (gcnew System::String((const char*)monster) == (targetWhite_Listbox->Items[tmp]->ToString()))
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

    DWORD monsterStatus;
    int attackRange = ((int)*(BYTE*)range) - 2;

    short int myX;
    short int myY;
    short int entityX;
    short int entityY;


    double timer = 0;

    while (!targetBot_Worker->CancellationPending)
    {
        if (state == 0)
        {
            for (unsigned int i = 0; i < ((unsigned int)*(uint32_t*)monsterCount) - 1; ++i)
            {
                monsterStatus = *(DWORD*)(monsterList + 0x04 * i);
                monsterName = (string)(const char*)*(DWORD*)(*(DWORD*)(monsterStatus + 0x1BC) + 0x04);
                if (attackBlack_CheckBox->Checked)
                {
                    for (int monsterAttack = 0; monsterAttack < (int)targetBlack_Listbox->Items->Count; ++monsterAttack)
                    {
                        if (monsterName == msclr::interop::marshal_as<std::string>(targetBlack_Listbox->Items[monsterAttack]->ToString()))
                        {
                            myX = *(short int*)myPosition;
                            myY = *(short int*)(myPosition + 0x2);
                            entityX = *(short int*)(monsterStatus + 0x0C);
                            entityY = *(short int*)(monsterStatus + 0x0E);
                            while (abs(myX - entityX) < attackRange && abs(myY - entityY) < attackRange && !targetBot_Worker->CancellationPending && *(uint32_t*)(monsterStatus + 0x08) != 0xFFFFFFFF)
                            {
                                i = 0;
                                myX = *(short int*)myPosition;
                                myY = *(short int*)(myPosition + 0x2);
                                entityX = *(short int*)(monsterStatus + 0x0C);
                                entityY = *(short int*)(monsterStatus + 0x0E);
                                for (int spell = 0; spell < (int)targetSpell_Listbox->Items->Count; ++spell)
                                {
                                    for (int spell2 = 0; spell2 < (int)targetSpell_ComboBox->Items->Count; ++spell2)
                                    {
                                        if ((targetSpell_Listbox->Items[spell]->ToString() == targetSpell_ComboBox->Items[spell2]->ToString()) && ((int)*(DWORD*)(skillCD + spell2 * 0x48)) == 0)
                                        {
                                            AttackMonster(monsterStatus, (spell2 + 1));
                                            break;
                                        }
                                    }
                                }
                                AttackMonster(monsterStatus, 0);
                                Sleep(300);
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
                            myX = *(short int*)myPosition;
                            myY = *(short int*)(myPosition + 0x2);
                            entityX = *(short int*)(monsterStatus + 0x0C);
                            entityY = *(short int*)(monsterStatus + 0x0E);
                            while (abs(myX - entityX) < attackRange && abs(myY - entityY) < attackRange && !targetBot_Worker->CancellationPending && *(uint32_t*)(monsterStatus + 0x08) != 0xFFFFFFFF)
                            {
                                i = 0;
                                myX = *(short int*)myPosition;
                                myY = *(short int*)(myPosition + 0x2);
                                entityX = *(short int*)(monsterStatus + 0x0C);
                                entityY = *(short int*)(monsterStatus + 0x0E);
                                for (int spell = 0; spell < (int)targetSpell_Listbox->Items->Count; ++spell)
                                {
                                    for (int spell2 = 0; spell2 < (int)targetSpell_ComboBox->Items->Count; ++spell2)
                                    {
                                        if ((targetSpell_Listbox->Items[spell]->ToString() == targetSpell_ComboBox->Items[spell2]->ToString()) && ((int)*(DWORD*)(skillCD + spell2 * 0x48)) == 0)
                                        {
                                            AttackMonster(monsterStatus, (spell2 + 1));
                                            break;
                                        }
                                    }
                                }
                                AttackMonster(monsterStatus, 0);
                                Sleep(300);
                            }
                        }
                    }
                }
                if (attackEverything_CheckBox->Checked)
                {
                    myX = *(short int*)myPosition;
                    myY = *(short int*)(myPosition + 0x2);
                    entityX = *(short int*)(monsterStatus + 0x0C);
                    entityY = *(short int*)(monsterStatus + 0x0E);
                    while (abs(myX - entityX) < attackRange && abs(myY - entityY) < attackRange && !targetBot_Worker->CancellationPending && *(uint32_t*)(monsterStatus + 0x08) != 0xFFFFFFFF)
                    {
                        i = 0;
                        myX = *(short int*)myPosition;
                        myY = *(short int*)(myPosition + 0x2);
                        entityX = *(short int*)(monsterStatus + 0x0C);
                        entityY = *(short int*)(monsterStatus + 0x0E);
                        for (int spell = 0; spell < (int)targetSpell_Listbox->Items->Count; ++spell)
                        {
                            for (int spell2 = 0; spell2 < (int)targetSpell_ComboBox->Items->Count; ++spell2)
                            {
                                if ((targetSpell_Listbox->Items[spell]->ToString() == targetSpell_ComboBox->Items[spell2]->ToString()) && ((int)*(DWORD*)(skillCD + spell2 * 0x48)) == 0)
                                {
                                    AttackMonster(monsterStatus, (spell2 + 1));
                                    break;
                                }
                            }
                        }
                        AttackMonster(monsterStatus, 0);
                        Sleep(300);
                    }
                }
            }        
        state = 1;
        }
        Sleep(10);
    }
}