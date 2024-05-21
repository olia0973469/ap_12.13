#include "pch.h"
#include "CppUnitTest.h"
#include "../ap_12.13/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            OpenHashTable hashTable;
            Student student = { "Smith", 85, 90, 95 };
            hashTable.insert(student);

            std::stringstream output;
            std::streambuf* oldCoutBuf = std::cout.rdbuf();
            std::cout.rdbuf(output.rdbuf());

            hashTable.display();

            std::cout.rdbuf(oldCoutBuf);
            std::string result = output.str();
            Assert::IsTrue(result.find("Smith") != std::string::npos);
		}
	};
}
