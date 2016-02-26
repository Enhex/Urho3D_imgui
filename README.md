# Urho3D_imgui
External library for integrating imgui with Urho3D.
No forks to switch to and maintain.

Currently it only has OpenGL3 renderer implementation.

Currently only Visual Studio 2015 solution is provided, no cross platform build system.
To setup a project for another system just include Urho3D, Urho3D\ThridParty, and imgui, and add GLEW_STATIC preprocessor.

Using C++11.

### Usage
You need to add imgui to your Urho3D project.

Create an instance of Urho3D::imgui for your application.
Include "imguiEvents.h" and subscribe to **E_IMGUI_NEWFRAME** to create imgui UI. The event is sent after ImGui::NewFrame() is called.
Check the Test project for example.

The test application doesn't have proper CMake. You need to add imgui and this library manually.

### License
MIT license.
