# Overview
Simulate the a rope utilizing the NGLScene, by implementing distance constraints and collision constraints to accurately depict the movement and interaction of the rope within the simulated environment.
# Short term roadmap

## Particle genertor
A portion of this class references the Particle class, as previously studied in Animation Software Engineering. In addition to this, additional private attributes have been incorporated to enhance the storage and manipulation of data in relation to particles. Furthermore, the code has been restructured to incorporate a significant number of accessors that allow for greater accessibility to the attributes and functionality of the class.This class is designed to be relatively independent and can easily be utilized by other classes or functions through its convenient design and structure, making it easy to call.

## Constraint
I have established a constraint class which serves as a parent class for various types of constraints such as distance constraint and collision constraint. The implementation of the method outlined in "Position Based Dynamic"([Miles Macklin 2016](https://doi.org/10.1145/2994258.2994272)) enables easy implementation of the constraint process using position based approach. This parent class can be inherited by other different constraint types, making the process of adding new constraint types more efficient and easier.

**Distance constraint projection**: The distance constraint is utilized to maintain a specific distance between two points or to prevent objects from penetrating each other. In my rope simulation, I applied it to a set of particles, where it is defined by the target distance between each point and its neighboring point. The constraint projection algorithm is then employed to iteratively adjust the positions of the points in order to maintain the specified target distance. This allows for the simulation of realistic rope behavior and movement.

**Collision constraint projection**: The collision constraint uses the cross product of the surface normal and the direction from the particle to the surface vertex to detect when an object collides with a collider. Once a collision is detected, the position of the particle is adjusted until the distance between the particle and the surface is approximately equal to zero. Initially, I had written a function to correct the position within the collision constraint class, however, the results were not satisfactory because other constraint projections that came after this step would influence the accuracy. To rectify this, I decided to incorporate the correction of the position within my simulation solver, which improved the overall accuracy and performance of the simulation.

## Simulation Solver
The simulation solver is the core component of my code, it takes an array of particles and constraints as input in order to adjust the positions of the particles. The functions that I have written include: dampVelocity(), generateConstraint(), makeProposedPosition(), projectConstraint(), finalizeUpdate(). These functions work together to simulate realistic motion and behavior of particles. My approach to the design of the simulation solver is consistent with my initial design, as outlined above.

# result
Implement distance constraint. Press F to give it the force.
![](./../assets/distance%20constraint.gif)

Implement distance constraint & collision constraint. Press arrows to control the collider plane.
![](./../assets/collision%20constraint.gif)

Add different colliders as tests. Press 1 is cube. Press 2 is cone. Press 3 is cylinder. Press 4 is grid. Some problems happened when I use complex geometry.
![](./../assets/colliders.GIF)

Press 0 to add more ropes. This project cannot simulate well when ropes' number are over 20, I didn't fix this problem because out of time.
![](./../assets/ropes.GIF)

# Building

```
# Setup environment here:https://github.com/NCCA/ase-assignment-Yuqian-He/blob/main/README.md

# Download repository
$ git clone https://github.com/NCCA/ase-assignment-Yuqian-He.git
$ cd ase-assignment-Yuqian-He/PBDNGL

# Configure and build project
$ mkdir build
$ cd build
$ cmake .. 
$ make

# Run the program
$ ./PBDNGL
```

# Reference
Bender, J., Müller, M. and Macklin, M., 2017. A survey on position based dynamics, 2017. Proceedings of the European Association for Computer Graphics: Tutorials, pp.1-31.

Macklin, M., Müller, M., Chentanez, N. and Kim, T.Y., 2014. Unified particle physics for real-time applications. ACM Transactions on Graphics (TOG), 33(4), pp.1-12.
