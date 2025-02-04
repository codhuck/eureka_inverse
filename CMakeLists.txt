cmake_minimum_required(VERSION 3.16)
project(eureka_inverse LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
  geometry_msgs
  rclcpp
  rcpputils
)

foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

include_directories(include/)

add_executable(${PROJECT_NAME}
  src/main.cpp
)

ament_target_dependencies(${PROJECT_NAME}
  geometry_msgs
  rclcpp
  rcpputils
)

# INSTALL
install(TARGETS 
  ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME},
  DESTINATION lauch/${PROJECT_NAME})


ament_package()