#pragma once

#include <unordered_map>
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

	bool isEmpty();

private:
	std::unordered_map<int, std::set<int>> leaderToFollowersMap;
	std::unordered_map<int, std::set<int>> followerToLeadersMap;
};