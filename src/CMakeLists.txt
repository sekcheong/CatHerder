add_subdirectory(diagnostic)
add_subdirectory(sqlite)
add_subdirectory(kvs)
add_subdirectory(rpc)
add_subdirectory(tests)

include_directories(
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src/debug"
	"${PROJECT_SOURCE_DIR}/src/kvs"
	"${PROJECT_SOURCE_DIR}/src/rpc"
)

link_libraries(Threads::Threads)

# message( ${PROJECT_SOURCE_DIR} )
# message( ${CMAKE_CURRENT_SOURCE_DIR} )

