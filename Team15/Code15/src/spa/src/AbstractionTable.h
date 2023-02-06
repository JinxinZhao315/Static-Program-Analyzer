#pragma once

#include <map>
#include <set>

using namespace std;

template <typename L, typename R>
class AbstractionTable {
public:
	inline AbstractionTable() = default;

	inline void addOneToOneAbstraction(L left, R right) {
		addLeftToOneRight(left, right);
		addRightToOneLeft(left, right);
	}

	inline void addOneToManyAbstraction(L left, std::set<R> right) {
		addLeftToManyRight(left, right);
		addRightToManyLeft(left, right);
	}

	inline R getOneRight(L left) {
		auto pair = leftToOneRightMap.find(left);
		if (pair == leftToOneRightMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	inline L getOneLeft(R right) {
		auto pair = rightToOneLeftMap.find(right);
		if (pair == rightToOneLeftMap.end()) {
			return nullptr;
		}
		return pair->second;
	}

	inline std::set<R> getManyRight(L left) {
		auto pair = leftToManyRightMap.find(left);
		if (pair == leftToManyRightMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline std::set<L> getManyLeft(R right) {
		auto pair = rightToManyLeftMap.find(right);
		if (pair == rightToManyLeftMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline bool inOneToOneRelationship(L left, R right) {
		auto pair = leftToOneRightMap.find(left);
		if (pair == leftToOneRightMap.end()) {
			return false;
		}
		auto rightOne = pair->second;
		if (rightOne == right) {
			return true;
		}
		return false;
	}

	inline bool inOneToManyRelationship(L left, R right) {
		auto pair = leftToManyRightMap.find(left);
		if (pair == leftToManyRightMap.end()) {
			return false;
		}
		auto rightSide = pair->second;
		auto rightOne = rightSide.find(right);
		if (rightOne == rightSide.end()) {
			return false;
		}
		return true;
	}

private:
	inline void addLeftToOneRight(L left, R right) {
		auto pair = leftToOneRightMap.find(left);
		if (pair == leftToOneRightMap.end()) {
			leftToOneRightMap[left] = right;
		}
	}

	inline void addRightToOneLeft(L left, R right) {
		auto pair = rightToOneLeftMap.find(right);
		if (pair == rightToOneLeftMap.end()) {
			rightToOneLeftMap[right] = left;
		}
	}

	inline void addLeftToManyRight(L left, std::set<R> right) {
		auto pair = leftToManyRightMap.find(left);
		if (pair == leftToManyRightMap.end()) {
			leftToManyRightMap[left] = right;
		}
		else {
			pair->second.insert(right.begin(), right.end());
		}
	}

	inline void addRightToManyLeft(L left, std::set<R> right) {
		for (R r : right) {
			auto pair = rightToManyLeftMap.find(r);
			if (pair == rightToManyLeftMap.end()) {
				rightToManyLeftMap[r] = { left };
			}
			else {
				pair->second.insert(left);
			}
		}
	}
	
	std::map<L, R> leftToOneRightMap;
	std::map<R, L> rightToOneLeftMap;
	std::map<L, std::set<R>> leftToManyRightMap;
	std::map<R, std::set<L>> rightToManyLeftMap;	
};
