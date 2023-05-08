#
#   author  :   huke
#   date    :   2023-5-7
#   Apache Licence
#

include_guard()
message("EC11 driver is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/EC11_api.c
	${CMAKE_CURRENT_LIST_DIR}/EC11.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

