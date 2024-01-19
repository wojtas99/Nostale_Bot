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
}

void easyBot::main_form::ListFilesInFolder(const std::wstring& folderPath) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((folderPath + L"\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Nie mo�na znale�� plik�w w folderze: " << folderPath << std::endl;
        return;
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            saveWalker_Listbox->Items->Add(msclr::interop::marshal_as<String^>(findFileData.cFileName));
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}
void easyBot::main_form::walkerActions_ComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
    if (walkerActions_ComboBox->SelectedItem != nullptr && walkerActions_ComboBox->SelectedItem->ToString() == "Walk")
    {
        walkerAction_TextBox->Enabled = false;
    }
    else
    {
        walkerAction_TextBox->Enabled = true;
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
void easyBot::main_form::addWaypoint(System::Object^ sender, System::EventArgs^ e)
{
    DWORD myPosPointer = ReadPointer(0x004C4E4C, { 0x560, 0x1C, 0x10, 0xB60, 0x0C });
    short int myX = (short int)*(short int*)myPosPointer;
    short int myY = (short int)*(short int*)(myPosPointer + 0x02);
    if (*(uint32_t*)myPosPointer != 0)
        walker_Listbox->Items->Add("X = " + myX + " Y = " + myY);
}
//###################### StartWalker ######################
void easyBot::main_form::startWalkerBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
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
    MoveTo(mapY * 65536 + mapX);
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