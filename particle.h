#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>		// Includes random number generator

class Particle {
public:
    // Attributes taken from A.1.2 State of a Particle (Lab2 PDF)
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 force;
    glm::vec4 color;
    float mass;
    float lifetime;
    float radius;

    // Constructor
    Particle(glm::vec2 pos = {0, 0}, glm::vec2 vel = {0, 0}, glm::vec2 force = {0, 0},
             glm::vec4 col = {0, 0, 0, 0}, float mass = 0, float life = 0, float rad = 0)
        : position(pos)
        , velocity(vel)
        , force(force)
        , color(col)
        , mass(mass)
        , lifetime(life)
        , radius(rad) {}
    
    // Destructor
    ~Particle() {}
};