include_directories(test_rpc_server PUBLIC 
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src/debug"
	"${PROJECT_SOURCE_DIR}/src/include"
)

add_executable(test_rpc_server test_rpc_server.cpp)
target_link_libraries(test_rpc_server PUBLIC rpc)

add_executable(test_rpc_client test_rpc_client.cpp)
target_link_libraries(test_rpc_client PUBLIC rpc)

add_executable(test_rapidjson test_rapidjson.cpp)

add_executable(test_dbg test_dbg.cpp)