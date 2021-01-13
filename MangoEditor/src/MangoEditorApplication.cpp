#include <Mango.h>
#include <Mango/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Mango {

	class MangoEditor : public Mango::Application
	{
	public:
		MangoEditor()
			: Application("Mango Editor")
		{
			PushLayer(new EditorLayer());
		}

		~MangoEditor()
		{

		}
	};

	Mango::Application* Mango::CreateApplication()
	{
		return new MangoEditor();
	}
}