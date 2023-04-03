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

	inline void addLeftToRights(L left, std::set<R> rights) {
		auto pair = leftToAllRightsMap.find(left);
		if (pair == leftToAllRightsMap.end()) {
			leftToAllRightsMap[left] = rights;
		}
		else {
			pair->second.insert(rights.begin(), rights.end());
		}
		flipRightToAllLefts(left, rights);
	}

	inline void addRightToLefts(R right, std::set<L> lefts) {
		auto pair = rightToAllLeftsMap.find(right);
		if (pair == rightToAllLeftsMap.end()) {
			rightToAllLeftsMap[right] = lefts;
		}
		else {
			pair->second.insert(lefts.begin(), lefts.end());
		}
		flipLeftToAllRights(right, lefts);
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

	inline std::unordered_map<L, std::set<R>> getLeftToAllRightsMap() {
		return leftToAllRightsMap;
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

	inline bool isLeftToRightMapEmpty() {
		return leftToRightMap.empty();
	}

	inline bool isRightToLeftMapEmpty() {
		return rightToLeftMap.empty();
	}

	inline bool isLeftToAllRightsMapEmpty() {
		return leftToAllRightsMap.empty();
	}

	inline bool isRightToAllLeftsMapEmpty() {
		return rightToAllLeftsMap.empty();
	}

	inline bool isKeyInLeftToAllRightsMap(L leftKey) {
		if (leftToAllRightsMap.find(leftKey) == leftToAllRightsMap.end()) {
			return false;
		}
		return true;
	}

	inline bool isKeyInRightToAllLeftsMap(R rightKey) {
		if (rightToAllLeftsMap.find(rightKey) == rightToAllLeftsMap.end()) {
			return false;
		}
		return true;
	}

	inline void clearMaps() {
		clearLeftToRightMap();
		clearRightToLeftMap();
		clearLeftToAllRightsMap();
		clearRightToAllLeftsMap();
	}

private:
	std::unordered_map<L, R> leftToRightMap;
	std::unordered_map<R, L> rightToLeftMap;
	std::unordered_map<L, std::set<R>> leftToAllRightsMap;
	std::unordered_map<R, std::set<L>> rightToAllLeftsMap;

	inline void flipRightToLeft(L left, R right) {
		auto pair = rightToLeftMap.find(right);
		if (pair == rightToLeftMap.end()) {
			rightToLeftMap[right] = left;
		}
	}

	inline void flipRightToAllLefts(L left, std::set<R> rights) {
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

	inline void flipLeftToAllRights(R right, std::set<L> lefts) {
		for (L left : lefts) {
			auto pair = leftToAllRightsMap.find(left);
			if (pair == leftToAllRightsMap.end()) {
				leftToAllRightsMap[left] = { right };
			}
			else {
				pair->second.insert(right);
			}
		}
	}

	inline void flipOneToOneRelationship(std::unordered_map<L, R> oneToOneRelationships) {
		for (const auto& [left, right] : oneToOneRelationships) {
			flipRightToLeft(left, right);
		}
	}
	
	inline void flipManyToManyRelationship(std::unordered_map<L, std::set<R>> oneToManyRelationships) {
		for (const auto& [left, rights] : oneToManyRelationships) {
			flipRightToAllLefts(left, rights);
		}
	}

	inline void flipOneToManyRelationship(std::unordered_map<L, std::set<R>> oneToManyRelationships) {
		for (const auto& [left, rights] : oneToManyRelationships) {
			for (R right : rights) {
				flipRightToLeft(left, right);
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
