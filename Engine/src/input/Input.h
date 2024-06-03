#pragma once
#include "glm/vec2.hpp"
#include <unordered_map>
#include <string>
namespace eng
{
	enum class KeyCode
	{

	};

	struct Axis
	{
		KeyCode positive;
		KeyCode negative;
	};

	/*class Input
	{
	public:
		static bool GetKeyDown();
		static bool GetKeyUp();

		static bool GetMouseButtonDown();
		static bool GetMouseButtonUp();

		static glm::vec2 GetMousePos();

		static float GetAxis();
	private:
		static std::unordered_map<std::string, Axis> _axes;
		static std::unordered_map<std::string, KeyCode> _buttons;
	};*/
}