add_library(BattleManager BattleManager.cpp)
add_library(IOManager IOManager.cpp)
add_library(GameManager GameManager.cpp)
add_library(Character Character.cpp)
add_library(Player Player.cpp)
add_library(CharacterManager CharacterManager.cpp)
add_library(FileSceneStore FileSceneStore.cpp)
add_library(NarrativeScene NarrativeScene.cpp)
add_library(SceneManager SceneManager.cpp)
add_library(SceneParser INTERFACE)
target_link_libraries(SceneParser INTERFACE NarrativeScene)
target_link_libraries(Player Character)
target_link_libraries(CharacterManager Character Player IOManager)
target_link_libraries(BattleManager Character Player IOManager)
target_link_libraries(GameManager IOManager BattleManager CharacterManager)
target_link_libraries(FileSceneStore NarrativeScene)

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} CharacterManager Character IOManager GameManager BattleManager SceneManager NarrativeScene FileSceneStore SceneParser)