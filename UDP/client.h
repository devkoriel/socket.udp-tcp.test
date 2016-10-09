#pragma once

#define BUFSIZE 4096
#define FILENAME "src.jpg"

#ifndef boolean
#define boolean
typedef enum { false, true } bool;
#endif

typedef struct packet Packet;

void clientOpen(const char* ip, const char* port);
