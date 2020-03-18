#pragma once

#include <halley.hpp>


#include "components/camera_component.h"
#include "components/position_component.h"

// Generated file; do not modify.
template <typename T>
class CameraSystemBase : private Halley::System {
	friend Halley::System* halleyCreateCameraSystem();
	
public:
	class TrackingCameraFamily : public Halley::FamilyBaseOf<TrackingCameraFamily> {
	public:
		const CameraComponent& camera;
		PositionComponent& position;
		
		using Type = Halley::FamilyType<CameraComponent, PositionComponent>;
		
	protected:
		TrackingCameraFamily(const CameraComponent& camera, PositionComponent& position)
			: camera(camera)
			, position(position)
		{}
	};
	
protected:
	void initBase() override {
		invokeInit<T>(static_cast<T*>(this));
		initialiseFamilyBinding<T, TrackingCameraFamily>(trackingCameraFamily, static_cast<T*>(this));
	}
	
public:
	Halley::FamilyBinding<TrackingCameraFamily> trackingCameraFamily;
protected:
	
private:
	void updateBase(Halley::Time time) override final {
		static_cast<T*>(this)->update(time);
	}
	
public:
	CameraSystemBase()
		: System({&trackingCameraFamily}, {})
	{}
};

