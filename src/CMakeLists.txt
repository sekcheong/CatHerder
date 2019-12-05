add_subdirectory(math)
add_subdirectory(debug)
add_subdirectory(sqlite)
add_subdirectory(kvs)

add_executable(hello main.cpp)
add_executable(catherder catherder.cpp)
add_executable(test test.cpp)

include_directories(
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src/debug"
	"${PROJECT_SOURCE_DIR}/src/kvs"
)

# message( ${PROJECT_SOURCE_DIR} )
# message( ${CMAKE_CURRENT_SOURCE_DIR} )

target_include_directories(catherder PUBLIC 
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src/math"
)

link_libraries(Threads::Threads)

target_link_libraries(catherder PUBLIC mymath)
target_link_libraries(hello PUBLIC kvs)
