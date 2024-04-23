#pragma once
#include "glm/matrix.hpp"
#include <iostream>

namespace eng
{
	static glm::mat4 eulerToMat4(const glm::vec3 angles)
	{
		glm::mat4 rotation(1.0f);

		rotation *= glm::rotate(glm::mat4(1.0f), glm::radians(angles.x), { 1.0f, 0.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(angles.y), { 0.0f, 1.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(angles.z), { 0.0f, 0.0f, 1.0f });
	}


	static void printMatrix(const glm::mat4 matrix)
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
}