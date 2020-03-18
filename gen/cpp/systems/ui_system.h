#pragma once

#include <halley.hpp>

#include "src/services/item_service.h"
#include "src/services/ui_service.h"

#include "components/sprite_animation_component.h"
#include "components/ui_component.h"

// Generated file; do not modify.
template <typename T>
class UISystemBase : private Halley::System {
	friend Halley::System* halleyCreateUISystem();
	
public:
	class UiFamily : public Halley::FamilyBaseOf<UiFamily> {
	public:
		SpriteAnimationComponent& spriteAnimation;
		const UIComponent& uI;
		
		using Type = Halley::FamilyType<SpriteAnimationComponent, UIComponent>;
		
	protected:
		UiFamily(SpriteAnimationComponent& spriteAnimation, const UIComponent& uI)
			: spriteAnimation(spriteAnimation)
			, uI(uI)
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
	
public:
	ItemService* itemService = nullptr;
	ItemService& getItemService() const {
		return *itemService;
	}
	
	UIService* uIService = nullptr;
	UIService& getUIService() const {
		return *uIService;
	}
	void initBase() override {
		itemService = &doGetWorld().template getService<ItemService>();
		uIService = &doGetWorld().template getService<UIService>();
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, UiFamily>(uiFamily, static_cast<T*>(this));
	}
	
protected:
public:
	Halley::FamilyBinding<UiFamily> uiFamily;
protected:
	
private:
	void updateBase(Halley::Time time) override final {
		static_cast<T*>(this)->update(time);
	}
	
public:
	UISystemBase()
		: System({&uiFamily}, {})
	{}
};

