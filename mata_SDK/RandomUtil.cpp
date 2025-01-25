#include "RandomUtil.h"

RandomUtil randomUtil;

GLfloat RandomUtil::Gen(int DistType, GLfloat Min, GLfloat Max) {
	if (DistType == RANDOM_TYPE_REAL) {
		std::uniform_real_distribution URD{ Min, Max };
		return URD(RD);
	}

	else if (DistType == RANDOM_TYPE_INT) {
		std::uniform_int_distribution UID{ (int)Min, (int)Max };
		return UID(RD);
	}

	return 0.0;
}

GLfloat RandomUtil::Select(GLfloat Value1, GLfloat Value2) {
	std::uniform_int_distribution UID{ 0, 1 };
	int RandomNum = UID(RD);
	if (RandomNum == 0)
		return Value1;
	else
		return Value2;
}
