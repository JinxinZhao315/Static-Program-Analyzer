#include "pkb/include/table/FollowsStarTable.h"

FollowsStarTable::FollowsStarTable() = default;

void FollowsStarTable::addFollowsStar(int leader, set<int> followers) {
	addFollowers(leader, followers);
	addLeaders(leader, followers);
}

void FollowsStarTable::addAllFollowsStar(std::unordered_map<int, std::set<int>> leaderToFollowers) {
	leaderToFollowersMap = leaderToFollowers;
	flipLeaderToFollowers(leaderToFollowers);
}

std::set<int> FollowsStarTable::getFollowers(int leader) {
	auto pair = leaderToFollowersMap.find(leader);
	if (pair == leaderToFollowersMap.end()) {
		return {};
	}
	return pair->second;
}

std::set<int> FollowsStarTable::getLeaders(int follower) {
	auto pair = followerToLeadersMap.find(follower);
	if (pair == followerToLeadersMap.end()) {
		return {};
	}
	return pair->second;
}

bool FollowsStarTable::inRelationship(int leaderNumber, int followerNumber) {
	auto pair = leaderToFollowersMap.find(leaderNumber);
	if (pair == leaderToFollowersMap.end()) {
		return false;
	}
	auto followers = pair->second;
	auto follower = followers.find(followerNumber);
	if (follower == followers.end()) {
		return false;
	}
	return true;
}

bool FollowsStarTable::isEmpty() {
	return leaderToFollowersMap.empty() && followerToLeadersMap.empty();
}

void FollowsStarTable::addFollowers(int leader, std::set<int> followers) {
	auto pair = leaderToFollowersMap.find(leader);
	if (pair == leaderToFollowersMap.end()) {
		leaderToFollowersMap[leader] = followers;
	}
	else {
		pair->second.insert(followers.begin(), followers.end());
	}
}

void FollowsStarTable::addLeaders(int leader, set<int> followers) {
	std::set<int>::iterator follower;
	for (follower = followers.begin(); follower != followers.end(); follower++) {
		auto pair = followerToLeadersMap.find(*follower);
		if (pair == followerToLeadersMap.end()) {
			followerToLeadersMap[*follower] = { leader };
		}
		else {
			pair->second.insert(leader);
		}
	}
}

void FollowsStarTable::flipLeaderToFollowers(std::unordered_map<int, std::set<int>> leaderToFollowers) {
	for (const auto& [key, values] : leaderToFollowers) {
		for (int value : values) {
			auto pair = followerToLeadersMap.find(value);
			if (pair == followerToLeadersMap.end()) {
				followerToLeadersMap[value] = { key };
			}
			else {
				pair->second.insert(key);
			}
		}
	}
}