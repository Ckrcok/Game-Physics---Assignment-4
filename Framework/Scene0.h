#ifndef SCENE0_H
#define SCENE0_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"

using namespace MATH;
class Scene0 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	Body* balloon1;
	Body* balloon2;

	SDL_Surface* ballImage;
	bool start = false;
	
public:
	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render() const;

	virtual void HandleEvent(const SDL_Event& sdlEvent) = 0;
};

#endif

