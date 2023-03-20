#pragma once

#include <unordered_map>
#include <set>

template <typename L, typename R>
class RelationshipTable {
public:
	inline RelationshipTable() = default;

	inline void addAllOneToOneRelationships(std::unordered_map<L, R> oneToOneRelationships) {
		leftToRightMap = oneToOneRelationships;
		flipOneToOneRelationship(oneToOneRelationships);
	}

	inline void addAllManyToManyRelationships(std::unordered_map<L, std::set<R> > oneToManyRelationships) {
		leftToAllRightsMap = oneToManyRelationships;
		flipManyToManyRelationship(oneToManyRelationships);
	}

	inline void addAllOnetoManyRelationships(std::unordered_map<L, std::set<R>> oneToManyRelationships) {
		leftToAllRightsMap = oneToManyRelationships;
		flipOneToManyRelationship(oneToManyRelationships);
	}

	inline R getRight(L left, R invalidRight) {
		auto pair = leftToRightMap.find(left);
		if (pair == leftToRightMap.end()) {
			return invalidRight;
		}
		return pair->second;
	}

	inline L getLeft(R right, L invalidLeft) {
		auto pair = rightToLeftMap.find(right);
		if (pair == rightToLeftMap.end()) {
			return invalidLeft;
		}
		return pair->second;
	}

	inline std::set<R> getAllRights(L left) {
		auto pair = leftToAllRightsMap.find(left);
		if (pair == leftToAllRightsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline std::set<L> getAllLefts(R right) {
		auto pair = rightToAllLeftsMap.find(right);
		if (pair == rightToAllLeftsMap.end()) {
			return {};
		}
		return pair->second;
	}

	inline bool inOneToOneRelationship(L left, R right) {
		auto pair = rightToLeftMap.find(right);
		if (pair == rightToLeftMap.end()) {
			return false;
		}
		auto leftOne = pair->second;
		if (leftOne == left) {
			return true;
		}
		return false;
	}

	inline bool inManyToManyRelationship(L left, R right) {
		auto pair = leftToAllRightsMap.find(left);
		if (pair == leftToAllRightsMap.end()) {
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
		return leftToRightMap.empty() && rightToLeftMap.empty() && leftToAllRightsMap.empty() && rightToAllLeftsMap.empty();
	}

	inline void clearMaps() {
		clearLeftToRightMap();
		clearRightToLeftMap();
		clearLeftToAllRightsMap();
		clearRightToAllLeftsMap();
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
	std::unordered_map<L, R> leftToRightMap;
	std::unordered_map<R, L> rightToLeftMap;
	std::unordered_map<L, std::set<R> > leftToAllRightsMap;
	std::unordered_map<R, std::set<L> > rightToAllLeftsMap;
	bool isReady = false;

	inline void addRightToLeft(L left, R right) {
		auto pair = rightToLeftMap.find(right);
		if (pair == rightToLeftMap.end()) {
			rightToLeftMap[right] = left;
		}
	}

	inline void addRightToAllLefts(L left, std::set<R> rights) {
		for (R right : rights) {
			auto pair = rightToAllLeftsMap.find(right);
			if (pair == rightToAllLeftsMap.end()) {
				rightToAllLeftsMap[right] = { left };
			}
			else {
				pair->second.insert(left);
			}
		}
	}

	inline void flipOneToOneRelationship(std::unordered_map<L, R> oneToOneRelationships) {
		for (const auto& [left, right] : oneToOneRelationships) {
			addRightToLeft(left, right);
		}
	}
	
	inline void flipManyToManyRelationship(std::unordered_map<L, std::set<R>> oneToManyRelationships) {
		for (const auto& [left, rights] : oneToManyRelationships) {
			addRightToAllLefts(left, rights);
		}
	}

	inline void flipOneToManyRelationship(std::unordered_map<L, std::set<R>> oneToManyRelationships) {
		for (const auto& [left, rights] : oneToManyRelationships) {
			for (R right : rights) {
				addRightToLeft(left, right);
			}
		}
	}

	inline void clearLeftToRightMap() {
		leftToRightMap.clear();
	}

	inline void clearRightToLeftMap() {
		rightToLeftMap.clear();
	}

	inline void clearLeftToAllRightsMap() {
		leftToAllRightsMap.clear();
	}

	inline void clearRightToAllLeftsMap() {
		rightToAllLeftsMap.clear();
	}
};
