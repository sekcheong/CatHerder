include_directories(test_rpc_server PUBLIC 
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src/diagnostic"
	"${PROJECT_SOURCE_DIR}/src/include"
)

add_executable(test_rpc_server test_rpc_server.cpp)
target_link_libraries(test_rpc_server PUBLIC cat_rpc)

add_executable(test_rpc_client test_rpc_client.cpp)
target_link_libraries(test_rpc_client PUBLIC cat_rpc)

add_executable(test_rapidjson test_rapidjson.cpp)

add_executable(test_dbg test_dbg.cpp)
target_link_libraries(test_dbg PUBLIC cat_diag)

add_executable(broadcast_server broadcast_server.cpp)
target_link_libraries(broadcast_server PUBLIC cat_diag)

add_executable(broadcast_client broadcast_client.cpp)
target_link_libraries(broadcast_client PUBLIC cat_diag)

add_executable(get_server_ip get_server_ip.cpp)
