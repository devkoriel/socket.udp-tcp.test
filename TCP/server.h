#pragma once

#define BUFSIZE 4096
#define FILENAME "dst.jpg"

#ifndef boolean
#define boolean
typedef enum { false, true } bool;
#endif

typedef struct packet Packet;

void serverOpen(const char* port);
void rcvPacket(int sock);
void toApp(Packet pkt);
