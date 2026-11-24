add_library(training
    core/PoseHandler.cpp
    executor/ExecutorImpl.cpp
)

target_include_directories(training
    PUBLIC "${CMAKE_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_options(training PRIVATE -Wall -Werror)