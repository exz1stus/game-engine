#pragma once
#include "glm/matrix.hpp"
#include <iostream>

namespace eng
{
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