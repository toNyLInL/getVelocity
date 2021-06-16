cmake_minimum_required(VERSION 2.8)
 
PROJECT(getVelocity)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(getVelocity MACOSX_BUNDLE getVelocity)
 
if(VTK_LIBRARIES)
  target_link_libraries(getVelocity ${VTK_LIBRARIES})
else()
  target_link_libraries(getVelocity vtkHybrid vtkWidgets)
endif()