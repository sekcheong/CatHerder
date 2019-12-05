add_subdirectory(math)
add_subdirectory(sqlite)
add_subdirectory(kvs)

add_executable(hello main.cpp)
add_executable(catherder catherder.cpp)
add_executable(test test.cpp)

target_link_libraries(catherder PUBLIC Threads::Threads PUBLIC mymath)

# include_directories(
# 	"${PROJECT_BINARY_DIR}"
# 	"${PROJECT_SOURCE_DIR}/math"
# )

# message( ${PROJECT_SOURCE_DIR} )

# message( ${CMAKE_CURRENT_SOURCE_DIR} )

target_include_directories(catherder PUBLIC 
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src/math"
)