#include "gui.h"

void easyBot::main_form::InitializeLootTab(void)
{
    //######################   Loot Tab     ##########################      
    //######################     GroupBoxes    ######################   
    lootWhite_GroupBox = gcnew System::Windows::Forms::GroupBox();
    lootWhite_GroupBox->Text = "White List";
    lootWhite_GroupBox->Size = System::Drawing::Size(223, 173);
    lootWhite_GroupBox->Location = Point(12, 12);

    lootBlack_GroupBox = gcnew System::Windows::Forms::GroupBox();
    lootBlack_GroupBox->Text = "Black List";
    lootBlack_GroupBox->Size = System::Drawing::Size(223, 173);
    lootBlack_GroupBox->Location = Point(247, 12);

    addLoot_GroupBox = gcnew System::Windows::Forms::GroupBox();
    addLoot_GroupBox->Text = "Loot Settings";
    addLoot_GroupBox->Size = System::Drawing::Size(282, 153);
    addLoot_GroupBox->Location = Point(12, 191);

    saveLoot_GroupBox = gcnew System::Windows::Forms::GroupBox();
    saveLoot_GroupBox->Text = "Save && Load Settings";
    saveLoot_GroupBox->Size = System::Drawing::Size(170, 153);
    saveLoot_GroupBox->Location = Point(300, 191);

    //######################     ListBoxes     ######################
    lootWhite_Listbox = gcnew System::Windows::Forms::ListBox();
    lootWhite_Listbox->Size = System::Drawing::Size(207, 134);
    lootWhite_Listbox->Location = Point(10, 20);
    lootWhite_Listbox->DoubleClick += gcnew EventHandler(this, &main_form::addItemToBlackList);


    lootBlack_Listbox = gcnew System::Windows::Forms::ListBox();
    lootBlack_Listbox->Size = System::Drawing::Size(207, 134);
    lootBlack_Listbox->Location = Point(10, 20);
    lootBlack_Listbox->DoubleClick += gcnew EventHandler(this, &main_form::addItemToWhiteList);

    saveLoot_Listbox = gcnew System::Windows::Forms::ListBox();
    saveLoot_Listbox->Size = System::Drawing::Size(150, 69);
    saveLoot_Listbox->Location = Point(10, 19);

    //######################    Buttons    ########################
    addLootItem_Button = gcnew System::Windows::Forms::Button();
    addLootItem_Button->Location = Point(201, 16);
    addLootItem_Button->Size = System::Drawing::Size(65, 24);
    addLootItem_Button->Text = "Add Item";
    addLootItem_Button->Click += gcnew EventHandler(this, &main_form::addItem);

    refreshLoot_Button = gcnew System::Windows::Forms::Button();
    refreshLoot_Button->Location = Point(166, 49);
    refreshLoot_Button->Size = System::Drawing::Size(100, 24);
    refreshLoot_Button->Text = "Refresh Items";
    refreshLoot_Button->Click += gcnew EventHandler(this, &main_form::refreshItems);

    saveLoot_Button = gcnew System::Windows::Forms::Button();
    saveLoot_Button->Location = Point(10, 120);
    saveLoot_Button->Size = System::Drawing::Size(70, 25);
    saveLoot_Button->Text = "Save";
    saveLoot_Button->Click += gcnew EventHandler(this, &main_form::saveLoot);

    loadLoot_Button = gcnew System::Windows::Forms::Button();
    loadLoot_Button->Location = Point(90, 120);
    loadLoot_Button->Size = System::Drawing::Size(70, 25);
    loadLoot_Button->Text = "Load";
    loadLoot_Button->Click += gcnew EventHandler(this, &main_form::loadLoot);

    //######################   Text Boxes  ########################
    addLootItem_TextBox = gcnew System::Windows::Forms::TextBox();
    addLootItem_TextBox->Location = Point(96, 19);
    addLootItem_TextBox->Size = System::Drawing::Size(99, 20);

    lootRadius_TextBox = gcnew System::Windows::Forms::TextBox();
    lootRadius_TextBox->Location = Point(96, 53);
    lootRadius_TextBox->Size = System::Drawing::Size(64, 20);
    lootRadius_TextBox->Text = "10";

    saveLoot_TextBox = gcnew System::Windows::Forms::TextBox();
    saveLoot_TextBox->Location = Point(52, 94);
    saveLoot_TextBox->Size = System::Drawing::Size(108, 20);

    //######################   Labels  ########################
    saveLoot_Label = gcnew System::Windows::Forms::Label();
    saveLoot_Label->Location = Point(7, 94);
    saveLoot_Label->Text = "Name";
    saveLoot_Label->Width = 45;
    saveLoot_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Regular);

    itemName_Label = gcnew System::Windows::Forms::Label();
    itemName_Label->Location = Point(7, 20);
    itemName_Label->Text = "Item Name";
    itemName_Label->Width = 85;
    itemName_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Regular);

    lootRadius_Label = gcnew System::Windows::Forms::Label();
    lootRadius_Label->Location = Point(7, 54);
    lootRadius_Label->Text = "Loot Radius";
    lootRadius_Label->Width = 85;
    lootRadius_Label->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 10, FontStyle::Regular);

    //######################  CheckBoxes  ########################
    lootWhite_CheckBox = gcnew System::Windows::Forms::CheckBox();
    lootWhite_CheckBox->Location = Point(166, 102);
    lootWhite_CheckBox->Text = "Loot White List";
    lootWhite_CheckBox->Width = 100;
    lootWhite_CheckBox->CheckedChanged += gcnew EventHandler(this, &main_form::checkBoxLoot_CheckedChanged);

    lootBlack_CheckBox = gcnew System::Windows::Forms::CheckBox();
    lootBlack_CheckBox->Location = Point(166, 79);
    lootBlack_CheckBox->Text = "Loot Black List";
    lootBlack_CheckBox->Width = 100;
    lootBlack_CheckBox->CheckedChanged += gcnew EventHandler(this, &main_form::checkBoxLoot_CheckedChanged);

    lootEverything_CheckBox = gcnew System::Windows::Forms::CheckBox();
    lootEverything_CheckBox->Location = Point(166, 125);
    lootEverything_CheckBox->Text = "Loot Everything";
    lootEverything_CheckBox->Width = 100;
    lootEverything_CheckBox->CheckedChanged += gcnew EventHandler(this, &main_form::checkBoxLoot_CheckedChanged);

    //##################### Add to GroupBoxes ######################
    lootWhite_GroupBox->Controls->Add(lootWhite_Listbox);

    lootBlack_GroupBox->Controls->Add(lootBlack_Listbox);

    addLoot_GroupBox->Controls->Add(itemName_Label);
    addLoot_GroupBox->Controls->Add(lootRadius_Label);
    addLoot_GroupBox->Controls->Add(lootWhite_CheckBox);
    addLoot_GroupBox->Controls->Add(lootBlack_CheckBox);
    addLoot_GroupBox->Controls->Add(lootEverything_CheckBox);
    addLoot_GroupBox->Controls->Add(addLootItem_TextBox);
    addLoot_GroupBox->Controls->Add(lootRadius_TextBox);
    addLoot_GroupBox->Controls->Add(addLootItem_Button);
    addLoot_GroupBox->Controls->Add(refreshLoot_Button);


    saveLoot_GroupBox->Controls->Add(saveLoot_Listbox);
    saveLoot_GroupBox->Controls->Add(saveLoot_Button);
    saveLoot_GroupBox->Controls->Add(loadLoot_Button);
    saveLoot_GroupBox->Controls->Add(saveLoot_Label);
    saveLoot_GroupBox->Controls->Add(saveLoot_TextBox);

    //##################### Add to Loot Tab ######################
    lootTab->Controls->Add(lootWhite_GroupBox);
    lootTab->Controls->Add(lootBlack_GroupBox);
    lootTab->Controls->Add(addLoot_GroupBox);
    lootTab->Controls->Add(saveLoot_GroupBox);
}

void easyBot::main_form::refreshItems(System::Object^ sender, System::EventArgs^ e)
{
    unsigned int itemsOnTheGround = (unsigned int)*(DWORD*)ReadPointer(0x003282D8, { 0x288 });
    bool found = 0;
    lootBlack_Listbox->Items->Clear();
    for (unsigned int i = 0; i < itemsOnTheGround; ++i)
    {
        DWORD itemsGround = ReadPointer(0x004BB2AC, { 0x28, 0xFA0, 0x4, 0x6A4, 0x0 });
        itemsGround = *(DWORD*)(itemsGround + 0x04 * i);
        itemsGround = *(DWORD*)(itemsGround + 0xC4);
        itemsGround = *(DWORD*)(itemsGround + 0x38);
        for (int tmp = 0; tmp < (int)lootBlack_Listbox->Items->Count; ++tmp)
        {
            if (gcnew System::String((const char*)itemsGround) == lootBlack_Listbox->Items[tmp]->ToString())
            {
                found = 1;
                break;
            }
        }
        for (int tmp = 0; tmp < (int)lootWhite_Listbox->Items->Count; ++tmp)
        {
            if (gcnew System::String((const char*)itemsGround) == lootWhite_Listbox->Items[tmp]->ToString())
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            lootBlack_Listbox->Items->Add(gcnew System::String((const char*)itemsGround));
        }
        found = 0;
    }
}

void easyBot::main_form::addItem(System::Object^ sender, System::EventArgs^ e)
{
    if (addLootItem_TextBox->Text != "")
    {
        lootBlack_Listbox->Items->Add(addLootItem_TextBox->Text);
        addLootItem_TextBox->Clear();
    }
}

void easyBot::main_form::saveLoot(System::Object^ sender, System::EventArgs^ e)
{
    if (saveLoot_TextBox->Text != "")
    {
        string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveLoot_TextBox->Text->ToString()));
        ofstream save("Loot/" + fileName);
        for (int i = 0; i < (int)lootBlack_Listbox->Items->Count; ++i)
        {
        
            save << msclr::interop::marshal_as<string>(lootBlack_Listbox->Items[i]->ToString()) << endl;
        }
        if ((int)lootWhite_Listbox->Items->Count > 0)
        {
            save << "W" << endl;
        }
        for (int i = 0; i < (int)lootWhite_Listbox->Items->Count; ++i)
        {

            save << msclr::interop::marshal_as<string>(lootWhite_Listbox->Items[i]->ToString()) << endl;
        }
        saveLoot_Listbox->Items->Add(saveLoot_TextBox->Text);
        save.close();
    }
}

void easyBot::main_form::loadLoot(System::Object^ sender, System::EventArgs^ e)
{
    bool addToBlack = 0;
    if (saveLoot_TextBox->Text != "")
    {
        string myText;
        string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveLoot_TextBox->Text->ToString()));
        ifstream save("Loot/" + fileName);
        lootWhite_Listbox->Items->Clear();
        lootBlack_Listbox->Items->Clear();
        while (getline(save, myText))
        {
            if (myText == "W")
            {
                addToBlack = 1;
                continue;
            }
            if (!addToBlack)
            {
                lootBlack_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
            }
            else
            {
                lootWhite_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
            }
        }
    }
    else if (saveLoot_Listbox->SelectedIndex != -1)
    {
        string myText;
        string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveLoot_Listbox->Items[saveLoot_Listbox->SelectedIndex]->ToString()));
        ifstream save("Loot/" + fileName);
        lootWhite_Listbox->Items->Clear();
        lootBlack_Listbox->Items->Clear();
        while (getline(save, myText))
        {
            if (myText == "W")
            {
                addToBlack = 1;
                continue;
            }
            if (!addToBlack)
            {
                lootBlack_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
            }
            else
            {
                lootWhite_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
            }
        }
    }
}
void easyBot::main_form::addItemToWhiteList(System::Object^ sender, System::EventArgs^ e)
{
    bool found = 0;
    if (lootBlack_Listbox->SelectedItem != nullptr)
    {
        for (int i = 0; i < (int)lootWhite_Listbox->Items->Count; ++ i)
        {
            if (lootBlack_Listbox->SelectedItem->ToString() == lootWhite_Listbox->Items[i]->ToString())
            {
                found = 1;
            }
        }
        if (!found)
        {
            lootWhite_Listbox->Items->Add(lootBlack_Listbox->SelectedItem->ToString());
            lootBlack_Listbox->Items->Remove(lootBlack_Listbox->SelectedItem);
        }
        found = 0;
    }
}

void easyBot::main_form::addItemToBlackList(System::Object^ sender, System::EventArgs^ e)
{
    bool found = 0;
    if (lootWhite_Listbox->SelectedItem != nullptr)
    {
        for (int i = 0; i < (int)lootBlack_Listbox->Items->Count; ++i)
        {
            if (lootWhite_Listbox->SelectedItem->ToString() == lootBlack_Listbox->Items[i]->ToString())
            {
                found = 1;
            }
        }
        if (!found)
        {
            lootBlack_Listbox->Items->Add(lootWhite_Listbox->SelectedItem->ToString());
            lootWhite_Listbox->Items->Remove(lootWhite_Listbox->SelectedItem);
        }
        found = 0;
    }
}
void easyBot::main_form::checkBoxLoot_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
    if (lootWhite_CheckBox->Checked)
    {
        lootBlack_CheckBox->Checked = false;
        lootBlack_CheckBox->Enabled = false;
        lootEverything_CheckBox->Checked = false;
        lootEverything_CheckBox->Enabled = false;
    }
    else if (lootBlack_CheckBox->Checked)
    {
        lootWhite_CheckBox->Checked = false;
        lootWhite_CheckBox->Enabled = false;
        lootEverything_CheckBox->Checked = false;
        lootEverything_CheckBox->Enabled = false;
    }
    else if (lootEverything_CheckBox->Checked)
    {
        lootWhite_CheckBox->Checked = false;
        lootWhite_CheckBox->Enabled = false;
        lootBlack_CheckBox->Checked = false;
        lootBlack_CheckBox->Enabled = false;
    }
    else
    {
        lootWhite_CheckBox->Enabled = true;
        lootBlack_CheckBox->Enabled = true;
        lootEverything_CheckBox->Enabled = true;
    }
}

void easyBot::main_form::startLootBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
    DWORD myPosPointer = ReadPointer(0x004C44EC, { 0x1C, 0x4, 0x0, 0x40, 0xC });

    short int myX;
    short int myY;
    short int entityX;
    short int entityY;

    double timer = 0;

    int lootRadius = System::Convert::ToInt32(lootRadius_TextBox->Text->ToString());
    if (lootRadius_TextBox->Text == "")
    {
        lootRadius = 10;
    }
    DWORD numberOfItemsOnTheGround = ReadPointer(0x003282D8, { 0x288 });

    String^ itemName;
    while (!lootBot_Worker->CancellationPending)
    {
        if (state == 1)
        {
            if (lootEverything_CheckBox->Checked)
            {
                for (int item = 0; item < (int)*(DWORD*)numberOfItemsOnTheGround; ++item)
                {
                    DWORD itemsPointer = ReadPointer(0x004BB2AC, { 0x28, 0xFA0, 0x4, 0x6A4, 0x0 });
                    itemsPointer = *(DWORD*)(itemsPointer + item * 0x04);
                    myX = *(short int*)myPosPointer;
                    myY = *(short int*)(myPosPointer + 0x2);
                    entityX = *(short int*)(itemsPointer + 0x0C);
                    entityY = *(short int*)(itemsPointer + 0x0E);
                    itemsPointer = (uint32_t)itemsPointer;
                    if (abs(myX - entityX) <  lootRadius && abs(myY - entityY) < lootRadius)
                    {
                        MoveTo(entityY * 65536 + entityX);
                        while (abs(myX - entityX) > 1 && abs(myY - entityY) > 1)
                        {
                            myX = *(short int*)myPosPointer;
                            myY = *(short int*)(myPosPointer + 0x2);
                            Sleep(50);
                            timer += 0.05;
                            if (timer > 1)
                            {
                                MoveTo(entityY * 65536 + entityX);
                                timer = 0;
                            }
                        }
                        Sleep(200);
                        Collect(itemsPointer);
                        Sleep(100);
                        timer = 0;
                        item = 0;
                    }
                }
            }
            else if (lootBlack_CheckBox->Checked)
            {
                for (int item = 0; item < (int)*(DWORD*)numberOfItemsOnTheGround; ++item)
                {
                    DWORD itemsPointer = ReadPointer(0x004BB2AC, { 0x28, 0xFA0, 0x4, 0x6A4, 0x0 });
                    itemsPointer = *(DWORD*)(itemsPointer + item * 0x04);
                    myX = *(short int*)myPosPointer;
                    myY = *(short int*)(myPosPointer + 0x2);
                    entityX = *(short int*)(itemsPointer + 0x0C);
                    entityY = *(short int*)(itemsPointer + 0x0E);
                    itemsPointer = (uint32_t)itemsPointer;
                    itemName = gcnew System::String((const char*)*(DWORD*)(*(DWORD*)(itemsPointer + 0xC4) + 0x38));
                    if (abs(myX - entityX) < lootRadius && abs(myY - entityY) < lootRadius)
                    {
                        for (int i = 0; i < (int)lootBlack_Listbox->Items->Count; ++i)
                        {
                            if (itemName == lootBlack_Listbox->Items[i]->ToString())
                            {
                                MoveTo(entityY * 65536 + entityX);
                                while (abs(myX - entityX) > 1 && abs(myY - entityY) > 1)
                                {
                                    myX = *(short int*)myPosPointer;
                                    myY = *(short int*)(myPosPointer + 0x2);
                                    Sleep(50);
                                    timer += 0.05;
                                    if (timer > 2)
                                    {
                                        MoveTo(entityY * 65536 + entityX);
                                        timer = 0;
                                    }
                                }
                                Sleep(200);
                                Collect(itemsPointer);
                                Sleep(100);
                                timer = 0;
                                item = 0;
                            }
                        }
                    }
                }
            }
            else if (lootWhite_CheckBox->Checked)
            {
                for (int item = 0; item < (int)*(DWORD*)numberOfItemsOnTheGround; ++item)
                {
                    DWORD itemsPointer = ReadPointer(0x004BB2AC, { 0x28, 0xFA0, 0x4, 0x6A4, 0x0 });
                    itemsPointer = *(DWORD*)(itemsPointer + item * 0x04);
                    myX = *(short int*)myPosPointer;
                    myY = *(short int*)(myPosPointer + 0x2);
                    entityX = *(short int*)(itemsPointer + 0x0C);
                    entityY = *(short int*)(itemsPointer + 0x0E);
                    itemsPointer = (uint32_t)itemsPointer;
                    itemName = gcnew System::String((const char*)*(DWORD*)(*(DWORD*)(itemsPointer + 0xC4) + 0x38));
                    if (abs(myX - entityX) < lootRadius && abs(myY - entityY) < lootRadius)
                    {
                        for (int i = 0; i < (int)lootWhite_Listbox->Items->Count; ++i)
                        {
                            if (itemName == lootWhite_Listbox->Items[i]->ToString())
                            {
                                MoveTo(entityY * 65536 + entityX);
                                while (abs(myX - entityX) > 1 && abs(myY - entityY) > 1)
                                {
                                    myX = *(short int*)myPosPointer;
                                    myY = *(short int*)(myPosPointer + 0x2);
                                    Sleep(50);
                                    timer += 0.05;
                                    if (timer > 2)
                                    {
                                        MoveTo(entityY * 65536 + entityX);
                                        timer = 0;
                                    }
                                }
                                Sleep(200);
                                Collect(itemsPointer);
                                Sleep(100);
                                timer = 0;
                                item = 0;
                            }
                        }
                    }
                }
            }
            state = 2;
        }
        Sleep(10);
    }
}