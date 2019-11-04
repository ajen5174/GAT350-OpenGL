#include "transform.h"

void Transform::Edit()
{
	ImGui::SliderFloat3("Translation", (float*)&translation, -1000.0f, 1000.0f);
	ImGui::SliderFloat4("Rotation", (float*)&rotation, -1000.0f, 1000.0f);
	ImGui::SliderFloat3("Scale", (float*)&scale, 0.0f, 100.0f);
}
