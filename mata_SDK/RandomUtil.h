#pragma once
#include "SDKHeader.h"
#include <random>

class RandomUtil {
private:
	std::random_device RD{};

public:
	GLfloat Gen(int DistType, GLfloat Min, GLfloat Max);
	GLfloat Select(GLfloat Value1, GLfloat Value2);
};
extern RandomUtil randomUtil;