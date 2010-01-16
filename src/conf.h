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
#ifndef CONF_H_24564356
#define CONF_H_24564356

#include "messages.h"

typedef enum param {
	CERTIFICATE,
	KEY,
	PASSPHRASE,
	BINDPORT,
	BINDADDR,
	WELCOMETEXT,
	MAX_BANDWIDTH,
	MAX_CLIENTS,
	DEAFULT_CHANNEL,
} param_t;

typedef struct {
	char parent[MAX_TEXT];
	char name[MAX_TEXT];
	char description[MAX_TEXT];
} conf_channel_t;

typedef struct {
	char source[MAX_TEXT];
	char destination[MAX_TEXT];
} conf_channel_link_t;

int Conf_init(const char *conffile);
void Conf_deinit();

const char *getStrConf(param_t param);
int getIntConf(param_t param);
int Conf_getNextChannel(conf_channel_t *chdesc, int index);
int Conf_getNextChannelLink(conf_channel_link_t *chlink, int index);

#endif
