# Todo
- [ ] Try to 'install' cxxopts (no idea what that means) and see what files is he talking about.
- [ ] QnA


# QnA

`Why were cmake files moved from lib/cmake to lib/cmake and pc file moved from libdata/pkgconfig to share/pkgconfig ?`

1. What exact files is he talking about?
2. What code decides these locations?
3. What the hell is in `packaging/` directory? How does it matters? Where is it used? 

# slop

`cmake/cxxopts.cmake::cxxopts_install_logic()`
`GNUInstallDirs` 
`CXXOPTS_CMAKE_DIR`