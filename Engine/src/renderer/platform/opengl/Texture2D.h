#pragma once
namespace eng
{
	class Texture2D
	{
	public:
		Texture2D(const std::string& path);
		void Bind(uint32_t slot = 0) const;
		uint32_t GetRendererID() const { return _rendererID; }
		bool operator==(const Texture2D& other) const
		{
			return _rendererID == other.GetRendererID();
		}
		const uint32_t& GetSlot() const { return _slot; }

	private:
		uint32_t _slot;

		uint32_t _height;
		uint32_t _width;
		uint32_t _rendererID;
	};
}
