#pragma once
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
        main_form(void(*lpMoveTo)(void), void(lpAttackMonster(uint32_t)))
        {
            InitializeComponent();
            this->Width = 700;
            this->Height = 700;
            this->Text = "KrawczorBot";
            //this->attackMonster = lpAttackMonster;
        }
        ~main_form()
        {
            if (components)
            {
                delete components;
            }
        }
    private:
        void(*attackMonster)(uint32_t);

        System::ComponentModel::BackgroundWorker^ attackWorker;

        System::ComponentModel::Container^ components; //Required designer variable.
        System::Windows::Forms::ListBox^ monsterList;
        System::Windows::Forms::ListBox^ attackMonsterList;

        System::Windows::Forms::Button^ refreshMonsterList;
        System::Windows::Forms::Button^ addMonster;

        System::Windows::Forms::Label^ labelMonsterList;
        System::Windows::Forms::Label^ labelMonsterAttack;



        void InitializeComponent(void)
        {
            //################ Background Workers ####################
            attackWorker = gcnew System::ComponentModel::BackgroundWorker();
            attackWorker->WorkerSupportsCancellation = true;
            attackWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &main_form::startBotWorker);


            //######################## Labels #######################
            labelMonsterList = gcnew System::Windows::Forms::Label();
            labelMonsterList->Width = 250;
            labelMonsterList->Height = 25;
            labelMonsterList->Location = Point(500, 270);
            labelMonsterList->Text = "Monsters On The Map";
            this->Controls->Add(labelMonsterList);


            labelMonsterAttack = gcnew System::Windows::Forms::Label();
            labelMonsterAttack->Width = 250;
            labelMonsterAttack->Height = 25;
            labelMonsterAttack->Location = Point(250, 270);
            labelMonsterAttack->Text = "Monsters To Attack";
            this->Controls->Add(labelMonsterAttack);
            //###################### ListBoxes ######################

            attackMonsterList = gcnew System::Windows::Forms::ListBox();
            attackMonsterList->Size = System::Drawing::Size(150, 300);
            attackMonsterList->Location = Point(250, 300);
            attackMonsterList->DoubleClick += gcnew EventHandler(this, &main_form::removeMonsterFromList);
            this->Controls->Add(attackMonsterList);

            monsterList = gcnew System::Windows::Forms::ListBox();
            monsterList->Size = System::Drawing::Size(150, 300);
            monsterList->Location = Point(500, 300);
            monsterList->DoubleClick += gcnew EventHandler(this, &main_form::addMonsterToList);
            this->Controls->Add(monsterList);

            //###################### Buttons ########################
            refreshMonsterList = gcnew System::Windows::Forms::Button();
            refreshMonsterList->Location = Point(500, 600);
            refreshMonsterList->Width = 100;
            refreshMonsterList->Height = 30;
            refreshMonsterList->Text = "Refresh";
            refreshMonsterList->Click += gcnew EventHandler(this, &main_form::refreshList);
            this->Controls->Add(refreshMonsterList);

            addMonster = gcnew System::Windows::Forms::Button();
            addMonster->Location = Point(0, 500);
            addMonster->Width = 75;
            addMonster->Height = 25;
            addMonster->Text = "Start Bot";
            addMonster->BackColor = Color::Green;
            addMonster->Click += gcnew EventHandler(this, &main_form::startBot);
            this->Controls->Add(addMonster);

            //###################### Entities ########################

        }
        /*
        System::Void main_form_Load(System::Object^ sender, System::EventArgs^ e) 
        {
            this->attackWorker->RunWorkerAsync();
        }
        */
        System::Void main_form_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) 
        {
            this->attackWorker->CancelAsync();
        }
        
        //###################### Refresh Monster List Button ######################
        System::Void refreshList(System::Object^ sender, System::EventArgs^ e)
        {
            uint32_t x;
            bool found = 0;

            EntityList* monsters[18];
            monsters[0] = (EntityList*)0x0CCCBF40;
            for (int i = 1; i < 18; ++i)
            {
               monsters[i] = (EntityList*)(*monsters + i);
            }
            for (int i = 0; i < 18; ++i)
            {
                x = monsters[i]->monsterID;
                x = *(uint32_t*)(x + 0x1BC);
                x = *(uint32_t*)(x + 0x04);

                for (int tmp = 0; tmp < (int)this->monsterList->Items->Count; ++tmp)
                {
                    if (gcnew System::String(((const char*)x)) == (this->monsterList->Items[tmp]->ToString()))
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    this->monsterList->Items->Add(gcnew System::String(((const char*)x)));
                }
                found = 0;
            }
        }

        System::Void addMonsterToList(Object^ sender, EventArgs^ e)
        {
            if (monsterList->SelectedItem != nullptr)
            {
                this->attackMonsterList->Items->Add(monsterList->SelectedItem->ToString());
            }
        }

        System::Void removeMonsterFromList(Object^ sender, EventArgs^ e)
        {
            if (this->attackMonsterList->SelectedItem != nullptr)
            {
                this->attackMonsterList->Items->Remove(attackMonsterList->SelectedItem);
            }
        }
        System::Void startBot(Object^ sender, EventArgs^ e)
        {
            this->attackWorker->RunWorkerAsync();
            addMonster->BackColor = Color::Red;
            addMonster->Text = "Stop Bot";
        }    
        
        System::Void startBotWorker(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
        {
            EntityList* monsters[18];
            monsters[0] = (EntityList*)0x0D57C000;
            uint32_t monsterPosX = 0;
            uint32_t monsterPosY = 0;
            uint32_t x;
            for (int i = 0; i < 18; ++i)
                (*(monsters + i)) = (EntityList*)(*monsters + i);
            while (!this->attackWorker->CancellationPending)
            {
                uint32_t myPos = *(uint32_t*)0x02C9DB1C;
                uint32_t myPosX = (myPos >> 16) & 0xFFFF;
                uint32_t myPosY = myPos & 0xFFFF;
                for (int i = 0; i < 18; ++i)
                {
                    x = (*monsters + i)->monsterID;
                    x = *(uint32_t*)(x + 0xC);
                    monsterPosX = (x >> 16) & 0xFFFF;
                    monsterPosY = x & 0xFFFF;
                    if (abs(int(myPosX - monsterPosX)) <= 3 && abs(int(myPosY - monsterPosY)) <= 3)
                    {
                        AttackMonster((*monsters + i)->monsterID);
                        System::Threading::Thread::Sleep(3000);
                    }
                }
            }
            System::Console::WriteLine("Koniec");
            system("pause");
        }
        
    };
}
