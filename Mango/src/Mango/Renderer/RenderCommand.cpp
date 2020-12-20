#include "MangoPCH.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Mango {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
