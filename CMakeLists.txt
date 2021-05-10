cmake_minimum_required(VERSION 2.8.3)

set(PROJECT_NAME lib_cvgutils)
project(${PROJECT_NAME})

### Use version 2011 of C++ (c++11). By default ROS uses c++98
#see: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#see: http://stackoverflow.com/questions/10984442/how-to-detect-c11-support-of-a-compiler-with-cmake
##add_definitions(-std=c++11)
#add_definitions(-std=c++0x)
add_definitions(-std=c++03)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)
#SET(CMAKE_BUILD_TYPE Release) # Release, RelWithDebInfo


set(CVGUTILSLIB_SOURCE_DIR
        src/source)

set(CVGUTILSLIB_INCLUDE_DIR
        src/include)

set(CVGUTILSLIB_HEADER_FILES
        ${CVGUTILSLIB_INCLUDE_DIR}/matrixLib.h
        ${CVGUTILSLIB_INCLUDE_DIR}/cvg_utils_library.h
        ${CVGUTILSLIB_INCLUDE_DIR}/Timer.h
        ${CVGUTILSLIB_INCLUDE_DIR}/xmlfilereader.h
        ${CVGUTILSLIB_INCLUDE_DIR}/control/FilteredDerivative.h
        ${CVGUTILSLIB_INCLUDE_DIR}/control/filtered_derivative_wcb.h
        ${CVGUTILSLIB_INCLUDE_DIR}/control/LowPassFilter.h
        ${CVGUTILSLIB_INCLUDE_DIR}/control/MidLevelControlledsimMultirotor.h
        ${CVGUTILSLIB_INCLUDE_DIR}/control/PID.h
        ${CVGUTILSLIB_INCLUDE_DIR}/control/DMC.h
        ${CVGUTILSLIB_INCLUDE_DIR}/control/Controller_MidLevel_controlModes.h
        ${CVGUTILSLIB_INCLUDE_DIR}/control/simpletrajectorywaypoint.h
        ${CVGUTILSLIB_INCLUDE_DIR}/drone_utils/drone_state_enum.h
        ${CVGUTILSLIB_INCLUDE_DIR}/drone_utils/drone_state_command_enum.h
        # from MAVwork
        ${CVGUTILSLIB_INCLUDE_DIR}/control/CompFilter1.h
        ${CVGUTILSLIB_INCLUDE_DIR}/control/Filter.h
        # from c++03
        ${CVGUTILSLIB_INCLUDE_DIR}/cvg_string_conversions.h
        ${CVGUTILSLIB_INCLUDE_DIR}/cvg_random.h
)

set(CVGUTILSLIB_SOURCE_FILES
        ${CVGUTILSLIB_SOURCE_DIR}/matrixLib.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/cvg_utils_library.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/xmlfilereader.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/control/FilteredDerivative.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/control/filtered_derivative_wcb.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/control/LowPassFilter.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/control/MidLevelControlledsimMultirotor.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/control/PID.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/control/DMC.cpp
        # from MAVwork
        ${CVGUTILSLIB_SOURCE_DIR}/control/CompFilter1.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/control/Filter.cpp
        # from c++03
        ${CVGUTILSLIB_SOURCE_DIR}/cvg_string_conversions.cpp
        ${CVGUTILSLIB_SOURCE_DIR}/cvg_random.cpp
)


find_package(catkin REQUIRED
                COMPONENTS roscpp pugixml)

find_package(OpenCV REQUIRED)


catkin_package(
	INCLUDE_DIRS ${CVGUTILSLIB_INCLUDE_DIR}
        LIBRARIES lib_cvgutils
        DEPENDS OpenCV
        CATKIN_DEPENDS roscpp pugixml
  )



include_directories(${CVGUTILSLIB_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})



add_library(lib_cvgutils ${CVGUTILSLIB_SOURCE_FILES} ${CVGUTILSLIB_HEADER_FILES})
add_dependencies(lib_cvgutils ${catkin_EXPORTED_TARGETS})
target_link_libraries(lib_cvgutils ${OpenCV_LIBS})
target_link_libraries(lib_cvgutils ${catkin_LIBRARIES})


add_library(lib_pruebastaticbool ${CVGUTILSLIB_INCLUDE_DIR}/pruebastaticbool.h ${CVGUTILSLIB_SOURCE_DIR}/pruebastaticbool.cpp)
add_dependencies(lib_pruebastaticbool ${catkin_EXPORTED_TARGETS})
target_link_libraries(lib_pruebastaticbool lib_cvgutils ${OpenCV_LIBS})
target_link_libraries(lib_pruebastaticbool ${catkin_LIBRARIES})


add_executable(${PROJECT_NAME}_code_tests ${CVGUTILSLIB_SOURCE_DIR}/code_tests.cpp ${CVGUTILSLIB_INCLUDE_DIR}/pruebastaticbool.h)
add_dependencies(${PROJECT_NAME}_code_tests ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_code_tests lib_cvgutils lib_pruebastaticbool ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME}_code_tests ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_code_tests2 ${CVGUTILSLIB_SOURCE_DIR}/code_tests2.cpp ${CVGUTILSLIB_INCLUDE_DIR}/pruebastaticbool.h)
add_dependencies(${PROJECT_NAME}_code_tests2 ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_code_tests2 lib_cvgutils lib_pruebastaticbool ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME}_code_tests2 ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_circular_buffer_example ${CVGUTILSLIB_SOURCE_DIR}/circular_buffer_example.cpp)
add_dependencies(${PROJECT_NAME}_circular_buffer_example ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_circular_buffer_example lib_cvgutils ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME}_circular_buffer_example ${catkin_LIBRARIES})


# DMC Controller stuff, MGG
add_executable(${PROJECT_NAME}_DMC_test_suite ${CVGUTILSLIB_SOURCE_DIR}/DMC_test_suite.cpp ${CVGUTILSLIB_SOURCE_FILES} ${CVGUTILSLIB_HEADER_FILES})
add_dependencies(${PROJECT_NAME}_DMC_test_suite ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_DMC_test_suite lib_cvgutils ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME}_DMC_test_suite ${catkin_LIBRARIES})


add_executable(${PROJECT_NAME}_DMC_configuration_file_creator ${CVGUTILSLIB_SOURCE_DIR}/DMC_configuration_file_creator.cpp)
add_dependencies(${PROJECT_NAME}_DMC_configuration_file_creator ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_DMC_configuration_file_creator lib_cvgutils ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME}_DMC_configuration_file_creator ${catkin_LIBRARIES})

