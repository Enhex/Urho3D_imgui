#include "MyApp.hpp"
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Resource/ResourceCache.h>

#include <im/Urho3D/imguiEvents.h>
#include <imgui.h>


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
	// Set background color
	auto renderer = GetSubsystem<Renderer>();
	auto zone = renderer->GetDefaultZone();
	zone->SetFogColor(Color(0.4f, 0.65f, 0.9f));

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

	// imgui's Test window
	ImGui::ShowTestWindow();

	// Using Urho3D texture with the integration's renderer
	auto cache = GetSubsystem<ResourceCache>();
	auto logoTexture = cache->GetResource<Texture2D>("Textures/LogoLarge.png");
	if (!logoTexture)
		return;

	ImGui::Image(logoTexture, ImVec2((float)logoTexture->GetWidth(), (float)logoTexture->GetHeight()), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
}