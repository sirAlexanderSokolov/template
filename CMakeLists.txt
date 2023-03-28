cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project (helloworldXXL)
#=====================================================
# версия
set (PROJECT_DESCRIPTION "base template")
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set (PROJECT_VERSION_PATCH 0)
set (PROJECT_DEVELOPER "Alexander Sokolov")
set(CMAKE_PROJECT_HOMEPAGE_URL "shadoffarts.ru")
string(TIMESTAMP PROJECT_DATE "%d.%m.%Y")

execute_process(
  COMMAND git status -suno
  RESULT_VARIABLE STATUS1
  OUTPUT_VARIABLE COMMIT1 
  ERROR_QUIET )
    message(STATUS "STATUS1: ${STATUS1}")
    message(STATUS "COMMIT1: ${COMMIT1}")

execute_process(
  COMMAND git rev-parse --short HEAD
  RESULT_VARIABLE STATUS
  OUTPUT_VARIABLE COMMIT 
  ERROR_QUIET )
if(STATUS AND NOT STATUS EQUAL 0)
    set(COMMIT "NO COMMIT")
    message(STATUS "FAILED TO GET COMMIT: ${STATUS}")
endif()

message ("Сборка: ${PROJECT_NAME} Версии ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} от ${PROJECT_DATE}")
#=====================================================
# опции проекта
option(IMPROVED_ALLOC   "Включить аллокатор от google"      ON)
option(TESTING_GTEST    "Включить модульное тестирование"   OFF)
option(COVERAGE_GTEST   "Включить покрытие кода тестами"    OFF)
option(MAKE_PACKAGE     "Включить сборку пакетов"           OFF)
option(DEBUG            "Режим отладки"                     OFF)

message (STATUS "Модульное тестирование : ${TESTING_GTEST}")
message (STATUS "Покрытие кода : ${COVERAGE_GTEST}")
message (STATUS "Сборка пакета : ${MAKE_PACKAGE}")
message (STATUS "Debug: ${DEBUG}")
#=====================================================
if (DEBUG)
    add_definitions(" -O0 -g3 -DDEBUG")
else()
    add_definitions(" -O3 -g3 ")
endif()
#=====================================================
# поиск библиотек
find_package(Boost COMPONENTS 
program_options
# thread 
# system 
# chrono 
REQUIRED)

# find_library(PTREAD_LIBRARY pthread REQUIRED)   #POSIX thread
# find_library(RT_LIBRARY rt REQUIRED)            #POSIX.1b  Realtime Extension
# find_library(DL_LIBRARY dl REQUIRED)            #Dynamic link
# find_library(PCAP_LIBRARY pcap REQUIRED)        #tcp package capture
# find_library(PCRE_LIBRARY pcre REQUIRED)        #PERL 5
# find_library(SQLITE3_LIBRARY sqlite3 REQUIRED)  #sqlite
# find_library(JSON_LIBRARY json-c REQUIRED)      #JSON
#=====================================================
# сборка
# add_library(LIB_LOGGER INTERFACE lib/lib_logger/logger.hpp)
add_library(LIB_LOGGER STATIC lib/lib_logger/logger.cpp)
add_library(LIB_MAIN STATIC .)


target_link_libraries(
LIB_MAIN
LIB_LOGGER
${Boost_LIBRARIES}
# ${PTREAD_LIBRARY}
# ${RT_LIBRARY}
# ${DL_LIBRARY}
# ${PCAP_LIBRARY}
# ${PCRE_LIBRARY}
# ${SQLITE3_LIBRARY}
# ${JSON_LIBRARY}    
)
#=====================================================
set(SOURCES main.cpp)
set(HEADERS core.hpp includes/includes.hpp)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_compile_definitions(${PROJECT_NAME} PUBLIC 
PR_NAME="${PROJECT_NAME}"
PR_DESCRIPT="${PROJECT_DESCRIPTION}"
PR_VERSION="${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
PR_VERSION_DATE="${PROJECT_DATE}"
PR_DEVELOPER="${PROJECT_DEVELOPER}"
PR_COMMIT="${COMMIT}"
PR_UNCOMMITED="${UNCOMMITED}"
)
#=====================================================
if(IMPROVED_ALLOC)
    find_library(GMALLOC tcmalloc)
    if(GMALLOC)
    message (STATUS "Сборка с tcmalloc: ${GMALLOC}")
    add_definitions(-ltcmalloc)
    else()
    message (STATUS "Библиотека tcmalloc не найдена")
    endif()
endif()
#=====================================================
# линковка
target_link_libraries(
${PROJECT_NAME} 
LIB_MAIN 
LIB_LOGGER 
)
#=====================================================
# модульные гугл-тесты
if (TESTING_GTEST)
find_program(GCOVR_EXECUTABLE lcov)
# add_definitions(-DGTEST)
add_subdirectory(unit_test)
endif()
#=====================================================
# сборка пакета
if (MAKE_PACKAGE)
set(CPACK_GENERATOR "DEB;TGZ")
set(CPACK_PACKAGE_CONTACT "shad@shad.ru")
set(CPACK_PACKAGE_DIRECTORY ${PROJECT_SOURCE_DIR}/packages)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "sir_Alexander")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Project_Hello by Alex for Otus")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
# set(CPACK_PACKAGE_INSTALL_DIRECTORY "/opt/mydir/")
    if (CPACK_GENERATOR MATCHES "DEB")
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /opt/mylib)
    elseif (CPACK_GENERATOR MATCHES "DEB")  
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
    endif()
include(CPack)
endif()
#=====================================================
# Генерация run файла
if (TESTING_GTEST)
set(RUN_EXE_NAME "/unit_test/unit_test")
else()
set(RUN_EXE_NAME ${PROJECT_NAME})
endif()
message (STATUS "run.sh generated with : ${RUN_EXE_NAME}")
configure_file(run.sh.in run.sh @ONLY)
#=====================================================
# Doxygen
if (NOT IS_SUBPROJECT)
    add_subdirectory(doxygen)
endif()
#=====================================================
