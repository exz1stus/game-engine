#pragma once
namespace eng
{
	class Texture2D
	{
	public:
		Texture2D();
		void Bind(uint32_t slot = 0) const;

	private:
		uint32_t _height;
		uint32_t _width;
		uint32_t _rendererID;
		uint32_t _cachedID;
	};
}
