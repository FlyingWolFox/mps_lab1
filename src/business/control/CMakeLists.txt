add_library(mps_control UserManager.cpp)
get_filename_component(BUSINESS_DIR ../../ ABSOLUTE)
get_filename_component(SRC_DIR ../../ ABSOLUTE)
target_include_directories(mps_control PUBLIC ${BUSINESS_DIR}/model ${SRC_DIR}/infra ${SRC_DIR}/util)

target_compile_options(mps_control PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic> # -Werror>
)
