#include "light.h"
#include "program.h"

void Light::SetShader(class Program* program, const glm::mat4& view)
{
	ASSERT(program);

	program->Use();

	program->SetUniform("light.ambient", ambient);
	program->SetUniform("light.diffuse", diffuse);
	program->SetUniform("light.specular", specular);
	program->SetUniform("light.position", glm::vec4(m_transform.translation, 1.0f) * view);
}

void Light::Edit()
{
	ImGui::PushID("Light");
	ImGui::Text("Light");
	ImGui::ColorEdit3("Ambient", (float*)(&ambient));
	ImGui::ColorEdit3("Diffuse", (float*)(&diffuse));
	ImGui::ColorEdit3("Specular", (float*)(&specular));
	ImGui::SliderFloat4("position", (float*)(&m_transform.translation), -100.0f, 100.0f);
	ImGui::PopID();
}
