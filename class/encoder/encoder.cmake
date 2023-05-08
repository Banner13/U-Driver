#
#   author  :   huke
#   date    :   2023-5-7
#   Apache Licence
#

include_guard()
message("U-Peripheral: class driver-encoder is included.")


#enable switch
set(U_DRIVER_CLASS_ENCODER_EC11 ON)
#   switch end



#include list
if(${U_DRIVER_CLASS_ENCODER_EC11})
    include(${CMAKE_CURRENT_LIST_DIR}/EC11/EC11.cmake)
endif()
#   include end

