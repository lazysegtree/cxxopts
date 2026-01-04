PR - https://github.com/jarro2783/cxxopts/pull/437

# TODO List
- [x] Get a gist of what is he trying to do.
- [ ] Figure out the QnA questions
- [ ] Understand basics of the cmake as per this project's usage.

# Notes

Guy says `support the installation of cxxopts together with the main project`

Diff in `CMakeLists.txt` at root
```diff
- option(CXXOPTS_ENABLE_INSTALL "Generate the install target" ${CXXOPTS_STANDALONE_PROJECT})
+ if (NOT CXXOPTS_ENABLE_INSTALL)
+     option(CXXOPTS_ENABLE_INSTALL "Generate the install target" ${CXXOPTS_STANDALONE_PROJECT})
+ endif()
```

# QnA 
1a. What is this `option()` syntax exactly, what is it doing, how does it works? 


1b. Are these `CXXOPTS_ENABLE_INSTALL` shell env variables?
- Not shell variable


2. What is this `if` and `endif` syntax?
3. Looks like someone wants to pass a custom `CXXOPTS_ENABLE_INSTALL` option from outside. How exactly will that be used by anyone? How will it be useful? I thought the entire usage of these `CMakeLists.txt` was to build and compile test programs for our CI.? Why would external users care about it, won't they just copy the `include/cxxopts.hpp` and to their include path and include it?
4. What is `CXXOPTS_STANDALONE_PROJECT` here?
5. What is a downstream project? What is `find_package`? How does parent/child projects in cmake works? How do they inherit/redefine configuration? Examples


# Slops

- What is it doing?

```
Guarding the option with: if (NOT CXXOPTS_ENABLE_INSTALL) option(CXXOPTS_ENABLE_INSTALL "Generate the install target" ${CXXOPTS_STANDALONE_PROJECT}) endif() ensures that if a parent project pre-sets CXXOPTS_ENABLE_INSTALL (e.g., OFF), cxxopts won’t blindly redefine/override it. The default applies only when the variable isn’t already provided by a consumer.

CXXOPTS_ENABLE_INSTALL lets standalone builders/packagers enable installation artifacts, and lets superprojects disable those artifacts when cxxopts is a dependency. The guard makes the option respect values provided by the parent project.

```

> headers get installed into a standard include directory
Its just copying an hpp file right? Why so complex?

> CMake package files (cxxoptsConfig.cmake) and/or pkg-config metadata get installed

WHy would that be needed?

won't they just copy the `include/cxxopts.hpp` and to their include path and include it

> downstream projects can do find_package(cxxopts)



- 

```
While cxxopts is header-only, many consumers rely on CMake package discovery (find_package) and package managers (vcpkg, Conan, system packages). For that, a proper install target is necessary to place headers and export package config files into standard locations.
Projects embedding cxxopts want to keep install control centralized. Being able to turn off cxxopts’ install rules prevents duplicate installs and keeps their packaging clean.
```


```
How can I show the example of usage of `CXXOPTS_ENABLE_INSTALL` via a sample project setup.
To prove that it works and is useful in certain cases
```
```

```