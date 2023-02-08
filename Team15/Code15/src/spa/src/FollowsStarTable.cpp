#include "FollowsStarTable.h"

FollowsStarTable::FollowsStarTable() = default;

void FollowsStarTable::addFollowsStar(int leader, set<int> followers) {
	addFollowers(leader, followers);
	addLeaders(leader, followers);
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
			pair->second.emplace(leader);
		}
	}
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
	return leaderToFollowersMap.empty();
}