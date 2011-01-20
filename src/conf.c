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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libconfig.h>

#include "types.h"
#include "conf.h"
#include "log.h"

static config_t configuration;

#define DEFAULT_CONFIG "/etc/umurmur.conf"
#define DEFAULT_WELCOME "Welcome to uMurmur!"
#define DEFAULT_MAX_CLIENTS 10
#define DEFAULT_MAX_BANDWIDTH 48000
#define DEFAULT_BINDPORT 64738

const char defaultconfig[] = DEFAULT_CONFIG;

void Conf_init(const char *conffile)
{
	config_init(&configuration);
	if (conffile == NULL)
		conffile = defaultconfig;
	if (config_read_file(&configuration, conffile) != CONFIG_TRUE) {
		Log_fatal("Error in config file %s line %d: %s", conffile,
				  config_error_line(&configuration), config_error_text(&configuration));
	}
}

void Conf_deinit()
{
	config_destroy(&configuration);
}

const char *getStrConf(param_t param)
{
	config_setting_t *setting = NULL;
	const char *strsetting = NULL;
	
	switch (param) {
	case CERTIFICATE:
		setting = config_lookup(&configuration, "certificate");
		if (!setting)
			return "/etc/umurmur/certificate.crt";
		else {
			if ((strsetting = config_setting_get_string(setting)) != NULL)
				return strsetting;
			else
				return "/etc/umurmur/certificate.crt";
		}
		break;
	case KEY:
		setting = config_lookup(&configuration, "private_key");
		if (!setting)
			return "/etc/umurmur/private_key.key";
		else {
			if ((strsetting = config_setting_get_string(setting)) != NULL)
				return strsetting;
			else
				return "/etc/umurmur/private_key.key";
		}
		break;
	case PASSPHRASE:
		setting = config_lookup(&configuration, "password");
		if (!setting)
			return "";
		else {
			if ((strsetting = config_setting_get_string(setting)) != NULL)
				return strsetting;
			else
				return "";
		}
		break;
	case BINDADDR:
		setting = config_lookup(&configuration, "bindaddr");
		if (!setting)
			return "";
		else {
			if ((strsetting = config_setting_get_string(setting)) != NULL)
				return strsetting;
			else
				return "";
		}
		break;
	case WELCOMETEXT:
		setting = config_lookup(&configuration, "welcometext");
		if (!setting)
			return DEFAULT_WELCOME;
		else {
			if ((strsetting = config_setting_get_string(setting)) != NULL)
				return strsetting;
			else
			return DEFAULT_WELCOME;
		}
		break;
	case DEFAULT_CHANNEL:
		setting = config_lookup(&configuration, "default_channel");
		if (!setting)
			return "";
		else {
			if ((strsetting = config_setting_get_string(setting)) != NULL)
				return strsetting;
			else
			return "";
		}
		break;
	default:
		doAssert(false);
		break;
	}
	return NULL;
}

int getIntConf(param_t param)
{
	config_setting_t *setting = NULL;
	
	switch (param) {
	case BINDPORT:
		setting = config_lookup(&configuration, "bindport");
		if (!setting)
			return DEFAULT_BINDPORT;
		else {
			return config_setting_get_int(setting);
		}
		break;
	case MAX_BANDWIDTH:
		setting = config_lookup(&configuration, "max_bandwidth");
		if (!setting)
			return DEFAULT_MAX_BANDWIDTH;
		else {
			return config_setting_get_int(setting);
		}
		break;
	case MAX_CLIENTS:
		setting = config_lookup(&configuration, "max_users");
		if (!setting)
			return DEFAULT_MAX_CLIENTS;
		else {
			return config_setting_get_int(setting);
		}
		break;
	default:
		doAssert(false);
	}
}

int Conf_getNextChannel(conf_channel_t *chdesc, int index)
{
	config_setting_t *setting = NULL;
	int maxconfig = 64, ret = 0;
	char configstr[maxconfig];
	
	ret = snprintf(configstr, maxconfig, "channels.[%d].name", index);
	setting = config_lookup(&configuration, configstr);
	if (ret >= maxconfig || ret < 0 || setting == NULL)
		return -1; /* Required */
	chdesc->name =  config_setting_get_string(setting);
	
	ret = snprintf(configstr, maxconfig, "channels.[%d].parent", index);
	setting = config_lookup(&configuration, configstr);
	if (ret >= maxconfig || ret < 0 || setting == NULL)
		return -1; /* Required */
	chdesc->parent = config_setting_get_string(setting);
	
	ret = snprintf(configstr, maxconfig, "channels.[%d].description", index);
	setting = config_lookup(&configuration, configstr);
	if (ret >= maxconfig || ret < 0 || setting == NULL) /* Optional */
		chdesc->description = NULL;
	else
		chdesc->description = config_setting_get_string(setting);
	
	ret = snprintf(configstr, maxconfig, "channels.[%d].noenter", index);
	setting = config_lookup(&configuration, configstr);
	if (ret >= maxconfig || ret < 0 || setting == NULL) /* Optional */
		chdesc->noenter = false;
	else
		chdesc->noenter = config_setting_get_bool(setting);

	return 0;
}

int Conf_getNextChannelLink(conf_channel_link_t *chlink, int index)
{
	config_setting_t *setting = NULL;
	int maxconfig = 64, ret = 0;
	char configstr[maxconfig];
	
	ret = snprintf(configstr, maxconfig, "channel_links.[%d].source", index);
	setting = config_lookup(&configuration, configstr);
	if (ret >= maxconfig || ret < 0 || setting == NULL)
		return -1;
	chlink->source = config_setting_get_string(setting);

	ret = snprintf(configstr, maxconfig, "channel_links.[%d].destination", index);
	setting = config_lookup(&configuration, configstr);
	if (ret >= maxconfig || ret < 0 || setting == NULL)
		return -1;
	chlink->destination = config_setting_get_string(setting);

	return 0;
}
