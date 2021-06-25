# Crank through a set of pcaps and verify the Community ID inputs and
# outputs. Since each output line is triggered by a connection state
# removal in Zeek, the ordering of sets of those events can change
# across Zeek releases, and we don't care about the order (just the
# values involved), we sort the output files.

# @TEST-EXEC: bash %INPUT

set -e

ln -s $PACKAGE zeek-community-id

for pcap in $(cd $TRACES && ls *.pcap); do
    zeek -r $TRACES/$pcap load-community-id | sort >$pcap.out
    btest-diff $pcap.out
done

@TEST-START-FILE load-community-id.zeek
# This mimicks the way zkg will later load the package.
@load zeek-community-id

# We validate verbose logging in this test.
redef CommunityID::verbose=T;
@TEST-END-FILE
