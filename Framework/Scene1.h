#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"

using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window *window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Body* cliff;
	Body* flappyBird;

	SDL_Texture* cliffTexture;
	SDL_Texture* flappyBirdTexture;
	bool start = false;
	
public:
	Scene1(SDL_Window* sdlWindow);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void HandleEvent(const SDL_Event& sdlEvent);
	void Update(const float time);
	void Render() const;
};

#endif

