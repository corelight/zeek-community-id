# @TEST-EXEC: zeek -NN Corelight::CommunityID |sed -e 's/version.*)/version)/g' >output
# @TEST-EXEC: btest-diff output
