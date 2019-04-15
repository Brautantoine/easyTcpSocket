#ifndef EASYTCPCLIENT
#define EASYTCPCLIENT

#include <string>
#include <thread>
#include <queue>
#include <mutex>

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define UNBINDED_SOCKET -1

class tcp_client
{
  public:
    tcp_client();
    tcp_client(std::string ip_addr,int port_number);
    virtual ~tcp_client();


    void connect_to_remote(std::string ip_addr,int port_number);
    void Disconnect();

    // Basic methods
    virtual void Send(std::string msg);
    std::string Receive(int maxSize=1024);

    // Advanced methods - WIP
    //void force_disconnect();
    //void start_bufferized_reception();
    //void stop_bufferized_reception();
    //std::string get_message();
    //void clean_rx_buffer(){clear_queue(reception_buffer);}
    //bool buffer_empty(){return reception_buffer.empty();}
    //std::queue<std::string> get_buffer(){return reception_buffer;}

    // Status methods
    bool get_connect_status(){return sender_alive;}
    std::string get_remote_ip(){return remote_ip_addr;}
    int get_remote_port(){return remote_port_number;}

    static int nb_client;
    static int get_nb_client(){return nb_client;}

  protected:
    //

  private:

    void connect_to_remote();

    void kill_thread();

    void sender_loop();
    void receiver_loop();

    int tcp_socket;
    std::string remote_ip_addr;
    int remote_port_number;

    std::thread sender_task;
    std::thread receiver_task;

    std::unique_lock<std::mutex> tx_lock;

    bool sender_alive;
    bool receiver_alive;

    std::queue<std::string> reception_buffer;
    std::queue<std::string> emmission_buffer;

    void clear_queue(std::queue<std::string>& q){std::queue<std::string> n;std::swap(q,n);}
};

#endif // EASYTCPCLIENT
