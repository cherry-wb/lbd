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

<<<<<<< HEAD
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
according the following list steps, the corresponding commands shown as follows,

1) Enter /usr/local/llvm/3.1.test/cpu0/1 and 
``cp -rf /usr/local/llvm/3.1/src .``.

2) Update my modified files to support cpu0 by command, 
``cp -rf /home/Gamma/Gamma_flash/LLVMBackendTutorial/src_files_modify/src .``.

3) Check step 3 is effect by command 
``grep -R "Cpu0" . | more```. I add the Cpu0 backend support, so check with 
grep.

4) Enter src/lib/Target and copy example code LLVMBackendTutorialExampleCode/2/
Cpu0 to the directory by command ``cd lib/Target/`` and 
``cp -rf /home/Gamma/LLVMBackendTutorialExample/2/Cpu0 .``.

5) Remove clang from 3.1.test/cpu0/1/src/tools/clang, and mkdir 
3.1.test/cpu0/1/cmake_debug_build. Without this you will waste extra time for 
command ``make`` in cpu0 example code build.

.. code-block:: bash

  [Gamma@localhost 1]$ pwd
  /usr/local/llvm/3.1.test/cpu0/1
  [Gamma@localhost 1]$ cp -rf /usr/local/llvm/3.1/src .
  [Gamma@localhost Target]$ cd ../..
  [Gamma@localhost src]$ grep -R "Cpu0" .|more
  ./CMakeLists.txt:  Cpu0
  ./lib/Target/LLVMBuild.txt:subdirectories = ARM CellSPU CppBackend Hexagon MBlaz
  e MSP430 Mips Cpu0 PTX PowerPC Sparc X86 XCore
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GPREL: return "GPREL";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GOT_CALL: return "GOT_CALL";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GOT16: return "GOT16";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GOT: return "GOT";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_ABS_HI: return "ABS_HI";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_ABS_LO: return "ABS_LO";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_TLSGD: return "TLSGD";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_TLSLDM: return "TLSLDM";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_DTPREL_HI: return "DTPREL_HI";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_DTPREL_LO: return "DTPREL_LO";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GOTTPREL: return "GOTTPREL";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_TPREL_HI: return "TPREL_HI";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_TPREL_LO: return "TPREL_LO";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GPOFF_HI: return "GPOFF_HI";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GPOFF_LO: return "GPOFF_LO";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GOT_DISP: return "GOT_DISP";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GOT_PAGE: return "GOT_PAGE";
  ./lib/MC/MCExpr.cpp:  case VK_Cpu0_GOT_OFST: return "GOT_OFST";
  ./lib/MC/MCELFStreamer.cpp:    case MCSymbolRefExpr::VK_Cpu0_TLSGD:
  ./lib/MC/MCELFStreamer.cpp:    case MCSymbolRefExpr::VK_Cpu0_GOTTPREL:
  ./lib/MC/MCELFStreamer.cpp:    case MCSymbolRefExpr::VK_Cpu0_TPREL_HI:
  ./lib/MC/MCELFStreamer.cpp:    case MCSymbolRefExpr::VK_Cpu0_TPREL_LO:
  ./lib/MC/MCDwarf.cpp:  // AT_language, a 4 byte value.  We use DW_LANG_Cpu0_Asse
  mbler as the dwarf2
  ./lib/MC/MCDwarf.cpp://  MCOS->EmitIntValue(dwarf::DW_LANG_Cpu0_Assembler, 2);
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GPREL,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GOT_CALL,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GOT16,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GOT,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_ABS_HI,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_ABS_LO,
  ./include/llvm/MC/MCExpr.h://    VK_Cpu0_ABS,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_TLSGD,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_TLSLDM,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_DTPREL_HI,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_DTPREL_LO,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GOTTPREL,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_TPREL_HI,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_TPREL_LO,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GPOFF_HI,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GPOFF_LO,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GOT_DISP,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GOT_PAGE,
  ./include/llvm/MC/MCExpr.h:    VK_Cpu0_GOT_OFST 
  ./include/llvm/Support/ELF.h:// Cpu0 Specific e_flags
  ./include/llvm/Support/ELF.h:// ELF Relocation types for Cpu0
  ./cmake/config-ix.cmake:  set(LLVM_NATIVE_ARCH Cpu0)
  [Gamma@localhost src]$ cd lib/Target/
  [Gamma@localhost Target]$ cp -rf /home/Gamma/Gamma_flash/LLVMBackendTutorial/LLVMBackendTutorialExampleCode/2/Cpu0 .
  [Gamma@localhost Target]$ ls
  ARM             Mips                     TargetIntrinsicInfo.cpp
  CellSPU         MSP430                   TargetJITInfo.cpp
  CMakeLists.txt  PowerPC                  TargetLibraryInfo.cpp
  CppBackend      PTX                      TargetLoweringObjectFile.cpp
  Cpu0            README.txt               TargetMachineC.cpp
  Hexagon         Sparc                    TargetMachine.cpp
  LLVMBuild.txt   Target.cpp               TargetRegisterInfo.cpp
  Makefile        TargetData.cpp           TargetSubtargetInfo.cpp
  Mangler.cpp     TargetELFWriterInfo.cpp  X86
  MBlaze          TargetInstrInfo.cpp      XCore
  [Gamma@localhost Target]$ cd ../..
  [Gamma@localhost src]$ rm -rf tools/clang

Now, go into directory 3.1.test/cpu0/1, create directory cmake_debug_build and 
do cmake 
like build the 3.1 release, but we do Debug build and use clang as our compiler 
instead, 
as follows,

.. code-block:: bash

  [Gamma@localhost src]$ cd ..
  [Gamma@localhost 1]$ pwd
  /usr/local/llvm/3.1.test/cpu0/1
  [Gamma@localhost 1]$ mkdir cmake_debug_build
  [Gamma@localhost 1]$ cd cmake_debug_build/
  [Gamma@localhost cmake_debug_build]$ cmake 
  -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
  -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ../src/
  -- The C compiler identification is Clang 3.1.0
  -- The CXX compiler identification is Clang 3.1.0
  -- Check for working C compiler: /usr/local/llvm/3.1/cmake_release_build/bin/cla
  ng
  -- Check for working C compiler: /usr/local/llvm/3.1/cmake_release_build/bin/cla
  ng
   -- works
  -- Detecting C compiler ABI info
  -- Detecting C compiler ABI info - done
  -- Check for working CXX compiler: /usr/local/llvm/3.1/cmake_release_build/bin/c
  lang++
  -- Check for working CXX compiler: /usr/local/llvm/3.1/cmake_release_build/bin/c
  lang++
   -- works
  -- Detecting CXX compiler ABI info
  -- Detecting CXX compiler ABI info – done ...
  -- Targeting Mips
  -- Targeting Cpu0
  -- Targeting MBlaze
  -- Targeting MSP430
  -- Targeting PowerPC
  -- Targeting PTX
  -- Targeting Sparc
  -- Targeting X86
  -- Targeting XCore
  -- Configuring done
  -- Generating done
  -- Build files have been written to: /usr/local/llvm/3.1.test/cpu0/1/cmake_debug
  _build
  [Gamma@localhost cmake_debug_build]$

Then do make as follows,

.. code-block:: bash

  [Gamma@localhost cmake_debug_build]$ make
  Scanning dependencies of target LLVMSupport
  [ 0%] Building CXX object lib/Support/CMakeFiles/LLVMSupport.dir/APFloat.cpp.o
  [ 0%] Building CXX object lib/Support/CMakeFiles/LLVMSupport.dir/APInt.cpp.o
  [ 0%] Building CXX object lib/Support/CMakeFiles/LLVMSupport.dir/APSInt.cpp.o
  [ 0%] Building CXX object lib/Support/CMakeFiles/LLVMSupport.dir/Allocator.cpp.o
  [ 1%] Building CXX object lib/Support/CMakeFiles/LLVMSupport.dir/BlockFrequency.
  cpp.o ...
  Linking CXX static library ../../lib/libgtest.a
  [100%] Built target gtest
  Scanning dependencies of target gtest_main
  [100%] Building CXX object utils/unittest/CMakeFiles/gtest_main.dir/UnitTestMain
  /
  TestMain.cpp.o Linking CXX static library ../../lib/libgtest_main.a
  [100%] Built target gtest_main
  [Gamma@localhost cmake_debug_build]$
  
  Now, we are ready for the cpu0 backend development. We can run gdb debug as 
  follows. 
  If your setting has anything about gdb errors, please follow the errors indication 
  (maybe need to download gdb again). 
  Finally, try gdb as follows.

.. code-block:: bash

  [Gamma@localhost InputFiles]$ pwd
  /home/Gamma/LLVMBackendTutorialExampleCode/InputFiles
  [Gamma@localhost InputFiles]$ clang -c ch3.cpp -emit-llvm -o ch3.bc
  [Gamma@localhost InputFiles]$ gdb -args /usr/local/llvm/3.1.test/cpu0/1/
  cmake_debug_build/bin/llc -march=cpu0 -relocation-model=pic -filetype=obj 
  ch3.bc -o ch3.cpu0.o
  GNU gdb (GDB) Fedora (7.4.50.20120120-50.fc17)
  Copyright (C) 2012 Free Software Foundation, Inc.
  License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
  This is free software: you are free to change and redistribute it.
  There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
  and "show warranty" for details.
  This GDB was configured as "x86_64-redhat-linux-gnu".
  For bug reporting instructions, please see:
  <http://www.gnu.org/software/gdb/bugs/>...
  Reading symbols from /usr/local/llvm/3.1.test/cpu0/1/cmake_debug_build/bin/llc.
  ..done.
  (gdb) break MipsTargetInfo.cpp:19
  Breakpoint 1 at 0xd54441: file /usr/local/llvm/3.1.test/cpu0/1/src/lib/Target/
  Mips/TargetInfo/MipsTargetInfo.cpp, line 19.
  (gdb) run
  Starting program: /usr/local/llvm/3.1.test/cpu0/1/cmake_debug_build/bin/llc 
  -march=cpu0 -relocation-model=pic -filetype=obj ch3.bc -o ch3.cpu0.o
  [Thread debugging using libthread_db enabled]
  Using host libthread_db library "/lib64/libthread_db.so.1".
  
  Breakpoint 1, LLVMInitializeMipsTargetInfo ()
    at /usr/local/llvm/3.1.test/cpu0/1/src/lib/Target/Mips/TargetInfo/MipsTar
    getInfo.cpp:20
  20          /*HasJIT=*/true> X(TheMipsTarget, "mips", "Mips");
  (gdb) next
  23          /*HasJIT=*/true> Y(TheMipselTarget, "mipsel", "Mipsel");
  (gdb) print X
  $1 = {<No data fields>}
  (gdb) quit
  A debugging session is active.
  
    Inferior 1 [process 10165] will be killed.
  
  Quit anyway? (y or n) y
  [Gamma@localhost InputFiles]$ 



.. _LLVM Download Page:
	http://llvm.org/releases/download.html#3.1


.. _section Create LLVM.xcodeproj of supporting cpu0 by terminal cmake command:
    http://jonathan2251.github.com/lbd/install.html#create-llvm-xcodeproj-of-
    supporting-cpu0-by-terminal-cmake-command

.. _section Create LLVM.xcodeproj by cmake Graphic UI:
    http://jonathan2251.github.com/lbd/install.html#create-llvm-xcodeproj-by-
    cmake-graphic-ui
