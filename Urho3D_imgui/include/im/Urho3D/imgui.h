#ifndef im_Urho3D_imgui_h
#define im_Urho3D_imgui_h


#include <Urho3D/Core/Object.h>


namespace Urho3D
{
	class Texture2D;


	class imgui : public Object
	{
		URHO3D_OBJECT(imgui, Object);

	public:
		imgui(Context* context);



	protected:
		// Used to track if there's already a touch, since imgui doesn't have multi-touch support.
		bool touching = false;
		// The touch ID of the single tracked touch
		int single_touchID;


		static const char* GetClipboardText();
		static void SetClipboardText(const char* text);

		// Call ImGui::NewFrame()
		void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
		// Call ImGui::Render()
		void HandleEndRendering(StringHash eventType, VariantMap& eventData);

		// Input
		void HandleKeyUp(StringHash eventType, VariantMap& eventData);
		void HandleKeyDown(StringHash eventType, VariantMap& eventData);
		void HandleTextInput(StringHash eventType, VariantMap& eventData);
		void HandleTouchBegin(StringHash eventType, VariantMap& eventData);
		void HandleTouchEnd(StringHash eventType, VariantMap& eventData);
		void HandleTouchMove(StringHash eventType, VariantMap& eventData);
	};
}


#endif//im_Urho3D_imgui_h