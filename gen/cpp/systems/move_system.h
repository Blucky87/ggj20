#pragma once

#include <halley.hpp>


#include "components/move_animation_component.h"
#include "components/position_component.h"
#include "../messages/move_message.h"

// Generated file; do not modify.
template <typename T>
class MoveSystemBase : private Halley::System {
	friend Halley::System* halleyCreateMoveSystem();
	
public:
	class MainFamily : public Halley::FamilyBaseOf<MainFamily> {
	public:
		MoveAnimationComponent& moveAnimation;
		PositionComponent& position;
		
		using Type = Halley::FamilyType<MoveAnimationComponent, PositionComponent>;
		
	protected:
		MainFamily(MoveAnimationComponent& moveAnimation, PositionComponent& position)
			: moveAnimation(moveAnimation)
			, position(position)
		{}
	};
	
protected:
	void initBase() override {
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, MainFamily>(mainFamily, static_cast<T*>(this));
	}
	
public:
	Halley::FamilyBinding<MainFamily> mainFamily;
protected:
	
private:
	void updateBase(Halley::Time time) override final {
		static_cast<T*>(this)->update(time);
	}
	
	void onMessagesReceived(int msgIndex, Halley::Message** msgs, size_t* idx, size_t n) override final {
		switch (msgIndex) {
		case MoveMessage::messageIndex: onMessagesReceived(reinterpret_cast<MoveMessage**>(msgs), idx, n); break;
		}
	}
	
	template <typename M>
	void onMessagesReceived(M** msgs, size_t* idx, size_t n) {
		for (size_t i = 0; i < n; i++) static_cast<T*>(this)->onMessageReceived(*msgs[i], mainFamily[idx[i]]);
	}
	
public:
	MoveSystemBase()
		: System({&mainFamily}, {MoveMessage::messageIndex})
	{}
};

