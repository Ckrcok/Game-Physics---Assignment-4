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


	star.push_back(new Body(Vec3(10.f, 20.f, 0.0f)));

	star[0]->setVel(Vec3(0.0f, 0.0f, 0.0f));
	star[0]->setAccel(Vec3(0.0f, 0.0f, 0.0f));

	star.push_back(new Body(Vec3(5.0f, 10.0f, 0.0f)));
	star[1]->setVel(Vec3(0.0f, 0.0f, 0.0f));
	star[1]->setAccel(Vec3(0.0f, 0.0f, 0.0f));

	star.push_back(new Body(Vec3(15.0f, 25.0f, 0.0f)));
	star[2]->setVel(Vec3(0.0f, 0.0f, 0.0f));
	star[2]->setAccel(Vec3(0.0f, 0.0f, 0.0f));
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
	Matrix4 ortho = MMath::orthographic(0.0f, 50.0f, 0.0f, 50.0f, 0.0f, 1.0f);// it's gonna be 0 zero bottom 15 hieght 
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
		star[i]->setRadius(size.x / 2.0f);
	}

	

	return true;
}

void Scene3::OnDestroy() {}

void Scene3::Update(const float deltaTime) {
	
		star[0]->Update(deltaTime);


		Vec3 DirSt1P1 =  star[1]->getPos() - star[0]->getPos();
		Vec3 DirSt2P1 =   star[2]->getPos() - star[0]->getPos();

		float disSt1P1 = VMath::distance(star[0]->getPos(), star[1]->getPos());
		float disSt2P1 = VMath::distance(star[0]->getPos(), star[2]->getPos());


		//Star[0]->ApplyForce;




		//if(distance <  star[0]->getRadius() + star[1]->getRadius()) {
		//	// gether the info

		//	Vec3 v1 = star[0]->getVel();
		//	Vec3 v2 = star[1]->getVel();
		//	float m1 = star[0]->getMass();
		//	float m2 = star[1]->getMass();
		//	float e = 1.0f;

		//	// Do the collision
		//	Vec3 lineOfAction = star[0]->getPos() - star[1]->getPos();
		//	Vec3 normal = VMath::normalize(lineOfAction);
		//	float v1p = VMath::dot(v1, normal);
		//	float v2p = VMath::dot(v2, normal);
		//	float v1pnew = (m1 - e * m2) * v1p + (1.0f + e) * m2 * v2p / (m1 + m2);
		//	float v2pnew = (m2 - e * m1) * v2p + (1.0f + e) * m1 * v1p / (m1 + m2);

		//	if ((v1p - v2p) > 0.0f) {

		//	}

		//	Vec3 v1new = v1 + (v1pnew - v1p) * normal;
		//	Vec3 v2new = v2 + (v2pnew - v2p) * normal;

		//	star[0]->setVel(v1new);
		//	star[1]->setVel(v2new);

		//	std::cout << "Collision\n";
		//}
		//else {
		//	std::cout << "Nothing\n";
		//}
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