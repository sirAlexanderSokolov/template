#include <gtest/gtest.h>
#include "../lib/lib_logger/logger.hpp"

using namespace std;

TEST(Employee_Constructor, AllValidArgs_ReturnSuccess) {
  logger::instance().print("asd");
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}