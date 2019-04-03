#ifndef FORMATTEDEASYTCPCLIENT
#define FORMATTEDEASYTCPCLIENT

//** WIP DONT USE IT **//

#include "easyTcpClient.hpp"
#include <string>
#include <thread>
#include <queue>

template <class T>
class ftcp_client : public tcp_client
{
  public:
    ftcp_client();
    ftcp_client(std::string ip_addr,int port_number);
    virtual ~ftcp_client();

    T receive(int maxSize=1024){return freceive(maxSize);}
    T freceive(int maxSize=1024);

  protected:
    //

  private:

    std::string remote_ip_addr;
    int remote_port_number;

    std::thread sender_task;
    std::thread receiver_task;

    bool connected;
    bool alive;
    bool to_send;

    std::queue<T> formatted_buffer_queue;
};

#endif // FORMATTEDEASYTCPCLIENT
