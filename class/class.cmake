#
#   author  :   huke
#   date    :   2023-5-7
#   Apache Licence
#

include_guard()
message("U-Peripheral: class driver is included.")


#enable switch
set(U_DRIVER_CLASS_ENCODER ON)     # encoder
#   switch end


#include list
if(${U_DRIVER_CLASS_ENCODER})
    include(${CMAKE_CURRENT_LIST_DIR}/encoder/encoder.cmake)
endif()
#   include end

