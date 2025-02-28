#pragma once

#include <particlesystem/particle.h>
#include <particlesystem/effects.h>


#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class Emitter {
	public: 
		
		double time = 0.0;		// time since last 
        double delay = 0.0;     // Time interval between emissions
        float radius = 0.0f;	// Radius size
        bool tick(double dt);	// Updates emitter state; true if emitting
        glm::vec2 position = {0.0f, 0.0f};

		// Virtual function to add particles, must be implemented by child classes.
		virtual void addParticle(std::vector<Particle>& particles, float dt) = 0;

        // For delay
        float getDelay() const;
        void setDelay(float newDelay);

        // For position
        void setPosition(float x, float y) { position = {x, y}; }
        glm::vec2 getPosition() const { return position; }
};

class Directional : public Emitter {
	public:
		void addParticle(std::vector<Particle>& particles, float dt) override;

		float getAngle() const;
		void setAngle(float newAngle);
        Directional(float angle, double delay) : Emitter(), angle(angle), delay(delay) {} 

	private:
		float angle;
        double delay;  // Time interval between emissions
};

class Ring : public Emitter {
public:
    void addParticle(std::vector<Particle>& particles, float dt) override;

    // Constructor
    Ring(float initialRadius = 0.2f, double initialDelay = 1.0f)
        : Emitter(), radius(initialRadius), delay(initialDelay) {}  // Initialize delay here

    // Setter for radius
    void setRadius(float newRadius) { radius = newRadius; }

private:
    float radius;  // Radius of the ring
    double delay;  // Delay between emissions

    // Helper for random number generation
    float randomFloat(float min, float max);
};

class Explosion : public Emitter {
public:
    void addParticle(std::vector<Particle>& particles, float dt) override;

    // Constructor
    void setBurstInterval(float newInterval) { burstInterval = newInterval; }
    void setBurstDuration(float newDuration) { burstDuration = newDuration; }
    Explosion(float burstInterval = 2.0f, float burstDuration = 0.2f)
        : Emitter()
        , burstInterval(burstInterval)
        , burstDuration(burstDuration)
        , burstTimer(0.0f)
        , isBursting(false) {}

private:
    // Helper for random number generation
    float randomFloat(float min, float max);

    float burstInterval;  // Time between bursts
    float burstDuration;  // Duration of each burst
    float burstTimer;     // Timer for burst cycle
    bool isBursting;      // Whether the emitter is currently bursting

};