#include "easyTcpClient.hpp"

int main()
{
  std::string msg;
  tcp_client tcp("localhost",4242);
  while(1)
  {
    std::cin >> msg;
    tcp.Send(msg);
    std::cout << tcp.Receive() << '\n';
  }
  return 0;
}
