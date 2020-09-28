#include "gtest/gtest.h"
//#include "../src/lab2.20.h"
#include "../src/lab2.20.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}