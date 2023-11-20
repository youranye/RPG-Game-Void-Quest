
add_subdirectory(googletest)

enable_testing()

add_executable(runAllTests
  CharacterManagerTests.cpp
  CharacterTests.cpp
  iomanagertests.cpp
  GameManagerTests.cpp

  BattleManagerTests.cpp
  SceneParserTests.cpp
  SceneManagerTests.cpp
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

add_executable (testBattleManager
    BattleManagerTests.cpp
)

add_executable(testSceneParser SceneParserTests.cpp)
add_executable(testSceneManager SceneManagerTests.cpp)

target_link_libraries(runAllTests CharacterManager Character IOManager GameManager BattleManager SceneManager NarrativeScene gmock gtest GTest::gtest_main)
target_link_libraries(testCharacterManager CharacterManager gmock gtest gtest_main)
target_link_libraries(testCharacterClass Character gmock gtest gtest_main)
target_link_libraries(testBattleManager BattleManager Character gmock gtest gtest_main)
target_link_libraries(testIoManager IOManager gmock gtest GTest::gtest_main)
target_link_libraries(testGameManager GameManager gmock gtest GTest::gtest_main)
target_link_libraries(testSceneParser SceneParser gmock gtest GTest::gtest_main)
target_link_libraries(testSceneManager SceneManager NarrativeScene gmock gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runAllTests)
