#include "MangoPCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Mango {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
