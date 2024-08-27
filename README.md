# **PathTracer**

This is a simple path tracer made using the book ['Raytracing in One Weekend' ](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
Currently I only officially support windows (but the compilation should work since the build system uses premake, and no third partly libraries except
[STB](https://github.com/nothings/stb) is used.

---
### Compilation

prerequisite: **premake5**

`premake5 vs2022`

set build configuration to Release and hit build.

using 
`premake5 gmake2` with `make config=release` should also work.

^ also works.
