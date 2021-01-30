#pragma once

#include "Mango/Renderer/Framebuffer.h"

namespace Mango
{

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;
		
		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentID(uint32_t index = 0) const override { return m_ColorAttachments[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID;
		uint32_t m_DepthAttachment;
		std::vector<uint32_t> m_ColorAttachments;
		FramebufferSpecification m_Specification;
		
		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

	};

}


