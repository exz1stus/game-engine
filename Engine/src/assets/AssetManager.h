#pragma once
#include <memory>
#include <string>
#include "renderer/platform/opengl/Shader.h"
#include "renderer/platform/opengl/Texture2D.h"
#include "Asset.h"
namespace eng
{
	//class AssetManager
	//{
	//public:
	//	static void Init();
	//	static void AddAsset(const std::shared_ptr<void> asset, const std::string& fileName);

	//	template<typename T>
	//	static std::shared_ptr<T> GetAsset(const std::string& fileName)
	//	{
	//		//if (!_cachedIDs.contains(fileName)) return /*T::get()->FailedToLoad(); */ std::make_shared<T>();

	//		return std::dynamic_pointer_cast<shared_ptr<T>>(_assets[_cachedIDs[fileName]]);
	//	}
	//private:
	//	static void LoadAssets();
	//	static uint32_t GetAssetID();
	//	static std::unordered_map<std::string, uint32_t> _cachedIDs;
	//	static std::unordered_map<uint32_t, void*> _assets;

	//};
	class AssetManager
	{
	public:
		static void Init();
		static void LoadAssetsOfType(const AssetFactory& factory);
		static std::shared_ptr<Shader> Load(const std::string& fileName);
		template<typename T>
		static std::shared_ptr<T> GetAsset(const std::string& fileName)
		{
			if (!_assets.contains(fileName)) return nullptr;

			return std::shared_ptr(std::static_pointer_cast<T>(_assets[fileName]));
		}
	private:
		static std::vector<AssetFactory> _factories;
		//static std::unordered_map<std::string, uint32_t> _cachedIDs;
		//static std::unordered_map<uint32_t, std::shared_ptr<void>> _assets;
		static std::unordered_map<std::string, std::shared_ptr<void>> _assets;
	};
}