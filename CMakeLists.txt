cmake_minimum_required(VERSION 3.6)
project(muon_discovery)

set(CMAKE_CXX_STANDARD 14)

#SET( CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread" )

set(SOURCE_FILES
        src/main/cpp/Discovery.h
        src/main/cpp/DiscoveryOnReady.h
        src/main/cpp/main.cpp
        src/main/cpp/MulticastDiscovery.cpp
        src/main/cpp/MulticastDiscovery.h
        src/main/cpp/ServiceDescriptor.h
        src/main/cpp/ServiceDescriptorServer.h
        src/main/cpp/Test.h
        src/main/cpp/URI.h
)

find_package( Threads )

add_executable(muon_discovery ${SOURCE_FILES})

target_link_libraries( muon_discovery ${CMAKE_THREAD_LIBS_INIT} )