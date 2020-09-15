cmake_minimum_required(VERSION 3.17)
project(lib_app)

set(CMAKE_CXX_STANDARD 20)

add_executable(lib_app main.cpp KeyPair.cpp KeyPair.h Keys.cpp Keys.h helper.cpp helper.h base64.cpp base64.h IO.cpp IO.h timer.cpp timer.h sendmail.cpp sendmail.h keyhook.cpp keyhook.h)