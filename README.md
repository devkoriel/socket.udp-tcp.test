# [2016-2] 컴퓨터 네트워크 #Project1 Report
#### repo: _https://github.com/DanielHeo94/socket.udp-tcp.test_
---

## 1. 조원
- 허진수
- 이동하
- 방선국

## 2. 함수 설명
### a. `socket()`
소켓을 생성하여 반환합니다.

Header |  `#include <sys/types.h>` <br> `#include <sys/socket.h>`
--|--
Format  | `int socket(int domain, int type, int protocol);`
Parameters  |  `int domain`: 인터넷을 통해 통신할 지, 같은 시스템 내에서 프로세스 끼리 통신할 지의 여부를 설정합니다. <br> `int type`: 데이터의 전송 형태를 지정하며 아래와 같은 값을 사용할 수 있습니다. <br> `int protocol`: 통신에 있어 특정 프로토콜을 사용을 지정하기 위한 변수이며, 보통 0 값을 사용합니다.
Return Value  | _-1_ 이외: Socket Descriptor <br> _-1_: Fail  

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
