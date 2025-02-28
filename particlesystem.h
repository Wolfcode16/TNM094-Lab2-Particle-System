#pragma once

#include <particlesystem/particle.h>
#include <particlesystem/emitters.h>
#include <particlesystem/effects.h>

#include <vector>
#include <glm/vec2.hpp>

class Particlesystem {
	public:
		void update(float dt);              // Updates time
        std::vector<Particle> particles;    // No pointer due to no polymorphism
        std::vector<Emitter*> emitters;     // Use pointer cause of polymorphism
        std::vector<Effect*> effects;       // Use pointer cause of polymorphism
};