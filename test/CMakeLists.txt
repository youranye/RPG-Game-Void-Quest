
add_subdirectory(googletest)

add_executable(runAllTests
  CharacterManagerTests.cpp
  CharacterTests.cpp
  IOManagerTests.cpp
  GameManagerTests.cpp
  BattleManagerTests.cpp
  PlayerClassTests.cpp
)

add_executable(testCharacterManager
  CharacterManagerTests.cpp
)

add_executable(testIoManager
  IOManagerTests.cpp
)

add_executable(testGameManager
  GameManagerTests.cpp
)

add_executable(testCharacterClass
  CharacterTests.cpp
)

add_executable(testPlayerClass
  PlayerClassTests.cpp
)

add_executable (testBattleManager
    BattleManagerTests.cpp
)
 

target_link_libraries(runAllTests CharacterManager Character IOManager GameManager BattleManager gmock gtest GTest::gtest_main)
target_link_libraries(testCharacterManager CharacterManager Character Player IOManager gmock gtest gtest_main)
target_link_libraries(testCharacterClass Character gmock gtest gtest_main)
target_link_libraries(testPlayerClass Player Character gmock gtest gtest_main)
target_link_libraries(testBattleManager BattleManager Character gmock gtest gtest_main)
target_link_libraries(testIoManager IOManager gmock gtest GTest::gtest_main)
target_link_libraries(testGameManager GameManager gmock gtest GTest::gtest_main)

include(GoogleTest)
