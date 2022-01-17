#include "hkpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hickory
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(filepath);
		}

		HK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		HK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HK_CORE_ASSERT(!Exists(name), "Shader already Exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Hickory::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);

		return shader;
	}

	Ref<Hickory::Shader> ShaderLibrary::Load(const std::string name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);

		return shader;
	}

	Ref<Hickory::Shader> ShaderLibrary::Get(const std::string& name)
	{
		HK_CORE_ASSERT(Exists(name), "Shader not Found !");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}