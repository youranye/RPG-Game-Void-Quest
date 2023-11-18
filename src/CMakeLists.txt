add_library(BattleManager BattleManager.cpp)
add_library(IOManager IOManager.cpp)
add_library(GameManager GameManager.cpp)
add_library(Character Character.cpp)
add_library(Player Player.cpp)
add_library(CharacterManager CharacterManager.cpp)
target_link_libraries(Player Character)
target_link_libraries(CharacterManager Character Player)
target_link_libraries(BattleManager Character Player IOManager)
target_link_libraries(GameManager IOManager BattleManager CharacterManager)

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} GameManager IOManager)