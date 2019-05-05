set(HEADER_FILES
        inc/contact_node.h
        inc/info_node.h
        inc/hashtable.h)

set(SOURCE_FILES
        src/hashtable.cpp src/contact_node.cpp)
include_directories(inc)
include_directories(test/googletest)

add_library(library STATIC ${SOURCE_FILES} ${HEADER_FILES})