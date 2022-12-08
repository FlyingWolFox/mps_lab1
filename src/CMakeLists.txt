add_executable(mps_lab1 main.cpp)
add_subdirectory(business)
target_link_libraries(mps_lab1 mps_control mps_report)
target_include_directories(mps_lab1 PUBLIC business/control util/)

target_compile_options(mps_lab1 PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic> # -Werror>
)
