#include "Scene2.h"
#include <SDL.h>
#include <SDL_image.h>
Scene2::Scene2(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std:: cout << "Can't create the renderer \n";
	}
	flappyBird = new Body(Vec3(0, 16.0f,0.0f )); // (x , y , z)
	//flappyBird->setAccel(Vec3(6.0f, -9.81, 0.0f));
	boulder = new Body(Vec3(0.0f, 2.25f, 0.0f));
	boulder->setVel(Vec3(3.0f, 0.0f, 0.0f));
	boulderAngle = 0.0;

	std::cout << "hello from Scene2 \n";
}

Scene2::~Scene2(){
	delete flappyBird;
	delete boulder;
}


//SDL_KeyboardEvent

bool Scene2::OnCreate() {
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

	image = IMG_Load("textures/boulder.png");
	Matrix4 invProjection = MMath::inverse(projectionMatrix);
	if (image == nullptr) {
		std::cout << "can't load image \n";
		return false;
	}

	boulderTexture = SDL_CreateTextureFromSurface(renderer, image);
	int width, height;
	SDL_QueryTexture(boulderTexture, nullptr, nullptr, &width, &height);
	
	Vec3 size = invProjection * Vec3(width, height, 0.0f);
	size.print();
	boulder->setRadius(size.x / 2.0f);

	return true;
}

void Scene2::OnDestroy() {}

void Scene2::Update(const float deltaTime) {
	
	if (start == true) {
		//printf("%f\n", deltaTime);
		boulderAngle += 2.0;
		flappyBird->Update(deltaTime);
		boulder->Update(deltaTime);
		//apply force
		//ApplyForce(); 
		//wind 
		//totalForce = gravity + drag; // + wind 
	}
}


void Scene2::HandleEvent(const SDL_Event&  sdlEvent) {

	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE) {
		start = !start;
	}

}

void Scene2::Render() const {
	// clear the screen

	SDL_GetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	Vec3 screenCoords;
	SDL_Rect square;
	int width, height;


	screenCoords = projectionMatrix * boulder->getPos();
	SDL_QueryTexture(boulderTexture, nullptr, nullptr, &width, &height);
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;


	SDL_RenderCopyEx(renderer, boulderTexture, nullptr, &square, boulder->getAngle(), nullptr, SDL_FLIP_NONE);




	screenCoords = projectionMatrix * flappyBird->getPos();
	SDL_QueryTexture(flappyBirdTexture, nullptr, nullptr, &width, &height);
	square.x = (int)screenCoords.x; /// We must update this with C11 typecasting - SSF
	square.y = (int)screenCoords.y;
	square.w = width;
	square.h = height;
	SDL_RenderCopyEx(renderer, flappyBirdTexture, nullptr, &square, 0.0, nullptr, SDL_FLIP_NONE);


	SDL_RenderPresent(renderer);
};