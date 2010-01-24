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
#ifndef CHANNEL_H_8939873
#define CHANNEL_H_8939873

#include "log.h"
#include "list.h"
#include "client.h"

typedef struct channel {
	int id;
	char name[MAX_TEXT];
	char desc[MAX_TEXT];
	struct channel *parent;
	bool_t temporary;
	struct dlist node;
	struct dlist subs;
	struct dlist clients;
	struct dlist flatlist_node;
	struct dlist channel_links;
	struct dlist link_node;
} channel_t;

void Chan_init();
void Chan_free();
void Chan_addChannel(channel_t *parent, channel_t *sub);
void Chan_removeChannel(channel_t *c);
void Chan_addClient(channel_t *c, client_t *client);
void Chan_removeClient(channel_t *c, client_t *client);
int Chan_playerJoin(channel_t *ch, client_t *client);
int Chan_playerJoin_id(int channelid, client_t *client);
channel_t *Chan_iterate(channel_t **channelpptr);
channel_t *Chan_iterate_siblings(channel_t *parent, channel_t **channelpptr);
channel_t *Chan_createChannel(const char *name, const char *desc);
channel_t *Chan_fromId(int channelid);
void Chan_freeChannel(channel_t *ch);

#endif
