# This test verifies Community ID presence in the notice log, when
# that part of the package is loaded. The test creates one notice
# without connection state and one with, and verifies that the latter
# includes the Community ID value for it.

# @TEST-EXEC: ln -s $PACKAGE zeek-community-id
# @TEST-EXEC: zeek -r $TRACES/tcp.pcap %INPUT
# @TEST-EXEC: btest-diff notice.log

@load zeek-community-id
@load zeek-community-id/notice

redef enum Notice::Type += {
    COMMUNITY_ID_INIT,
    COMMUNITY_ID_CONN_ESTABLISHED,
};

event zeek_init() {
    # Trim down the notice log to focus on field we care about:
    local f = Log::get_filter(Notice::LOG, "default");
    f$include=set("ts", "uid", "id.orig_h", "id.orig_p", "id.resp_h", "id.resp_p",
                  "proto", "note", "msg", "actions", "community_id");
    Log::add_filter(Notice::LOG, f);

    # A notice without connection context
    NOTICE([$note=COMMUNITY_ID_INIT,
            $msg="Zeek initializing"]);
}

event connection_established(c: connection) {
    # A notice with connection context
    NOTICE([$note=COMMUNITY_ID_CONN_ESTABLISHED,
            $msg="Connection establishment",
	    $conn=c]);
}
