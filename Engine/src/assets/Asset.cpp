#include "engpch.h"
#include "Asset.h"
#include "renderer/platform/opengl/Shader.h"
#include "renderer/platform/opengl/Texture2D.h"

namespace eng
{
	//add asset classes image, audioTrack which will contain asset
	//asset shared ptr will unload when only 1 reference(asset manager), asset class, formats dict, ILoadable interfac5e
	//for non asset classes e.g. Shader : ILoadable ,where shader will take ShaderAsset or smth


	void AssetFactory::Create(const std::vector<std::string>& formats,const std::string& location)
	{
		_assetFormats = std::move(formats);//const move??
		_assetLocation = std::move(location);
		OnCreation();
	}

	std::shared_ptr<void> AssetFactory::Load(const std::string& fileName) const
	{
		//bool????
		bool loaded = false;
		auto asset = LoadAsset(fileName, loaded);
		if (!asset) return FailedToLoad(fileName);
		return asset;
	}

	std::shared_ptr<void> AssetFactory::FailedToLoad(const std::string& fileName) const
	{
		Logger::Error("failed to load asset at location: " + _assetLocation + fileName);
		return nullptr;
	}

	std::shared_ptr<void> ShaderFactory::LoadAsset(const std::string& fileName, bool& loadStatus) const
	{
		std::vector<std::string> shaderSources(_assetFormats.size());

		for (size_t i = 0; i < _assetFormats.size(); i++)
		{
			std::ifstream stream(_assetLocation + fileName + '.' + _assetFormats[i]);
			stream.seekg(0, std::ios::beg);
			shaderSources[i].assign((std::istreambuf_iterator<char>(stream)),
				std::istreambuf_iterator<char>());
			stream.close();

			if (shaderSources[i].empty())
				return FailedToLoad(fileName);
		}
		auto shader = std::make_shared<Shader>(fileName);
		ShaderSource src;
		src.vert = shaderSources[0];
		src.frag = shaderSources[1];
		shader->CreateShader(src);
		return shader;
	}

	std::shared_ptr<void> ShaderFactory::FailedToLoad(const std::string& fileName) const
	{
		Logger::Error("Failed to load shader " + fileName + " at location " + _assetLocation + "/" + fileName);
		return std::make_shared<Shader>(fileName);
	}

	std::shared_ptr<void> TextureFactory::LoadAsset(const std::string& fileName, bool& loadStatus) const
	{
		return std::shared_ptr<void>();
	}

	std::shared_ptr<void> TextureFactory::FailedToLoad(const std::string& fileName) const
	{
		return std::shared_ptr<void>();
	}
}