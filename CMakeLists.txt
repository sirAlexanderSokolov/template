cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project (helloworldXXL VERSION 1.0.0)
set (SOURCES main.cpp)
file(GLOB LIB_MAIN_SOURCES 
${PROJECT_SOURCE_DIR}/source/*.cpp 
${PROJECT_SOURCE_DIR}/source/*.hpp 
${PROJECT_SOURCE_DIR}/source/*.cxx 
${PROJECT_SOURCE_DIR}/source/*.c 
${PROJECT_SOURCE_DIR}/source/*.h
)
#=====================================================
# версия
set (PROJECT_DESCRIPTION "base template")
set (PROJECT_INSTALL_DIR "/usr/local/bin/")
set (PROJECT_DEVELOPER "Alexander Sokolov")
set (DEV_CONTACT "sir.alexander.sokolov@gmail.com")
string(TIMESTAMP PROJECT_DATE "%d.%m.%Y")

message ("Сборка: ${PROJECT_NAME} Версии ${PROJECT_VERSION} от ${PROJECT_DATE}")
#=====================================================
# опции проекта
option(IMPROVED_ALLOC   "Включить аллокатор от google"      ON)
option(TESTING_GTEST    "Включить модульное тестирование"   OFF)
option(COVERAGE_GTEST   "Включить покрытие кода тестами"    OFF)
option(MAKE_PACKAGE     "Включить сборку пакетов"           OFF)
option(DEBUG            "Режим отладки"                     OFF)

message (STATUS "Аллокация памяти tcmalloc :  ${IMPROVED_ALLOC}")
message (STATUS "Модульное тестирование :     ${TESTING_GTEST}")
message (STATUS "Покрытие кода :              ${COVERAGE_GTEST}")
message (STATUS "Сборка пакета :              ${MAKE_PACKAGE}")
message (STATUS "Режим отладки:               ${DEBUG}")
#=====================================================
# поиск библиотек
find_package(Boost COMPONENTS program_options REQUIRED)
#=====================================================
# библиотеки
add_library(LIB_MAIN SHARED ${LIB_MAIN_SOURCES})
target_link_libraries(LIB_MAIN PUBLIC ${Boost_LIBRARIES})

add_subdirectory(lib/lib_logger)
target_link_libraries(LIB_MAIN PRIVATE LIB_LOGGER)
#=====================================================
# сборка
add_executable(${PROJECT_NAME} ${SOURCES})
add_definitions("-O3 -Wall -fPIC -fmessage-length=0 -Wextra -pedantic -c -W -Wfatal-errors -std=c++17")
#=====================================================
# линковка
target_link_libraries(${PROJECT_NAME} LIB_MAIN)
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
if (DEBUG)
  add_definitions(-O0 -g3 -DDEBUG)
else()
  add_definitions(-O3 -g3 )
endif()
#=====================================================
# модульные гугл-тесты
if (TESTING_GTEST)
  add_subdirectory(unit_test)
endif()
#=====================================================
# сборка пакета
if (MAKE_PACKAGE)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_PACKAGE_CONTACT ${DEV_CONTACT})
  set(CPACK_PACKAGE_DIRECTORY ${PROJECT_SOURCE_DIR}/packages)
  set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
  set(CPACK_PACKAGE_VENDOR ${PROJECT_DEVELOPER})
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_SET_DESTDIR ON)
  set(CPACK_INSTALL_PREFIX ${PROJECT_INSTALL_DIR}) 
  set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_INSTALL_DIR})
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${PROJECT_INSTALL_DIR})
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
