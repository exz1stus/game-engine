#include "engpch.h"

#include "Utilities.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace eng
{
	void test()
	{
		auto projection = glm::perspective(glm::radians(45.0f), (float)700.0f / (float)600.0f, 0.1f, 100.0f);


		std::cout << "PRJ 1" << "\n";
		printMatrix(projection);

		projection = glm::ortho(0.0f, 700.0f, 0.0f, 600.0f, -100.0f, 100.0f);

		std::cout << "PRJ 2" << "\n";
		printMatrix(projection);


	}
}