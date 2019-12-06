#include "model.h"
#include "camera.h"

void Model::Update()
{
}

void Model::Draw(GLenum primitiveType)
{
	auto camera = m_scene->GetActive<Camera>();
	//ASSERT(!cameras.empty());

	glm::mat4 model_view_matrix = camera->m_view_matrix * m_transform.GetMatrix();
	glm::mat4 mvp_matrix = camera->m_projection_matrix * model_view_matrix;
	glm::mat4 view_matrix = glm::mat4(glm::mat3(camera->m_view_matrix));
	glm::mat4 projection_matrix = camera->m_projection_matrix;

	m_shader->Use();
	m_shader->SetUniform("camera_position", camera->m_transform.translation);
	m_shader->SetUniform("model_matrix", m_transform.GetMatrix());
	m_shader->SetUniform("model_view_matrix", model_view_matrix);
	m_shader->SetUniform("mvp_matrix", mvp_matrix);
	m_shader->SetUniform("view_matrix", view_matrix);
	m_shader->SetUniform("projection_matrix", projection_matrix);

	m_mesh->SetShader(m_shader.get());
	m_mesh->Draw();
}
