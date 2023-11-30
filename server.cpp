#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        std::cerr << "Error creat socket" <<std::endl;
        return  1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8888);
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
        std::cerr << "Error binding" <<std::endl;
        return  1;
    }

    listen(server_socket,5);
    std::cout << "Server is listening..." << std::endl;

    struct  sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket < 0){
        std::cerr << "Error accept" <<std::endl;
        return  1;
    }

    char buffer[256];
    int n;
    memset(buffer, 0, 256);
    while (true){
        n = read(client_socket, buffer,255);
        if (n < 0) {
            std::cerr << "Error reading from socket" << std::endl;
            return 1;
        }
        std::cout << "Received: " << buffer << std::endl;

// Send data back to the client
        n = write(client_socket, buffer, strlen(buffer));
        if (n < 0) {
            std::cerr << "Error writing to socket" << std::endl;
            return 1;
        }
    }

    close(client_socket);
    close(server_socket);

}