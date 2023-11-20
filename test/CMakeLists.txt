
add_subdirectory(googletest)

add_executable(runAllTests
  CharacterManagerTests.cpp
  CharacterTests.cpp
  iomanagertests.cpp
  GameManagerTests.cpp

#  BattleManagerTests.cpp
)

add_executable(testCharacterManager
  CharacterManagerTests.cpp
)

add_executable(testIoManager
  iomanagertests.cpp
)

add_executable(testGameManager
  GameManagerTests.cpp
)


add_executable(testCharacterClass
  CharacterTests.cpp
)
 

target_link_libraries(runAllTests CharacterManager Character IOManager GameManager BattleManager gmock gtest GTest::gtest_main)
target_link_libraries(testCharacterManager CharacterManager gmock gtest gtest_main)
target_link_libraries(testCharacterClass Character gmock gtest gtest_main)
target_link_libraries(testIoManager IOManager gmock gtest GTest::gtest_main)
target_link_libraries(testGameManager GameManager gmock gtest GTest::gtest_main)

include(GoogleTest)
