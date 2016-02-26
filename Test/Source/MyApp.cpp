#include "MyApp.hpp"
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>

#include <im/Urho3D/imguiEvents.h>
#include <imgui.h>

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Font.h>

//
// Constructor
//
MyApp::MyApp(Context* context) :
Application(context)
{
}


void MyApp::Setup()
{
	// Modify engine startup parameters
	engineParameters_["FullScreen"] = false;
}

//
// Start
//
void MyApp::Start()
{
	// Enable OS cursor
	GetSubsystem<Input>()->SetMouseVisible(true);

	// Create the imgui system
	imGui = new imgui(context_);

	// Called after engine initialization. Setup application & subscribe to events here
	SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MyApp, HandleKeyDown));
	SubscribeToEvent(E_IMGUI_NEWFRAME, URHO3D_HANDLER(MyApp, HandleImGuiNewFrame));
}


//
// HandleKeyDown
//
void MyApp::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
	using namespace KeyDown;
	// Check for pressing ESC. Note the engine_ member variable for convenience access to the Engine object
	int key = eventData[P_KEY].GetInt();
	if (key == KEY_ESC)
		engine_->Exit();
}


//
// HandleImGuiNewFrame
//
void MyApp::HandleImGuiNewFrame(StringHash eventType, VariantMap& eventData)
{
	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
	{
		static float f = 0.0f;
		ImGui::Text("Hello, world!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	ImGui::ShowTestWindow();
}