add_library(kvs kvs.cpp)
target_link_libraries(kvs PUBLIC sqlite)
target_include_directories(kvs PUBLIC 
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src/sqlite"
)