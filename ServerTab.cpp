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
void easyBot::main_form::startServerBot_thread(Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
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
        listen(serverSocket, 5);
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            return;
        }
        while (true)
        {
            uint32_t net_num = htonl(*(uint32_t*)ReadPointer(0x004F4904, { 0x20, 0x0C }));
            send(clientSocket, reinterpret_cast<char*>(&net_num), sizeof(net_num), 0);
            Sleep(500);
        }
    }
    if (client_CheckBox->Checked)
    {
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket < 0) {
            return;
        }
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            return;
        }
        char buffer[sizeof(uint32_t)]; // Buffer to store the received bytes
        int bytesReceived = 0;
        while (true)
        {
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0); // Receive data
            if (bytesReceived > 0) {
                uint32_t net_num;
                memcpy(&net_num, buffer, sizeof(net_num)); // Copy from buffer to uint32_t variable
                uint32_t num = ntohl(net_num);
                MoveTo(num);
            }
        }
    }
}