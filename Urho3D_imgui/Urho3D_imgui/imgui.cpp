#include "..\include\im\Urho3D\imgui.h"

#include "..\include\im\Urho3D\imguiEvents.h"
#include "../include/im/Urho3D/imguiGraphics.h"

#include <imgui.h>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/Profiler.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/GraphicsEvents.h>
#include <Urho3D/Graphics/Texture.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/ThirdParty/SDL/SDL_clipboard.h>


namespace Urho3D
{
	//
	// Constructor
	//
	imgui::imgui(Context * context) :
		Object(context)
	{

		ImGuiIO& io = ImGui::GetIO();

		io.KeyMap[ImGuiKey_Tab] = SCANCODE_TAB;                 // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
		io.KeyMap[ImGuiKey_LeftArrow] = SCANCODE_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SCANCODE_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SCANCODE_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SCANCODE_DOWN;
		io.KeyMap[ImGuiKey_Home] = SCANCODE_HOME;
		io.KeyMap[ImGuiKey_End] = SCANCODE_END;
		io.KeyMap[ImGuiKey_Delete] = SCANCODE_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SCANCODE_BACKSPACE;
		io.KeyMap[ImGuiKey_Enter] = SCANCODE_RETURN;
		io.KeyMap[ImGuiKey_Escape] = SCANCODE_ESCAPE;
		io.KeyMap[ImGuiKey_A] = SCANCODE_A;
		io.KeyMap[ImGuiKey_C] = SCANCODE_C;
		io.KeyMap[ImGuiKey_V] = SCANCODE_V;
		io.KeyMap[ImGuiKey_X] = SCANCODE_X;
		io.KeyMap[ImGuiKey_Y] = SCANCODE_Y;
		io.KeyMap[ImGuiKey_Z] = SCANCODE_Z;

		// setup callback functions
		io.RenderDrawListsFn = ImGui_Impl_RenderDrawLists;
		io.SetClipboardTextFn = SetClipboardText;
		io.GetClipboardTextFn = GetClipboardText;

		// Subscribe to events
		SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(imgui, HandlePostUpdate));
		SubscribeToEvent(E_ENDRENDERING, URHO3D_HANDLER(imgui, HandleEndRendering));

		SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(imgui, HandleKeyUp));
		SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(imgui, HandleKeyDown));
		SubscribeToEvent(E_TEXTINPUT, URHO3D_HANDLER(imgui, HandleTextInput));

		SubscribeToEvent(E_TOUCHBEGIN, URHO3D_HANDLER(imgui, HandleTouchBegin));
		SubscribeToEvent(E_TOUCHEND, URHO3D_HANDLER(imgui, HandleTouchEnd));
		SubscribeToEvent(E_TOUCHMOVE, URHO3D_HANDLER(imgui, HandleTouchMove));
	}


	//
	// Desctructor
	//
	imgui::~imgui()
	{
		ImGui_Impl_InvalidateDeviceObjects();
	}


	//
	// GetClipboardText
	//
	const char * imgui::GetClipboardText(void* user_data)
	{
		return SDL_GetClipboardText();
	}


	//
	// SetClipboardText
	//
	void imgui::SetClipboardText(void* user_data, const char * text)
	{
		SDL_SetClipboardText(text);
	}


	//
	// HandlePostUpdate
	//
	void imgui::HandlePostUpdate(StringHash eventType, VariantMap & eventData)
	{
		if (!ImGui_Impl_GetFontTexture())
			ImGui_Impl_CreateDeviceObjects(context_);

		using namespace PostUpdate;
		float timeStep = eventData[P_TIMESTEP].GetFloat();

		auto& io = ImGui::GetIO();

		// Get display size (every frame for resizing)
		auto graphics = GetSubsystem<Graphics>();
		io.DisplaySize = ImVec2((float)graphics->GetWidth(), (float)graphics->GetHeight());

		// Setup time step
		io.DeltaTime = timeStep > 0.0f ? timeStep : 1.0f / 60.0f;

		// mouse input
		auto input = GetSubsystem<Input>();
		if (input->IsMouseVisible() && !input->GetTouchEmulation())
		{
			IntVector2 pos = input->GetMousePosition();
			// Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
			io.MousePos.x = (float)pos.x_;
			io.MousePos.y = (float)pos.y_;
		}
		else
		{
			io.MousePos.x = -1.0f;
			io.MousePos.y = -1.0f;
		}

		io.MouseDown[0] = input->GetMouseButtonDown(MOUSEB_LEFT);
		io.MouseDown[1] = input->GetMouseButtonDown(MOUSEB_RIGHT);
		io.MouseDown[2] = input->GetMouseButtonDown(MOUSEB_MIDDLE);
		io.MouseWheel = (float)input->GetMouseMoveWheel();

		// Modifiers
		io.KeyCtrl = input->GetQualifierDown(QUAL_CTRL);
		io.KeyShift = input->GetQualifierDown(QUAL_SHIFT);
		io.KeyAlt = input->GetQualifierDown(QUAL_ALT);

		// Start new ImGui frame
		ImGui::NewFrame();

		// Send imgui NewFrame events, so users can use it as a guarenteed way to use imgui after NewFrame() was called.
		URHO3D_PROFILE(ImGuiNewFrame);
		SendEvent(E_IMGUI_NEWFRAME);
	}


	//
	// HandleEndRendering
	//
	void imgui::HandleEndRendering(StringHash eventType, VariantMap & eventData)
	{
		// Render after Urho's main renderer has rendered
		URHO3D_PROFILE(ImGuiRender);
		ImGui::Render();
	}


	//
	// HandleKeyUp
	//
	void imgui::HandleKeyUp(StringHash eventType, VariantMap & eventData)
	{
		using namespace KeyUp;

		ImGuiIO& io = ImGui::GetIO();
		int Scancode = eventData[P_SCANCODE].GetInt();

		if (Scancode < 512)
			io.KeysDown[Scancode] = false;
	}


	//
	// HandleKeyDown
	//
	void imgui::HandleKeyDown(StringHash eventType, VariantMap & eventData)
	{
		using namespace KeyDown;
		ImGuiIO& io = ImGui::GetIO();
		int Scancode = eventData[P_SCANCODE].GetInt();

		if (Scancode < 512)
			io.KeysDown[Scancode] = true;
	}


	//
	// HandleTextInput
	//
	void imgui::HandleTextInput(StringHash eventType, VariantMap & eventData)
	{
		using namespace TextInput;
		const String& text = eventData[P_TEXT].GetString();
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharactersUTF8(text.CString());
	}


	//
	// HandleTouchBegin
	//
	void imgui::HandleTouchBegin(StringHash eventType, VariantMap & eventData)
	{
		using namespace TouchBegin;

		if (!touching)
		{
			touching = true;
			single_touchID = eventData[P_TOUCHID].GetInt();

			auto& io = ImGui::GetIO();
			io.MousePos.x = (float)eventData[P_X].GetInt();
			io.MousePos.y = (float)eventData[P_Y].GetInt();
			io.MouseDown[0] = true;
		}
	}


	//
	// HandleTouchEnd
	//
	void imgui::HandleTouchEnd(StringHash eventType, VariantMap & eventData)
	{
		using namespace TouchEnd;
		
		int touchID = eventData[P_TOUCHID].GetInt();
		
		if (touchID == single_touchID)
		{
			auto& io = ImGui::GetIO();
			io.MousePos.x = (float)eventData[P_X].GetInt();
			io.MousePos.y = (float)eventData[P_Y].GetInt();
			io.MouseDown[0] = false;
		}

		touching = false;
	}


	//
	// HandleTouchMove
	//
	void imgui::HandleTouchMove(StringHash eventType, VariantMap & eventData)
	{
		using namespace TouchMove;

		int touchID = eventData[P_TOUCHID].GetInt();

		if (touchID == single_touchID)
		{
			auto& io = ImGui::GetIO();
			io.MousePos.x = (float)eventData[P_X].GetInt();
			io.MousePos.y = (float)eventData[P_Y].GetInt();
		}
	}
}