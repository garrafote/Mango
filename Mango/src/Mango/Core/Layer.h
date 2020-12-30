#pragma once

#include "Mango/Core/Core.h"
#include "Mango/Core/Timestep.h"
#include "Mango/Events/Event.h"

namespace Mango {

	class MANGO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDettach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}

		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};


};

