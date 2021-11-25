#ifndef SCENE3_H
#define SCENE3_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"
#include <vector>

using namespace MATH;
class Scene3 : public Scene {
private:
	SDL_Window *window;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	std::vector <Body*> star;
	SDL_Texture* GalaxyTexture;
	SDL_Texture* starTexture;
	double starAngle;

	bool start = false;
	
public:
	Scene3(SDL_Window* sdlWindow);
	~Scene3();
	bool OnCreate();
	void OnDestroy();
	void HandleEvent(const SDL_Event& sdlEvent);
	void Update(const float time);
	void Render() const;
};

#endif

