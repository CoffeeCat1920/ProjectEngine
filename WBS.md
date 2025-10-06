# Work Breakdown Structure (WBS)

## 1. Core ECS Implementation
### 1.1 Basic ECS
- [ ] Implement entity-component-system base  
- [ ] Verify entity creation, component attachment, and system updates  

### 1.2 ECS Improvements
- [ ] Add argument pack methods for flexibility  
- [ ] Improve functionality of system manager signatures  
- [ ] Correct asserts and add safety checks  
- [ ] Move game test logic to game layer  
- [ ] Add utility methods in `gameEngine` class to allow game layer usage  

---

## 2. Built-in Components & Systems
### 2.1 Component Management
- [ ] Implement efficient saving of components in gameEngine layer  
- [ ] Implement efficient loading of required components in a scene  

### 2.2 System Management
- [ ] Implement efficient saving of systems in gameEngine layer  
- [ ] Implement efficient loading of systems in a scene  
- [ ] Restrict direct `gEcs` access from game layer  

---

## 3. Systems & Component Management
### 3.1 Default System Handling
- [ ] Ensure all default systems are always present  
- [ ] Validate no conflicts from always-present systems  

### 3.2 Signature Refactor
- [ ] Move signature handling to `System` base class  

---

## 4. Scene Management
### 4.1 Entity Utilities
- [ ] Add utility method in ECS for scene handling  
- [ ] Implement entity serialization  
- [ ] Implement entity deserialization  

### 4.2 Scene Structure
- [ ] Design `Scene` struct  
- [ ] Implement JSON loading  
- [ ] Extract entities from JSON  
- [ ] Extract components from JSON and deserialize them  
- [ ] Create entities based on extracted data  

---

## 5. Asset Management
- [ ] Implement asset manager module  
- [ ] Define resource loading/unloading strategy  

---

## 6. Input Handling
### 6.1 Input Abstraction
- [ ] Implement agnostic input handling  
- [ ] Define input at the systems layer  

---

## 7. Game Layer Testing
- [ ] Test engine from game layer  
- [ ] Validate ECS interaction with higher-level API  

---

## 8. Lua Support
- [ ] Add Lua scripting support  
- [ ] Expose ECS/gameEngine API to Lua  

---

## 9. Extended Functionality
### 9.1 Dynamic Component & System Handling
- [ ] Implement runtime addition of components at game level  
- [ ] Implement runtime addition of systems at game level  

### 9.2 Spatial Queries
- [ ] Add QuadTree-based entity positioning  
- [ ] Implement position-based entity queries  

---

## 10. Testing & Validation
- [ ] Write unit tests for ECS components, systems, and scene management  
- [ ] Add integration tests for game layer and Lua scripts  
- [ ] Validate performance under large data sets  
