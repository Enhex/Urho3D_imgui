// ImGui GLFW binding with OpenGL3 + shaders
// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you use this binding you'll need to call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(), ImGui::Render() and ImGui_ImplXXXX_Shutdown().
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

#include <GLEW/glew.h>

struct ImDrawData;


GLuint ImGui_Impl_GetFontTexture();

void ImGui_Impl_RenderDrawLists(ImDrawData* draw_data);
void        ImGui_Impl_Shutdown();

// Use if you want to reset your rendering device without losing ImGui state.
void        ImGui_Impl_InvalidateDeviceObjects();
bool        ImGui_Impl_CreateDeviceObjects();