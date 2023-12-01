set(CMAKE_CXX_FLAGS --coverage)
add_subdirectory(googletest)

add_executable(runAllTests
  CharacterManagerTests.cpp
  CharacterTests.cpp
  IOManagerTests.cpp
  GameManagerTests.cpp
  BattleManagerTests.cpp
  PlayerClassTests.cpp
  SceneParserTests.cpp
  SceneManagerTests.cpp
)

add_executable(testCodeCoverage
  CharacterManagerTests.cpp
  CharacterTests.cpp
  IOManagerTests.cpp
  GameManagerTests.cpp
  BattleManagerTests.cpp
  PlayerClassTests.cpp
  SceneParserTests.cpp
  SceneManagerTests.cpp
  ../src/CharacterManager.cpp
  ../src/Character.cpp
  ../src/IOManager.cpp
  ../src/GameManager.cpp
  ../src/BattleManager.cpp
  ../src/Player.cpp
  ../src/SceneManager.cpp
  ../src/FileSceneStore.cpp
  ../src/NarrativeScene.cpp
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

add_executable(testSceneParser SceneParserTests.cpp)
add_executable(testSceneManager SceneManagerTests.cpp)

target_link_libraries(runAllTests CharacterManager Character IOManager GameManager BattleManager SceneManager NarrativeScene gmock gtest GTest::gtest_main)
target_link_libraries(testCodeCoverage CharacterManager Character IOManager GameManager BattleManager SceneManager NarrativeScene gmock gtest GTest::gtest_main)
target_link_libraries(testCharacterManager CharacterManager Character Player IOManager gmock gtest gtest_main)
target_link_libraries(testCharacterClass Character gmock gtest gtest_main)
target_link_libraries(testPlayerClass Player Character gmock gtest gtest_main)
target_link_libraries(testBattleManager BattleManager Character gmock gtest gtest_main)
target_link_libraries(testIoManager IOManager gmock gtest GTest::gtest_main)
target_link_libraries(testGameManager CharacterManager Character IOManager GameManager SceneManager BattleManager NarrativeScene gmock gtest GTest::gtest_main)
target_link_libraries(testSceneParser SceneParser gmock gtest GTest::gtest_main)
target_link_libraries(testSceneManager SceneManager NarrativeScene IOManager CharacterManager BattleManager gmock gtest GTest::gtest_main)

include(GoogleTest)
