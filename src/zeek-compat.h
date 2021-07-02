#pragma once

// Modest compatibility wrappers for differences between the Zeek 3.2
// series and 4.0+. If things become too cumbersome to handle via this
// header, we fork a dedicated zeek/x.y branch.

// We drive the compatibilities purely from Zeek version numbers
// (available since Zeek 3.1) since it saves us from implementing
// feature checks.

// Namespacing tweaks
#include <zeek/zeek-config.h>
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
