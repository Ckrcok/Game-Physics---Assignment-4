#include "Scene3.h"
#include <SDL.h>
#include <SDL_image.h>
#include "VMath.h"
using namespace MATH;
using namespace std;

Scene3::Scene3(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std:: cout << "Can't create the renderer \n";
	}


	star.push_back(new Body(Vec3(10.0f,100.0f, 0.0f)));
	star[0]->setVel(Vec3(0.0f, 0.0f, 0.0f));
	star[0]->setAccel(Vec3(0.0f, 0.0f, 0.0f));
	star[0]->setMass(1);


	star.push_back(new Body(Vec3(100.0f, 140.0f, 0.0f)));
	star[1]->setVel(Vec3(0.0f, 0.0f, 0.0f));
	star[1]->setAccel(Vec3(0.0f, 0.0f, 0.0f));
	star[1]->setMass(100);

	star.push_back(new Body(Vec3(600.0f, 50.0f, 0.0f)));
	star[2]->setVel(Vec3(0.0f, 0.0f, 0.0f));
	star[2]->setAccel(Vec3(0.0f, 0.0f, 0.0f));
	star[2]->setMass(150);
	starAngle = 0.0;

	std::cout << "hello from Scene3 \n";
}

Scene3::~Scene3(){
	for (int i = 0; i < star.size(); i++){
		delete star[i];
	}

	if (renderer) SDL_DestroyRenderer(renderer);
}


//SDL_KeyboardEvent

bool Scene3::OnCreate() {
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* image;
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, 1090.0f, 0.0f, 144.0f, 0.0f, 1.0f);// it's gonna be 0 zero bottom 15 hieght 
	projectionMatrix = ndc * ortho;


	image = IMG_Load("textures/boulder.png");
	Matrix4 invProjection = MMath::inverse(projectionMatrix);
	if (image == nullptr) {
		std::cout << "can't load image \n";
		return false;
	}

	starTexture = SDL_CreateTextureFromSurface(renderer, image);
	int width, height;
	SDL_QueryTexture(starTexture, nullptr, nullptr, &width, &height);
	
	Vec3 size = invProjection * Vec3(width, height, 0.0f);
	size.print();
	for (int i = 0; i < star.size(); ++i)
	{
		star[i]->setRadius(size.x / 4.0f);
	}

	

	return true;
}

void Scene3::OnDestroy() {}

void Scene3::Update(const float deltaTime) {
	
		star[0]->Update(deltaTime);
		star[1]->Update(deltaTime);
		star[2]->Update(deltaTime);

		const float G = 1.0;


		Vec3 DirSt1P1 =  star[1]->getPos() - star[0]->getPos();
		Vec3 DirSt2P1 =   star[2]->getPos() - star[0]->getPos();

		float disSt1P1 = VMath::distance(star[1]->getPos() , star[0]->getPos());
		float disSt2P1 = VMath::distance(star[2]->getPos() , star[0]->getPos());

		Vec3 normalized1 = VMath::normalize(DirSt1P1);
		Vec3 normalized2 = VMath::normalize(DirSt2P1);
		float Mag1 = G* star[1]->getMass()* star[0]->getMass() / disSt1P1 * disSt1P1;
		float Mag2 = G * star[2]->getMass() * star[0]->getMass() / disSt2P1 * disSt2P1;

		Vec3 GforceSt1P1 = Vec3 (normalized1) * Mag1;
		Vec3 GforceSt21P1 = Vec3(normalized2) * Mag2;
		Vec3 netForce = Vec3(GforceSt1P1) + Vec3(GforceSt21P1);
		star[0]->ApplyForce(Vec3(netForce));


		printf("x = %f \n  y =   %f \n mass = %f \n", star[0]->getPos().x, star[0]->getPos().y, star[0]->getMass());
}


void Scene3::HandleEvent(const SDL_Event&  sdlEvent) {

	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE) {
		start = !start;
	}

}

void Scene3::Render() const {
	// clear the screen

	SDL_GetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;

	for (int i = 0; i < star.size(); ++i) {
		screenCoords = projectionMatrix * star[i]->getPos();
		SDL_QueryTexture(starTexture, nullptr, nullptr, &width, &height);
		square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
		square.y = (int)screenCoords.y;
		square.w = width;
		square.h = height;
		SDL_RenderCopyEx(renderer, starTexture, nullptr, &square, star[i]->getAngle(), nullptr, SDL_FLIP_NONE);
	}

	SDL_RenderPresent(renderer);
};