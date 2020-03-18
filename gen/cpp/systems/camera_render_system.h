#pragma once

#include <halley.hpp>

#include "src/services/painter_service.h"

#include "components/camera_component.h"
#include "components/position_component.h"

// Generated file; do not modify.
template <typename T>
class CameraRenderSystemBase : private Halley::System {
	friend Halley::System* halleyCreateCameraRenderSystem();
	
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
	
public:
	PainterService* painterService = nullptr;
	PainterService& getPainterService() const {
		return *painterService;
	}
	void initBase() override {
		painterService = &doGetWorld().template getService<PainterService>();
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
	CameraRenderSystemBase()
		: System({&cameraFamily}, {})
	{}
};

