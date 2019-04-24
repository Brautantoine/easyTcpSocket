#include "easyTcpClient.hpp"

int tcp_client::nb_client=0;

tcp_client::tcp_client()
{
  //std::cout << "constructor ..." << '\n';
  tcp_socket=UNBINDED_SOCKET;
  sender_alive = false;
  receiver_alive = false;

  nb_client++;
}
tcp_client::tcp_client(std::string ip_addr,int port_number)
{
  remote_ip_addr = ip_addr;
  remote_port_number = port_number;
  tcp_socket=UNBINDED_SOCKET;
  sender_alive = false;
  receiver_alive = false;
  //std::cout << "advanced constructor ..." << '\n';
  connect_to_remote();
}

tcp_client::~tcp_client()
{
  Disconnect();
  nb_client--;
}

void tcp_client::connect_to_remote()
{
  struct sockaddr_in server_info;
  struct in_addr ip_addr;

  //std::cout << "connection ..." << '\n';
  if(tcp_socket==UNBINDED_SOCKET)
  {
    //std::cout << "creating socket ..." << '\n';
    clear_queue(reception_buffer);

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

    sender_alive = true;
    sender_task = std::thread(&tcp_client::sender_loop,this);
    //std::cout << "connected" << '\n';
  }


}
void tcp_client::connect_to_remote(std::string ip_addr,int port_number)
{
  if(tcp_socket != UNBINDED_SOCKET)
    throw std::runtime_error("Socket already binded, do you have an active connection yet ?");

  remote_ip_addr = ip_addr;
  remote_port_number = port_number;

  connect_to_remote();
}

void tcp_client::Send(std::string msg)
{
  std::unique_lock<std::mutex> lock(tx_lock);
  emmission_buffer.emplace(msg);
  lock.unlock();
}

void tcp_client::sender_loop()
{
  //std::cout << "thread started ..." << '\n';
  while(sender_alive)
  {
    if( (tcp_socket != UNBINDED_SOCKET) && (!emmission_buffer.empty()) )
    {
      std::string buffer;

      std::unique_lock<std::mutex> lock(tx_lock);
      buffer = emmission_buffer.front();
      emmission_buffer.pop();
      lock.unlock();
      //std::cout << "sending ..." << '\n';
      if(send(tcp_socket, buffer.c_str(), buffer.size(), 0) < 0)
      {
          // To Do exception
      }
    }
  }
}

void tcp_client::Disconnect()
{
  kill_thread();
  close(tcp_socket);
}

void tcp_client::kill_thread()
{
  //std::cout << "disconnect" << '\n';
  while(!emmission_buffer.empty());
  sender_alive=false;
  receiver_alive=false;
  sender_task.join();
  //receiver_task.join();
}

std::string tcp_client::Receive(int maxSize)
{
  std::string ret;
  if(tcp_socket != UNBINDED_SOCKET)
  {

    char buffer[maxSize];
    int bytesReceived;
    memset(&buffer[0], 0, sizeof(buffer));
    bytesReceived = recv(tcp_socket, buffer, maxSize, 0);
    if(bytesReceived < 0)
      throw std::runtime_error("Error while receiving."); // TO UP
    buffer[bytesReceived]='\0';
    ret = buffer;
  }
  return ret;
}
