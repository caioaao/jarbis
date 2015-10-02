#Jarbis

Simple two-wheeled mobile robot. Going to use a beaglebone, but intend to
support other platforms as well.

##Software architecture

The project is divided in layers and each layer is subdivided in packages. Each
package on a layer can only depend on packages from the same layer or from lower
level layers. The packages for each layer:

0. Simulator / Hardware Abstraction / Baselib
1. Control Abstraction
2. AI / Teleop

Each package has its own substructure, hence the folders' configuration on the
first level of the project.

##Tests

The testing is meant to be as simple as possible. Each package has a subproject
called "test", where testing modules should stay. For now, no global tests are
being done, but a smoke test should be added soon.
