# Ashley Ho Assignment -- Position Based Dynamics

## Overall Idea

### abstract

PositionBasedDynamics is a method enables mechanical effects based on physics simulation in the graphics community. As opposed to PBA (Physically Based Animation) in the traditional industry, PBD offers more realistic visual effects and highly computationally efficient simulations because it compute the position changes in each simulation step directly([Miles Macklin 2013](https://doi.org/10.1145/2461912.2461984)). This project develops a position-based dynamics library according to algorithms and mathematical equations provided in academic researches. Afterwards, it adds features including XPBD constraints ([Miles Macklin 2016](https://doi.org/10.1145/2994258.2994272)), and gives compared results when implemented on deformable solids.

### development environment

- build system generator: [CMake](https://cmake.org/)
- build system: [Ninja](https://ninja-build.org/)
- compiler: [GCC 11.2.1 x86_64-redhat-linux](https://linux.die.net/man/1/gcc)
- Integrated Development Environment (IDE): [Visual Studio Code](https://code.visualstudio.com/) 
- C++ libraries:
  - NCCA graphics library: [ngl](https://github.com/NCCA/NGL)
  - general-purpose: C++ Standard Library
  - string formatting: [fmt](https://fmt.dev/latest/index.html)
  - automated testing: [Google Test](https://github.com/google/googletest)
  - graphical user interface (GUI): [Qt](https://www.qt.io/)
- package manager: [vcpkg](https://github.com/Microsoft/vcpkg)
- version control system (VCS): [Git](https://git-scm.com/)

## Class Design

https://app.diagrams.net/

## Reference
Miles Macklin and Matthias Müller. 2013. Position based fluids. ACM Trans. Graph. 32, 4, Article 104 (July 2013), 12 pages. https://doi.org/10.1145/2461912.2461984

Miles Macklin, Matthias Müller, and Nuttapong Chentanez. 2016. XPBD: position-based simulation of compliant constrained dynamics. In Proceedings of the 9th International Conference on Motion in Games (MIG '16). Association for Computing Machinery, New York, NY, USA, 49–54. https://doi.org/10.1145/2994258.2994272

