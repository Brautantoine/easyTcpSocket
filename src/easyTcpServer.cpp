#include "easyTcpServer.hpp"

tcp_server::tcp_server()
{

}
tcp_server::tcp_server(std::string ip_addr,int port_number)
{
  server_addr = ip_addr;
  server_port = port_number;

  _start_listening();
}

tcp_server::~tcp_server()
{

}

void tcp_server::start_server(std::string ip_addr,int port_number)
{
  server_addr = ip_addr;
  server_port = port_number;

  _start_listening();
}

void tcp_server::_start_listening()
{
  struct sockaddr_in _server;

  server_socket = socket(AF_INET,SOCK_STREAM,0);

  memset(&_server,0,sizeof(_server));

  _server.sin_family=AF_INET;
	_server.sin_addr.s_addr=htonl(INADDR_ANY);
  _server.sin_port=htons(server_port);

  bind(server_socket,(struct sockaddr *)&_server, sizeof(_server));
  listen(server_socket,easyTCP::MAXCONNECTIONS);

  
}

void tcp_server::_listen_for_client()
{

}

void tcp_server::stop_server()
{

}

void tcp_server::send_to_client(int socket, std::string msg)
{

}
