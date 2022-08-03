########################################################################

cmake_minimum_required(VERSION 3.7)

############# Prevents Building From Source path #######################

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
message(FATAL_ERROR “In-source build detected!”)
endif()

################### Version Info #######################################

project(f18_env VERSION 0.1)

################## Macro Code ##########################################

# Macro Code to Add Packages
# Add Multiple Packages in a Folder
macro(add_multiple_packages path)
 file(GLOB libs RELATIVE ${path} ${path}/*)
 foreach(library ${libs})  
   if(IS_DIRECTORY ${path}/${library})
     add_subdirectory(${path}/${library})
     list(APPEND EXTRA_LIBS ${library})
     list(APPEND EXTRA_INCLUDES ${path}/${library})
     message(STATUS "Adding " ${library} "...")
   endif()
 endforeach()
endmacro()

# To add Single Packages
macro(add_single_package path package_name)
 add_subdirectory(${path})
 list(APPEND EXTRA_LIBS ${package_name})
 list(APPEND EXTRA_INCLUDES ${path})
 message(STATUS "Adding " ${package_name} "...")
endmacro()

#################### Set CXX Standard ##################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

########################################################################

# Change the paths Here
set(LIBS_PATH ${PROJECT_SOURCE_DIR}/fdm/lib)
set(INPUT_PATH ${PROJECT_SOURCE_DIR}/input)
set(FG_PATH ${PROJECT_SOURCE_DIR}/fg)
set(MAIN_CPP_PATH ${PROJECT_SOURCE_DIR}/fdm)

set(EXTRA_LIBS "")
set(EXTRA_INCLUDES "")

########################################################################

# Add all the Libraries and Packages
add_multiple_packages(${LIBS_PATH})
add_single_package(${INPUT_PATH} input)
add_single_package(${FG_PATH} fg)

#########################################################################
# fdm executable
add_executable(fdm_ext ${MAIN_CPP_PATH}/main.cpp)
target_include_directories(fdm_ext PUBLIC ${PROJECT_BINARY_DIR} ${EXTRA_INCLUDES} ${LIBS_PATH} ${INPUT_PATH} ${FG_PATH})
target_link_libraries(fdm_ext PUBLIC ${EXTRA_LIBS} fg input)

#########################################################################
#########################################################################

