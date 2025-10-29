#add_library(tests example.cpp)

# keywords: private public interface
# # private: for the current target, but not used for other parts of program
# interface: used only by dependencies
# public: used by both
enable_testing()

target_include_directories(lib 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SKIPLIST_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/skiplist/*.cpp")
file(GLOB MEMTABLE_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/memtable/*.cpp")
file(GLOB WAL_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/wal/*.cpp")
file(GLOB DB_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/db/*.cpp")

add_executable(test_skiplist ${SKIPLIST_TEST_SOURCES})
add_executable(test_memtable ${MEMTABLE_TEST_SOURCES})
add_executable(test_wal ${WAL_TEST_SOURCES})
add_executable(test_db ${DB_TEST_SOURCES})

target_include_directories(test_skiplist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/skiplist)
target_include_directories(test_memtable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/memtable)
target_include_directories(test_wal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/memtable)
target_include_directories(test_db PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

target_link_libraries(test_skiplist PRIVATE lib GTest::gtest_main)
target_link_libraries(test_memtable PRIVATE lib GTest::gtest_main)
target_link_libraries(test_wal PRIVATE lib GTest::gtest_main)
target_link_libraries(test_db PRIVATE lib GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(test_skiplist)
gtest_discover_tests(test_memtable)
gtest_discover_tests(test_wal)
gtest_discover_tests(test_db)

