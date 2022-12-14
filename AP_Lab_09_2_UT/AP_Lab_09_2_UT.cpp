// Якубовський Владислав, ІКНІ, РІ-11, АП, unit-тест до ЛР 09.2, варіант 24
#include "pch.h"
#include "CppUnitTest.h"
#include "../AP_Lab_09_2_A/AP_Lab_09_2_A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace APLab092UT
{
	TEST_CLASS(APLab092UT)
	{
	public:
		
		TEST_METHOD(TestBinSearch)
		{
			Student* students = new Student[2];

			students[1].surname = "Петренко"; students[1].course = 2; students[1].physicsGrade = 5; students[1].mathGrade = 5; students[1].ITGrade = 5;

			float averageGrade = AverageGrade(students[1]);

			Assert::AreEqual(1, BinSearch(students, 2, "Петренко", 2, averageGrade));
		}
	};
}
