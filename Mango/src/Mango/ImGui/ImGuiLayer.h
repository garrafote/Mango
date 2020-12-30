#pragma once

#include "Mango/Core/Layer.h"
#include "Mango/Events/ApplicationEvent.h"
#include "Mango/Events/KeyEvent.h"
#include "Mango/Events/MouseEvent.h"

namespace Mango {

	class MANGO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		
	private:
		float m_Time = 0.0f;
	};


}