#ifndef im_Urho3D_imguiGraphics_h
#define im_Urho3D_imguiGraphics_h


#if defined(URHO3D_OPENGL)
#include "..\include\im\Urho3D\imgui_impl_gl3.h"
// TODO add the other implementations
#elif defined(URHO3D_D3D11)
#include "..\include\im\Urho3D\imgui_impl_dx11.h"
#else
#include "..\include\im\Urho3D\imgui_impl_dx9.h"
#endif


#endif//im_Urho3D_imguiGraphics_h