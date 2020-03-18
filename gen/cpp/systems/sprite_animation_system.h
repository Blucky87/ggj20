#pragma once

#include <halley.hpp>


#include "components/sprite_component.h"
#include "components/sprite_animation_component.h"
#include "../messages/play_animation_message.h"

// Generated file; do not modify.
template <typename T>
class SpriteAnimationSystemBase : private Halley::System {
	friend Halley::System* halleyCreateSpriteAnimationSystem();
	
public:
	class MainFamily : public Halley::FamilyBaseOf<MainFamily> {
	public:
		SpriteComponent& sprite;
		SpriteAnimationComponent& spriteAnimation;
		
		using Type = Halley::FamilyType<SpriteComponent, SpriteAnimationComponent>;
		
	protected:
		MainFamily(SpriteComponent& sprite, SpriteAnimationComponent& spriteAnimation)
			: sprite(sprite)
			, spriteAnimation(spriteAnimation)
		{}
	};
	
protected:
	void initBase() override {
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, MainFamily>(mainFamily, static_cast<T*>(this));
	}
	
private:
public:
	Halley::FamilyBinding<MainFamily> mainFamily;
protected:
	
private:
	void updateBase(Halley::Time time) override final {
		invokeIndividual([this, &time] (auto& e) { static_cast<T*>(this)->update(time, e); }, mainFamily);
	}
	
	void onMessagesReceived(int msgIndex, Halley::Message** msgs, size_t* idx, size_t n) override final {
		switch (msgIndex) {
		case PlayAnimationMessage::messageIndex: onMessagesReceived(reinterpret_cast<PlayAnimationMessage**>(msgs), idx, n); break;
		}
	}
	
	template <typename M>
	void onMessagesReceived(M** msgs, size_t* idx, size_t n) {
		for (size_t i = 0; i < n; i++) static_cast<T*>(this)->onMessageReceived(*msgs[i], mainFamily[idx[i]]);
	}
	
public:
	SpriteAnimationSystemBase()
		: System({&mainFamily}, {PlayAnimationMessage::messageIndex})
	{}
};

