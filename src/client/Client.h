#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <queue>
#include <thread>

class Client
{
public:
    Client();
    ~Client();
    void connect_Client();
    void send_Client(std::string s);
    void test_Client();
    std::queue<std::string> recv_buf; // очередь с сообщениями от сервера
    int seed, id;

private:
    int sockfd; // сокет для подключения
};