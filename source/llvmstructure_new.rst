.. _llvm_structure:

=======================
Introduce Cpu0 and LLVM 
=======================

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

This chapter shows you the cpu0 instruction format first. 
Next, the llvm structure is introduced to you by copy and paste the related 
article from llvm web site. The llvm structure introduced here is extracted 
from the asop web site. You can read the whole article from the asop web site. 
After that we will show you how to write register and instruction definitions 
(Target Description File) which will be used in next chapter.

Cpu0 Architecture
=================

We copy and redraw figures in english in this section. This 
web site [#]_ is chinese version and here [#]_ is english version.

Introduction
------------

CPU0 is a 32-bit processor which has registers R0 .. R15, IR, MAR, MDR, etc., 
and its structure is shown below.

.. _llvmstructure_f1: 
.. figure:: ../Fig/llvmstructure/1.png
	:align: center

	The structure of the processor of CPU0

Uses of each register as follows:

.. _llvmstructure_t1: 
.. figure:: ../Table/llvmstructure/1.png
	:align: center

	Cpu0 registers table

Instruction Set
---------------

The CPU0 instruction divided into three types, L-type usually load the saved 
instruction, A-type arithmetic instruction-based J-type usually jump 
instruction, the following figure shows the three types of instruction encoding 
format.

.. _llvmstructure_f2: 
.. figure:: ../Fig/llvmstructure/2.png
	:align: center

	CPU0 three instruction formats

The following is the CPU0 processor's instruction table format

.. _llvmstructure_t2: 
.. figure:: ../Table/llvmstructure/2.png
	:align: center

	CPU0 instruction table

In the second edition of CPU0_v2 we fill the following command:

.. _llvmstructure_t3: 
.. figure:: ../Table/llvmstructure/3.png
	:align: center

	CPU0_v2 instruction table

Status Register
---------------

CPU0 status register contains the state of the N, Z, C, V, and I, T and other 
interrupt mode bit. 
Its structure is shown below.

.. _llvmstructure_f3: 
.. figure:: ../Fig/llvmstructure/3.png
	:align: center

	CPU0 status register

When CMP Ra, Rb instruction execution, the state flag will thus change.

If Ra> Rb, then the setting state of N = 0, Z = 0. 
If Ra <Rb, it will set the state of N = 1, Z = 0. 
If Ra = Rb, then the setting state of N = 0, Z = 1.

So conditional jump the JGT, JLT, JGE, JLE, JEQ, JNE instruction jumps N, Z 
flag in the status register.

Pipeline
--------

CPU0 has three stage pipeline: Instruction fetch, Decode and Execution.

#. Instruction fetch

   - Action 1. The instruction fetch: IR = [PC]
   - Action 2. Update program counter: PC = PC + 4

#. Decode

   - Action 3. Decode: Control unit decodes IR, then set data flow switch 
	   and ALU operation mode. 

#. Execute

   - Action 4. Execute: Data flow into ALU. After ALU done the operation, 
	   the result stored back into destination register. 

Instruction Change
------------------

We have recognized the ldi instruction is a bad design and replace it with mips 
instruction addiu. 
The reason we replace ldi with addiu is that ldi use only one register even 
though ldi is L type format and has two registers, as :num:`llvmstructure-f4`.
Mips addiu which allow programmer to do load constant to register like ldi, 
and add constant to a register. So, it's powerful and fully contains the ldi 
ability. 

The two instruction formats are shown in :num:`figure #llvmstructure-f4`
and :num:`figure #llvmstructure-f5`.

.. _llvmstructure-f4:
.. figure:: ../Fig/llvmstructure/4.png
	:align: center

	Cpu0 ldi instruction

.. _llvmstructure-f5:
.. figure:: ../Fig/llvmstructure/5.png
	:align: center

	Mips addiu instruction format

From :num:`figure #llvmstructure-f4` and :num:`figure #llvmstructure-f5`,
you can find ``ldi $Ra, 5`` can be replaced by ``addiu $Ra, $zero, 5``.
And more, ``addiu`` can do ``addiu $Ra, $Rb, 5`` which add $Rb and 5 then
save to $Ra, but ldi cannot.

As a CPU design, it's common to redesign CPU instruction when find a better
solution during design the compiler backend for that CPU.
So, we add addiu instruction to cpu0.
The cpu0 is my brother's work, I will find time to talk with him.

LLVM Structure
==============

Overview
--------

首先介紹編譯的基本知識，編譯流程可以簡化成 :num:`figure #compilation-pipeline` 。
源語言 (代碼) 經過編譯器前端解析成編譯器內部的中間表示，並在此階段優化代碼，最後
產生目標平台語言。:num:`figure #compilation-flow` 展示了更進一步的編譯流程。

.. _compilation-pipeline:

.. figure:: ../Fig/llvmstructure/compilation_pipeline.png
   :figclass: align-center

   Compilation Pipeline

.. _compilation-flow:

.. figure:: ../Fig/llvmstructure/compilation_flow_part_1.png
   :figclass: align-center

   Compilation Flow

LLVM 後端的四大功能標明在 :num:`figure #llvm-backend` 。

#. 將 LLVM IR 編譯成匯編文本文件: 傳統的靜態編譯。

#. 將 LLVM IR 編譯成目標二進制文件: .o file writer。

#. 將匯編文本文件轉譯為目標二進製文件: 匯編。

#. 將目標二進制文件還原為匯編文本文件: 反匯編。

.. _llvm-backend:

.. figure:: ../Fig/llvmstructure/llvm_backend.png
   :figclass: align-center

   LLVM 後端

Detail
------

Following came from AOSA [#]_.

The most popular design for a traditional static compiler (like most C 
compilers) is the three phase design whose major components are the front end, 
the optimizer and the back end (:num:`figure #simple-compiler`).
The front end parses source code, checking it for errors, and builds a 
language-specific Abstract Syntax Tree (AST) to represent the input code. 
The AST is optionally converted to a new representation for optimization, and 
the optimizer and back end are run on the code.

.. _simple-compiler:
.. figure:: ../Fig/llvmstructure/SimpleCompiler.png
	:align: center

	Three major components of a Three Phase Compiler

The optimizer is responsible for doing a broad variety of transformations to 
try to improve the code's running time, such as eliminating redundant 
computations, and is usually more or less independent of language and target. 
The back end (also known as the code generator) then maps the code onto the 
target instruction set. 
In addition to making correct code, it is responsible for generating good code 
that takes advantage of unusual features of the supported architecture. 
Common parts of a compiler back end include instruction selection, register 
allocation, and instruction scheduling.

This model applies equally well to interpreters and JIT compilers. 
The Java Virtual Machine (JVM) is also an implementation of this model, which 
uses Java bytecode as the interface between the front end and optimizer.

The most important win of this classical design comes when a compiler decides 
to support multiple source languages or target architectures. 
If the compiler uses a common code representation in its optimizer, then a 
front end can be written for any language that can compile to it, and a back 
end can be written for any target that can compile from it, as shown in 
:num:`figure #retargetablity`.

.. _retargetablity:
.. figure:: ../Fig/llvmstructure/RetargetableCompiler.png
	:align: center

	Retargetablity

With this design, porting the compiler to support a new source language (e.g., 
Algol or BASIC) requires implementing a new front end, but the existing 
optimizer and back end can be reused. 
If these parts weren't separated, implementing a new source language would 
require starting over from scratch, so supporting N targets and M source 
languages would need N*M compilers.

Another advantage of the three-phase design (which follows directly from 
retargetability) is that the compiler serves a broader set of programmers than 
it would if it only supported one source language and one target. 
For an open source project, this means that there is a larger community of 
potential contributors to draw from, which naturally leads to more enhancements 
and improvements to the compiler. 
This is the reason why open source compilers that serve many communities (like 
GCC) tend to generate better optimized machine code than narrower compilers 
like FreePASCAL. 
This isn't the case for proprietary compilers, whose quality is directly 
related to the project's budget. 
For example, the Intel ICC Compiler is widely known for the quality of code it 
generates, even though it serves a narrow audience.

A final major win of the three-phase design is that the skills required to 
implement a front end are different than those required for the optimizer and 
back end. 
Separating these makes it easier for a "front-end person" to enhance and 
maintain their part of the compiler. 
While this is a social issue, not a technical one, it matters a lot in 
practice, particularly for open source projects that want to reduce the barrier 
to contributing as much as possible.

The most important aspect of its design is the LLVM Intermediate Representation 
(IR), which is the form it uses to represent code in the compiler. 
LLVM IR is designed to host mid-level analyses and transformations that you 
find in the optimizer section of a compiler. 
It was designed with many specific goals in mind, including supporting 
lightweight runtime optimizations, cross-function/interprocedural 
optimizations, whole program analysis, and aggressive restructuring 
transformations, etc. 
The most important aspect of it, though, is that it is itself defined as a 
first class language with well-defined semantics. 
To make this concrete, here is a simple example of a .ll file:

.. literalinclude:: ../code_fragment/llvmstructure/1.txt

As you can see from this example, LLVM IR is a low-level RISC-like virtual 
instruction set. 
Like a real RISC instruction set, it supports linear sequences of simple 
instructions like add, subtract, compare, and branch. 
These instructions are in three address form, which means that they take some 
number of inputs and produce a result in a different register. 
LLVM IR supports labels and generally looks like a weird form of assembly 
language.

Unlike most RISC instruction sets, LLVM is strongly typed with a simple type 
system (e.g., i32 is a 32-bit integer, i32** is a pointer to pointer to 32-bit 
integer) and some details of the machine are abstracted away. 
For example, the calling convention is abstracted through call and ret 
instructions and explicit arguments. 
Another significant difference from machine code is that the LLVM IR doesn't 
use a fixed set of named registers, it uses an infinite set of temporaries 
named with a % character.

Beyond being implemented as a language, LLVM IR is actually defined in three 
isomorphic forms: the textual format above, an in-memory data structure 
inspected and modified by optimizations themselves, and an efficient and dense 
on-disk binary "bitcode" format. 
The LLVM Project also provides tools to convert the on-disk format from text to 
binary: llvm-as assembles the textual .ll file into a .bc file containing the 
bitcode goop and llvm-dis turns a .bc file into a .ll file.

The intermediate representation of a compiler is interesting because it can be 
a "perfect world" for the compiler optimizer: unlike the front end and back end 
of the compiler, the optimizer isn't constrained by either a specific source 
language or a specific target machine. 
On the other hand, it has to serve both well: it has to be designed to be easy 
for a front end to generate and be expressive enough to allow important 
optimizations to be performed for real targets.
	

Introduce Target Description File
---------------------------------

.. note::
   This section comes from AOSA. http://www.ituring.com.cn/article/4206

The "mix and match" approach allows target authors to choose what makes sense 
for their architecture and permits a large amount of code reuse across 
different targets. 
This brings up another challenge: each shared component needs to be able to 
reason about target specific properties in a generic way. 
For example, a shared register allocator needs to know the register file of 
each target and the constraints that exist between instructions and their 
register operands. 
LLVM's solution to this is for each target to provide a target description 
in a declarative domain-specific language (a set of .td files) processed by the 
tblgen tool. 
The (simplified) build process for the x86 target is shown in :num:`figure #x86-target` .

.. _x86-target:

.. figure:: ../Fig/llvmstructure/X86Target.png
	:align: center

	Simplified x86 Target Definition

The different subsystems supported by the .td files allow target authors to 
build up the different pieces of their target. 
For example, the x86 back end defines a register class that holds all of its 
32-bit registers named "GR32" (in the .td files, target specific definitions 
are all caps) like this:

.. literalinclude:: ../code_fragment/llvmstructure/2.txt


Writing Target Description File
-------------------------------

LLVM use target description files (.td) to describe target register file and
instruction format. After you writing up those .td files, LLVM generates C++
files (\*.inc) by ``llvm-tblgen``. Those \*.inc files are C++ files with table
driven in concept. [#]_ is the web site.

You should write one ``XX.td`` under your target subdirectory, it then includes
other target description files defining various target information. The syntax
of target description file is pretty similar to C++. Below is ``Cpu0.td``.

.. literalinclude:: ../code_fragment/2/Cpu0/Cpu0.td

As shown above, ``Cpu0.td`` includes ``Cpu0RegisterInfo.td`` which defines
the Cpu0 register file.

.. literalinclude:: ../code_fragment/2/Cpu0/Cpu0RegisterInfo.td

In C++ the data layout is declared by class. Declaration tells the variable 
layout; definition allocates memory for the variable. 
For example,

.. literalinclude:: ../code_fragment/llvmstructure/5.txt

Just like C++ class, the keyword **“class”** is used for declaring data structure 
layout. 
``Cpu0Reg<string n>`` declare a derived class from ``Register<n>`` which is 
declared by llvm already, where n is the argument of type string. 
In addition to inherited from all the fields of Register class, Cpu0Reg add a 
new field "Num" of type 4 bits. 
Namespace is same with  C++ namespace. 
**“Def”** is used by define(instance) a concrete variable.

As above, we define a ZERO register which type is Cpu0GPRReg, it's field Num 
is 0 (4 bits) and field n is **“ZERO”** (declared in Register class). 
Note the use of **“let”** expressions to override values that are initially defined 
in a superclass. For example, let Namespace = **“Cpu0”** in class Cpu0Reg, will 
override Namespace declared in Register class. 
The Cpu0RegisterInfo.td also define that CPURegs is a variable for type of 
RegisterClass, where the RegisterClass is a llvm built-in class. 
The type of RegisterClass is a set/group of Register, so CPURegs variable is 
defined with a set of Register.

``Cpu0InstrFormats.td`` defines Cpu0 instruction format. We define a base class
``Cpu0Inst``, then define class ``FA``, ``FI`` and ``FJ`` for each Cpu0 instruction
types.

.. literalinclude:: ../code_fragment/2/Cpu0/Cpu0InstrFormats.td

The cpu0 instructions td is named to Cpu0InstrInfo.td which contents as follows,

.. literalinclude:: ../code_fragment/llvmstructure/6.txt

Here we take ``ADDiu`` as an example. ``ADDiu`` is an instance of class ``ArithLogicI``
which is a subclass of class ``FL``.

.. literalinclude:: ../code_fragment/2/Cpu0/Cpu0InstrInfo_ADDiu.td

.. literalinclude:: ../code_fragment/llvmstructure/8.txt

Expand with FL further,

.. literalinclude:: ../code_fragment/llvmstructure/9.txt

Expand with Cpu0Inst further,

.. literalinclude:: ../code_fragment/llvmstructure/10.txt

It's a lousy process. 
Similarly, LD and ST instruction definition can be expanded in this way. 
Please notify the Pattern =  
[(set CPURegs:$ra, (add RC:$rb, immSExt16:$imm16))] which include keyword 
**“add”**. 
We will use it in DAG transformations later. 


Writing configuration files
---------------------------

You must have to add one LLVMBuild.txt under ``Target/Cpu0`` directory.
If you want to support cmake, then CMakeLists.txt needed to be added.

.. literalinclude:: ../example/2/Cpu0/CMakeLists.txt

.. literalinclude:: ../example/2/Cpu0/LLVMBuild.txt

LLVMBuild.txt files are written in a simple variant of the INI or configuration 
file format. 
Comments are prefixed by ``#`` in both files. 
We explain the setting for these 2 files in comments. 
Please spend a little time to read it.

Both CMakeLists.txt and LLVMBuild.txt coexist in sub-directories 
``MCTargetDesc`` and ``TargetInfo``. 
Their contents indicate they will generate Cpu0Desc and Cpu0Info libraries. 
After building, you will find three libraries: ``libLLVMCpu0CodeGen.a``, 
``libLLVMCpu0Desc.a`` and ``libLLVMCpu0Info.a`` in lib/ of your build 
directory. 
For more details please see 
"Building LLVM with CMake" [#]_ and 
"LLVMBuild Guide" [#]_.

Target Registration
===================

You must also register your target with the TargetRegistry, which is what other 
LLVM tools use to be able to lookup and use your target at runtime. 
The TargetRegistry can be used directly, but for most targets there are helper 
templates which should take care of the work for you.

All targets should declare a global Target object which is used to represent 
the target during registration. 
Then, in the target's TargetInfo library, the target should define that object 
and use the RegisterTarget template to register the target. 
For example, the file TargetInfo/Cpu0TargetInfo.cpp register TheCpu0Target for 
big endian and TheCpu0elTarget for little endian, as follows.

.. literalinclude:: ../code_fragment/llvmstructure/12.txt

Files Cpu0TargetMachine.cpp and MCTargetDesc/Cpu0MCTargetDesc.cpp just define 
the empty initialize function since we register nothing in them for this moment.

.. literalinclude:: ../code_fragment/llvmstructure/13.txt

Please see "Target Registration" [#]_ for reference.

Build libraries and td
======================

The llvm3.1 source code is put in /usr/local/llvm/3.1/src and have llvm3.1 
release-build in /usr/local/llvm/3.1/configure_release_build. 
About how to build llvm, please refer [#]_. 
We made a copy from /usr/local/llvm/3.1/src to 
/usr/local/llvm/3.1.test/cpu0/1/src for working with my Cpu0 target back end. 
Sub-directories src is for source code and cmake_debug_build is for debug 
build directory.

Except directory src/lib/Target/Cpu0, there are a couple of files modified to 
support cpu0 new Target. 
Please check files in src_files_modify/src/. 
You can search cpu0 without case sensitive to find the modified files by 
command,

.. literalinclude:: ../terminal_io/llvmstructure/1.txt

You can update your llvm working copy by,

.. literalinclude:: ../terminal_io/llvmstructure/2.txt

Now, run the cmake and make command to build td (the following cmake command is 
for my setting),

.. literalinclude:: ../terminal_io/llvmstructure/3.txt

After build, you can type command ``llc –version`` to find the cpu0 backend,

.. literalinclude:: ../terminal_io/llvmstructure/4.txt

The ``llc -version`` can display **“cpu0”** and **“cpu0el”** message, because 
the following code from file TargetInfo/Cpu0TargetInfo.cpp what in 
"section Target Registration" [#]_ we made. 
List them as follows again,

.. literalinclude:: ../code_fragment/llvmstructure/14.txt

Now try to do ``llc`` command to compile input file ch3.cpp as follows,

.. literalinclude:: ../code_fragment/llvmstructure/15.txt

First step, compile it with clang and get output ch3.bc as follows,

.. literalinclude:: ../terminal_io/llvmstructure/5.txt

Next step, transfer bitcode .bc to human readable text format as follows,

.. literalinclude:: ../terminal_io/llvmstructure/6.txt

Now, compile ch3.bc into ch3.cpu0.s, we get the error message as follows,

.. literalinclude:: ../terminal_io/llvmstructure/7.txt

Currently we just define target td files (Cpu0.td, Cpu0RegisterInfo.td, ...). 
According to LLVM structure, we need to define our target machine and include 
those td related files. 
The error message say we didn't define our target machine.



.. [#] http://ccckmit.wikidot.com/ocs:cpu0

.. [#] http://translate.google.com.tw/translate?js=n&prev=_t&hl=zh-TW&ie=UTF-8&layout=2&eotf=1&sl=zh-CN&tl=en&u=http://ccckmit.wikidot.com/ocs:cpu0

.. [#] http://www.aosabook.org/en/llvm.html

.. [#] http://llvm.org/docs/TableGenFundamentals.html

.. [#] http://llvm.org/docs/CMake.html

.. [#] http://llvm.org/docs/LLVMBuild.html

.. [#] http://llvm.org/docs/WritingAnLLVMBackend.html#target-registration

.. [#] http://clang.llvm.org/get_started.html

.. [#] http://jonathan2251.github.com/lbd/llvmstructure.html#target-registration
