#ifndef SCENE_H
#define SCENE_H
#include <SDL.h>

class Scene {
public:

	virtual ~Scene() {};
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void HandleEvent(const SDL_Event& sdlEvent) = 0;
	virtual void Render() const = 0;
};

#endif
