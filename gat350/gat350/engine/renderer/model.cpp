#include "model.h"
#include "camera.h"

void Model::Update()
{
}

void Model::Draw(GLenum primitiveType)
{
	std::vector<Camera*> cameras = m_scene->Get<Camera>();
	ASSERT(!cameras.empty());

	glm::mat4 model_view_matrix = cameras[0]->m_view_matrix * m_transform.GetMatrix();
	glm::mat4 mvp_matrix = cameras[0]->m_projection_matrix * model_view_matrix;

	m_shader->Use();
	m_shader->SetUniform("model_view_matrix", model_view_matrix);
	m_shader->SetUniform("mvp_matrix", mvp_matrix);

	m_mesh->SetShader(m_shader.get());
	m_mesh->Draw();
}
