#pragma once

#include <unordered_map>
#include <set>

template <typename L, typename R>
class RelationshipTable {
public:
	inline RelationshipTable() = default;

	inline void addAllOneToOneRelationships(std::unordered_map<L, R> oneToOneRelationships) {
		leftToOneRightMap = oneToOneRelationships;
		flipOneToOne(oneToOneRelationships);
	}

	inline void addAllManyToManyRelationships(std::unordered_map<L, std::set<R> > oneToManyRelationships) {
		leftToManyRightMap = oneToManyRelationships;
		flipOneToMany(oneToManyRelationships);
	}

	inline void addAllOnetoManyRelationships(std::unordered_map<L, std::set<R>> oneToManyRelationships) {
		leftToManyRightMap = oneToManyRelationships;
		flipOneSidedOneToMany(oneToManyRelationships);
	}

	inline R getRight(L left, R invalidRight) {
		auto pair = leftToOneRightMap.find(left);
		if (pair == leftToOneRightMap.end()) {
			return invalidRight;
		}
		return pair->second;
	}

	inline L getLeft(R right, L invalidLeft) {
		auto pair = rightToOneLeftMap.find(right);
		if (pair == rightToOneLeftMap.end()) {
			return invalidLeft;
		}
		return pair->second;
	}

	inline std::set<R> getAllRights(L left) {
		auto pair = leftToManyRightMap.find(left);
		if (pair == leftToManyRightMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline std::set<L> getAllLefts(R right) {
		auto pair = rightToManyLeftMap.find(right);
		if (pair == rightToManyLeftMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline bool inOneToOneRelationship(L left, R right) {
		auto pair = rightToOneLeftMap.find(right);
		if (pair == rightToOneLeftMap.end()) {
			return false;
		}
		auto leftOne = pair->second;
		if (leftOne == left) {
			return true;
		}
		return false;
	}

	inline bool inManyToManyRelationship(L left, R right) {
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

	inline void clearMaps() {
		clearLeftToOneRightMap();
		clearRightToOneLeftMap();
		clearLeftToManyRightMap();
		clearRightToManyLeftMap();
	}

	inline bool checkReadiness() {
		return isReady;
	}

	inline void setToReady() {
		this->isReady = true;
	}

	inline void setToUnready() {
		this->isReady = false;
	}

private:
	std::unordered_map<L, R> leftToOneRightMap;
	std::unordered_map<R, L> rightToOneLeftMap;
	std::unordered_map<L, std::set<R> > leftToManyRightMap;
	std::unordered_map<R, std::set<L> > rightToManyLeftMap;
	bool isReady = false;

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

	inline void addRightToManyLeft(L left, std::set<R> rights) {
		for (R right : rights) {
			auto pair = rightToManyLeftMap.find(right);
			if (pair == rightToManyLeftMap.end()) {
				rightToManyLeftMap[right] = { left };
			}
			else {
				pair->second.insert(left);
			}
		}
	}

	inline void flipOneToOne(std::unordered_map<L, R> oneToOneRelationships) {
		for (const auto& [left, right] : oneToOneRelationships) {
			addRightToOneLeft(left, right);
		}
	}
	
	inline void flipOneToMany(std::unordered_map<L, std::set<R>> oneToManyRelationships) {
		for (const auto& [left, rights] : oneToManyRelationships) {
			addRightToManyLeft(left, rights);
		}
	}

	inline void flipOneSidedOneToMany(std::unordered_map<L, std::set<R>> oneToManyRelationships) {
		for (const auto& [left, rights] : oneToManyRelationships) {
			for (R right : rights) {
				addRightToOneLeft(left, right);
			}
		}
	}

	inline void clearLeftToOneRightMap() {
		leftToOneRightMap.clear();
	}

	inline void clearRightToOneLeftMap() {
		rightToOneLeftMap.clear();
	}

	inline void clearLeftToManyRightMap() {
		leftToManyRightMap.clear();
	}

	inline void clearRightToManyLeftMap() {
		rightToManyLeftMap.clear();
	}
};
