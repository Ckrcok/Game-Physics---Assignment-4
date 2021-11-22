#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	balloon1 = new Body(Vec3(15.0f, 14.0f,0.0f )); // (x , y , z)
	balloon2 = new Body(Vec3(3.0f, 10.0f, 0.0f));

	std::cout << "hello from Scene0 \n";

}

Scene0::~Scene0(){
	delete balloon1;
	delete balloon2;
}


void Scene0::HandleEvent(const SDL_Event& sdlEvent) {

	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE) {
		start = !start;
	}

}


bool Scene0::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);// it's gonna be 0 zero bottom 15 hieght 
	projectionMatrix = ndc * ortho;
	



	IMG_Init(IMG_INIT_PNG);
	ballImage = IMG_Load("textures/ball.png");
	if (ballImage == nullptr) {
		std::cout << "Can't Open Image file \n";
		return false;
	}


	return true;
}

void Scene0::OnDestroy() {}



void Scene0::Update(const float deltaTime) {
	//printf("%f\n", deltaTime);
	balloon1->Update(deltaTime);
	balloon2->Update(deltaTime);
}

void Scene0::Render() const {
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0));
	Vec3 screenCoords;
	SDL_Rect square;


	screenCoords = projectionMatrix * balloon1->getPos();
	square.x = (int) screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int) screenCoords.y;
	square.w = 30;
	square.h = 30;
	SDL_BlitSurface(ballImage, nullptr,  screenSurface, &square );
	//SDL_FillRect(screenSurface, &square, SDL_MapRGB(screenSurface->format,255, 0, 0));


	screenCoords = projectionMatrix * balloon2->getPos();
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = 30;
	square.h = 30;
	SDL_BlitSurface(ballImage, nullptr, screenSurface, &square);
	//SDL_FillRect(screenSurface, &square, SDL_MapRGB(screenSurface->format, 0, 0, 255));

	SDL_UpdateWindowSurface(window);
}