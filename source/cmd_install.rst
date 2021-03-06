Getting Started: Installing LLVM and the Cpu0 example code
==========================================================

In this chapter, we will run through how to set up LLVM using if you are using 
Mac OS X or Linux.  When discussing Mac OS X, we are using Apple's Xcode IDE 
(version 4.5.1) running on Mac OS X Mountain Lion (version 10.8) to modify and 
build LLVM from source, and we will be debugging using lldb.  
We cannot debug our LLVM builds within Xcode at the 
moment, but if you have experience with this, please contact us and help us 
build documentation that covers this.  For Linux machines, we are building and 
debugging (using gdb) our LLVM installations on a Fedora 17 system.  We will 
not be using an IDE for Linux, but once again, if you have experience building/
debugging LLVM using Eclipse or other major IDEs, please contact the authors. 
For information on using ``cmake`` to build LLVM, please refer to the "Building 
LLVM with CMake" [#]_ documentation for further information. 
We are using cmake version 2.8.9.

We will install two llvm directories in this chapter. One is the directory 
llvm/3.1/ which contains the clang, clang++ compiler we will use to translate 
the C/C++ input file into llvm IR. 
The other is the directory llvm/3.1.test/cpu0/1 which contains our cpu0 backend 
program and without clang and clang++.

Install LLVM 3.1 release on Linux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Our tutorial is based on LLVM 3.1 release. We need `LLVM`_,
`clang`_ and `compiler-rt`_.
In this section, we will show the command line steps to build and install LLVM
on your Linux machine. We use the following names to denote paths specific to
your enviroment.

.. _LLVM: http://llvm.org

.. _clang: http://clang.llvm.org

.. _compiler-rt: http://compiler-rt.llvm.org


``LLVM_SRC``

  This is the top level directory of the LLVM source tree.

``Example_SRC``

  This is the top level directory where our example code lives. In our tutorial,
  the example is a git submodule stored in ``lbd-example`` directory.

``Debug_OBJ``

  This is the top level directory of the LLVM object tree (i.e. the tree where
  object files and compiled programs will be placed). We build LLVM in debug
  mode here.

``INSTALL``

  The resulting binary will be installed in this directory.

If you are using IDE, please see `appendix`_ for more information.

.. _appendix: http://jonathan2251.github.com/lbd/install.html

#. Download the source code.

    .. code-block:: bash

      $ wget http://llvm.org/releases/3.1/llvm-3.1.src.tar.gz
      $ wget http://llvm.org/releases/3.1/clang-3.1.src.tar.gz
      $ wget http://llvm.org/releases/3.1/compiler-rt-3.1.src.tar.gz
      $ tar xvf llvm-3.1.src.tar.gz
      $ tar xvf clang-3.1.src.tar.gz -C llvm-3.1.src/tools/
      $ tar xvf compiler-rt-3.1.src.tar.gz -C llvm-3.1.src/projects/
      $ mv llvm-3.1.src/tools/clang-3.1.src llvm-3.1.src/tools/clang
      $ mv llvm-3.1.src/projects/compiler-rt-3.1.src llvm-3.1.src/projects/compiler-rt

#. Build LLVM

    .. code-block:: bash

      $ mkdir obj; cd obj
      $ ../llvm-3.1.src/configure --prefix=$INSTALL
        --enable-targets=host
      $ make -j; make install

#. Set $PATH

    .. code-block:: bash

      $ echo "PATH=$INSTALL/bin:$PATH" > $HOME/.bash_profile

Install cpu0 debug build on Linux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#. Download the example code.

    .. code-block:: bash

     $ git clone git://github.com/azru0512/lbd-example.git example

#. Make a new directory.

    .. code-block:: bash

     $ mkdir -p cpu0/2/src; cd cpu0/2/src
     $ cp -rf $LLVM_SRC/* .

#. Update top-level source code.

    .. code-block:: bash

     $ cp -rf $Example_SRC/top-level/* .

#. Update subdirecotry ``lib/Target``.

    .. code-block:: bash

     $ cp -rf $Example_SRC/2/Cpu0/ lib/Target/

#. Remove clang source tree since we don't need it at this moment. Build LLVM in
   debug mode.

    .. code-block:: bash

      $ cd ..
      $ mkdir debug; cd debug
      $ rm -rf ../src/tools/clang/
      $ cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang \
        -DLLVM_TARGETS_TO_BUILD="Mips;Cpu0" \
        -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ../src/      
      $ make

#. Debug

    .. code-block:: bash

      $ gdb bin/llc

.. [#] http://www.llvm.org/docs/CMake.html
