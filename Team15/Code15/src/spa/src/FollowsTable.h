#pragma once

#include <unordered_map>

using namespace std;

class FollowsTable {
public:
	FollowsTable();

	void addFollows(int leader, int follower);

	int getFollower(int leader);

	int getLeader(int follower);

	bool inRelationship(int leaderNumber, int followerNumber);

	bool isEmpty();

	void addFollower(int leader, int follower);

	void addLeader(int leader, int follower);

private:
	std::unordered_map<int, int> leaderToFollowerMap;
	std::unordered_map<int, int> followerToLeaderMap;
};
