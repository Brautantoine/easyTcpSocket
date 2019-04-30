#include "uniquesendertask.hpp"


void unique_sender_task::init_thread()
{
  static auto init = false;
  if( ! init)
  {
    init=true;
    sender_alive = true;
    thread_handler = std::thread(&unique_sender_task::sender_loop,this);
  }
}

void unique_sender_task::kill_thread()
{
  while(!emmission_buffer.empty());
  sender_alive=false;
  thread_handler.join();
}

void unique_sender_task::push_message(std::string msg, int socket, std::mutex& socket_lock)
{
  std::unique_lock<std::mutex> lock(tx_lock);
  emmission_buffer.emplace(message_request(msg,socket,socket_lock));
  tx_lock.unlock();
}
void unique_sender_task::push_message(const message_request& msg)
{
  std::unique_lock<std::mutex> lock(tx_lock);
  emmission_buffer.emplace(msg);
  tx_lock.unlock();
}

void unique_sender_task::sender_loop ()
{
  std::cout << "sender started ..." << '\n';
  while(sender_alive)
  {
    if( !emmission_buffer.empty() )
    {
      //message_request buffer;

      std::unique_lock<std::mutex> lock(tx_lock);
      message_request buffer = emmission_buffer.front();
      emmission_buffer.pop();
      lock.unlock();
      //std::cout << "sending ..." << '\n';
      std::unique_lock<std::mutex> sock_lock(buffer.socket_lock);
      if( ! (buffer.socket == UNBINDED_SOCKET) )
      {
        if(send(buffer.socket, buffer.msg.c_str(), buffer.msg.size(), 0) < 0)
        {
            // To Do exception
        }
      }
      sock_lock.unlock();

    }
  }
}
