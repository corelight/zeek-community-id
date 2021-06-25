# "Community ID" flow hashing for Zeek

[![Zeek matrix tests](https://github.com/corelight/zeek-community-id/actions/workflows/zeek-matrix.yml/badge.svg)](https://github.com/corelight/zeek-community-id/actions/workflows/zeek-matrix.yml)
[![Zeek nightly build](https://github.com/corelight/zeek-community-id/actions/workflows/zeek-nightly.yml/badge.svg)](https://github.com/corelight/zeek-community-id/actions/workflows/zeek-nightly.yml)

This Zeek package provides support for "community ID" flow hashing, a
standardized way of labeling traffic flows in network monitors. When
loaded, the package adds a `community_id` string field to
conn.log. This is work in progress between the Zeek and Suricata
communities, to enable correlation of flows in the outputs of both
tools. Feedback is very welcome, also from users/developers of other
monitoring software.

This package implements a BiF to implement the hashing logic and thus
needs binary compilation, so it's also a Zeek plugin. Here's an example
of a resulting conn.log:

```
#separator \x09
#set_separator  ,
#empty_field    (empty)
#unset_field    -
#path   conn
#open   2018-01-31-13-06-56
#fields ts      uid     id.orig_h       id.orig_p       id.resp_h       id.resp_p       proto   service duration        orig_bytes      resp_bytes      conn_state      local_orig      local_resp      missed_bytes    history orig_pkts       orig_ip_bytes   resp_pkts       resp_ip_bytes   tunnel_parents  community_id
#types  time    string  addr    port    addr    port    enum    string  interval        count   count   string  bool    bool    count   string  count   count   count   count   set[string]     string
1071580904.891921       CPcWB54kqKkvkdNEXe      128.232.110.120 34855   66.35.250.204   80      tcp     -       0.311104        496     1731    SF      -       -       2227    ShADadfF        6       816     6       2051    -       1:LQU9qZlK+B5F3KDmev6m5PMibrg=
#close  2018-01-31-13-06-56
```

## Zeek notice support

The package supports Community ID in Zeek's `notice.log` for notices
with a connection context. If you'd like to use this functionality,
place the following line in your `local.zeek` or similar site-local
configuration:

```
@load zeek-community-id/notice
```

This line has no effect when the Community ID package itself isn't
loaded. This extra-script approach ensures that users who don't want
the ID in their `notice.log` don't have that log cluttered with an
additional column that's always unused.

## Protocol support

The Community ID spec currently envisions support for a number of
protocol constellations for which Zeek does not track flow-level state
because its analyzers wouldn't know what to do with the traffic. For
such flows Zeek never triggers the connection-related events used by
the package, so there won't be output in conn.log anyway. (If there
were protocols Zeek tracks at the flow level but the plugin doesn't
support, the reported ID would be empty.)  We currently support TCP
and UDP over IPv4 or IPv6, as well as ICMPv4 and ICMPv6. We do _not_
support other transport-level protocols (such as SCTP), or general
IP-address-pair flows for unsupported transport layer protocols.

## Using the package

The package's name is `zeek-community-id`; the plugin's name is
`Corelight::CommunityID`. You can see the package's configuration
options in the corresponding [Zeek script](scripts/Corelight/CommunityID/__load__.zeek).

## Compatibility with Zeek versions

The Community ID package works with any Zeek version since 2.6.4.
Since the Zeek codebase has undergone substantial changes since then,
the package provides compatibility branches that support specific Zeek
version ranges, striking a balance between readable code vs. ease of
installation and branch management.

On the `zeek/x.y` and master branches, git tags label the Community ID
releases. For example, `3.1.0` is the first release on the `zeek/3.1`
branch, and works with any Zeek in the 3.1 series. The next Community
ID release for the Zeek 3.1 series will be called `3.1.1` and also
live on this branch, followed by `3.1.2`, etc. (Therefore this isn't
semantic versioning.)

Each branch also declares a Zeek version compatibility window in
`zkg.meta`, so won't install if paired with an incompatible Zeek
version. For example, the master branch currently requires at least
Zeek 3.2.0, with no upper bound.

Here's a summary of how Zeek versions, git tags, and git branches
line up:

Zeek version   | Git tag              | Git branch
-------------- | -------------------- | ----------
2.6.4 - 3.0.x  | 3.0.y                | zeek/3.0
3.1.x          | 3.1.y                | zeek/3.1
3.2.x - master | 3.2.y                | master

## Testing

The package includes btests that verify plugin loading and crunch
included test pcaps through Zeek to check baselined Zeek console
output. You can run these by saying `btest -c btest.cfg` in the tests
directory.

## Contact

For questions and feedback, please get in touch on
[Zeek mailing list](https://lists.zeek.org/mailman3/lists/zeek.lists.zeek.org/)
or the [Zeek Slack](https://app.slack.com/client/TSXGCHZE1/CTGDGK6EA).
Github issues and PRs are welcome.
