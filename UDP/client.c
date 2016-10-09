#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>

#include <unistd.h>
#include <assert.h>

struct packet {
  char data[BUFSIZE];
  int dataSize;
  int dataSeq;
  bool isFinish;
};

void clientOpen(const char* ip, const char* port) {
  int clnt_sock;
  struct sockaddr_in servAddr;

  FILE* fp = NULL;
  size_t fSize;

  Packet sndPkt;
  int sentSize = 0;

  const char eof = 0x1A;

  assert(-1 != (clnt_sock = socket(PF_INET, SOCK_DGRAM, 0)));
  printf("Socket has been created.\n\n\n");

  usleep(500000);
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(ip);
  servAddr.sin_port = htons(atoi(port));

  usleep(500000);

  assert(fp = fopen(FILENAME, "r"));

  fseek(fp, 0, SEEK_END);
  fSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  sndPkt.dataSeq = 0;
  sndPkt.isFinish = false;

  while(fSize > 0) {
    sndPkt.dataSize = fSize > BUFSIZE ? BUFSIZE : fSize;

    sndPkt.isFinish = fSize > BUFSIZE ? false : true;

    fread(sndPkt.data, sndPkt.dataSize, 1, fp);

    sendto(clnt_sock, sndPkt.data, sndPkt.dataSize, 0, (const struct sockaddr*)&servAddr, sizeof(servAddr));
    printf("%i Bytes data (seq: %i) sent.\n", sndPkt.dataSize, sndPkt.dataSeq);

    fSize -= sndPkt.dataSize;
    sentSize += sndPkt.dataSize;
    sndPkt.dataSeq++;
    usleep(500000);
  }

  sendto(clnt_sock, &eof, sizeof(eof), 0, (const struct sockaddr*)&servAddr, sizeof(servAddr));
  printf("The file (%i Bytes) has been sent.\n", sentSize);
  fclose(fp);

  close(clnt_sock);
}
