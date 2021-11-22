#include "Scene1.h"
#include <SDL.h>
#include <SDL_image.h>
Scene1::Scene1(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std:: cout << "Can't create the renderer \n";
	}
	flappyBird = new Body(Vec3(0, 16.0f,0.0f )); // (x , y , z)
	flappyBird->setAccel(Vec3(6.0f, -9.81, 0.0f));
	cliff = new Body(Vec3(0.0f, 15.0f, 0.0f));
	std::cout << "hello from Scene1 \n";
}

Scene1::~Scene1(){
	delete flappyBird;
	delete cliff;
}


//SDL_KeyboardEvent

bool Scene1::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);// it's gonna be 0 zero bottom 15 hieght 
	projectionMatrix = ndc * ortho;



	image = IMG_Load("textures/flappybird1.png");
	if (image == nullptr) {
		std::cout << "can't load image \n";
		return false;
	}
	flappyBirdTexture = SDL_CreateTextureFromSurface(renderer, image);

	image = IMG_Load("textures/cliff.png");
	if (image == nullptr) {
		std::cout << "can't load image \n";
		return false;
	}
	cliffTexture = SDL_CreateTextureFromSurface(renderer, image);

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	if (start == true) {
		//printf("%f\n", deltaTime);
		flappyBird->Update(deltaTime);
		cliff->Update(deltaTime);
		//apply force
		//wind 
		//totalForce = gravity + drag; // + wind 
	}
}


void Scene1::HandleEvent(const SDL_Event&  sdlEvent) {

	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE) {
		start = !start;
	}

}

void Scene1::Render() const {
	// clear the screen

	SDL_GetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;


	screenCoords = projectionMatrix * cliff->getPos();
	SDL_QueryTexture(cliffTexture, nullptr, nullptr, &width, &height);
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, cliffTexture, nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);



	screenCoords = projectionMatrix * flappyBird->getPos();
	SDL_QueryTexture(flappyBirdTexture, nullptr, nullptr, &width, &height);
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, flappyBirdTexture, nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);


	SDL_RenderPresent(renderer);
};