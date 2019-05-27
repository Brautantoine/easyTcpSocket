#ifndef EASYTCPSERVER
#define EASYTCPSERVER

#include <string>
#include <vector>
#include <queue>
#include <thread>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>

namespace easyTCP
{
  struct connectedClient
  {
    int socket;
    std::string ip_addr;
    int readable;                                                               // Pseudo Semaphore
    std::queue<std::string> msg;
  };

  const int MAXCONNECTIONS = 5;
}

using namespace easyTCP;

class tcp_server
{

  public:
    tcp_server();
    tcp_server(std::string ip_addr,int port_number);
    virtual ~tcp_server();

    void start_server(std::string ip_addr,int port_number);
    void stop_server();

    void send_to_client(int socket, std::string msg);

    std::vector<connectedClient> get_client(){ return clientTable;}

  protected:
    //

  private:

    void _start_listening();
    void _listen_for_client();

    std::vector<connectedClient> clientTable;

    std::string server_addr;
    int server_port;
    int server_socket;

    std::thread listener_task;


};

#endif // EASYTCPSERVER
