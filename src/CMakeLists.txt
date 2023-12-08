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
target_link_libraries(GameManager IOManager BattleManager CharacterManager SceneManager)
target_link_libraries(FileSceneStore NarrativeScene)
target_link_libraries(SceneManager BattleManager)

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME}.elf)
target_link_libraries(${CMAKE_PROJECT_NAME} CharacterManager Character IOManager GameManager BattleManager SceneManager NarrativeScene FileSceneStore SceneParser)

#specifying dirs for making the release executable
set(RESOURCES_SOURCE_DIR "${PROJECT_SOURCE_DIR}/resources")
set(RESOURCES_DESTINATION_DIR "${PROJECT_SOURCE_DIR}/release/resources")
set(VOIDQUEST_EXECUTABLE_SOURCE_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VoidQuest.elf")
set(VOIDQUEST_EXECUTABLE_DESTINATION_DIR "${PROJECT_SOURCE_DIR}/release")

# Add custom commands to copy the folder and file to release directory
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCES_SOURCE_DIR}
    ${RESOURCES_DESTINATION_DIR}
)
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${VOIDQUEST_EXECUTABLE_SOURCE_DIR}
    ${VOIDQUEST_EXECUTABLE_DESTINATION_DIR}
)

# Add a custom target to make sure the copy is executed after building
add_custom_target(CopyFolderTarget ALL DEPENDS ${CMAKE_PROJECT_NAME})