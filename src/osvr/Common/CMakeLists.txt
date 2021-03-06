osvr_setup_lib_vars(Common)

include(CheckIncludeFile)

check_include_file(byteswap.h OSVR_HAVE_BYTESWAP_H)
configure_file(ConfigByteSwapping.h.cmake_in "${CMAKE_CURRENT_BINARY_DIR}/ConfigByteSwapping.h")

set(API
    "${HEADER_LOCATION}/AddDevice.h"
    "${HEADER_LOCATION}/AlignmentPadding.h"
    "${HEADER_LOCATION}/BaseDevice.h"
    "${HEADER_LOCATION}/BaseDevicePtr.h"
    "${HEADER_LOCATION}/BaseMessageTraits.h"
    "${HEADER_LOCATION}/Buffer.h"
    "${HEADER_LOCATION}/BufferTraits.h"
    "${HEADER_LOCATION}/Buffer_fwd.h"
    "${HEADER_LOCATION}/ChangeOfBasis.h"
    "${HEADER_LOCATION}/Common.h"
    "${HEADER_LOCATION}/ConnectionWrapper.h"
    "${HEADER_LOCATION}/CreateDevice.h"
    "${HEADER_LOCATION}/DegreesToRadians.h"
    "${HEADER_LOCATION}/DeviceComponent.h"
    "${HEADER_LOCATION}/DeviceComponentPtr.h"
    "${HEADER_LOCATION}/Endianness.h"
    "${HEADER_LOCATION}/GetEnvironmentVariable.h"
    "${HEADER_LOCATION}/ImagingComponent.h"
    "${HEADER_LOCATION}/JSONEigen.h"
    "${HEADER_LOCATION}/JSONTransformVisitor.h"
    "${HEADER_LOCATION}/MessageHandler.h"
    "${HEADER_LOCATION}/MessageRegistration.h"
    "${HEADER_LOCATION}/PathElementTools.h"
    "${HEADER_LOCATION}/PathElementTypes.h"
    "${HEADER_LOCATION}/PathElementTypes_fwd.h"
    "${HEADER_LOCATION}/PathNode.h"
    "${HEADER_LOCATION}/PathNode_fwd.h"
    "${HEADER_LOCATION}/PathTree.h"
    "${HEADER_LOCATION}/PathTreeFull.h"
    "${HEADER_LOCATION}/PathTree_fwd.h"
    "${HEADER_LOCATION}/RawMessageType.h"
    "${HEADER_LOCATION}/RawSenderType.h"
    "${HEADER_LOCATION}/RouteContainer.h"
    "${HEADER_LOCATION}/RoutingConstants.h"
    "${HEADER_LOCATION}/RoutingExceptions.h"
    "${HEADER_LOCATION}/RoutingKeys.h"
    "${HEADER_LOCATION}/Serialization.h"
    "${HEADER_LOCATION}/SerializationTags.h"
    "${HEADER_LOCATION}/SerializationTraits.h"
    "${HEADER_LOCATION}/SystemComponent.h"
    "${HEADER_LOCATION}/SystemComponent_fwd.h"
    "${HEADER_LOCATION}/Transform.h"
    "${CMAKE_CURRENT_BINARY_DIR}/ConfigByteSwapping.h")

set(SOURCE
    AddDevice.cpp
    BaseDevice.cpp
    Common.cpp
    CreateDevice.cpp
    DeviceComponent.cpp
    DeviceWrapper.cpp
    DeviceWrapper.h
    GetEnvironmentVariable.cpp
    ImagingComponent.cpp
    JSONTransformVisitor.cpp
    MessageHandler.cpp
    MessageRegistration.cpp
    PathElementTools.cpp
    PathElementTypes.cpp
    PathNode.cpp
    PathParseAndRetrieve.cpp
    PathParseAndRetrieve.h
    PathTree.cpp
    RawMessageType.cpp
    RawSenderType.cpp
    RouteContainer.cpp
    RoutingConstants.cpp
    RoutingKeys.cpp
    Serialization.cpp
    SystemComponent.cpp)

osvr_add_library()

set_target_properties(${LIBNAME_FULL} PROPERTIES
    VERSION ${OSVR_VERSION}
    SOVERSION 0
    INTERFACE_osvrcore_MAJOR_VERSION 0)

set_property(TARGET ${LIBNAME_FULL} APPEND PROPERTY
    COMPATIBLE_INTERFACE_STRING osvrcore_MAJOR_VERSION)

target_include_directories(${LIBNAME_FULL}
    PUBLIC
    ${Boost_INCLUDE_DIRS})

target_compile_options(${LIBNAME_FULL}
    PUBLIC
    ${OSVR_CXX11_FLAGS})

target_link_libraries(${LIBNAME_FULL}
    PUBLIC
    osvrUtilCpp
    jsoncpp_lib
    PRIVATE
    opencv_core
    vendored-vrpn
    eigen-headers)

osvr_delayload_opencv(${LIBNAME_FULL} opencv_core)

###
# Grab DLLs please.
###
if(OSVR_COPY_OPENCV)
    osvr_copy_dep(${LIBNAME_FULL} opencv_core)
    osvr_copy_dep(${LIBNAME_FULL} opencv_highgui)   # used by plugin
    osvr_copy_dep(${LIBNAME_FULL} opencv_imgproc)   # used by plugin
endif()
