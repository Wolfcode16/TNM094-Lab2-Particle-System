#include <particlesystem/particlesystem.h>
#include <particlesystem/particle.h>
#include <particlesystem/emitters.h>
#include <particlesystem/effects.h>

#include <vector>

void Particlesystem::update(float dt) {
    // Update particles and remove dead ones
    particles.erase(std::remove_if(particles.begin(), particles.end(),
                    [dt](Particle& p) {
                        p.lifetime -= dt;
                        p.position += p.velocity * dt;
                        return p.lifetime <= 0;  // Remove if lifetime is over
                    }),
    particles.end());

    // Add new particles from emitters
    for (auto& emitter : emitters) {
        if (emitter) {
            emitter->addParticle(particles, dt);
        }
    }

    // Apply forces from effects
    for (auto& effect : effects) {
        if (effect) {
            effect->applyEffect(particles);
        }
    }
}