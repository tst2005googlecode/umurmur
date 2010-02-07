/* Copyright (C) 2009-2010, Martin Johansson <martin@fatbob.nu>
   Copyright (C) 2005-2010, Thorvald Natvig <thorvald@natvig.com>

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.
   - Neither the name of the Developers nor the names of its contributors may
     be used to endorse or promote products derived from this software without
     specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef CLIENT_H_45786678
#define CLIENT_H_45786678

#include <openssl/ssl.h>
#include <stdint.h>
#include <unistd.h>             /* close() */
#include <sys/types.h>
#include <sys/socket.h>         /* socket() */
#include <netinet/in.h>         /* IPPROTO_TCP */
#include <arpa/inet.h>          /* inet_addr() */
#include <errno.h>              /* errno */
#include <sys/poll.h>

#include "list.h"
#include "types.h"
#include "messages.h"
#include "crypt.h"
#include "timer.h"
#include "pds.h"

#define BUFSIZE 8192
#define UDP_BUFSIZE 512
#define INACTICITY_TIMEOUT 15 /* Seconds */
#define MAX_CODECS 10

#define IS_AUTH(_a_) ((_a_)->authenticated)

typedef struct {
	int tcpfd;
	SSL *ssl;
	bool_t SSLready;
	bool_t shutdown_wait;
	cryptState_t cryptState;
	bool_t readBlockedOnWrite, writeBlockedOnRead;
	
	struct sockaddr_in remote_tcp;
	struct sockaddr_in remote_udp; 
	uint8_t rxbuf[BUFSIZE], txbuf[BUFSIZE];
	uint32_t rxcount, msgsize, drainleft, txcount, txsize;
	int sessionId;
	uint64_t key;
	char *username;
	bool_t bUDP, authenticated, deaf, mute;
	char *os, *release;
	uint32_t version;
	int codec_count;
	struct dlist codecs;
	int availableBandwidth;
	etimer_t lastActivity;
	struct dlist node;
	struct dlist txMsgQueue;
	int txQueueCount;
	void *channel; /* Ugly... */
	char *context;
	struct dlist chan_node;
	struct dlist voicetargets;
} client_t;

typedef struct {
	int codec, count;
	struct dlist node;
} codec_t;

void Client_init();
int Client_getfds(struct pollfd *pollfds);
void Client_janitor();
int Client_add(int fd, struct sockaddr_in *remote);
int Client_read_fd(int fd);
int Client_write_fd(int fd);
int Client_send_message(client_t *client, message_t *msg);
int Client_count(void);
void Client_close(client_t *client);
client_t *Client_iterate(client_t **client);
int Client_send_message_except(client_t *client, message_t *msg);
int Client_read_udp(void);
void Client_disconnect_all();
int Client_voiceMsg(client_t *client, uint8_t *data, int len);
void recheckCodecVersions();
void Client_codec_add(client_t *client, int codec);
void Client_codec_free(client_t *client);
codec_t *Client_codec_iterate(client_t *client, codec_t **codec_itr);

#endif
