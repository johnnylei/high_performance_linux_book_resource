## abstract
- linux服务器一般以后台进程形式运行．后台程序又称之为守护进程(daemon),守护进程的父进程通常是init进程(PID=1)
- 日志系统
  - 输出到文件
  - 输出到udp服务器
  - 大部分进程都在/var/log目录下面记录自己的日志目录(root:syslog)
- linux服务器一般已某个专门的非root身份运行，eg:mysqld, httpd, syslogd, 等后台进程，分别拥有自己的运行账户，mysql,apache,syslog
- linux服务器通常是可以配置的，配置文件通常/etc下面
- liunx服务器进程通常会在启动的时候生成一个pid文件，并存入/var/run目录中，以记录该后台进程的pid,比如syslogd的pid文件是/var/run/syslogd.pid
- linux服务器进程通常需要考虑系统资源和限制，以预测自身能承受多大负荷，比如进程可用文件描述副总数和内存总量

![img_1](https://github.com/johnnylei/high_performance_linux_book_resource/blob/master/resource/Screenshot%20from%202018-03-07%2013-24-26.png?raw=true)
## 日志
linux 提供的守护进程是syslogd, 现在用升级版rsyslogd

### syslog函数
应用程序使用syslog函数与rsyslogd守护进程通信
```
#include <syslog.h>
void syslog(int priority, const char * message, ...);
void openlog(const char * ident, int logopt, int facility); // facility:设备，容易，能力
int setlogmask(int maskpri);
void closelog();
```

## 用户信息
#### UID, EUID(有效用户id), GID(真实组id), EGID(有效组ID)
```
#include <sys/types.h>
#include <unistd.h>

uid_t getuid();
uid_t geteuid();
gid_t getgid();
get_t getegid();
int setuid(uid_t uid);
int seteuid(uid_t uid);
int setgid(gid_t gid);
int setegid(gid_t gid);
```
一个进程拥有两个用户id:UID 和EUID

## 进程间关系
### 进程组
进程有进程组，因此除了有pid以外还有pgid
```
pid_t getpgid(pid_t pid);
int setpgid(pid_t pgid);
```

### 会话
