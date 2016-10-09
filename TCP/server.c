#include "server.h"

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

void serverOpen(const char* port) {
        int serv_sock, clnt_sock;
        struct sockaddr_in servAddr, clntAddr;
        socklen_t clntAddrSize;

        assert(-1 != (serv_sock = socket(PF_INET, SOCK_STREAM, 0)));
        printf("Socket has been created.\n");

        usleep(500000);
        memset(&servAddr, 0, sizeof(servAddr));
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(4000);

        assert(-1 != bind(serv_sock, (const struct sockaddr*)&servAddr, sizeof(servAddr)));
        printf("The server address information (ANYIP.%s) is bound.\n\n\n", port);

        usleep(500000);

        assert(-1 != listen(serv_sock, 5));
        printf("The listen queue has been created.\n");

        usleep(500000);

        printf("Ready to receive TCP connection request\n");

        clntAddrSize = sizeof(clntAddr);
        assert(-1 != accept(serv_sock, (const struct sockaddr*)&clntAddr, &clntAddrSize));

        printf("a client (%s:%i) has been connected...\n\n\n", inet_ntoa(clntAddr.sin_addr), ntohs(clntAddr.sin_port));

        rcvPacket(clnt_sock);

        close(clnt_sock);
        close(serv_sock);
}

void rcvPacket(int sock) {
        Packet rcvPkt;
        rcvPkt.dataSeq = 0;
        rcvPkt.isFinish = false;

        int rcvedSize = 0;

        const char eof = 0x1A;

        while(1) {
                assert(-1 != (rcvPkt.dataSize = read(sock, rcvPkt.data, BUFSIZE)));
                if(*(rcvPkt.data) == eof) {
                        break;
                }

                usleep(250000);

                printf("%i Bytes data (seq: %i) received.\n", rcvPkt.dataSize, rcvPkt.dataSeq);
                rcvedSize += rcvPkt.dataSize;

                toApp(rcvPkt);
                rcvPkt.dataSeq++;
        }

        usleep(500000);
        printf("The file (%i Bytes) has been received.\n", rcvedSize);
}

void toApp(Packet pkt) {
        FILE* fp = NULL;
        static bool isFirst = true;
        long int offset;

        if(isFirst == true) {
                assert(fp = fopen(FILENAME, "w+"));
                isFirst = false;
        } else
        assert(fp = fopen(FILENAME, "a"));

        offset = BUFSIZE * pkt.dataSeq;

        fseek(fp, offset, SEEK_SET);

        fwrite(pkt.data, pkt.dataSize, 1, fp);

        fclose(fp);
}
