add_subdirectory(googletest)

enable_testing()

add_executable(runAllTests
  CharacterManagerTests.cpp
  CharacterTests.cpp
  iomanagertests.cpp
)

add_executable(testCharacterManager
  CharacterManagerTests.cpp
)

add_executable(testCharacterClass
  CharacterTests.cpp
)
 
target_link_libraries(runAllTests CharacterManager Character IOManager gmock gtest GTest::gtest_main)
target_link_libraries(testCharacterManager CharacterManager gmock gtest gtest_main)
target_link_libraries(testCharacterClass Character gmock gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(runAllTests)