# What is easyTcpSocket - WIP #

Bassicaly it's a lib describing two class (the client one and the server one) to help you easyly implement tcp communication in your software


## Distribution ##

easyTcpSocket is based on some posix lib, so it's only available for linux.

It have been tested on the following distributions :
* Ubuntu 16.04 et 18.06
* OpenSTLinux
* Raspbian

## How to compile it ? ##

If you need a shared library, you will find the corresponding Makefile in the shared-lib branche.
```sh
make # invoke g++
```
You can use CXX=myCompiler to use a custom compiler.

## How to use it ? - client side ##

Just add the source file and the header to your project.

Then instance a tcp_client class, it will connect to the server at the same time
```c++
tcp_client client ("localhost",5320) // connect to localhost on port 5320
```

Once it's done you can send and receive message to/from the server with Send and
Receive method :
```c++
extern std::string msg;
std::string reply;

client.Send(msg); // Send the msg to the server
reply = client.Receive(); // Receive a message from the server
```

Example :
```c++
#include "easyTcpClient.hpp"

int main()
{
  std::string msg;
  tcp_client client("localhost",4242);
  while(1)
  {
    std::cin >> msg;
    client.Send(msg);
    std::cout << client.Receive() << std::endl;
  }
  return 0;
}
```

>**IMPORTANT** : Note that the Receive functions use recv wich bufferized the receptionned
message. By calling Receive you will get the oldest message received.

It is recommended to use Receive on a concurrent task. For example :
```c++
#include "easyTcpClient.hpp"

static tcp_client client("localhost",4242);

void rx_task()
{
  while(1)
    std::cout << client.Receive() << '\n';
}

int main()
{
  std::thread task1 (rx_task);
  std::string msg;
  while(1)
  {
    std::cin >> msg;
    tcp.Send(msg);
    //std::cout << client.Receive() << '\n';
  }
  return 0;
}
```

Some method will come to automatically to transfer the reception part on a separated thread.

>Don't forget to link against `pthread` or another parralel framework when you are using easyTcpSocket

## Contact ##

If you have any questions feel free to mail me : <antoine.braut@gmail.com>

**I hope this software will help you ! Have a nice day !**

<img src="https://images.ecosia.org/x8hEzRW0N0B1oHUTXqREorZ73aE=/0x390/smart/https%3A%2F%2Fcdn170.picsart.com%2Fupscale-241091004033212.png%3Fr1024x1024" alt="drawing" width="200"/>
