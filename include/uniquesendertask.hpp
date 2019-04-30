#ifndef UNIQUESENDERTASK
#define UNIQUESENDERTASK

#include <string>
#include <thread>
#include <queue>
#include <mutex>
//#include <shared_mutex>
#include <atomic>

#include <iostream>

#include <netinet/in.h>

#define UNBINDED_SOCKET -1

typedef struct _message_request
{

  std::string msg;
  int socket;
  std::mutex& socket_lock;

  //_message_request() {socket_lock = NULL;}
  _message_request(std::string nmsg, int nsocket, std::mutex& nsocket_loc ) : msg(nmsg), socket(nsocket), socket_lock(nsocket_loc) {}
  //_message_request(const _message_request& that) {}
} message_request;

class unique_sender_task
{
  public:
    static unique_sender_task& get_instance()
    {
      static unique_sender_task instance;

      return instance;
    }

    /* Deleted copy constructor */
    unique_sender_task (unique_sender_task const&)  = delete;
    void operator=(unique_sender_task const&)       = delete;

    void init_thread();
    void kill_thread();

    void push_message(std::string msg,int socket, std::mutex& socket_lock);
    void push_message(const message_request& msg);

  private:
    unique_sender_task () {}

    void sender_loop ();



    std::thread thread_handler;
    bool sender_alive;
    std::mutex tx_lock;
    //std::mutex socket_lock;

    std::queue<message_request> emmission_buffer;
};

#endif //UNIQUESENDERTASK
