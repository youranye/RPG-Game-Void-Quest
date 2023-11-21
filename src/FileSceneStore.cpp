#include "FileSceneStore.h"

#include "SceneParser.h"

#include <fstream>

void FileSceneStore::loadFile(std::string const path)
{
    std::ifstream ifs{root + '/' + path};
    std::istreambuf_iterator<char> it{ifs};
    std::istreambuf_iterator<char> const end{};

    SceneParser parser{it, end, path.substr(0, path.size() - 3)};

    for (auto &&[name, scene] : parser.parseScenes())
    {
        // The key is filepath#name
        auto const key = path.substr(0, path.length() - 3);
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
    auto const path = std::string{key.substr(0, idx)} + ".md";
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