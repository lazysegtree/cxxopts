## Goal - understand the build workflow (one of the 3 github workflows)


### Concise QnA
- Why do we need `cd build; cmake ..`? Why not `cmake .`?
- How exactly `cmake` builds all the stuff in `build` directory?
- What does plain `make` command does in our project? Which target it builds
- What are we even building? Its just a header-only library.
- What are the `package` and `install` steps for? How exactly can they be used by a end-user? For example will someone be copying the generated rpm file and running `rpm --install`?
- What are these so many cmake related files in the directory?

#### Cmake
- `CMakeLists.txt` - What is the general structure of the file? 
- What is an `INTERFACE` target?
### Additional notes

- I see it builds some tests and examples.
`mkdir build; cd build; cmake ..; make`
```
➜  ~/Workspace/kuknitin/cxxopts/build git:(lazysegtree) [1:23:52] make
[ 25%] Built target example
[ 62%] Built target options_test
[100%] Built target link_test
➜  ~/Workspace/kuknitin/cxxopts/build git:(lazysegtree) [1:24:01]
```

- Tests
```
➜  ~/Workspace/kuknitin/cxxopts git:(lazysegtree) [1:29:53] build/test/options_test
===============================================================================
All tests passed (210 assertions in 35 test cases)

➜  ~/Workspace/kuknitin/cxxopts git:(lazysegtree) [1:30:04]
```

## Goal - build the project with unicode string option

## Goal - set up reproducible build environment with nix

## Goal - understand the cmake github workflow
- What the `ctest` command does? How is its behaviour configured?
- `cmake -S "${{github.workspace}}" -B "${{github.workspace}}/build" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_CXX_COMPILER=${{matrix.compiler}}`
- - Where is this `BUILD_TYPE` coming from? What is its value?

## Notes
All this cmake, nix, etc is too confusing and going over my head. I also have no clear goal that I need to achieve. I need to start with a low scope goal.
