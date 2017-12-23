## socket 地址api
### 主机字节序和网络字节序
**大端字节序和小端字节序**
- 大端字节序:一个整数的高位字节(23-31bit)存储在内存的低地址处，低位字节(0-7bit)存在内存的高地址处
- 小端字节序正好相反

**现代pc多采用小端字节序, 又称为主机字节序, 而网络字节序为大端字节序**

发送端总是把要发送的数据转化成大端字节序数据后在发送,而接收端可以根据自身采用的字节序决定是否要对接受的数据进行数据转换;
```
#include <netinet/in.h>
unsigned long int htonl(unsigned long int hostlong); // host to network long
unsigned short int htons(unsigned short int hostshort); // host to network short
unsigned long int ntohl(unsigned long int netlong); // network to host long
unsigned short int ntohs(unsigned short int netshort); // network to host short
```

### 通用的socket地址
socket 网络编程接口中表示socket地址的是结构体sockaddr
```
#include <bits/socket.h>
struct sockaddr {
    sa_family_t sa_family;
    char sa_data[14];
}
```
sa_family是地址族(sa_family_t)类型的变量．地址族类型通常与协议族类型对应，常见的协议族和地址族对应关系如下:
|协议族|地址族|描述|
|-|-|-|
|PF_UNIX|AF_UNIX|UNIX本地域协议族|
|PF_INET|AF_INET|TCP/IPv4协议族|
|PF_INET_6|AF_INET_6|TCP/IPv6协议族|

sa_data成员用于存放socket地址值;不同的协议族地址值具有不同的意义和长度
|协议族|地址值含义和长度|
|-|-|
|PF_UNIX|文件路劲名，108字节|
|PF_INET|16bit端口号，32bit IPv4地址，共6字节|
|PF_INET_6|16big端口号，32bit流标识，128bit　IPv6地址，32bit范围id,共26字节|

### 专用socket地址
```
#include <sys/un.h>
struct socketaddr_un {
  sa_family_t sa_family;
  char sun_path[108];
};
```
tcp/ip有专用的结构体，socketaddr_in, socketaddr_in6
```
struct sockaddr_in {
  sa_family_t sin_family; //协议族AF_INET
  u_int16_t sin_port;　//端口号
  struct in_addr sin_addr;
};

struct in_addr {
  u_int_32_t s_addr; // 32位ipv4地址
};

struct socketaddr_in6 {
  sa_family_t sa_family;　//协议族类型AF_INET_6
  u_int16_t sin6_port; //16位端口号
  u_int32_t sin6_flowinfo; //32bit流信息，应设置为0
  struct in6_addr sin6_addr; // 128位ipv6
  u_int32_t sin6_scope_id; //32bit 范围id
};

struct in6_addr{
   unsigned char sa_addr[16]; // ipv6地址，16*8=128bit
};
```
### ip地址转化函数
```
#include <arpa/inet.h>
in_addr_t inet_addr(const char * strptr); // 字符串转in_addr_t
int inet_aton(const char *strptr, in_addr * in); // 字符串转in_addr
char * inet_ntoa(in_addr * in); // in_addr 转字符串
```

```
char *szValue1 = inet_ntoa("1.2.3.4");
char *szValue2 = inet_ntoa("10.194.71.60");
printf("address 1:%s\n", szValue1);
printf("address 1:%s\n", szValue2);
```
适用于ipv4和ipv6
```
#include <arpa/inet.h>
int inet_pton(int af, const char * src, void *dts); // af协议族，src地址，dts网络字节序整数
const char * inet_ntop(int af, const void *src, char * dts, sockelent_t cnt);　// 与上面相反

// sockelent_t cnt
#include <netinet/in.h>
#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46
```
## 创建socket
```
#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
// domain 系统使用那个地城协议族．对tcp/ip,PF_INET, PF_INET6,对于unix本地PF_UNIX.
// type 制定服务类型．SOCKET_STREAM(数据流服务/ tcp)和SOCEKT_UGRAM(数据报服务 udp)
// type可以接受上述服务类型之外还可以接受两个标识:SOCK_NONBLOCK(非阻塞)和SOCK_CLOEXEC(用fork调用创建子进程时在子进程中关闭该socket).
// protocol在前两个参数构成的协议集合下，再选择一个具体的协议．通常使用0,表示默认协议
```
## socket绑定地址
```
#include <sys/types.h>
#include <sys/socket.h>
int bind(int socketfd, const struct sockadd* my_addr, sockelent_t addrlen);
```
## 监听socket
```
#include <sys/socket.h>
int listen(int sockfd, int backlog); // backlog:最大连接数
```
