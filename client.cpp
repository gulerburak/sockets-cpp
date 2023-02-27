// client
#define PORT 8080
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char const **argv)
{
    char *data_to_send;
    if (argc < 2)
        data_to_send = (char *)"empty";
    else
        data_to_send = (char *)argv[1];

    int client_fd, status, valread;
    struct sockaddr_in address;
    char buffer[1024];

    // create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    // convert ip address to binary
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0)
    {
        perror("invalid address");
        return -1;
    }

    // connect to the socket
    if ((status = connect(client_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
    {
        perror("connect");
        return -1;
    }
    send(client_fd, data_to_send, strlen(data_to_send), 0);

    read(client_fd, buffer, 1024);
    std::cout << "Received data from server: " << buffer << std::endl;
    memset(buffer, '\0', sizeof(buffer)); // empty the buffer

    close(client_fd);
    return 0;
}
