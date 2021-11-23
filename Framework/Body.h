#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#pragma once
using namespace MATH;

class Body {
private:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	float radius;
	double angle;
public:
	Body();
	Body(Vec3 pos_);
	~Body();
	void Update(float deltaTime);

	float getMass() {
		return mass;
	}

	Vec3 getPos() { return pos; }
	void setAccel(const Vec3 &accel_) {
		accel.x = accel_.x;
		accel.y = accel_.y;
		accel.z = accel_.z;
	}
	void setVel(const Vec3& vel_) {
		vel.x = vel_.x;
		vel.y = vel_.y;
		vel.z = vel_.z;
	}
	Vec3 getVel() {
		return vel;
	}

	void setMass(float mass_) {
		mass = mass_;
	}

	void setRadius(const float radius_) {
		radius = radius_;
	}

	float getRadius() {
		return radius;
	}

	double getAngle() {
		return angle;
	}

	void ApplyForce(Vec3 force);
};

#endif