cmake_minimum_required(VERSION 3.20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/src")
add_subdirectory(googletest)

add_executable(runAllTests
  CharacterManagerTests.cpp
  CharacterTests.cpp
)

add_executable(testCharacterManager
CharacterManagerTests.cpp
)

add_executable(testCharacterClass
CharacterTests.cpp
)
 
target_link_libraries(runAllTests gmock gtest gtest_main)
target_link_libraries(runAllTests CharacterManager Character)
target_link_libraries(testCharacterManager gmock gtest gtest_main)
target_link_libraries(testCharacterManager CharacterManager Character)
target_link_libraries(testCharacterClass gmock gtest gtest_main)
target_link_libraries(testCharacterClass Character)