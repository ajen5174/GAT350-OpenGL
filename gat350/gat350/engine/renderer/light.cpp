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
	m_debug_model->m_mesh = m_engine->Resources()->Get<Mesh>("meshes/cube.obj");
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
	ASSERT(shader);

	shader->Use();
	shader->SetUniform("light.ambient", ambient);
	shader->SetUniform("light.diffuse", diffuse);
	shader->SetUniform("light.specular", specular);
	shader->SetUniform("light.type", type);
	shader->SetUniform("light.cutoff", cutoff);
	shader->SetUniform("light.exponent", exponent);

	std::vector<Camera*> cameras = m_scene->Get<Camera>();
	ASSERT(!cameras.empty());

	glm::mat4 light_view_matrix = cameras[0]->m_view_matrix * m_transform.GetMatrix();
	shader->SetUniform("light.position", light_view_matrix[3]);
	shader->SetUniform("light.direction", glm::mat3(light_view_matrix) * glm::vec3(0.0f, 0.0f, 1.0f));
}

void Light::Edit()
{
	ImGui::Begin("Light");
	ImGui::ColorEdit3("Ambient", (float*)&ambient);
	ImGui::ColorEdit3("Diffuse", (float*)&diffuse);
	ImGui::ColorEdit3("Specular", (float*)&specular);
	ImGui::End();
}
