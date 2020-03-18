#pragma once

#include <halley.hpp>

#include "src/services/item_service.h"
#include "src/services/ui_service.h"

#include "components/camera_component.h"
#include "components/position_component.h"

// Generated file; do not modify.
template <typename T>
class UIRenderSystemBase : private Halley::System {
	friend Halley::System* halleyCreateUIRenderSystem();
	
public:
	class CameraFamily : public Halley::FamilyBaseOf<CameraFamily> {
	public:
		const CameraComponent& camera;
		const PositionComponent& position;
		
		using Type = Halley::FamilyType<CameraComponent, PositionComponent>;
		
	protected:
		CameraFamily(const CameraComponent& camera, const PositionComponent& position)
			: camera(camera)
			, position(position)
		{}
	};
	
protected:
	const Halley::HalleyAPI& getAPI() const {
		return doGetAPI();
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
		initialiseFamilyBinding<T, CameraFamily>(cameraFamily, static_cast<T*>(this));
	}
	
protected:
public:
	Halley::FamilyBinding<CameraFamily> cameraFamily;
protected:
	
private:
	void renderBase(Halley::RenderContext& rc) override final {
		static_cast<T*>(this)->render(rc);
	}
	
public:
	UIRenderSystemBase()
		: System({&cameraFamily}, {})
	{}
};

