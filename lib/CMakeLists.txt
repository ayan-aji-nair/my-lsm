add_library(lib db.cpp util/skiplist.cpp memtable/memtable.cpp wal/wal_writer.cpp wal/wal_reader.cpp)

# keywords: private public interface
# # private: for the current target, but not used for other parts of program
# interface: used only by dependencies
# public: used by both
target_include_directories(lib 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
