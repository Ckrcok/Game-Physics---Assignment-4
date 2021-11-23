#include "Body.h"
#include "SDL_timer.h"

Body::Body(){
	pos.x = 2.0f;
	pos.y = 12.5f;
	pos.z = 0.0f;

	vel.x = 15.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = -9.81f;
	accel.z = 0.0f;

	mass = 0.0f;
	radius = 1.0f;
	angle = 0.0;
}


Body::Body(Vec3 pos_) {
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = 0;
	accel.z = 0.0f;

	mass = 1.0f;
	radius = 1.0f;
	angle = 0.0;
}

Body::~Body(){

}



void Body::Update(float deltaTime) {
	pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
	vel += accel * deltaTime;

	float radianToDegrees = 360.0f / 2.0f * M_PI;
	float circumference = 2.0f * M_PI * radius;
	angle += radianToDegrees * vel.x * deltaTime / circumference;



}




//apply force
void Body::ApplyForce(Vec3 force) {
	accel = force / mass;
}