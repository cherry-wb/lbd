Getting Started: Installing LLVM and the Cpu0 example code
==========================================================

Before you start, you should know that you can always examine existing LLVM 
backend code and attempt to port what you find for your own target architecture
.  The majority of this code can be found in the /lib/Target directory of your 
root LLVM directory. As most major RISC instruction set architectures have some 
similarities, this may be the avenue you might try if you are both an 
experienced programmer and knowledgable of compiler backends. 
However, there is a steep learning curve and you may easily get held up 
debugging your new backend. You can easily spend a lot of time tracing which 
methods are callbacks of some function, or which are calling some overridden 
method deep in the LLVM codebase - and with a codebase as large as LLVM, this 
can easily become a headache. This tutorial will help you work through this 
process while learning the fundamentals of LLVM backend design. It will show 
you what is necessary to get your first backend functional and complete, and it 
should help you understand how to debug your backend when it does not produce 
desirable output using the output provided by LLVM.

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
For information on using ``cmake`` to build LLVM, please refer to the `Building 
LLVM with CMake`_ documentation for further information.  We are using cmake 
version 2.8.9.

We will install two llvm directories in this chapter. One is the directory 
llvm/3.1/ which contains the clang, clang++ compiler we will use to translate 
the C/C++ input file into llvm IR. 
The other is the directory llvm/3.1.test/cpu0/1 which contains our cpu0 backend 
program and without clang and clang++.

.. _Building LLVM with CMake: http://llvm.org/docs/CMake.html?highlight=cmake

.. todo:: Find information on debugging LLVM within Xcode for Macs.
.. todo:: Find information on building/debugging LLVM within Eclipse for Linux.

Install LLVM 3.1 release on Linux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Our tutorial is based on LLVM 3.1 release. We need `LLVM <http://llvm.org/>`_,
`clang <http://clang.llvm.org/>`_ and `compiler-rt <http://compiler-rt.llvm.org/>`_.
In this section, we will show the command line steps to build and install LLVM
on your Linux machine. We use the following names to denote paths specific to
your enviroment.

``INSTALL``

  The resulting binary will be installed in this directory.

If you are using IDE, please see :ref:`appendix` for more information.

#. Download the source code.

    .. code-block:: bash

      $ wget http://llvm.org/releases/3.1/llvm-3.1.src.tar.gz
      $ wget http://llvm.org/releases/3.1/clang-3.1.src.tar.gz
      $ wget http://llvm.org/releases/3.1/compiler-rt-3.1.src.tar.gz
      $ tar xvf llvm-3.1.src.tar.gz
      $ tar xvf clang-3.1.src.tar.gz -C llvm-3.1.src/tools/
      $ tar xvf compiler-rt-3.1.src.tar.gz -C llvm-3.1.src/projects/

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

Make another copy /usr/local/llvm/3.1.test/cpu0/1/src for cpu0 debug working 
project 
according the following list steps, the corresponding commands shown in 
:ref:`install_f25`:

1) Enter /usr/local/llvm/3.1.test/cpu0/1 and 
``cp -rf /usr/local/llvm/3.1/src .``.

2) Update my modified files to support cpu0 by command, 
``cp -rf /home/Gamma/Gamma_flash/LLVMBackendTutorial/src_files_modify/src .``.

3) Enter src/lib/Target and copy example code LLVMBackendTutorial/1/Cpu0 to the 
directory by command ``cd src/lib/Target/`` and 
``cp -rf /home/Gamma/Gamma_flash/LLVMBackendTutorial/1/Cpu0 .``.

4) Go into directory 3.1.test/cpu0/1/src and Check step 3 is effect by command 
``grep -R "Cpu0" . | more```. I add the Cpu0 backend support, so check with 
grep.

5) Remove clang from 3.1.test/cpu0/1/src/tools/clang, and mkdir 
3.1.test/cpu0/1/cmake_debug_build. Without this you will waste extra time for 
command 
``make`` in cpu0 example code build.

.. _install_f25:
.. figure:: ../Fig/install/25.png
	:height: 952 px
	:width: 1050 px
	:scale: 80 %
	:align: center

	Create llvm 3.1 debug copy

Now, go into directory 3.1.test/cpu0/1, create directory cmake_debug_build and 
do cmake 
like build the 3.1 release, but we do Debug build and use clang as our compiler 
instead, 
as follows,

.. literalinclude:: ../terminal_io/install/1.txt

Then do make as follows,

.. literalinclude:: ../terminal_io/install/2.txt

Now, we are ready for the cpu0 backend development. We can run gdb debug as 
follows. 
If your setting has anything about gdb errors, please follow the errors indication 
(maybe need to download gdb again). 
Finally, try gdb as :ref:`install_f26`.

.. _install_f26:
.. figure:: ../Fig/install/26.png
	:align: center

	Debug llvm cpu0 backend by gdb


.. _LLVM Download Page:
	http://llvm.org/releases/download.html#3.1


.. _section Create LLVM.xcodeproj of supporting cpu0 by terminal cmake command:
    http://jonathan2251.github.com/lbd/install.html#create-llvm-xcodeproj-of-
    supporting-cpu0-by-terminal-cmake-command

.. _section Create LLVM.xcodeproj by cmake Graphic UI:
    http://jonathan2251.github.com/lbd/install.html#create-llvm-xcodeproj-by-
    cmake-graphic-ui
