#ifndef EASYTCPCLIENT
#define EASYTCPCLIENT

#include <string>
#include <thread>
#include <queue>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <arpa/inet.h>

#define UNBINDED_SOCKET 1

class tcp_client
{
  public:
    tcp_client();
    tcp_client(std::string ip_addr,int port_number);
    virtual ~tcp_client();

    void connect_to_remote();
    void connect_to_remote(std::string ip_addr,int port_number);
    void disconnect();

    // Basic methods
    virtual void send(std::string msg);
    std::string receive(int maxSize=102);

    // Advanced reception methods
    void start_bufferized_reception();
    void stop_bufferized_reception();
    std::string get_first();
    std::string get_last();
    std::string clean_buffer();
    bool buffer_empty(){return reception_buffer.empty();}
    std::queue<std::string> get_buffer(){return reception_buffer;}

    // Status methods
    bool get_connect_status(){return sender_alive;}
    std::string get_remote_ip();
    int get_remote_port();

    static int nb_client;
    static int get_nb_client(){return nb_client;}

  protected:
    //template <class T> T freceive(int maxSize=1024);

  private:

    void kill_thread();

    int tcp_socket;
    std::string remote_ip_addr;
    int remote_port_number;

    std::thread sender_task;
    std::thread receiver_task;

    //bool connected;
    bool sender_alive;
    bool receiver_alive;
    //bool to_send;

    std::queue<std::string> reception_buffer;
    std::queue<std::string> emmission_buffer;
};

#endif // EASYTCPCLIENT
