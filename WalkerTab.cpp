#include "gui.h"

void easyBot::main_form::InitializeWalkerTab(void)
{
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
    walkerActions_ComboBox->Items->Add("Lure");
    walkerActions_ComboBox->Items->Add("Sleep");
    walkerActions_ComboBox->SelectedIndex = 0;

    //######################     ListBoxes     ######################
    walker_Listbox = gcnew System::Windows::Forms::ListBox();
    walker_Listbox->Size = System::Drawing::Size(140, 303);
    walker_Listbox->Location = Point(10, 20);
    walker_Listbox->DoubleClick += gcnew EventHandler(this, &main_form::deleteWaypoint);

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
    currentPos_Label->Text = "Current Position" + System::Environment::NewLine + "X = 0 | Y = 0";
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
}


void easyBot::main_form::deleteWaypoint(System::Object^ sender, System::EventArgs^ e)
{
    if (walker_Listbox->SelectedItem != nullptr)
    {
        walker_Listbox->Items->Remove(walker_Listbox->SelectedItem);
    }
}


void easyBot::main_form::saveWalker(System::Object^ sender, System::EventArgs^ e)
{
    if (saveWalker_TextBox->Text != "")
    {
        string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveWalker_TextBox->Text->ToString()));
        ofstream saveWpt("Waypoints/" + fileName);
        for (int i = 0; i < (int)walker_Listbox->Items->Count; ++i)
        {
            saveWpt << msclr::interop::marshal_as<string>(walker_Listbox->Items[i]->ToString()) << endl;;
        }
        saveWalker_Listbox->Items->Add(saveWalker_TextBox->Text);
        saveWpt.close();
    }
}


void easyBot::main_form::loadWalker(System::Object^ sender, System::EventArgs^ e)
{
    if (saveWalker_TextBox->Text != "")
    {
        string myText;
        string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveWalker_TextBox->Text->ToString()));
        ifstream save("Waypoints/" + fileName);
        walker_Listbox->Items->Clear();
        while (getline(save, myText))
        {
            walker_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
        }
        waypoint = 0;
    }
    else if (saveWalker_Listbox->SelectedIndex != -1)
    {
        string myText;
        string fileName = msclr::interop::marshal_as<string>(System::Convert::ToString(saveWalker_Listbox->Items[saveWalker_Listbox->SelectedIndex]->ToString()));
        ifstream save("Waypoints/" + fileName);
        walker_Listbox->Items->Clear();
        while (getline(save, myText))
        {
            walker_Listbox->Items->Add(msclr::interop::marshal_as<String^>(myText));
        }
        waypoint = 0;
    }
}


void easyBot::main_form::addWaypoint(System::Object^ sender, System::EventArgs^ e)
{
    DWORD myPosition = ReadPointer(0x004F4904, { 0x20, 0x0C });
    short int myX = (short int)*(short int*)myPosition;
    short int myY = (short int)*(short int*)(myPosition + 0x02);
    if (walkerActions_ComboBox->Items[walkerActions_ComboBox->SelectedIndex]->ToString() != "Sleep")
    {
        if (*(uint32_t*)myPosition != 0)
            walker_Listbox->Items->Add(walkerActions_ComboBox->Items[walkerActions_ComboBox->SelectedIndex]->ToString() + "| X = " + myX + " Y = " + myY);
    }
    else
    {
        walker_Listbox->Items->Add(walkerActions_ComboBox->Items[walkerActions_ComboBox->SelectedIndex]->ToString() + "|" + walkerAction_TextBox->Text->ToString());
    }
}
//###################### StartWalker ######################
void easyBot::main_form::startWalkerBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
    double timer = 0;

    short int myX;
    short int myY;

    short int mapY;
    short int mapX;

    DWORD myPosition;
    String^ walkerOption;

    myPosition = ReadPointer(0x004F4904, { 0x20, 0x0C });


    while (!walkerBot_Worker->CancellationPending)
    {
        if (state == 0)
        {
            if ((int)walker_Listbox->Items->Count > 0)
            {
                walker_Listbox->SetSelected(waypoint, TRUE);
                walkerOption = System::Convert::ToString(walker_Listbox->Items[waypoint]->ToString()->Split('|')[0]);
                if (walkerOption != "Sleep")
                {
                    mapX = System::Convert::ToInt32(walker_Listbox->Items[waypoint]->ToString()->Split('=')[1]->Substring(1)->Split('Y')[0]);
                    mapY = System::Convert::ToInt32(walker_Listbox->Items[waypoint]->ToString()->Split('Y')[1]->Substring(2));
                    myX = *(short int*)myPosition;
                    myY = *(short int*)(myPosition + 0x02);
                    while (myX != mapX || myY != mapY)
                    {
                        myX = *(short int*)myPosition;
                        myY = *(short int*)(myPosition + 0x02);
                        if (timer > 0.3)
                        {
                            if (moveAttackPartner_CheckBox->Checked)
                                MovePetPartner(mapY * 65536 + mapX, 1);
                            if (moveAttackPet_CheckBox->Checked)
                                MovePetPartner(mapY * 65536 + mapX, 0);
                            MoveTo(mapY * 65536 + mapX);
                            timer = 0;
                        }
                        timer += 0.01;
                        Sleep(10);
                    }
                    if (waypoint < (unsigned int)walker_Listbox->Items->Count - 1)
                    {
                        ++waypoint;
                    }
                    else
                    {
                        waypoint = 0;
                    }
                }
                else
                {
                    mapX = System::Convert::ToInt32(walker_Listbox->Items[waypoint]->ToString()->Split('|')[1]);
                    Sleep(mapX);
                    if (waypoint < (unsigned int)walker_Listbox->Items->Count - 1)
                    {
                        ++waypoint;
                    }
                    else
                    {
                        waypoint = 0;
                    }
                }
                if(walkerOption != "Lure")
                    state = 1;
            }
            else
            {
                state = 1;
            }
        }
        Sleep(10);
    }
}