# [2016-2] 컴퓨터 네트워크 #Project1 Report
#### repo: _https://github.com/DanielHeo94/socket.udp-tcp.test_
---

## 1. 조원
- 허진수
- 이동하
- 방선국

<br>
## 2. 함수 설명
### a. `socket()`

| Header | `#include <sys/types.h>` <br> `#include <sys/socket.h>` |
| :---:|:--- |
| Format  | `int socket(int domain, int type, int protocol);` |
| Parameters  |  `int domain`: 인터넷을 통해 통신할 지, 같은 시스템 내에서 프로세스 끼리 통신할 지의 여부를 설정합니다. <br> `int type`: 데이터의 전송 형태를 지정하며 아래와 같은 값을 사용할 수 있습니다. <br> `int protocol`: 통신에 있어 특정 프로토콜을 사용을 지정하기 위한 변수이며, 보통 0 값을 사용합니다. |
| Return | _-1_ 이외: Socket Descriptor <br> _-1_: Fail  |
> Socket을 생성하여 반환합니다.

<br>
### b. `memset()`
| Header | `#include <string.h>` |
|:---:|:---|
| Format | `void *memset(void *s, int c, size_t n);` |
| Parameters | `void *ptr`:	메모리의 크기를 변경할 포인터 <br> `int c`:	초기화 값 <br> `size_t size`:	초기화 길이 |
| Return | `void *`:	s에 대한 포인터를 반환하며 실패하면 NULL을 반환한다. |
> malloc() 이나 calloc() 에서 할당 받은 메모리를 특정 값으로 초기화합니다. 보통 어떤 작업을 하기 전에 NULL로 초기화할 때 많이 사용합니다.
데이터를 읽어 들이거나 어떤 함수를 호출 후 메모리에 입력된 값을 처리하는 경우 미리 메모리를 초기화를 하는 것이 디버깅에 유리합니다.

<br>
### c. `bind()`
| Header | `#include <sys/types.h>` <br> `#include <sys/socket.h>` |
|:---:|:---|
| Format | `int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);` |
| Parameters | `int sockfd`: 소켓 디스크립터 <br> `struct sockaddr *myaddr`: 주소 정보로 인터넷을 이용하는 `AF_INET`인지 시스템 내에서 통신하는 `AF_UNIX`에 따라서 달라집니다. 인터넷을 통해 통신하는 `AF_INET`인 경우에는 `struct sockaddr_in`을 사용합니다. <br> `socklen_t addrlen`: myadd 구조체의 크기|
| Return | _0_:	Success. <br> _-1_: Fail.|
> Socket에 IP주소와 포트번호를 지정해 줍니다. 이로서 소켓을 통신에 사용할 수 있도록 준비가 됩니다.

<br>
### d. `close()`
| Header | `#include <unistd.h>` |
|:---:|:---|
| Format | `int close(int s);` |
| Parameters | `int s`: Socket Descriptor |
| Return | _0_:	Success. <br> _-1_: Fail. |
> Socket을 닫습니다.

<br>
### e. `recvfrom()`
| Header | `#include <sys/types.h>` <br> `#include <sys/socket.h>` |
|:---:|:---|
| Format | `int recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);` |
| Parameters | `int s`: Socket Descriptor <br> `void *buf`: 자료 수신을 위한 버퍼 포인터 <br> `size_t len`: 버퍼의 바이트 단위 길이 <br> `int flags`: 수신을 위한 옵션 <br> `sockaddr *to`: 전송한 곳의 주소 정보 <br> `socklen_t tolen`: 전송한 곳의 주소 정보의 크기|
| Return | _-1_ 이외:	실제로 수신한 바이트 수. <br> _-1_: Fail. |
> UDP/IP 통신에서 소켓으로부터 데이터를 수신합니다.

<br>
### f. `sendto()`
| Header | `#include <sys/types.h>` <br> `#include <sys/socket.h>` |
|:---:|:---|
| Format | `int sendto(int s, const void *msg, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);` |
| Parameters | `int s`: Socket Descriptor <br> `void *msg`: 전송할 메시지 <br> `size_t len`: 버퍼의 바이트 단위 길이 <br> `int flags`: 전송을 위한 옵션 <br> `sockaddr *to`: 목적지 주소 정보 <br> `socklen_t tolen`: 목적지 주소 정보의 크기|
| Return | _-1_ 이외:	실제로 전송한 바이트 수. <br> _-1_: Fail. |
> UDP/IP 통신에서 소켓으로 데이터를 전송합니다.

<br>
### g. `listen()`
| Header | `#include <sys/socket.h>` |
|:---:|:---|
| Format | `int listen(int s, int backlog);` |
| Parameters | `int s`: Socket Descriptor <br> `int backlog`: 대기 메시지 큐의 개수|
| Return | _0_:	Success. <br> _-1_: Fail. |
> 소켓을 통해 클라이언트의 접속 요청을 기다리도록 설정합니다.

<br>
### h. `accept()`
| Header | `#include <sys/types.h>` <br> `#include <sys/socket.h>` |
|:---:|:---|
| Format | `int accept(int s, struct sockaddr *addr, socklen_t *addrlen);` |
| Parameters | `int s`: Socket Descriptor <br> `struct sockaddr *addr`: 클라이언트 주소 정보를 가지고 있는 포인터 <br> `socklen_t addrlen`: struct sockaddr *addr 포인터가 가르키는 구조체의 크기|
| Return |  _-1_ 이외: 새로운 Socket Descriptor. <br> _-1_: Fail. |
> 클라이언트의 접속 요청을 받아드리고 클라이언트와 통신하는 전용 소켓을 생성합니다.

<br>
### i. `read()`
| Header | `#include <unistd.h>` |
|:---:|:---|
| Format | `ssize_t read (int s, void *buf, size_t nbytes);` |
| Parameters | `int s`: Socket Descriptor <br> `void *buf`: 소켓에서 데이터를 읽어들일 버퍼 <br> `size_t nbytes`: 버퍼의 크기|
| Return |  _-1_ 이외: 읽어들인 바이트 수. <br> _-1_: Fail. |
> 소켓의 데이터를 읽어들입니다.

<br>
### j. `connect()`
| Header | `#include <sys/types.h>` <br> `#include <sys/socket.h>` |
|:---:|:---|
| Format | int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen); |
| Parameters | `int sockfd`: Socket Descriptor <br> `struct sockaddr *serv_addr`: 서버 주소 정보에 대한 포인터 <br> `socklen_t addrlen`: struct sockaddr *serv_addr 포인터가 가르키는 구조체의 크기|
| Return |  _0_:	Success. <br> _-1_: Fail.  |
> 생성한 소켓을 통해 서버로 접속을 요청합니다.

<br>
### k. `write()`
| Header | `#include <unistd.h>` |
|:---:|:---|
| Format | `ssize_t write (int s, const void *buf, size_t n)` |
| Parameters | `int s`: Socket Descriptor <br> `void *buf`: 소켓에 쓸 데이터를 담을 버퍼 <br> `size_t n`: 버퍼의 크기|
| Return |  _-1_ 이외: 쓴 데이터의 바이트 수. <br> _-1_: Fail. |
> 소켓에 데이터를 씁니다.

<br>
## 3. 결과 화면

### a. UDP Server
![udp-server](https://koriel.co/img/personal/comnet/스크린샷, 2016-10-09 19-09-19.png)

### b. UDP Client
![udp-client](https://koriel.co/img/personal/comnet/스크린샷, 2016-10-09 19-08-31.png)

### c. TCP Server
![tcp-server](https://koriel.co/img/personal/comnet/스크린샷, 2016-10-09 19-11-05.png)

### d. TCP Client
![tcp-client](https://koriel.co/img/personal/comnet/스크린샷, 2016-10-09 19-11-08.png)

### e. dst.jpg
![dst-jpg](https://koriel.co/img/personal/comnet/스크린샷, 2016-10-09 19-09-26.png)
