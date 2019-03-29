#ifndef EASYTCPCLIENT
#define EASYTCPCLIENT

#include <string>
#include <thread>
#include <queue>

class tcp_client
{
  public:
    tcp_client();
    tcp_client(std::string ip_addr,int port_number);
    virtual ~tcp_client();

    void connect(std::string ip_addr,int port_number);
    void disconnect();

    void send(std::string msg);
    std::string receive(int maxSize=1024);

    template <class T> T freceive(int maxSize=1024);

    static int nb_client;
    
  private:

    std::string remote_ip_addr;
    int remote_port_number;

    std::thread sender_task;
    std::thread receiver_task;

    bool connected;
    bool alive;
    bool to_send;

    std::queue<std::string> reception_buffer;



};

#endif // EASYTCPCLIENT
