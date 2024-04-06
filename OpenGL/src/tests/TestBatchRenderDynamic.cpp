#include "TestBatchRenderDynamic.h"

#include "../Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    TestBatchRenderDynamic::TestBatchRenderDynamic()
        :m_Proj(glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0))),
        m_Translation(glm::vec3(0, 0, 0))
	{
        struct Vertex
        {
            float Positions[4];
            float Color[4];
            float CoordTex[2];
            float index;
        };

        GLCall(glGenVertexArrays(1, &m_QuadVA));
        GLCall(glBindVertexArray(m_QuadVA));
        GLCall(glGenBuffers(1, &m_QuadVB));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB));
        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 10, nullptr, GL_DYNAMIC_DRAW));

        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Positions)));

        GLCall(glEnableVertexAttribArray(1));
        GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));

        GLCall(glEnableVertexAttribArray(2));
        GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, CoordTex)));

        GLCall(glEnableVertexAttribArray(3));
        GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, index)));


        float positions[] = {
            100.0f, 100.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            200.0f, 100.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            200.0f, 200.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            100.0f, 200.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            300.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            400.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            400.0f, 200.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            300.0f, 200.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

        };

        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4
        };

        GLCall(glGenBuffers(1, &m_QuadIB));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadIB));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        //m_VAO = std::make_unique<VertexArray>();

        //m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(positions)*10);
        //VertexBufferLayout layout;
        //
        //layout.Push<float>(4); // 坐标 x, y, z, w  w 齐次坐标, 对xyz进行缩放
        //layout.Push<float>(4); // 颜色数据
        //layout.Push<float>(2); // 纹理坐标
        //layout.Push<float>(1); // 纹理插槽
        ////m_VAO->AddBuffer(*m_VertexBuffer, layout);

        //m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

        m_Shader = std::make_unique<Shader>("res/shaders/Batch.shader");
        m_Shader->Bind();

        m_Texture[0] = std::make_unique<Texture>("res/textures/ChernoLogo.png");
        m_Texture[1] = std::make_unique<Texture>("res/textures/HazelLogo.png");
        for (size_t i = 0; i < 2; i++)
        {
            m_Texture[i]->Bind(static_cast<unsigned int>(i));
        }
        int samplers[2] = { 0, 1 };
        m_Shader->SetUniform1iv("u_Textures", 2, samplers);
	}

    TestBatchRenderDynamic::~TestBatchRenderDynamic()
	{
	}

	void TestBatchRenderDynamic::OnUpdate(float deltaTime)
	{
	}

	void TestBatchRenderDynamic::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));


        float positions[] = {
            100.0f, 100.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            200.0f, 100.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            200.0f, 200.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            100.0f, 200.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            300.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            400.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            400.0f, 200.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            300.0f, 200.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,

        };
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadIB));


        


        //Renderer renderer; // 每帧这个renderer都要不一样嘛
        glm::mat4 mvp = m_Proj * m_View;

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr));

        //renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestBatchRenderDynamic::OnImGuiRender()
	{
         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}