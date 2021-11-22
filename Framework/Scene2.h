#ifndef SCENE2_H
#define SCENE2_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"

using namespace MATH;
class Scene2 : public Scene {
private:
	SDL_Window *window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Body* boulder;
	Body* flappyBird;

	SDL_Texture* boulderTexture;
	double boulderAngle;
	SDL_Texture* flappyBirdTexture;
	bool start = false;
	
public:
	Scene2(SDL_Window* sdlWindow);
	~Scene2();
	bool OnCreate();
	void OnDestroy();
	void HandleEvent(const SDL_Event& sdlEvent);
	void Update(const float time);
	void Render() const;
};

#endif

