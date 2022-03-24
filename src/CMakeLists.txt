cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

project(Satelites)

# TODO: Add target

# Satelite
	#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Satelite/main)
	#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Satelite/UnitTest)
	#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Satelite)
	#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Common)

# GroundControl
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GroundControl/main)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GroundControl/UnitTest)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/GroundControl)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/Common)
