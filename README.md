# System-Monitor

System Monitor Project developed in the Object Oriented Programming Course of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 

Follow along with the classroom lesson to complete the project!

![System Monitor](images/monitor.png)

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Within the Udacity Workspace, `.student_bashrc` automatically installs ncurses every time you launch the Workspace.

If you are not using the Workspace, install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)

4. Follow along with the lesson.

5. Implement the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace.

### Debugging with VSCode

In addition I list below the steps used to debug this project using VS Code and [here](https://youtu.be/pThGzmT0C7E) is a video showing the steps.
1.	Create a .vscode directory in your project directory
2.	Copy the launch.json file (you see in the video) inside the .vscode directory
3.	Make sure you have the Makefile file in your project directory
4.	Run the commands

    4.1 "make clean" and "make debug"

5. The first command will cleanup unnecessary files and second command will generate your monitor project in debug mode
6. Open VS code inside the project directory
7. Set a breakpoint in a cpp file you want to stop
8. Click Debug > Start debugging
9. The program will stop in the first breakpoint

And voila, happy debugging!