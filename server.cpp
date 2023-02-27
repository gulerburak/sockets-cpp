// server
#define PORT 8080
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

int main(int argc, char **argv)
{

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen;
    char *data_to_send;

    int opt = 1;
    char buffer[1024];

    // create socket on localhost with TCP
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket is created" << std::endl;

    // to help to manipulate options for the socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    addrlen = sizeof(address);

    // bind socket to address and port
    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Bind is succesful" << std::endl;

    std::cout << "Listening..." << std::endl;

    for (;;) // listen and accept till close
    {
        // start to listen
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, 1024);
        std::cout << "Received data from client: " << buffer << std::endl;
        memset(buffer, '\0', sizeof(buffer)); // empty the buffer

        strcpy(data_to_send, "Message succesfully received by server");
        send(new_socket, data_to_send, strlen(data_to_send), 0);
    }

    return 0;
}