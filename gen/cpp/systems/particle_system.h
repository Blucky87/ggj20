#pragma once

#include <halley.hpp>


#include "components/particle_component.h"
#include "components/position_component.h"
#include "components/sprite_animation_component.h"

// Generated file; do not modify.
template <typename T>
class ParticleSystemBase : private Halley::System {
	friend Halley::System* halleyCreateParticleSystem();
	
public:
	class ParticleFamily : public Halley::FamilyBaseOf<ParticleFamily> {
	public:
		ParticleComponent& particle;
		PositionComponent& position;
		SpriteAnimationComponent& spriteAnimation;
		
		using Type = Halley::FamilyType<ParticleComponent, PositionComponent, SpriteAnimationComponent>;
		
	protected:
		ParticleFamily(ParticleComponent& particle, PositionComponent& position, SpriteAnimationComponent& spriteAnimation)
			: particle(particle)
			, position(position)
			, spriteAnimation(spriteAnimation)
		{}
	};
	
protected:
	Halley::World& getWorld() const {
		return doGetWorld();
	}
	void initBase() override {
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, ParticleFamily>(particleFamily, static_cast<T*>(this));
	}
	
public:
	Halley::FamilyBinding<ParticleFamily> particleFamily;
protected:
	
private:
	void updateBase(Halley::Time time) override final {
		static_cast<T*>(this)->update(time);
	}
	
public:
	ParticleSystemBase()
		: System({&particleFamily}, {})
	{}
};

