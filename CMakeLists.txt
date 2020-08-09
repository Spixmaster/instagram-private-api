cmake_minimum_required(VERSION "3.18.1")

#General
project("instagram-private-api")
set(CMAKE_CXX_STANDARD 17)

#Target
add_library("${PROJECT_NAME}" STATIC
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
    
    #tools-cpp
    "./tools-cpp/src/constants/Constants.cpp"
    "./tools-cpp/src/constants/Messages.cpp"
    
    "./tools-cpp/src/http/HttpArg.cpp"
    "./tools-cpp/src/http/HttpClient.cpp"
    "./tools-cpp/src/http/HttpCookie.cpp"
    "./tools-cpp/src/http/HttpHeader.cpp"
    "./tools-cpp/src/http/HttpResponse.cpp"
    "./tools-cpp/src/http/InputFile.cpp"
    
    "./tools-cpp/src/Tools.cpp"
    )

#Headers
target_include_directories("${PROJECT_NAME}" PRIVATE "./include/")
target_include_directories("${PROJECT_NAME}" PRIVATE "./tools-cpp/include/")

#Libraries
target_link_libraries("${PROJECT_NAME}" PocoFoundation)
target_link_libraries("${PROJECT_NAME}" PocoNet)
target_link_libraries("${PROJECT_NAME}" PocoNetSSL)
target_link_libraries("${PROJECT_NAME}" PocoCrypto)
target_link_libraries("${PROJECT_NAME}" boost_system)
target_link_libraries("${PROJECT_NAME}" boost_iostreams)
target_link_libraries("${PROJECT_NAME}" boost_filesystem)
target_link_libraries("${PROJECT_NAME}" boost_locale)
