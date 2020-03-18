#pragma once

#include <halley.hpp>


#include "components/environment_object_component.h"
#include "components/sprite_animation_component.h"
#include "components/bouncy_component.h"
#include "components/sprite_component.h"

// Generated file; do not modify.
template <typename T>
class EnvironmentObjectSystemBase : private Halley::System {
	friend Halley::System* halleyCreateEnvironmentObjectSystem();
	
public:
	class ObjectFamily : public Halley::FamilyBaseOf<ObjectFamily> {
	public:
		EnvironmentObjectComponent& environmentObject;
		SpriteAnimationComponent& spriteAnimation;
		
		using Type = Halley::FamilyType<EnvironmentObjectComponent, SpriteAnimationComponent>;
		
	protected:
		ObjectFamily(EnvironmentObjectComponent& environmentObject, SpriteAnimationComponent& spriteAnimation)
			: environmentObject(environmentObject)
			, spriteAnimation(spriteAnimation)
		{}
	};
	
	class BouncyFamily : public Halley::FamilyBaseOf<BouncyFamily> {
	public:
		const BouncyComponent& bouncy;
		SpriteComponent& sprite;
		
		using Type = Halley::FamilyType<BouncyComponent, SpriteComponent>;
		
	protected:
		BouncyFamily(const BouncyComponent& bouncy, SpriteComponent& sprite)
			: bouncy(bouncy)
			, sprite(sprite)
		{}
	};
	
protected:
	Halley::World& getWorld() const {
		return doGetWorld();
	}
	Halley::Resources& getResources() const {
		return doGetAPI().core->getResources();
	}
	void initBase() override {
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, ObjectFamily>(objectFamily, static_cast<T*>(this));
		initialiseFamilyBinding<T, BouncyFamily>(bouncyFamily, static_cast<T*>(this));
	}
	
public:
	Halley::FamilyBinding<ObjectFamily> objectFamily;
protected:
public:
	Halley::FamilyBinding<BouncyFamily> bouncyFamily;
	
private:
	void updateBase(Halley::Time time) override final {
		static_cast<T*>(this)->update(time);
	}
	
public:
	EnvironmentObjectSystemBase()
		: System({&objectFamily, &bouncyFamily}, {})
	{}
};

