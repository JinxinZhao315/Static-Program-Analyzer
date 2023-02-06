#pragma once

#include <stdio.h>
#include <iostream>
#include <map>

using namespace std;

class FollowsTable {
public:
	FollowsTable();

	void addFollows(int leader, int follower);

	int getFollower(int leader);

	int getLeader(int follower);

	bool inRelationship(int leader, int follower);

	void addFollower(int leader, int follower);

	void addLeader(int leader, int follower);

	bool isEmpty();
private:
	std::map<int, int> leaderToFollowerMap;
	std::map<int, int> followerToLeaderMap;
};
