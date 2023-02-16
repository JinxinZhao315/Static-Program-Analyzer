#pragma once

#include <unordered_map>

using namespace std;

class FollowsTable {
public:
	FollowsTable();

	void addFollows(int leader, int follower);

	void addAllFollows(std::unordered_map<int, int> leaderToFollower);

	int getFollower(int leader);

	int getLeader(int follower);

	bool inRelationship(int leaderNumber, int followerNumber);

	bool isEmpty();

	void addFollower(int leader, int follower);

	void addLeader(int leader, int follower);

	void flipLeaderToFollower(std::unordered_map<int, int> leaderToFollower);

private:
	std::unordered_map<int, int> leaderToFollowerMap;
	std::unordered_map<int, int> followerToLeaderMap;
};
