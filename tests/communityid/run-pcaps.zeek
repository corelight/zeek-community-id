# @TEST-EXEC: ln -s $PACKAGE zeek-community-id
# @TEST-EXEC: for pcap in $(cd $TRACES && ls *.pcap); do zeek -r $TRACES/$pcap %INPUT >$pcap.out; done
# @TEST-EXEC: for pcap in $(cd $TRACES && ls *.pcap); do btest-diff $pcap.out; done

# This mimicks the way zkg will later load the package.
@load zeek-community-id

# We validate verbose logging in this test.
redef CommunityID::verbose=T;
