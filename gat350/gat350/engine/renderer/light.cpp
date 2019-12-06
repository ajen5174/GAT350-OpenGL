#include "light.h"
#include "program.h"
#include "camera.h"

bool Light::Create(const Name& name)
{
	m_name = name;

#ifdef _DEBUG
	m_debug_model = m_engine->Factory()->Create<Model>(Model::GetClassName());
	m_debug_model->m_name = "model";
	m_debug_model->m_engine = m_engine;
	m_debug_model->m_scene = m_scene;
	m_debug_model->m_transform.scale = glm::vec3(0.15f, 0.15f, 0.15f);
	m_debug_model->m_mesh = m_engine->Resources()->Get<Mesh>("meshes/debug_cube.obj");
	m_debug_model->m_mesh->m_material = m_engine->Resources()->Get<Material>("debug_material");
	m_debug_model->m_shader = m_engine->Resources()->Get<Program>("debug_shader");
#endif // _DEBUG

	return true;
}

void Light::Update()
{
}

void Light::Draw(GLenum primitiveType)
{
#ifdef _DEBUG
	m_debug_model->m_transform.translation = m_transform.translation;
	m_debug_model->m_transform.rotation = m_transform.rotation;
	m_debug_model->m_mesh->m_material->diffuse = diffuse;
	m_debug_model->Draw(primitiveType);
#endif // _DEBUG
}

void Light::SetShader(class Program* shader)
{
	SetShader("light", shader);
}

void Light::SetShader(const std::string& lightname, Program* shader)
{
	ASSERT(shader);

	shader->Use();
	shader->SetUniform(lightname + ".ambient", ambient);
	shader->SetUniform(lightname + ".diffuse", diffuse);
	shader->SetUniform(lightname + ".specular", specular);
	shader->SetUniform(lightname + ".type", type);
	shader->SetUniform(lightname + ".cutoff", glm::radians(cutoff));
	shader->SetUniform(lightname + ".exponent", exponent);

	std::vector<Camera*> cameras = m_scene->Get<Camera>();
	ASSERT(!cameras.empty());

	glm::mat4 light_view_matrix = cameras[0]->m_view_matrix * m_transform.GetMatrix();
	shader->SetUniform(lightname + ".position", light_view_matrix[3]);
	shader->SetUniform(lightname + ".direction", glm::mat3(light_view_matrix) * glm::vec3(0.0f, 0.0f, 1.0f));
}

void Light::Edit()
{
	Actor::Edit();

	ImGui::Separator();
	ImGui::Text("Type: %s", Light::GetClassName());
	ImGui::ColorEdit3("Ambient", glm::value_ptr(ambient));
	ImGui::ColorEdit3("Diffuse", glm::value_ptr(diffuse));
	ImGui::ColorEdit3("Specular", glm::value_ptr(specular));
	ImGui::SliderFloat("Cutoff", &cutoff, 0.0f, 90.0f);
	ImGui::SliderFloat("Exponent", &exponent, 0.0f, 128.0f);

	const char* types[] = { "Point", "Direction", "Spot" };
	ImGui::Combo("Type", (int*)&type, types, IM_ARRAYSIZE(types));

}
