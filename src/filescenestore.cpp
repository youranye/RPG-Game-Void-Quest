#include "filescenestore.h"

#include "sceneparser.h"

#include <fstream>

void FileSceneStore::loadFile(std::filesystem::path const path)
{
    std::ifstream ifs{path};
    std::istreambuf_iterator<char> it{ifs};
    std::istreambuf_iterator<char> const end{};

    SceneParser parser{it, end};

    for (auto &&[name, scene] : parser.parseScenes())
    {
        // The key is filepath#name
        auto const key = std::filesystem::relative(path, root).replace_extension().generic_string();
        scenes.emplace(key + '#' + name, std::move(scene));
    }
}

Scene &FileSceneStore::getScene(std::string_view const key)
{
    // Get the cached scene if we have it
    if (auto it = scenes.find(key); it != std::end(scenes))
    {
        return *(it->second);
    }

    // Otherwise, we need to fetch it from the filesystem
    auto const idx = key.find_first_of('#');
    auto const path = (root / key.substr(0, idx)).replace_extension(".md");
    loadFile(path);

    if (auto it = scenes.find(key); it != std::end(scenes))
    {
        return *(it->second);
    }
    else
    {
        throw SceneNotFoundException{key};
    }
}