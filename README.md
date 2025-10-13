# Project Description

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

- [X] Systems and component Management
    - [X] I think all default systems be always present. I hope it doesn't becomes any issue though.
    - [X] Move the Signature to System base

- [-] Scene Management
    - [X] Make a util method in ECS class
    - [X] Entity Serilization 
    - [X] Entity Desiilization
    - [-] Scene struct 
        - [-] Macro Based Refelction 
            - [X] Create the component registry
            - [X] Register all the component through it
            - [-] Register component in most ECS and registry
            - [ ] Automatically creating to and from json functionality

- [ ] Refactoring
    - [ ] Fix the typeid(T).name problem

- [ ] Asset Management.
- [ ] Agnostic Input handeling.
    - [ ] Systems layer input defination
- [ ] Test it on game layer
- [ ] Add lua support
- [ ] Testing adding a component and system at game level
- [ ] Adding test cases 
- [ ] Adding QuadTree based entity poitioning
- [ ] Adding poition based entity query
