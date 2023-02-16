#include "FollowsTable.h"

FollowsTable::FollowsTable() = default;

void FollowsTable::addFollows(int leader, int follower) {
	addFollower(leader, follower);
	addLeader(leader, follower);
}

void FollowsTable::addAllFollows(std::unordered_map<int, int> leaderToFollower) {
	leaderToFollowerMap = leaderToFollower;
	flipLeaderToFollower(leaderToFollower);
}

int FollowsTable::getFollower(int leader) {
	auto pair = leaderToFollowerMap.find(leader);
	if (pair == leaderToFollowerMap.end()) {
		return -1;
	}
	return pair->second;
}

int FollowsTable::getLeader(int follower) {
	auto pair = followerToLeaderMap.find(follower);
	if (pair == followerToLeaderMap.end()) {
		return -1;
	}
	return pair->second;
}

bool FollowsTable::inRelationship(int leaderNumber, int followerNumber) {
	auto pair = leaderToFollowerMap.find(leaderNumber);
	if (pair == leaderToFollowerMap.end()) {
		return false;
	}
	auto follower = pair->second;
	if (follower == followerNumber) {
		return true;
	}
	return false;
}

bool FollowsTable::isEmpty() {
	return leaderToFollowerMap.empty() && followerToLeaderMap.empty();
}

void FollowsTable::addFollower(int leader, int follower) {
	auto pair = leaderToFollowerMap.find(leader);
	if (pair == leaderToFollowerMap.end()) {
		leaderToFollowerMap[leader] = follower;
	}
}

void FollowsTable::addLeader(int leader, int follower) {
	auto pair = followerToLeaderMap.find(follower);
	if (pair == followerToLeaderMap.end()) {
		followerToLeaderMap[follower] = leader;
	}
}

void FollowsTable::flipLeaderToFollower(std::unordered_map<int, int> leaderToFollower) {
	for (const auto& [key, value] : leaderToFollower) {
		followerToLeaderMap[value] = key;
	}
}