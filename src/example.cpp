#include "easyTcpServer.hpp"

int main(int argc, char** argv)
{
  tcp_server serv(argv[1],4343);
  std::cout << "start echo serv V3" << '\n';
  while(1)
  {
    if(!serv.get_new_client_fifo()->empty())
    {
      std::cout << "welcome to the new client" << '\n';
      serv.send_to_client(serv.get_new_client_fifo()->front(),"Welcome on the echo serv V3");
      serv.get_new_client_fifo()->pop();
    }
    for(int i=0; i<serv.get_client()->size();i++)
    {
      if(serv.get_client()->at(i).readable)
      {
        std::cout << "echo to client : " << i << " - " << serv.get_client()->at(i).msg.front().c_str() << '\n';
        serv.send_to_client(serv.get_client()->at(i),serv.get_client()->at(i).msg.front().c_str());
        serv.get_client()->at(i).readable --;
        serv.get_client()->at(i).msg.pop();
      }
    }
  }
  return 0;
}
