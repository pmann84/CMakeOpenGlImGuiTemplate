# Prerequisites
- CMake
- spdlog
- glm
- glad
- glfw
- ImGui

# Clone
For a new clone
```
git clone --recursive https://github.com/pmann84/CMakeOpenGlImGuiTemplate.git
```
For an already cloned repo
```
git clone https://github.com/pmann84/CMakeOpenGlImGuiTemplate.git
cd CMakeOpenGlImGuiTemplate
git submodule update --init --recursive
```
# Configure and Build
First do an out of source build by configuring the build scripts
```
cd CMakeOpenGlImGuiTemplate
mkdir out
cd out
cmake ..
```
Then build
```
cd out 
cmake --build . --config Debug
```