### swan game engine
game_engine/
├── core/
│   ├── engine.h
│   ├── engine.cpp
│   ├── ecs/
│   │   ├── entity.h
│   │   ├── entity.cpp
│   │   ├── component.h
│   │   ├── component.cpp
│   │   ├── system.h
│   │   └── system.cpp
│   ├── scene/
│   │   ├── scene.h
│   │   └── scene.cpp
│   ├── level/
│   │   ├── level.h
│   │   └── level.cpp
│   └── resource/
│       ├── resource_manager.h
│       └── resource_manager.cpp
├── components/
│   ├── transform.h
│   ├── transform.cpp
│   ├── mesh.h
│   ├── mesh.cpp
│   ├── material.h
│   └── material.cpp
├── systems/
│   ├── rendering_system.h
│   ├── rendering_system.cpp
│   ├── physics_system.h
│   └── physics_system.cpp
├── behaviors/
│   ├── behavior.h
│   ├── behavior.cpp
│   ├── behavior_tree.h
│   └── behavior_tree.cpp
├── logic/
│   ├── logic_node.h
│   └── logic_node.cpp
├── editors/
│   ├── block_editor.h
│   ├── block_editor.cpp
│   ├── level_editor.h
│   └── level_editor.cpp
├── asset/
│   ├── mesh.h
│   ├── texture.h
│   ├── audio.h
│   └── animation.h
└── main.cpp
