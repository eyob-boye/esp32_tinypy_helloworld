# ESP32 Tinypy Hello World example_tinypy_helloworld

This project demonstrates the use of tinypy in an esp-idf project using
the Makoo component framework. The esp-idf uses the its own component
build system. Instead of completely replacing this framework, Makoo
acts above the esp-idf managing the component dependencies and auto
generating the makefile the esp-idf requires.


The folder structure is as follows. There are two applications i.e there
are two main functions.

apps
  |-> helloearth
  |-> hellomars
source
  |-> test1.py
  |-> test2.py
  |-> test3.py


Here are the steps to build:

git clone https://github.com/eyob-boye/esp32_tinypy_helloworld.git  helloworld
cd helloworld
git submodule update --init

To build the first app:
cd apps/helloearth
scons
make flash

To build the second app:
cd apps/hellomars
scons
make flash

There are a lot of things that happend when you run scons under
the selected application.

1) Imports any specified component under imported/* folder
2) Rursively walk the imported components if they have sconscript file.
3) If tinypy modules are specified in the sconscript files they get discovered.
4) After walking the whole component tree... the following two things happen:
    4a) Makefile for the esp-idf is generated with the discovered component paths
    4b) tinypy modules are compiled into bytecode and tinypy_app is constructed. In
addition to the bytecodes, the module dependency is calculated and <<module>>_init() functions are
generated in the order of low to high level dependecy. The order matters... since
when the init() functions are called, the tinypy module which contains import * expects
the imported module to be already loaded.

Once scons is complete, then you can run make flash to let loose
the esp-idf build system.


How does scons know how to do all of this?
- Well scons does not know. But we have extended it using makoo_site_scons...
which is git submoduled to be present before we run scons. Note that it is
submoduled in each application path... so when we run scons it can simply
discover it. If you submodule it somewhere else then, you have to run
scons --site-dir=<<path_to_makoo_site_scons>>

Why not use git submodule feature to manage dependencies?
- It is possible. But I am not comfirtable using submodule to manage
component dependencies in a complex way. I am not sure what it would
do if there are circular dependencies for example. Path management 
can also become weird when dealing with deep dependencies or common
depenedencies.
