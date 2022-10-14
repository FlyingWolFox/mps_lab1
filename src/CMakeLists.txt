add_executable(mps_lab1 main.cpp UserManager.cpp)

target_compile_options(mps_lab1 PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic> # -Werror>
)
