# ESP32 Tinypy Hello World

This project demonstrates the use of tinypy (Python) using
the Makoo component framework. The esp-idf uses its own component
build system. Instead of completely replacing esp-idf builder, Makoo
operates above the esp-idf managing the component dependencies and auto
generating the makefile the esp-idf requires.


The folder structure is as follows. There are two applications i.e there
are two main functions.

```
apps
  |-> helloearth
      |->build        (folder contains the build output of esp-idf)
      |->imported     (folder contains the imported components when scons is run)
      |->source       (folder contains application specific source files. app_main is here for example)
      |->SConstruct   (main entry point when scons executes)
      |->component.mk (tells esp-idf about the app specific files in folder apps/helloearth/source)
      |->Makefile     (auto generated when scons is run)
  |-> hellomars
      |->SConstruct
source                (folder contains the share-able part sources of this component)
  |-> test1.py
  |-> test2.py
  |-> test3.py
|-> sconscript        (while scons is walking the dependency tree, this script is executed by a parent component that uses this component)
|-> component.mk      (tells esp-idf about the app specific files in folder source)
```

Here are the steps to build:
```
git clone https://github.com/eyob-boye/esp32_tinypy_helloworld.git  helloworld
cd helloworld
git submodule update --init
```

To build the first app:
```
cd apps/helloearth
scons
make flash
```

To build the second app:
```
cd apps/hellomars
scons
make flash
```

There are a lot of steps that happen when you run `scons` under
the selected application.

1) Scons executes SConstruct first. This top script imports the specified dependent 
components in `imported` folder under the application's root path. Then, it executes
their corresponding sconscript file if it exists.
2) Recursively "walk" the imported components execute their top level sconscript file
if it exists.
3) If tinypy modules are specified in the sconscript files they get discovered.
4) After walking the whole component dependency tree... the following two things 
happen:
    - Makefile for the esp-idf is generated with the discovered component paths
    - tinypy modules are compiled into bytecode and tinypy_app is constructed. In
addition to the byte codes, the module dependency is calculated and `<<module>>_init()` functions are
generated in the order of low to high level dependency. The order of initialization matters.
When the `<<module>>_init()` functions are called, the tinypy module which contains `import <<module>>` expects
the imported module to be already loaded in tinypy global module name space.

Once Makoo is complete, then you can run `make flash` to let loose
the esp-idf build system. Note that, before you run `make flash` make sure that
tools required by the esp-idf are available from the command line. I for example
run the `prepare_shell_path.bat` to add the compiler and tools on the path. Take
a look a this file for some details.

How does scons know how to do all of this?
- "scons" does not know anything about components. But we have extended scons
using makoo_site_scons. This extension is git submoduled so that it is present
and ready to be discovered before we run scons. Note that, it is
submoduled in each application path so that when we run scons, it can simply
discover site_scons in its default search paths. If you submodule it to a location 
other than where you invoke scons then, you have to run `scons --site-dir=<<path_to_makoo_site_scons>>`

Why not use git submodule feature to manage dependencies?
- It is possible. But I am not comfortable using submodule to manage
component dependencies in a complex way. I am not sure what git would
do if there are circular dependencies for example. Path management 
can also become weird when dealing with deep dependencies or common
dependencies. Makoo uses git submodule only to get makoo_site_scons.
