# Zeek package & plugin for adding community hash IDs to conn.log.
# This is loaded when a user activates the plugin.
#
module CommunityID;

export {
    # An unsigned 16-bit number to seed our hashing
    option seed: count = 0;

    # Whether to add a base64 pass over the hash digest.
    # Enabled by default, since it shortens the output.
    option do_base64: bool = T;

    # Verbose debugging log output to the console.
    option verbose: bool = F;

    # Add the ID string field to the connection log record.
    redef record Conn::Info += {
        community_id: string &optional &log;
    };
}

event connection_state_remove(c: connection) {
    c$conn$community_id = CommunityID::hash_conn(c);
}
