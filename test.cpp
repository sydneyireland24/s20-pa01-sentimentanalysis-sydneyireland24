#include "catch.hpp"
#include <cstring>
#include "dsstring.h"
using namespace std;

//DSString test cases
TEST_CASE("testing the substring methods", "DSString") //TEST_CASE(what you're testing, what class)
{
    char * test{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString(test);
    char * test2{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString2(test2);
    char * test3{new char[10]{'s', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString3(test3);
    char * test4{new char[10]{'s', 'y', 'd'}};
    DSString testString4(test4);

    SECTION("testing the Substring function (with one parameter)") //SECTION(a subtest of the whole Test_Case)
    {
        testString = testString.substring(3);
        testString2 = testString2.substring(3);
        REQUIRE((testString == testString2));
    }
    SECTION("testing the substring function (with two parameters)") //SECTION(a subtest of the whole Test_Case)F
    {
        testString3 = testString3.substring(0, 3);
        REQUIRE((testString3 == testString4));
    }
}

TEST_CASE("testing the indexOf methods", "DSString")
{
    char * test{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString(test);

    SECTION("testing the indexOf function (with one parameter)")
    {
        int testIndex = testString.indexOf('n');
        REQUIRE(testIndex == 3);
    }
    SECTION("testing the indexOf function (with two parameters)")
    {
        int testIndex = testString.indexOf(3, 'y');
        REQUIRE(testIndex == 5);
    }
}

TEST_CASE("testing to see if the equality operator works", "DSString")
{
    char * test{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString(test);
    char * test2{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString2(test2);
    char * test3{new char[10]{'s', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString3(test3);
    char * test4{new char[10]{'s', 'y', 'd'}};
    DSString testString4(test4);
    SECTION("testing to see if the equality operator works (for equal to)")
    {
        REQUIRE((testString == testString2));
    }
    SECTION("testing to see if the equality operator works (for NOT equal to)")
    {
        REQUIRE(!(testString == testString3));
        REQUIRE(!(testString2 == testString4));
    }
}

TEST_CASE("assignment operator check" , "DSString")
{
    char * test{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString(test);
    char * test4{new char[10]{'s', 'y', 'd'}};
    DSString testString4(test4);
    SECTION("testing to see if the assignment operator works")
    {
        testString = testString4;
        REQUIRE((testString4 == testString));
    }
}

TEST_CASE("Addition operator check", "DSString")
{
    char * test{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString(test);
    char * test2{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString2(test2);
    DSString testString3;
    char testChar = 'l';
    SECTION("testing to see if the addition operator works (with another DSString object)")
    {
        testString3 = testString = testString + testString2;
        REQUIRE((testString == testString3));
    }
}

TEST_CASE("getLength function check", "DSString")
{
    char * test3{new char[10]{'s', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString3(test3);
    char * test4{new char[10]{'s', 'y', 'd'}};
    DSString testString4(test4);
    SECTION("testing the getLength function")
    {
        int testLength1 = testString3.getLength();
        int testLength2 = testString4.getLength();
        REQUIRE(testLength1 == 6);
        REQUIRE(testLength2 == 3);
    }
}

TEST_CASE("getString function check", "DSString")
{
    char * test{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString(test);
    char * test4{new char[10]{'s', 'y', 'd'}};
    DSString testString4(test4);
    SECTION("testing the getString function")
    {
        REQUIRE(strcmp(testString.getString(), test) == 0);
        REQUIRE(strcmp(testString4.getString(), test4) == 0);
    }
}

TEST_CASE("toLower function check", "DSString")
{
    char * test{new char[10]{'S', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString(test);
    char * test3{new char[10]{'s', 'y', 'd', 'n', 'e', 'y'}};
    DSString testString3(test3);
    SECTION("testing the toLower function")
    {
        testString = testString.toLowerCase();
        REQUIRE((testString == testString3));
    }
}

TEST_CASE("toInt function check", "DSString")
{
    char * testInt1{new char[3]{'0', '\0'}};
    char * testInt2{new char[3]{'9', '\0'}};
    DSString testString(testInt1);
    DSString testString2(testInt2);
    int test;
    int test2;
    SECTION("testing the toInt function")
    {
        test = testString.toInt(testString);
        test2 = testString2.toInt(testString2);
        REQUIRE((test == 0));
        REQUIRE((test2 == 9));
    }

}