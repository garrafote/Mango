#pragma once

#include "Mango/Core/Layer.h"
#include "Mango/Events/ApplicationEvent.h"
#include "Mango/Events/KeyEvent.h"
#include "Mango/Events/MouseEvent.h"

namespace Mango {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();
		
	private:
		float m_Time = 0.0f;
	};


}