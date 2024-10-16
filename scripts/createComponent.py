import os

def fileName(name: str) -> str:
    return f'ecs/components/{name}/src/lib.cpp'

def fileHeader(name: str) -> str:
    return f'''/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** {name}
*/
'''

def fileContent(name: str) -> str:
    return f'''#include <nlohmann/json.hpp>

#include "Entity.hpp"
#include "Registry.hpp"

extern void register_component(ecs::Registry &registry, ecs::Entity &entity, const nlohmann::json &component)
{{
    auto &{name} = registry.register_component<{name}>(entity);

    //{name}[entity.getId()];
}}
'''

def cmakeContent(name: str) -> str:
    return f'''cmake_minimum_required(VERSION 3.17)
add_library({name} SHARED lib.cpp)
target_include_directories({name} PRIVATE ../../include)
target_include_directories({name} PRIVATE ../../../protocol/include)
'''

def createComponent(name: str) -> None:
    print(f'Creating component {name}')
    if not os.path.exists(f'ecs/components/{name}/src'):
        os.makedirs(f'ecs/components/{name}/src')
    with open(fileName(name), 'w') as f:
        f.write(fileHeader(name))
        f.write(fileContent(name))
    with open(f'ecs/components/{name}/CMakeLists.txt', 'w') as f:
        f.write(cmakeContent(name))
    return

def checkDir() -> None:
    if not os.path.exists('ecs/components'):
        os.makedirs('ecs/components')

def main(av: list[str]) -> int:
    checkDir();
    for f in av:
        createComponent(f)
    return 0

if __name__ == '__main__':
    import sys
    main(sys.argv[1:])
