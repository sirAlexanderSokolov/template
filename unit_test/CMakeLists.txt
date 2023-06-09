cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

enable_testing()

set (TEST_PROJECT_NAME unit_tests)

#зависимости
find_package(GTest REQUIRED)
if (NOT GTest_FOUND)
    message(FATAL_ERROR "Cannot find Google Test Framework!")
endif()
include(GoogleTest)

#сборка
set(SOURCES 
test_main.cpp
lib/lib_print_test.cpp
)

add_executable(${TEST_PROJECT_NAME} ${SOURCES})

#линковка
# target_link_libraries(${PROJECT_NAME} uc)

target_link_libraries(${TEST_PROJECT_NAME}
    PRIVATE
    GTest::GTest 
    GTest::Main
    gcov
    LIB_BIG LIB_HELLO 
    LIB_PRINT
    )
    
#покрытие
if (COVERAGE_GTEST AND GCOVR_EXECUTABLE)

message(STATUS "Измерение покрытия кода тестовой системой включено")

target_link_libraries(${PROJECT_NAME} gcov)
target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
target_compile_options(${TEST_PROJECT_NAME} PRIVATE --coverage)
    
  add_custom_target(coverage_gt
    COMMAND
        ${GCOVR_EXECUTABLE}
        --gcov-tool /usr/bin/gcov 
        -c
        -d ${PROJECT_BINARY_DIR}/CMakeFiles/
        -o kernel.info
    COMMAND
        ${GCOVR_EXECUTABLE}           
        --gcov-tool /usr/bin/gcov    
        -r kernel.info "*/usr*" "*.h" "*/opt*"
        -o kernel.info
    COMMAND
        genhtml          
        -o ${PROJECT_SOURCE_DIR}/report_coverage/gtest
        kernel.info
    DEPENDS
        check_gt
    )
 add_custom_target(check_gt COMMAND ${PROJECT_BINARY_DIR}/unit_test/${TEST_PROJECT_NAME} --gtest_output=xml:report-file.xml)   
elseif(NOT GCOVR_EXECUTABLE)
    set(COVERAGE_GTEST OFF)
    message(WARNING "Для замеров покрытия кода требуется программа gcov")
endif()

#поиск тестов
gtest_discover_tests(${TEST_PROJECT_NAME})