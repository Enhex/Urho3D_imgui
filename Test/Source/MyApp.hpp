#ifndef MY_APP_HPP
#define MY_APP_HPP


#include <Urho3D/Urho3D.h>
#include <Urho3D/Engine/Application.h>

#include <im/Urho3D/imgui.h>

using namespace Urho3D;


class MyApp : public Application
{
public:
	MyApp(Context* context);
	

	SharedPtr<imgui> imGui;

	virtual void Setup();

	void Start();

	void HandleKeyDown(StringHash eventType, VariantMap& eventData);
	void HandleImGuiNewFrame(StringHash eventType, VariantMap& eventData);
};


#endif//MY_APP_HPP