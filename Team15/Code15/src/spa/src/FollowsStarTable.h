#pragma once

#include <map>
#include <set>

using namespace std;

class FollowsStarTable {
public:
	FollowsStarTable();

	void addFollowsStar(int leader, std::set<int> followers);

	std::set<int> getFollowers(int leader);

	std::set<int> getLeaders(int follower);

	bool inRelationship(int leader, int follower);

	void addFollowers(int leader, std::set<int> followers);

	void addLeaders(int leader, std::set<int> followers);

private:
	std::map<int, std::set<int>> leaderToFollowersMap;
	std::map<int, std::set<int>> followerToLeadersMap;
};