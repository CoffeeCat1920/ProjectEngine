![icon](assets/icon.png)
# Project Description
An ECS-based Lua, Game Engine written in C++ to create games that have to handle alot of data. 

# TODO
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
    - [X] Systems and component Management
        - [X] I think all default systems be always present. I hope it doesn't becomes any issue though.
        - [X] Move the Signature to System base
    - [-] Scene Management
        - [X] Make a util method in ECS class
        - [-] Entity Serilization 
        - [ ] Entity Desiilization
        - [ ] Scene struct 
        - [ ] Scene Manager
        - [ ] Json based scene 
        - [ ] Parsing said Json based scene
        - [ ] Creating entities from json objects

- [ ] Asset Management.
- [ ] Agnostic Input handeling.
    - [ ] Systems layer input defination
- [ ] Test it on game layer
- [ ] Add lua support
- [ ] Testing adding a component and system at game level
- [ ] Adding test cases 
- [ ] Adding QuadTree based entity poitioning
- [ ] Adding poition based entity query
