#include <particlesystem/emitters.h>
#include <particlesystem/particle.h>

#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()

void Emitter::setDelay(float newDelay) { delay = newDelay; }
float Emitter::getDelay() const { return delay; }

bool Emitter::tick(double dt) {
    time += dt;
    //std::cout << "Accumulated Time: " << time << ", Delay: " << delay << std::endl; 
    if (time > delay) {
        time = 0;
        return true;
    }
    return false;
}

// *********** DIRECTIONAL ***********
void Directional::setAngle(float newAngle) { angle = newAngle; }
float Directional::getAngle() const { return angle; }
void Directional::addParticle(std::vector<Particle>& particles, float dt) {

    // Emitter
    Particle E;                         // Emitter particle (Visual representation of the emitter
    E.position = position;              // Set position
    E.radius = 30;                      // Set radius of emitter
    E.color = {1, 0, 0, 1};             // Set color of emitter
    E.velocity = {0.0, 0.0};            // Set velocity of emitter (stationary)
    particles.push_back(E);             // Add Emitter particles to the particle vector

    if (tick(dt)) {                                     // Check if time to emit a new particle
        Particle particle;              // Create Particle
        particle.position = position;   // Set inital spawn point of particle
        particle.lifetime = 2;          // Set lifetime for particle
        particle.color = {1, 1, 1, 1};  // Set color for particle
        particle.radius = 10;           // Set radius for particle
        
        angle = this->getAngle();                       // Get current emission angle set in UI
        particle.velocity = {cos(angle), sin(angle)};   // Set velocity based on angle
        particle.radius = particle.radius;              // Set the shot out particle's radius 
        particles.push_back(particle);                  // Add new particle to particles vector
    }
}

// *********** RING ***********
// Helper function to generate random floats
float Ring::randomFloat(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Ring::addParticle(std::vector<Particle>& particles, float dt) {
    // Emitter visualization (optional)
    Particle E;                 // Emitter particle (Visual representation of the emitter)
    E.position = position;      // Set position of the emitter (center)
    E.radius = 30;              // Set radius of emitter
    E.color = {1, 0, 1, 1};     // Set color of emitter (purple)
    E.velocity = {0.0, 0.0};    // Set velocity of emitter (stationary)
    particles.push_back(E);     // Add Emitter particles to the particle vector

    if (tick(dt)) {
        Particle particle;      // Create Particle
        particle.lifetime = 2;  // Set lifetime for particle
        particle.color = {randomFloat(0.0f, 1.0f), randomFloat(0.0f, 1.0f), randomFloat(0.0f, 1.0f),1.0f};
        particle.radius = 15;     // Set radius for particle

        // Calculate random angle for particle emission
        float angle = randomFloat(0.0f, 6.28f);  // Random angle (0 to 2pi)

        // Set particle position on the circumference of the ring
        particle.position = {position.x + radius * cos(angle), position.y + radius * sin(angle)};  // y = center.y + radius * sin(angle)

        // Set particle velocity (tangential to the ring)
        particle.velocity = {-sin(angle), cos(angle)};  // Tangential direction
        //particle.velocity = {cos(angle), sin(angle)}; // Straight out of circle

        particles.push_back(particle);  // Add particle to the vector
    }
}

// *********** EXPLOSION ***********
// Helper function to generate random floats
float Explosion::randomFloat(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Explosion::addParticle(std::vector<Particle>& particles, float dt) {
    burstTimer += dt;

    // Emitter
    Particle E;                      // Emitter particle (Visual representation of the emitter
    E.position = position;           // Set position
    E.radius = 30;                   // Set radius of emitter
    E.color = {1, 0, 1, 1};          // Set color of emitter
    E.velocity = {0.0, 0.0};         // Set velocity of emitter (stationary)
    particles.push_back(E);          // Add Emitter particles to the particle vector

    if (!isBursting && burstTimer >= burstInterval) {
        // Start a new burst
        isBursting = true;
        burstTimer = 0.0f;
    }

    if (isBursting) {   // Lmao
        if (burstTimer < burstDuration) {
            // Emit particles during the burst
            int numParticles = 100;                                             // Number of particles to emit per frame during the burst
            for (int i = 0; i < numParticles; ++i) {
                Particle particle;                                              // Create Particle
                particle.position = position;                                   // Set inital spawn point of particle
                particle.color = {randomFloat(0.0f, 1.0f), randomFloat(0.0f, 1.0f),randomFloat(0.0f, 1.0f), 1};
                particle.lifetime = randomFloat(0.5f, 1.5f);                    // Random lifetime
                particle.color = {1.0f, randomFloat(0.5f, 1.0f), 0.0f, 1.0f};   // Orange fire color
                particle.radius = randomFloat(2.0f, 5.0f);                      // Random size

                // Random velocity in all directions
                float angle = randomFloat(0.0f, 6.28f);                         // Random angle (0 to 2pi)
                float speed = randomFloat(0.1f, 0.5f);                          // Random speed
                particle.velocity = {cos(angle) * speed, sin(angle) * speed};   // Fly outwards

                particles.push_back(particle);  // Add particle to the vector
            }
        } else {
            // End the burst
            isBursting = false;
            burstTimer = 0.0f;
        }
    }
}