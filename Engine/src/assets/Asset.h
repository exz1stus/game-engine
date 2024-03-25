#pragma once
namespace eng
{
	//class ILoadable
	//{
	//private://protected?
	//	virtual void Load(const Asset& asset) = 0;
	//	
	//	friend class AssetManager;
	//};


	class AssetFactory
	{
	public:
		void Create(const std::vector<std::string>& formats,const std::string& location);
		std::shared_ptr<void> Load(const std::string& fileName) const;
		const std::vector<std::string>& GetFormats() const { return _assetFormats; }
		const std::string& GetLocation() const { return _assetLocation; }
	protected:
		virtual void OnCreation() {};
		virtual std::shared_ptr<void> LoadAsset(const std::string& fileName, bool& loadStatus) const = 0;
		virtual std::shared_ptr<void> FailedToLoad(const std::string& fileName) const;
		std::vector<std::string> _assetFormats;
		std::string _assetLocation;
	};

	class ShaderFactory : public AssetFactory
	{
		std::shared_ptr<void> LoadAsset(const std::string& fileName, bool& loadStatus) const override;
		std::shared_ptr<void> FailedToLoad(const std::string& fileName) const override;
	};

	class TextureFactory : public AssetFactory
	{
		std::shared_ptr<void> LoadAsset(const std::string& fileName, bool& loadStatus) const override;
		std::shared_ptr<void> FailedToLoad(const std::string& fileName) const override;
	};
}