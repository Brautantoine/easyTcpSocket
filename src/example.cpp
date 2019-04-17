#include "easyTcpClient.hpp"

static tcp_client tcp("localhost",4242);

void rx_task()
{
  while(1)
    std::cout << tcp.Receive() << '\n';
}

int main()
{
  std::thread task1 (rx_task);
  std::string msg;
  //tcp_client tcp("localhost",4242);
  while(1)
  {
    std::cin >> msg;
    tcp.Send(msg);
    //std::cout << tcp.Receive() << '\n';
  }
  return 0;
}
