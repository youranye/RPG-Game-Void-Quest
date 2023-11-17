add_subdirectory(googletest)

add_executable(runAllTests
    BattleManagerTests.cpp
)

add_executable (testBattleManager
    BattleManagerTests.cpp
)

target_link_libraries(runAllTests BattleManager Character gmock gtest gtest_main)
target_link_libraries(testBattleManager BattleManager Character gmock gtest gtest_main)

include(GoogleTest)