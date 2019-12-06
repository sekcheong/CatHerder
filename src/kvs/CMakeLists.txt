add_library(cat_kvs kvs.cpp)
target_link_libraries(cat_kvs PUBLIC cat_sqlite)
target_include_directories(cat_kvs PUBLIC 
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src/sqlite"
)