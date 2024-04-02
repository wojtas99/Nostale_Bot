#include "gui.h"

void easyBot::main_form::InitializeServerTab(void)
{
    server_CheckBox = gcnew System::Windows::Forms::CheckBox();
    server_CheckBox->Location = Point(0, 82);
    server_CheckBox->Text = "Server";
    server_CheckBox->Width = 110;


    client_CheckBox = gcnew System::Windows::Forms::CheckBox();
    client_CheckBox->Location = Point(0, 122);
    client_CheckBox->Text = "Client";
    client_CheckBox->Width = 110;


    serverTab->Controls->Add(client_CheckBox);
    serverTab->Controls->Add(server_CheckBox);
}
void easyBot::main_form::startServerBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) 
{
    DWORD myPos = ReadPointer(0x004F4904, { 0x20, 0x0C });
    if (server_CheckBox->Checked)
    {
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            return;
        }
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            return;
        }
        listen(serverSocket, 10);
        int clientSocket = 0;
        while (!serverBot_Worker->CancellationPending)
        {
            clientSocket = accept(serverSocket, nullptr, nullptr);
            uint32_t net_num = htonl(*(uint32_t*)myPos);
            send(clientSocket, reinterpret_cast<char*>(&net_num), sizeof(net_num), 0);
        }
    }
    if (client_CheckBox->Checked)
    {
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        int clientSocket;
        char buffer[sizeof(uint32_t)];
        int bytesReceived = 0;
        uint32_t net_num = 0;
        while (!serverBot_Worker->CancellationPending)
        {
            clientSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (clientSocket < 0) {
                return;
            }
            bytesReceived = 0;
            connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0); // Receive data
            if (bytesReceived > 0)
            {
                net_num = *reinterpret_cast<uint32_t*>(buffer);
                MoveTo(ntohl(net_num));
            }
            closesocket(clientSocket);
            Sleep(500);
        }
    }
}