#include "transform.h"

void Transform::Edit()
{
	ImGui::Separator();
	ImGui::Text("Transform");

	ImGui::SliderFloat3("Translation", (float*)&translation, -1000.0f, 1000.0f);
	ImGui::SliderFloat3("Scale", (float*)&scale, 0.0f, 100.0f);

	//glm::vec3 euler = glm::degrees(glm::eulerAngles(rotation));
	//std::string rotation_string = "Rotation: " + std::to_string(euler.x) + " " + std::to_string(euler.y) + " " + std::to_string(euler.z) + " ";
	//ImGui::gizmo3D(rotation_string.c_str(), rotation, 200.0f, imguiGizmo::mode3Axes | imguiGizmo::sphereAtOrigin);
	
	ImGui::gizmo3D("Rotation", rotation, 200.0f, imguiGizmo::mode3Axes | imguiGizmo::sphereAtOrigin);
}
