cmake_minimum_required(VERSION 3.15)
project(server VERSION 0.1.0)

# This configuration assumes that gRPC and all its dependencies are already installed
# on this system, so they can be located by find_package().

# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)


# # hw_grpc_proto
add_library(system_grpc_proto
../proto/system.grpc.pb.cc
../proto/system.grpc.pb.h
../proto/system.pb.cc
../proto/system.pb.h)

target_include_directories(system_grpc_proto PUBLIC ${CMAKE_SOURCE_DIR}/../proto/)
target_link_libraries(system_grpc_proto 
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF})

add_executable(server main.cpp database.cpp  )
target_include_directories(server PUBLIC ${CMAKE_SOURCE_DIR}/../proto/)
target_link_libraries(server system_grpc_proto 
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF})

