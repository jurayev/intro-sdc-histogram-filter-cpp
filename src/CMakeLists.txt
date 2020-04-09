add_library(
        filter_src
        #simulate.cpp
        localizer.cpp
        helpers.cpp
        debugging_helpers.cpp
)

add_executable(simulate simulate.cpp)
