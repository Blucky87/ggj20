#pragma once

#include <halley.hpp>

#include "src/services/rhythm_service.h"
#include "src/services/item_service.h"
#include "src/services/input_service.h"
#include "src/services/ui_service.h"


// Generated file; do not modify.
template <typename T>
class GameStateSystemBase : private Halley::System {
	friend Halley::System* halleyCreateGameStateSystem();
	
public:
protected:
	const Halley::HalleyAPI& getAPI() const {
		return doGetAPI();
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
	}
	
protected:
	
private:
	void updateBase(Halley::Time time) override final {
		static_cast<T*>(this)->update(time);
	}
	
public:
	GameStateSystemBase()
		: System({}, {})
	{}
};

