<p align="center">
  <img src="assets/icon.png" alt="Project Icon">
</p>
# 🎮 Project Engine 
A lightweight, modular **Entity-Component-System (ECS)** based game engine built in C++ with support for rendering, physics, and scene management. Designed for flexibility, maintainability, and extensibility — this engine separates the core ECS logic from the game layer.

---

## 🚀 Features

### ✅ Core Systems
- Efficient **ECS architecture**
- Improved **argument pack methods** for system and component management
- Strict **assertions and validation**
- **Utility methods** in `GameEngine` to interact cleanly with the game layer

### ✅ Components & Systems
- Built-in example components and systems
- Efficient component storage and retrieval
- Serialization & deserialization of entities and scenes
- Component registry with **macro-based reflection**

### ✅ Scene Management
- JSON-based **entity serialization/deserialization**
- Automatic **component registration**
- Simplified scene struct handling

---

## 🧩 Upcoming Work (Next Semester)
- Asset Management  
- Agnostic Input Handling  
- Lua Scripting Integration  
- Dynamic Component & System Loading at Game Level  
- QuadTree-Based Spatial Partitioning  
- Position-Based Entity Queries  

---

## 🛠️ Build Instructions
```bash
git clone <repo-url>
cd <repo-folder>
mkdir build && cd build
cmake ..
make
./FallingBoxes
