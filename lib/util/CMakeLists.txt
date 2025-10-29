add_library(util skiplist.cpp)

# keywords: private public interface
# # private: for the current target, but not used for other parts of program
# interface: used only by dependencies
# public: used by both
target_include_directories(skiplist 
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR})
