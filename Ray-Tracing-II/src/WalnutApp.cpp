#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		if (ImGui::Button("Render"))
		{
			Render();
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("ViewPort");
		nViewpotWidth = ImGui::GetContentRegionAvail().x;
		nViewpotHeight = ImGui::GetContentRegionAvail().y;

		if (m_Image)
			ImGui::Image(m_Image->GetDescriptorSet(), {(float)m_Image->GetWidth(), (float)m_Image->GetHeight()});

		ImGui::End();
		ImGui::PopStyleVar();
	}

	void Render()
	{
		if (!m_Image || nViewpotWidth != m_Image->GetWidth() || nViewpotHeight != m_Image->GetHeight())
		{
			m_Image = std::make_shared<Image>(nViewpotWidth, nViewpotHeight, ImageFormat::RGBA);
			delete[] m_ImageData;
			m_ImageData = new uint32_t[nViewpotWidth * nViewpotHeight];
		}

		for (uint32_t i = 0; i < nViewpotWidth * nViewpotHeight; i++)
		{
			m_ImageData[i] = 0xffff00ff;
		}

		m_Image->SetData(m_ImageData);
	}

private:
	std::shared_ptr<Image> m_Image;
	uint32_t nViewpotWidth = 0, nViewpotHeight = 0;
	uint32_t* m_ImageData = nullptr;
};

Walnut::Application *Walnut::CreateApplication(int argc, char **argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Ray Tracing";

	Walnut::Application *app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
													{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		} });
	return app;
}