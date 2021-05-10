// КЛИЕНТ ДЛЯ СЕРВЕРА

#include "Client.h"

const char *PORT = "3490";         // порт, к которому будет подключаться клиент
const int MAXDATASIZE = 100;       // максимальное количество байт, которое мы можем получить за раз от сервера
const char *IP = "84.201.189.157"; // клиент коннектится к хосту с глобальным IP 84.201.189.157

// получаем тип адреса сокета, IPv4 или IPv6:
void *get_in_addr(struct sockaddr *sa)
{

    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void thread_inf_recv(std::queue<std::string> &recv_buf, int sockfd)
{
    while (true)
    {
        // sleep(1);
        std::string out;
        char buf_to_send[MAXDATASIZE];
        if (recv(sockfd, buf_to_send, MAXDATASIZE, 0) == -1)
        {
            perror("client: recv");
            exit(1);
        }
        out = std::string(buf_to_send);
        recv_buf.push(out);
    }
}

Client::Client()
{
    sockfd = -1;
    // подключаем его сразу к серверу
    connect_Client();
    // читаем начальные данные
    char buf_to_send[MAXDATASIZE];
    if (recv(sockfd, buf_to_send, MAXDATASIZE, 0) == -1)
    {
        perror("client: recv");
        exit(1);
    }
    seed = atoi(&buf_to_send[2]);
    id = buf_to_send[0] - '1';
    // делаем отдельный поток, который будет бесконечно считывать и записывать в очередь recv_buf сообщения от сервера
    std::thread thr(thread_inf_recv, std::ref(recv_buf), sockfd);
    thr.detach();
}

Client::~Client()
{
    close(sockfd);
}

void Client::connect_Client()
{
    char s[INET6_ADDRSTRLEN];             // максимальный размер адреса сервера
    struct addrinfo hints, *servinfo, *p; // нужно для функции getaddrinfo(), которая позволит заполнить инфу по клиенту в servinfo
    int rv;

    // заполняем hints (начальные данные)
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // можно любой тип : Ipv4 или Ipv6
    hints.ai_socktype = SOCK_STREAM; // сокет - потоковый

    // заполняем всю инфу про наш клиент в list servinfo и сразу проверяем на ошибки. Указываем хост IP
    if ((rv = getaddrinfo(IP, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    // цикл по всем результатам и подключение к первому подходящему
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        // открываем сокет для подключения и сразу делаем проверку
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }

        // делаем сразу connect. Нам не нужно ничего биндить, тк нам не важно с какого порта клиент подключается, нам важно знать только порт сервера.
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        exit(2);
    }

    // записываем сетевой адрес к чему подключаемся в массив символов char s[max_size]
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connected to %s\n", s);

    freeaddrinfo(servinfo);
}

void Client::send_Client(std::string s)
{
    char buf_to_send[MAXDATASIZE];
    strcpy(buf_to_send, s.c_str());
    if (send(sockfd, buf_to_send, MAXDATASIZE, 0) == -1)
    {
        perror("client: send");
    }
}

void Client::test_Client()
{

    if (sockfd == -1)
    {
        perror("client: not initialized soket for server connection\n");
        exit(1);
    }

    while (recv_buf.empty() == true)
    {
        sleep(1);
    }

    std::cout << recv_buf.front() << std::endl;
    std::string buf = recv_buf.front();
    recv_buf.pop();

    // определяем в зависимости от прав действия
    if (buf == "New Step; you have rights to read and write")
    {
        while (true)
        {
            std::string buf1;
            getline(std::cin, buf1);
            send_Client(buf1);
        }
    }
    else
    {
        while (true)
        {
            sleep(1);
            if (recv_buf.empty() == false)
            {
                std::cout << recv_buf.size() << std::endl;
                std::cout << "another user sended : " << recv_buf.front() << std::endl;
                recv_buf.pop();
            }
        }
    }
}