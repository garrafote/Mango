#pragma once

namespace Mango {
	
	class GraphicsContext
	{
	public:
		//virtual ~GraphicsContext() = delete;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* window);
	};
}
