# Monster Engine

Welcome to Monster Engine, a video game engine under development by Gerard J. Ramon Catasus, a CITM student.
As the engine is updated, the readme will be updated to cover all the new features.

Thank you for your attention.

## Creator

- Gerard Ramon
    * Github Account: [Gerard Ramon](https://github.com/kramtron)

***

## Libraries Used:

&emsp; -&emsp;*[SDL2](https://www.libsdl.org/)*

&emsp; -&emsp;*[OpenGL](https://www.opengl.org/)* 

&emsp; -&emsp;*[ImGui](https://github.com/ocornut/imgui)*

&emsp; -&emsp;*[GLEW](https://glew.sourceforge.net/)*

&emsp; -&emsp;*[DevIL](https://openil.sourceforge.net/)*

&emsp; -&emsp;*[MathGeoLib](https://github.com/juj/MathGeoLib)*

&emsp; -&emsp;*[GLMath](https://glmath.sourceforge.net/)*


***

## Guid to execute
 * Go to Release  
 * Download the Engine
 * Unpack .zip
 * Execute .exe

***

## Windows
* Drag and drop is enabled to drop fbx and import it to the project.

* Dock the windows were you whant.

###  Main Bar
Here you can find multiple dropdowns: 
* *File*: there's a button to open a popUp about de engine, a button that it takes you to engine GitHub, and a button to close the engine.
* *GameObjects*: a list of basic shapes to use.
* *Windows*: you can change the therme of the window to **"light"**, **"mid night"** and **"dark"**. 

###  Inspector
Show the components of the selected GameObject and a cube to Disable/Enable the GameObject.
* Trnasform with position, rotarion and scale of the object.
* Mesh of the object.


###  Hierarchy
* Show the list of the GameObjects in the scene and their parents/chillds.

###  Console

* You have 3 types of LOG's to organize you're code.
* A button to clear the whole console LOGs.

###  Configuration
You can find some headers with some propertis of windows or configuration:
* *FPS*: Show the name of engine and the organisation that help us, shos too the fps (you can limitate), miliseconds and it shows u the with and height of the windows.
* *Visual*: Buttons to active some aditional widgets of the windows: VSync, brightness, lights, dephts test, face culling, color material, textures.
* *Hardware*: Show the CPU, GPU, the GB of RAM, the Caps that your PC are using and the versions of some librarys that we use.

###  Scene Window

* A button to activate wireframe mode.
* Play, pause and stop buttons.
* Draw the render of the scene.
* Mouse picking: New function. U can click the gameObjects from this window and its gonna be selected in the inspector window. (For perfect work you need to be near the gameObject. This problem gonna be solved soon).


###  Game Window

* Here u can see what your game camera sees and adjust some frustum options.


### Assets Window

* A whole new window that help's u to see what assets folder have while the engine is working
* U can create new Folders inside de Assets folder from this window with a button.
* Go back button tu help u go out from the folder.

### Camera

* The camera has been completely remodeled. It now has a frustum culling system!
* In addition to that, its internal functioning has been modified to make it more optimal and use fewer resources.
* Finally, problems with its movement have also been fixed and now it has a perfect movement
