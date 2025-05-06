#pragma once

// my includes
#include <Libraries/Dumper.hpp>
#include <Libraries/imgui/imgui.h>
#include <Core/Variables.h>
#include <Utils/SDK.h>
#include <Utils/Themes.h>
#include <Utils/Utils.h>
#include <Core/InternalGameFunctions.h>

using namespace Variables;

void DrawMouse() {
	if(!CheatMenuVariables::ShowMouse) return;

	ImColor color = CheatMenuVariables::RainbowMouse ? CheatVariables::RainbowColor : CheatMenuVariables::MouseColor;

	switch (CheatMenuVariables::MouseType) {
	case 0:
		ImGui::GetForegroundDrawList()->AddCircleFilled(ImGui::GetMousePos(), 4, color);
		break;
	case 1:
		Utils::DrawOutlinedTextForeground(gameFont, ImVec2(System::MousePos.x, System::MousePos.y), 13.0f, color, false, "X");
		break;
	case 2:
		if (!ImGui::GetIO().MouseDrawCursor) {
			ImGui::GetIO().MouseDrawCursor = true;
		}
		break;
	}
}

void DrawCrosshair() {
	if (CheatMenuVariables::Crosshair) {
		ImColor color = CheatMenuVariables::RainbowCrosshair ? CheatVariables::RainbowColor : CheatMenuVariables::CrosshairColor;
		switch (CheatMenuVariables::CrosshairType)
		{
		case 0:
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(System::ScreenCenter.x - CheatMenuVariables::CrosshairSize, System::ScreenCenter.y), ImVec2((System::ScreenCenter.x - CheatMenuVariables::CrosshairSize) + (CheatMenuVariables::CrosshairSize * 2), System::ScreenCenter.y), color, 1.2f);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(System::ScreenCenter.x, System::ScreenCenter.y - CheatMenuVariables::CrosshairSize), ImVec2(System::ScreenCenter.x, (System::ScreenCenter.y - CheatMenuVariables::CrosshairSize) + (CheatMenuVariables::CrosshairSize * 2)), color, 1.2f);
			break;
		case 1:
			ImGui::GetForegroundDrawList()->AddCircle(ImVec2(System::ScreenCenter.x, System::ScreenCenter.y), CheatMenuVariables::CrosshairSize, color, 100, 1.2f);
			break;
		}
	}
}

void DrawMenu()
{
	Themes::ImGuiThemeKio(true);

	if (CheatMenuVariables::ShowInspector) {
		Utils::DrawInspector();
	}

	if (ImGui::Begin(Prefix.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::SetWindowPos(ImVec2(500, 500), ImGuiCond_Once);
		ImGui::SetWindowSize(ImVec2(600, 300), ImGuiCond_Once);
		static MenuTab tabIndex = TAB_VISUALS;
		ImGui::SameLine();
		if (ImGui::Button("Visual"))
		{
			tabIndex = TAB_VISUALS;
		}
		ImGui::SameLine();
		if (ImGui::Button("Exploits"))
		{
			tabIndex = TAB_EXPLOITS;
		}
		ImGui::SameLine();
		if (ImGui::Button("Misc"))
		{
			tabIndex = TAB_MISC;
		}
		if (DEBUG) {
			ImGui::SameLine();
			if (ImGui::Button("Developer"))
			{
				tabIndex = TAB_DEV;
			}
		}
		ImGui::Separator();
		ImGui::Spacing();
		switch (tabIndex) {
			case TAB_VISUALS: {
				ImGui::Checkbox("Flashlight Hack", &CheatMenuVariables::FlashlightHack);
				ImGui::Text("Flashlight intensity");
				ImGui::SliderFloat("##FlashlightIntensity", &CheatMenuVariables::FlashlightIntensity, 0.0f, 30.0f);

				break;
			}
			case TAB_EXPLOITS: {

				ImGui::Text("Game timescale");
				ImGui::SliderFloat("##timescale", &CheatMenuVariables::GameSpeed, 0.0f, 100.0f);
				ImGui::SameLine(); 
				if(ImGui::Button("Set Timescale")) {
					GameFunctions::UnityEngine_Time__set_timeScale(CheatMenuVariables::GameSpeed);
				}	
				ImGui::SameLine(); Utils::HelpMarker("Change the game speed");
				if(ImGui::Button("Reset Timescale")) {
					CheatMenuVariables::GameSpeed = 1.0f;
					GameFunctions::UnityEngine_Time__set_timeScale(CheatMenuVariables::GameSpeed);
				}

				//{ // GodMode
				//	ImGui::Checkbox("GodMode (for you and bots)", &CheatMenuVariables::GodMode);
				//}

				//{ // No Recoil
				//	ImGui::Checkbox("No Recoil", &CheatMenuVariables::NoRecoil);
				//}

				//{ // No Spread
				//	ImGui::Checkbox("No Spread", &CheatMenuVariables::NoSpread);
				//}

				//{ // One Hit Kill
				//	ImGui::Checkbox("One Hit Kill", &CheatMenuVariables::OneShot);
				//}

				//{ // Rapid Fire
				//	ImGui::Checkbox("Rapid Fire", &CheatMenuVariables::RapidFire);
				//}

				//{ // Infinite Ammo
				//	ImGui::Checkbox("Infinite Ammo", &CheatMenuVariables::InfiniteAmmo);
				//}

				//{ // Speed Hack
				//	ImGui::Checkbox("Speed Hack", &CheatMenuVariables::SpeedHack);
				//	ImGui::SliderFloat("Speed", &CheatMenuVariables::SpeedValue, 0.1f, 1000.0f);
				//}
				break;
			}
			case TAB_MISC: {

				{ // Render Things
					ImGui::Checkbox("Show FPS", &CheatMenuVariables::ShowFps);
				}

				{ // Mouse things
					ImGui::Checkbox("Draw mouse", &CheatMenuVariables::ShowMouse);
					ImGui::SameLine();
					ImGui::ColorEdit3("##MouseColor", (float*)&CheatMenuVariables::MouseColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Color of the mouse");
					ImGui::SameLine();
					ImGui::Checkbox("##RGB1", &CheatMenuVariables::RainbowMouse);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toggle rainbow color on the mouse");
					ImGui::Text("Mouse Type");
					ImGui::SameLine();
					ImGui::SliderInt("##Mouse type", &CheatMenuVariables::MouseType, 0, 1);
				}

				{ // Crosshair
					ImGui::Checkbox("Crosshair", &CheatMenuVariables::Crosshair);
					ImGui::SameLine();
					ImGui::ColorEdit3("##CrosshairColor", (float*)&CheatMenuVariables::CrosshairColor, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Color of the crosshair");
					ImGui::SameLine();
					ImGui::Checkbox("##RGB2", &CheatMenuVariables::RainbowCrosshair);
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Toggle rainbow color on the crosshair");
					ImGui::Text("Crosshair Size");
					ImGui::SameLine();
					ImGui::SliderFloat("##Crosshair Size", &CheatMenuVariables::CrosshairSize, 0.1f, 10.0f);
					ImGui::Text("Crosshair Type");
					ImGui::SameLine();
					ImGui::SliderInt("##Crosshair type", &CheatMenuVariables::CrosshairType, 0, 1);
				}

				{ // Camera fov
					ImGui::Checkbox("Camera Fov Changer", &CheatMenuVariables::CameraFovChanger);
					ImGui::Text("Camera Custom FOV");
					ImGui::SameLine();
					ImGui::SliderFloat("##Camera Custom FOV", &CheatMenuVariables::CameraCustomFOV, 0.1f, 300.0f);
				}

				break;
			}
			case TAB_DEV: {

				ImGui::Checkbox("Enable Developer Options", &CheatMenuVariables::EnableDeveloperOptions);

				if (CheatMenuVariables::EnableDeveloperOptions)
				{
					ImGui::Indent();
					ImGui::Checkbox("Show Inspector", &CheatMenuVariables::ShowInspector);
					ImGui::Spacing();

				}
				break;
			}
		}
		ImGui::End();
	}
}

void CheatsLoop()
{
	DWORD currentTime = GetTickCount64(); 

	if (!Variables::System::InitIL2Cpp) return;


	if (CheatMenuVariables::CameraFovChanger)
	{
		Unity::CCamera* CameraMain = Unity::Camera::GetMain();
		if (CameraMain != nullptr) {
			CameraMain->CallMethodSafe<void*>("set_fieldOfView", CheatMenuVariables::CameraCustomFOV);
		}
	}

	if (currentTime - CheatVariables::LastTick > 5)
	{
		CheatVariables::LastTick = currentTime;
	}
}

void CacheManager()
{
	while (true)
	{
		if (!Variables::System::InitIL2Cpp)
			continue;

		void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());
		if (!m_pThisThread) continue;

		// here maybe you can check for a localplayer, or look the Objects Cache method

		try {
			// check the method in Utils.cpp to understand how find localplayer with that variable
			Utils::ObjectsCache(&CheatVariables::PlayersList, "UnityEngine.CharacterController");
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		IL2CPP::Thread::Detach(m_pThisThread);
		Sleep(2000);
	}
}