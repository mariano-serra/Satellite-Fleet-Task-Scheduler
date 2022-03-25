cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

project(globalProyect)

# TODO: Add target

# Satelite
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Common)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Satelite/main)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Satelite/UnitTest)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Satelite)

# GroundControl
	#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Common)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GroundControl/main)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GroundControl/UnitTest)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GroundControl)
