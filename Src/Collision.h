#ifndef Collision_h
#define	Collision_h

#include <SDL.h>

class ColliderComponent;

class Collision {
public:
	//Axis and Aligned Bounding Box - Checking to see if the boundary boxes for rectangles are overlapping
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);


};

#endif
