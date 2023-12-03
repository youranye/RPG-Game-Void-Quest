#include "FileSceneStore.h"

#include <gtest/gtest.h>

TEST(FileSceneStoreTest, testLoad)
{
    FileSceneStore sceneStore{"test"};
    sceneStore.getScene("dummy#Start");
}

TEST(FileSceneStoreTest, testCache)
{
    FileSceneStore sceneStore{"test"};
    sceneStore.getScene("dummy#Start");
    sceneStore.getScene("dummy#Start"); // Should hit the cached version
}

TEST(FileSceneStoreTest, testMissing)
{
    FileSceneStore sceneStore{"test"};

    ASSERT_THROW(sceneStore.getScene("dummy#nonexistent"), SceneNotFoundException);
}
