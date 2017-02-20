cmake_minimum_required (VERSION 2.6)

Project (ProjectEuler)

#Use solution folders. 
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory ("library")
add_subdirectory ("problems")