#pragma once

#include <halley.hpp>

#include "src/services/rhythm_service.h"
#include "src/services/item_service.h"
#include "src/services/ui_service.h"

#include "components/item_component.h"
#include "components/position_component.h"
#include "components/sprite_component.h"
#include "components/environment_object_component.h"
#include "components/sprite_animation_component.h"
#include "../messages/move_message.h"

// Generated file; do not modify.
template <typename T>
class ItemsSystemBase : private Halley::System {
	friend Halley::System* halleyCreateItemsSystem();
	
public:
	class ItemFamily : public Halley::FamilyBaseOf<ItemFamily> {
	public:
		ItemComponent& item;
		PositionComponent& position;
		SpriteComponent& sprite;
		
		using Type = Halley::FamilyType<ItemComponent, PositionComponent, SpriteComponent>;
		
	protected:
		ItemFamily(ItemComponent& item, PositionComponent& position, SpriteComponent& sprite)
			: item(item)
			, position(position)
			, sprite(sprite)
		{}
	};
	
	class VulcanFamily : public Halley::FamilyBaseOf<VulcanFamily> {
	public:
		EnvironmentObjectComponent& environmentObject;
		SpriteAnimationComponent& spriteAnimation;
		
		using Type = Halley::FamilyType<EnvironmentObjectComponent, SpriteAnimationComponent>;
		
	protected:
		VulcanFamily(EnvironmentObjectComponent& environmentObject, SpriteAnimationComponent& spriteAnimation)
			: environmentObject(environmentObject)
			, spriteAnimation(spriteAnimation)
		{}
	};
	
protected:
	const Halley::HalleyAPI& getAPI() const {
		return doGetAPI();
	}
	Halley::World& getWorld() const {
		return doGetWorld();
	}
	Halley::Resources& getResources() const {
		return doGetAPI().core->getResources();
	}
	void sendMessage(Halley::EntityId entityId, const MoveMessage& msg) {
		sendMessageGeneric(entityId, msg);
	}
	
public:
	RhythmService* rhythmService = nullptr;
	RhythmService& getRhythmService() const {
		return *rhythmService;
	}
	
	ItemService* itemService = nullptr;
	ItemService& getItemService() const {
		return *itemService;
	}
	
	UIService* uIService = nullptr;
	UIService& getUIService() const {
		return *uIService;
	}
	void initBase() override {
		rhythmService = &doGetWorld().template getService<RhythmService>();
		itemService = &doGetWorld().template getService<ItemService>();
		uIService = &doGetWorld().template getService<UIService>();
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, ItemFamily>(itemFamily, static_cast<T*>(this));
		initialiseFamilyBinding<T, VulcanFamily>(vulcanFamily, static_cast<T*>(this));
	}
	
protected:
public:
	Halley::FamilyBinding<ItemFamily> itemFamily;
protected:
public:
	Halley::FamilyBinding<VulcanFamily> vulcanFamily;
	
private:
	void updateBase(Halley::Time time) override final {
		static_cast<T*>(this)->update(time);
	}
	
public:
	ItemsSystemBase()
		: System({&itemFamily, &vulcanFamily}, {})
	{}
};

