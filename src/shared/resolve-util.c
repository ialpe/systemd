/* SPDX-License-Identifier: LGPL-2.1+ */
/***
  This file is part of systemd.

  Copyright 2016 Lennart Poettering
***/

#include "conf-parser.h"
#include "resolve-util.h"
#include "string-table.h"

DEFINE_CONFIG_PARSE_ENUM(config_parse_resolve_support, resolve_support, ResolveSupport, "Failed to parse resolve support setting");
DEFINE_CONFIG_PARSE_ENUM(config_parse_dnssec_mode, dnssec_mode, DnssecMode, "Failed to parse DNSSEC mode setting");
DEFINE_CONFIG_PARSE_ENUM(config_parse_private_dns_mode, private_dns_mode, PrivateDnsMode, "Failed to parse private DNS mode setting");

static const char* const resolve_support_table[_RESOLVE_SUPPORT_MAX] = {
        [RESOLVE_SUPPORT_NO] = "no",
        [RESOLVE_SUPPORT_YES] = "yes",
        [RESOLVE_SUPPORT_RESOLVE] = "resolve",
};
DEFINE_STRING_TABLE_LOOKUP_WITH_BOOLEAN(resolve_support, ResolveSupport, RESOLVE_SUPPORT_YES);

static const char* const dnssec_mode_table[_DNSSEC_MODE_MAX] = {
        [DNSSEC_NO] = "no",
        [DNSSEC_ALLOW_DOWNGRADE] = "allow-downgrade",
        [DNSSEC_YES] = "yes",
};
DEFINE_STRING_TABLE_LOOKUP_WITH_BOOLEAN(dnssec_mode, DnssecMode, DNSSEC_YES);

static const char* const private_dns_mode_table[_PRIVATE_DNS_MODE_MAX] = {
        [PRIVATE_DNS_NO] = "no",
        [PRIVATE_DNS_OPPORTUNISTIC] = "opportunistic",
};
DEFINE_STRING_TABLE_LOOKUP_WITH_BOOLEAN(private_dns_mode, PrivateDnsMode, PRIVATE_DNS_OPPORTUNISTIC);
