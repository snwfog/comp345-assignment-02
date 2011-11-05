# COMP345 ASSIGNMENT 02 #
> This assignment builds on the foundation of the first assignment in which the map editor is created to allow the user to build custom map. The difference between this assignment and assignment one is that this time, the map editor is build around the observer design pattern that we learn in class.

### Contains ###
- main.cpp
- GameMap.h + GameMap.cpp
- GameMapEditor.h + GameMapEditor.cpp

### How Is It Implemented ###
> I left a few comments in the source code to clarify the methods that were implemented for this assignment. _GameMap_ is the subject. _GameMapEditor_ is the observer.

#### GameMap ####
	void attach(Observer*)
	void detach(Observer*)
	void notify()
	std::vector<Observer*> observers

#### GameMapEditor ####
	void update(GameMap*)

### How Does It Work ###
> When a new _GameMapEditor_ is created, this _GameMapEditor_ is attached itself (in the constructor) to the subject as an observer by calling the subject's attach method. Since every _GameMapEditor_ contains a _GameMap_ object, this is done easily by calling the member function of the _GameMap_ member variable.

> When the new observer is attached to the member variable of _GameMap_, whenever a modification to the _GameMap_ is made through _GameMapEditor_ by calling _GameMap_->setAtLocation(int, int), the notify function of the _GameMap_ is called.

> When _GameMap_ notify is called, the _GameMap_ will then call the update method of all its stacks of observers.

> When the update method is called, what is modified inside of the _GameMap_ is printed in the _GameMapEditor_'s dialogue window.






