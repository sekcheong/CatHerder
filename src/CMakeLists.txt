# cmake_minimum_required(VERSION 3.14)
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIREDE True)
# set(THREAD_PREFER_PTHEARD_FLAG ON)
# SET(CMAKE_CXX_FLAGS -pthread)
# find_package(Threads REQUIRED)

add_subdirectory(math)
add_executable(hello main.cpp)
add_executable(catherder catherder.cpp)
add_executable(test test.cpp)


target_link_libraries(catherder PUBLIC Threads::Threads PUBLIC mymath)

# include_directories(
# 	"${PROJECT_BINARY_DIR}"
# 	"${PROJECT_SOURCE_DIR}/math"
# )

message( ${PROJECT_SOURCE_DIR} )

message( ${CMAKE_CURRENT_SOURCE_DIR} )

target_include_directories(catherder PUBLIC 
	"${PROJECT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/math"
)