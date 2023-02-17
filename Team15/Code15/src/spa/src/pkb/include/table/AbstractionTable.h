#pragma once

#include <unordered_map>
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

	inline void addAllOneToOneAbstractions(std::unordered_map<L, R> oneToOneAbstractions) {
		leftToOneRightMap = oneToOneAbstractions;
		flipOneToOne(oneToOneAbstractions);
	}

	inline void addAllOneToManyAbstractions(std::unordered_map<L, std::set<R>> oneToManyAbstractions) {
		leftToManyRightMap = oneToManyAbstractions;
		flipOneToMany(oneToManyAbstractions);
	}

	inline R getOneRight(L left) {
		auto pair = leftToOneRightMap.find(left);
		if (pair == leftToOneRightMap.end()) {
			return NULL;
		}
		return pair->second;
	}

	inline L getOneLeft(R right) {
		auto pair = rightToOneLeftMap.find(right);
		if (pair == rightToOneLeftMap.end()) {
			return NULL;
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

	inline bool isEmpty() {
		return leftToOneRightMap.empty() && rightToOneLeftMap.empty() && leftToManyRightMap.empty() && rightToManyLeftMap.empty();
	}

private:
	std::unordered_map<L, R> leftToOneRightMap;
	std::unordered_map<R, L> rightToOneLeftMap;
	std::unordered_map<L, std::set<R>> leftToManyRightMap;
	std::unordered_map<R, std::set<L>> rightToManyLeftMap;

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

	inline void flipOneToOne(std::unordered_map<L, R> oneToOneAbstractions) {
		for (const auto& [key, value] : oneToOneAbstractions) {
			rightToOneLeftMap[value] = key;
		}
	}
	
	inline void flipOneToMany(std::unordered_map<L, std::set<R>> oneToManyAbstractions) {
		for (const auto& [key, values] : oneToManyAbstractions) {
			for (R value : values) {
				auto pair = rightToManyLeftMap.find(value);
				if (pair == rightToManyLeftMap.end()) {
					rightToManyLeftMap[value] = { key };
				}
				else {
					pair->second.insert(key);
				}
			}
		}
	}
};
