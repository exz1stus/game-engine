#include "engpch.h"
#include "AssetManager.h"

namespace eng
{
	//std::unordered_map<std::string, uint32_t> AssetManager::_cachedIDs;
	std::unordered_map<std::string, std::shared_ptr<void>> AssetManager::_assets;
	std::vector<AssetFactory> AssetManager::_factories;
	void AssetManager::Init()
	{	
		ShaderFactory shaderFac;
		shaderFac.Create({ "vert", "frag" }, "../Engine/assets/shaders/opengl/");
		LoadAssetsOfType(shaderFac);
		/*TextureFactory texFactory;
		texFactory.Create({"jpg", "ad"}, "a/a/a/");
		LoadAssetsOfType(texFactory);*/
	}
	void AssetManager::LoadAssetsOfType(const AssetFactory& factory)
	{
		for (const auto& entry : std::filesystem::directory_iterator(factory.GetLocation()))
		{
			if (!entry.is_regular_file()) continue;

			std::string filePath = entry.path().string();
			for (const auto& format : factory.GetFormats())
			{
				const std::string formatWithDot = '.' + format;
				if (filePath.find(formatWithDot) == std::string::npos) continue;

				const auto& fileName = entry.path().filename().stem().string();
				if (_assets.contains(fileName))
				{
					std::cout << "asset of name " + fileName + " already exists" << std::endl;
					break;
				}
				_assets[fileName] = factory.Load(fileName);

				//supports only assets with different names
				//assets group(shaders) will be searched in load() by name
				break;

			}
		}

	}
}