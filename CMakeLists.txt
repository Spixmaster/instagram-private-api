cmake_minimum_required(VERSION "3.18.1")

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
  message(SEND_ERROR "In-source builds are not allowed!")
endif ()

#General
project("instagram-private-api")
set(CMAKE_CXX_STANDARD "17")

#Target
add_library("${CMAKE_PROJECT_NAME}"
    "./src/constants/Constants.cpp"
    "./src/constants/Messages.cpp"
    
    "./src/devices/Device.cpp"
    "./src/devices/HuaweiMate9Pro.cpp"
    "./src/devices/LgG5.cpp"
    "./src/devices/OnePlus3T.cpp"
    "./src/devices/OnePlus7.cpp"
    "./src/devices/SamsungGalaxyS7.cpp"
    "./src/devices/SamsungGalaxyS7Edge.cpp"
    "./src/devices/SamsungGalaxyS9Plus.cpp"
    "./src/devices/ZteAxon7.cpp"
    
    "./src/Api.cpp"
    )

    #Headers
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "./include/")

    #Link libraries
target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC "PocoFoundation")
target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC "PocoNet")
target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC "PocoNetSSL")
target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC "PocoCrypto")
target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC "boost_system")
target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC "boost_iostreams")
target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC "boost_filesystem")
target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC "boost_locale")

    #Options
        #Optimization
target_compile_options("${CMAKE_PROJECT_NAME}" PUBLIC "-O3")
        #Warnings
target_compile_options("${CMAKE_PROJECT_NAME}" PUBLIC "-Wall")
target_compile_options("${CMAKE_PROJECT_NAME}" PUBLIC "-Wextra")
        #Preprocessor
target_compile_options("${CMAKE_PROJECT_NAME}" PUBLIC "-MD")
target_compile_options("${CMAKE_PROJECT_NAME}" PUBLIC "-MP")
