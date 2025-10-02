![icon](assets/icon.png)
# Project Description
An ECS-based Lua, Game Engine written in C++ to create games that have to handle alot of data. 

# TODO
<<<<<<< HEAD
- Week 1
    - [X] Basic ECS
    - [X] Improving the ECS 
        - [X] Adding Argument Pack methods
        - [X] Improving functionality system manager's signature 
        - [X] Correcting the asserts and adding them where appropiate
        - [X] Moving the game test to game layer and adding utility methods to gameEngine class to allow game layer to make the actual game by using it.

- Week 2
    - [X] Adding one small built-in component and one simple system
        - [X] Finding a way to save components efficently in gameEngine layer.
        - [X] A way to efficently load the components required in a scene.
        - [X] Finding a way to save systems efficently in gameEngine layer.
        - [X] A way to efficently load the components required in a scene.
        - [X] A way to make gEcs inaccessable to game layer. 

- Week 3
    - [-] Scene Management
        - [X] Move the Signature to System base
        - [X] Move the archetypes to component manager 
        - [X] Make methods to get set of archetypes in systems. 
        - [ ] Checks to see if the component is initilized
        - [ ] System initilization if default components are initilized
        - [ ] Scene class
        - [ ] Json based scene 
        - [ ] Parsing said Json based scene

=======
- [X] Basic ECS
- [X] Improving the ECS 
    - [X] Adding Argument Pack methods
    - [X] Improving functionality system manager's signature 
    - [X] Correcting the asserts and adding them where appropiate
    - [X] Moving the game test to game layer and adding utility methods to gameEngine class to allow game layer to make the actual game by using it.
- [X] Adding one small built-in component and one simple system
    - [X] Finding a way to save components efficently in gameEngine layer.
    - [X] A way to efficently load the components required in a scene.
    - [X] Finding a way to save systems efficently in gameEngine layer.
    - [X] A way to efficently load the components required in a scene.
    - [X] A way to make gEcs inaccessable to game layer. 
- [-] Scene Management
    - [ ] Scene Base Class 
    - [ ] Scene Manager 
    - [ ] Adding <SceneId> bitset to Scenes 
    - [ ] Adding ability for creating entites and adding it to the scenes wanted. 
    - [ ] Adding ability for entities to be added and destroyed from scenes.
    - [ ] Adding scene based entities.
    - [ ] Scene switching
    - [ ] Scene based system management
>>>>>>> parent of c7c2daf (Move the Signature to System base)
- [ ] Asset Management.
- [ ] Agnostic Input handeling.
- [ ] Test it on game layer
- [ ] Add lua support
- [ ] Testing adding a component and system at game level
- [ ] Adding test cases 
- [ ] Adding QuadTree based entity poitioning
- [ ] Adding poition based entity query
