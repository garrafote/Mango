#pragma once

#include "Mango/Layer.h"
namespace Mango {

	class MANGO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDettach() override;

		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		float m_Time = 0.0f;
	};


}