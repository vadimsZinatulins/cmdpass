cmake_minimum_required(VERSION 3.16)

project(cmdpass)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/src/config.h)

add_executable(
	${PROJECT_NAME}
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/service/getService.cpp
	${PROJECT_SOURCE_DIR}/src/service/createService.cpp
	${PROJECT_SOURCE_DIR}/src/service/Service.cpp
)

set_target_properties(
	${PROJECT_NAME}
		PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)
