#pragma once

#include <particlesystem/effects.h>
#include <particlesystem/particle.h>
#include <particlesystem/emitters.h>

#include <vector>
#include <glm/vec2.hpp>

class Effect {
	public:
    virtual void applyEffect(std::vector<Particle>& particles) = 0;
};

// Add Effects