#pragma once

#include "Test.h"

#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"

#include <memory>

namespace test
{

	class TestDrawCube : public Test
	{
	private:
		/*std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;*/
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture[2];

		glm::mat4 m_Proj, m_View, m_model;
		glm::vec3 m_Translation;
		float m_angle;
		glm::vec3 m_Direction;


		unsigned int m_QuadVA;
		unsigned int m_QuadVB;
		unsigned int m_QuadIB;

	public:
		TestDrawCube();
		~TestDrawCube();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}