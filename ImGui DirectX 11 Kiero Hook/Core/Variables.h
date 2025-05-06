#pragma once
#include <cstdint>
#include <Utils/Includes.h>
#include <string>

namespace Variables
{
	std::string Prefix = "Giggity";
	const char* GameAssemblyName = "GameAssembly.dll";
	const char* UnityPlayerName = "UnityPlayer.dll";
	bool DEBUG = true;

	enum MenuTab
	{
		TAB_VISUALS,
		TAB_EXPLOITS,
		TAB_MISC,
		TAB_DEV
	};

	namespace System 
	{
		bool Init = false;
		bool InitIL2Cpp = false;

		POINT MousePos = { 0, 0 };

		inline static UINT vps = 1;
		Vector2 ScreenSize = { 0, 0 };
		Vector2 ScreenCenter = { 0, 0 };
		D3D11_VIEWPORT Viewport;
	}

	namespace Offsets
	{
		uintptr_t UnityEngineShader__FindShader_Offset = 0x0;
		uintptr_t UnityEngineTime__GetTimeScale_Offset = 0x0;
		uintptr_t UnityEngineTime__SetTimeScale_Offset = 0x0;
	}

	namespace CheatVariables 
	{
		Unity::CGameObject* LocalPlayer = NULL;
		std::vector<Unity::CGameObject*> PlayersList(NULL);

		Unity::CGameObject* TargetPlayer = NULL;
		ImColor TargetPlayerColor = ImColor(255, 0, 0);

		UnityEngine_Shader_o* ChamsShader;

		ImVec4 Rainbow = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // Global rainbow color
		ImColor RainbowColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255); // Global rainbow color

		static DWORD LastShotTime = 0;
		static DWORD LastTick = 0;
		static int SpinbotSupport = 0;
	}

	namespace CheatMenuVariables {

		bool ShowMenu = false;
		bool ShowFps = false;

		bool CameraFovChanger = false;
		float CameraCustomFOV = 80.0f;

		bool EnableDeveloperOptions = false;

		bool ShowInspector = false;
		bool ShowProperties = false;

		std::string InspectorCurrentComponent = "";

		float GameSpeed = 1.0f;
		
		bool ShowMouse = true;
		bool RainbowMouse = false;
		ImColor MouseColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255); 
		int MouseType = 0;

		bool Crosshair = false;
		bool RainbowCrosshair = false;
		ImColor CrosshairColor = ImColor(255.0f / 255, 255.0f / 255, 255.0f / 255);
		float CrosshairSize = 5.0f;
		int CrosshairType = 0;

		bool SpeedHack = false;	
		float SpeedValue = 1.0f;

		bool FlashlightHack = false;
		float FlashlightIntensity = 5.0f;
	}

	namespace Flashlights {
		std::vector<Unity::CLight*> LightList(NULL);
	}

	namespace KEYS
	{
		inline int SHOWMENU_KEY = VK_INSERT;
		inline int DEATTACH_KEY = VK_F9;
	}
}