About
======

Authors
-------


.. figure:: ../Fig/Author_ChineseName.png
	:align: right

Chen Chung-Shu
	gamma_chen@yahoo.com.tw
	
	http://jonathan2251.github.com/web/index.html

Anoushe Jamshidi
	ajamshidi@gmail.com


Revision history
----------------

Version 3.2.3, Released January 12, 2013
	Add chapter "Porting to LLVM 3.2".
Version 3.2.2, Released January 10, 2013
	Add section "Full support %" and section "Verify DIV for operator %".
Version 3.2.1, Released January 7, 2013
	Add Footnote for references.
	Reorganize chapters.
Version 3.2.0, Released January 1, 2013
	Add chapter Function.
	Move Chapter "Installing LLVM and the Cpu0 example code" from beginning to 
	Appendix A.
	Add subsection "Install other tools on Linux".
	Add chapter ELF.
Version 3.1.2, Released December 15, 2012
	Fix section 6.1 error by add “def : Pat<(brcond RC:$cond, bb:$dst), 
	(JNEOp (CMPOp RC:$cond, ZEROReg), bb:$dst)>;” in last pattern.
	Modify section 5.5
	Fix bug Cpu0InstrInfo.cpp SW to ST.
	Correct LW to LD; LB to LDB; SB to STB.
Version 3.1.1, Released November 28, 2012
	Add Revision history.
	Correct ldi instruction error (replace ldi instruction with addiu from the 
	beginning and in the all example code).
	Move ldi instruction change from section of "Adjust cpu0 instruction and 
	support type of local variable pointer" to Section ”CPU0 
	processor architecture”.
	Correct some English & typing errors.

Licensing
---------
.. todo:: Add info about LLVM documentation licensing.

Preface
-------

The LLVM Compiler Infrastructure provides a versatile structure for creating new
backends. Creating a new backend should not be too difficult once you 
familiarize yourself with this structure. However, the available backend 
documentation is fairly high level and leaves out many details. This tutorial 
will provide step-by-step instructions to write a new backend for a new target 
architecture from scratch. 

We will use the Cpu0 architecture as an example to build our new backend. Cpu0 
is a simple RISC architecture that has been designed for educational purposes. 
More information about Cpu0, including its instruction set, is available 
`here <http://ccckmit.wikidot.com/ocs:cpu0>`_. The Cpu0 example code referenced in
this book can be found `here <http://jonathan2251.github.com/lbd/LLVMBackendTutorialExampleCode.tar.gz>`_.
As you progress from one chapter to the next, you will incrementally build the 
backend's functionality.

This tutorial was written using the LLVM 3.1 Mips backend as a reference. Since 
Cpu0 is an educational architecture, it is missing some key pieces of 
documentation needed when developing a compiler, such as an Application Binary 
Interface (ABI). We implement our backend borrowing information from the Mips 
ABI as a guide. You may want to familiarize yourself with the relevant parts of 
the Mips ABI as you progress through this tutorial.
	

Prerequisites
-------------
Readers should be comfortable with the C++ language and Object-Oriented 
Programming concepts. LLVM has been developed and implemented in C++, and it is 
written in a modular way so that various classes can be adapted and reused as 
often as possible.

Already having conceptual knowledge of how compilers work is a plus, and if you 
already have implemented compilers in the past you will likely have no trouble 
following this tutorial. As this tutorial will build up an LLVM backend 
step-by-step, we will introduce important concepts as necessary.

This tutorial references the following materials.  We highly recommend you read 
these documents to get a deeper understanding of what the tutorial is teaching:

`The Architecture of Open Source Applications Chapter on LLVM <http://www.aosabook.org/en/llvm.html>`_

`LLVM's Target-Independent Code Generation documentation <http://llvm.org/docs/CodeGenerator.html>`_

`LLVM's TableGen Fundamentals documentation <http://llvm.org/docs/TableGenFundamentals.html>`_

`LLVM's Writing an LLVM Compiler Backend documentation <http://llvm.org/docs/WritingAnLLVMBackend.html>`_

`Description of the Tricore LLVM Backend <http://www.opus.ub.uni-erlangen.de/opus/volltexte/2010/1659/pdf/tricore_llvm.pdf>`_

`Mips ABI document <http://www.linux-mips.org/pub/linux/mips/doc/ABI/mipsabi.pdf>`_


Outline of Sections
-------------------

:ref:`sec-llvmstructure`:

This section introduces the Cpu0 architecture, a high-level view of LLVM, and how Cpu0 
will be targeted in in an LLVM backend. This section will run you through the initial 
steps of building the backend, including initial work on the target description (td), 
setting up cmake and LLVMBuild files, and target registration. Around 750 lines of source 
code are added by the end of this section.

:ref:`sec-backendstructure`:

This section highlights the structure of an LLVM backend using by UML graphs, and we 
continue to build the Cpu0 backend. Around 2300 lines of source code are added in this 
section, most of which is common from one LLVM backends to another, regardless of the 
target architecture. By the end of this section, the Cpu0 LLVM backend will support 
three instructions to generate some initial assembly output. 

:ref:`sec-addingmoresupport`:

Over ten C operators and their corresponding LLVM IR instructions are introduced in this 
section. Around 345 lines of source code, mostly in .td Target Description files, are 
added. With these 345 lines, the backend can now translate the **+, -, \*, /, &, |, ^, 
<<, >>, !** and **%** C operators into the appropriate Cpu0 assembly code. Use of the 
``llc`` debug option and of **Graphviz** as a debug tool are introduced in this section.

:ref:`sec-genobjfiles`:

Object file generation support for the Cpu0 backend is added in this section, as the 
Target Registration structure is introduced. With 700 lines of additional code, 
the Cpu0 backend can now generate big and little endian object files.

:ref:`sec-globalvars`:

Global variable, struct and array support are added in this section. 
About 300 lines of source code are added to do this. The Cpu0 supports PIC and static 
addressing mode, both of which area explained as they are added in this section.

:ref:`sec-controlflow`:

Support for the **if, else, while, for, goto** flow control statements are 
added in this section. Around 150 lines of source code added.

:ref:`sec-funccall`:

This section details the implementation of function calls in the Cpu0 backend. The stack 
frame, handling incoming & outgoing arguments, and their corresponding standard LLVM 
functions are introduced in this chapter. Over 700 lines of source code are added in 
this section.

:ref:`sec-elf`:

This section details Cpu0 support for the well-known ELF object file format. The ELF 
format and binutils tools are not a part of LLVM, but are introduced.  This section 
details how to use this ELF tool to verify and analyze the object files created by the 
Cpu0 backend.

:ref:`sec-porting32`:

Introduces the changes of the LLVM APIs used by Cpu0 and Mips when updating this guide 
from LLVM 3.1 to 3.2.  

:ref:`sec-appendix-installing`:

Details how to set up the LLVM source code, development tools, and environment
setting for Mac OS X and Linux platforms.
