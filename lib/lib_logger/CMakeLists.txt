# project(LIB_LOGGER )
set(LIB_NAME "LIB_LOGGER")
file(GLOB LIB_SOURCES *.cpp *.hpp *.cxx *.c *.h)
#=====================================================
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
add_definitions("-O3 -Wall -fPIC -fmessage-length=0 -Wextra -pedantic -c -W -Wfatal-errors -std=c++17")
#=====================================================
message ("Сборка: ${LIB_NAME} Версии ${PROJECT_VERSION} от ${PROJECT_DATE}")
#=====================================================
# поиск библиотек
find_package(Boost COMPONENTS REQUIRED)
target_link_libraries(${LIB_NAME} PRIVATE ${Boost_LIBRARIES})
#=====================================================
# директивы препроцессора
target_compile_definitions(${LIB_NAME} PUBLIC 
PR_NAME="${PROJECT_NAME}"
PR_DESCRIPT="${PROJECT_DESCRIPTION}"
PR_VERSION="${PROJECT_VERSION}"
PR_VERSION_DATE="${PROJECT_DATE}"
PR_DEVELOPER="${PROJECT_DEVELOPER}"
PR_CONTACT="${DEV_CONTACT}"
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
if (DEBUG)
  add_definitions(-DDEBUG)
endif()
#=====================================================