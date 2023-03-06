#pragma once

// Modest compatibility wrappers for differences between Zeek versions.
// If things become too cumbersome to handle via this header, we will
// fork a dedicated zeek/x.y branch.

// We drive the compatibilities purely from Zeek version numbers
// (available since Zeek 3.1) since it saves us from implementing
// feature checks.

#if __has_include(<zeek/zeek-version.h>)
#include <zeek/zeek-version.h>
#else
#include <zeek/zeek-config.h>
#endif

// bro_uint_t vs zeek_uint_t: we have the latter as of 5.1, and lose the former
// in 6.1.
#if ZEEK_VERSION_NUMBER < 50100
#define zeek_uint_t bro_uint_t
#endif

// Namespacing tweaks
#if ZEEK_VERSION_NUMBER >= 30200 && ZEEK_VERSION_NUMBER < 40000
#define ZEEK_DETAIL_NS
#elif ZEEK_VERSION_NUMBER >= 40000
#define ZEEK_DETAIL_NS zeek::detail
#endif

// In 4.1 the ICMP directionality code moved to packet-level analyzers.
#if ZEEK_VERSION_NUMBER >= 40100
#include <zeek/packet_analysis/protocol/icmp/ICMP.h>
#define ZEEK_ANALYZER_ICMP ::zeek::packet_analysis::ICMP
#else
#include <zeek/analyzer/protocol/icmp/ICMP.h>
#define ZEEK_ANALYZER_ICMP ::zeek::analyzer::icmp
#endif
