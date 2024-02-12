//#pragma once
//#include <iostream>
//
//
//#include "events/Event.h"
//
//// Example class with a static function and a member function
//class EventHandler
//{
//public:
//    static void StaticFunction(int value)
//    {
//        std::cout << "Static Function: " << value << std::endl;
//    }
//
//    void MemberFunction(int value)
//    {
//        std::cout << "Member Function: " << value << std::endl;
//    }
//};
//class Camera1
//{
//public:
//    int ab = 0;
//    Camera1() = default;
//
//    void SetProjection(float left, float right, float bottom, float top);
//
//    void ResizeProjection(int left, int right, uint32_t a, const std::string& str) { std::cout <<"Camera :"<< ab << " " << right << str; };
//private:
//
//
//    float _rotation = 0.0f;
//    float _fov = 45.0f;
//
//    bool isOrthographic = true;
//};
//int M()
//{
//    eng::Event<int, int,uint32_t, const std::string&> e;
//
//    Camera1 cam;
//    Camera1 cam2;
//
//    cam2.ab = 888;
//
//    e.Bind(&Camera1::ResizeProjection, &cam);
//    e.Bind(&Camera1::ResizeProjection, &cam2);
//
//
//    e.Invoke(3,3, 4 , "Test 1");
//
//    e.Unbind(&Camera1::ResizeProjection, &cam);
//
//
//    e.Invoke(4, 4, 5, "test 2");
//
//
//    return 0;
//}
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