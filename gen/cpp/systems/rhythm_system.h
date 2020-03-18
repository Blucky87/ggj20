#pragma once

#include <halley.hpp>

#include "src/services/rhythm_service.h"
#include "src/services/item_service.h"
#include "src/services/input_service.h"
#include "src/services/ui_service.h"

#include "components/position_component.h"
#include "components/rhythm_area_component.h"
#include "components/bouncy_component.h"

// Generated file; do not modify.
template <typename T>
class RhythmSystemBase : private Halley::System {
	friend Halley::System* halleyCreateRhythmSystem();
	
public:
	class MainFamily : public Halley::FamilyBaseOf<MainFamily> {
	public:
		const PositionComponent& position;
		RhythmAreaComponent& rhythmArea;
		
		using Type = Halley::FamilyType<PositionComponent, RhythmAreaComponent>;
		
	protected:
		MainFamily(const PositionComponent& position, RhythmAreaComponent& rhythmArea)
			: position(position)
			, rhythmArea(rhythmArea)
		{}
	};
	
	class BouncyFamily : public Halley::FamilyBaseOf<BouncyFamily> {
	public:
		BouncyComponent& bouncy;
		
		using Type = Halley::FamilyType<BouncyComponent>;
		
	protected:
		BouncyFamily(BouncyComponent& bouncy)
			: bouncy(bouncy)
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
	RhythmService* rhythmService = nullptr;
	RhythmService& getRhythmService() const {
		return *rhythmService;
	}
	
	ItemService* itemService = nullptr;
	ItemService& getItemService() const {
		return *itemService;
	}
	
	InputService* inputService = nullptr;
	InputService& getInputService() const {
		return *inputService;
	}
	
	UIService* uIService = nullptr;
	UIService& getUIService() const {
		return *uIService;
	}
	void initBase() override {
		rhythmService = &doGetWorld().template getService<RhythmService>();
		itemService = &doGetWorld().template getService<ItemService>();
		inputService = &doGetWorld().template getService<InputService>();
		uIService = &doGetWorld().template getService<UIService>();
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, MainFamily>(mainFamily, static_cast<T*>(this));
		initialiseFamilyBinding<T, BouncyFamily>(bouncyFamily, static_cast<T*>(this));
	}
	
protected:
public:
	Halley::FamilyBinding<MainFamily> mainFamily;
protected:
public:
	Halley::FamilyBinding<BouncyFamily> bouncyFamily;
	
private:
	void updateBase(Halley::Time time) override final {
		static_cast<T*>(this)->update(time);
	}
	
public:
	RhythmSystemBase()
		: System({&mainFamily, &bouncyFamily}, {})
	{}
};

