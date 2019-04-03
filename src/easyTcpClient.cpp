#include "easyTcpClient.hpp"

int tcp_client::nb_client=0;

tcp_client::tcp_client()
{
  tcp_socket=UNBINDED_SOCKET;
  //connected = false;
  sender_alive = true;
  receiver_alive = false;
  //to_send = false;

  //std::thread sender_task;
  //std::thread receiver_task;

  nb_client++;
}
tcp_client::tcp_client(std::string ip_addr,int port_number)
{
  remote_ip_addr = ip_addr;
  remote_port_number = port_number;

  tcp_socket=UNBINDED_SOCKET;
  //connected = false;
  sender_alive = true;
  receiver_alive = false;
  //to_send = false;

  connect_to_remote();
  // TO DO start the thread in connect()

  nb_client++;
}

tcp_client::~tcp_client()
{
  disconnect();
  nb_client--;
}

void tcp_client::connect_to_remote()
{
  struct sockaddr_in server_info;
  struct in_addr ip_addr;

  if(tcp_socket==UNBINDED_SOCKET)
  {
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket==UNBINDED_SOCKET)
      throw std::runtime_error("Error while creating socket\n"); // To up

    if(!inet_aton(remote_ip_addr.c_str(), &ip_addr))                            // Exit with 0 on fail
    {
      struct hostent* dns_resolve;
      dns_resolve = gethostbyname(remote_ip_addr.c_str());
      if(dns_resolve == NULL)
        throw std::runtime_error("Error while resolving hostname.\n"); // To up
      server_info.sin_addr = **((struct in_addr**)dns_resolve->h_addr_list);
    }
    else
    {
      server_info.sin_addr = ip_addr;
    }

    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(remote_port_number);

    if (connect(tcp_socket, (struct sockaddr *)&server_info, sizeof(server_info)) == -1)
      throw std::runtime_error("Error while connnecting to remote\n"); // To up
  }

}
