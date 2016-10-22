#pragma once
#include "GameObject.h"
#include <vector>

void determineCollisions(std::vector<GameObject> gameObjects) {
	for (int i = 0; i < gameObjects.size(); ++i) {
		GameObject obj1 = gameObjects[i];
		for (int j = i + 1; j < gameObjects.size(); ++j) {
			GameObject obj2 = gameObjects[j];
			if (obj1.isColliding(obj2)) {
				irr::core::vector2df dir = obj1.collisionDirectionNormalized(obj2);
				if (obj1.isStatic) {
					if (obj1.getPosition().X > 0) {
						//obj2.setPosition(, obj1.getPosition().Y)
					}
				}
				else if (obj2.isStatic) {

				}
			}
		}
	}
}