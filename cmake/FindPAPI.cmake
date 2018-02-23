find_path(PAPI_INCLUDE_DIR "papi.h" PATHS "/usr/include" )
find_library(PAPI_LIBRARY "libpapi.a" PATHS "/usr/lib")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(PAPI DEFAULT_MSG
    PAPI_INCLUDE_DIR
    PAPI_LIBRARY
)

add_library(PAPI STATIC IMPORTED)
set_target_properties(PAPI PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${PAPI_INCLUDE_DIR}
    IMPORTED_LOCATION ${PAPI_LIBRARY}
)