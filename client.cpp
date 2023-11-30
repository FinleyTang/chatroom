#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

int main(){
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket <0){
        std::cerr<< "Error creat client socket " <<std::endl;
        return 1;
    }

    struct hostent* server = gethostbyname("localhost");
    if (server == NULL) {
        std::cerr << "Error, no such host" << std::endl;
        return 1;
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0 , sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    strcpy((char*)server->h_addr,  (char*)&server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(8888);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error connecting" << std::endl;
        return 1;
    }

    char buffer[256];
    int n;

    // Send data to the server
    while (true){
//        std::string message = "Hello, server!";
        std::string message;
//        std::cin >> message;
        std::getline(std::cin, message);
        memset(buffer, 0, 256);
        strncpy(buffer, message.c_str(), sizeof(buffer));

        n = write(client_socket, buffer, strlen(buffer));
        if (n < 0) {
            std::cerr << "Error writing to socket" << std::endl;
            return 1;
        }

        // Receive data from the server
        memset(buffer, 0, 256);
        n = read(client_socket, buffer, 255);
        if (n < 0) {
            std::cerr << "Error reading from socket" << std::endl;
            return 1;
        }
        std::cout << "Received: " << buffer << std::endl;
    }

    close(client_socket);










}