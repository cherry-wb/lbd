lbd: llvm backend document
==========================

This document aims to provide a simple, concise, and clear step-by-step 
tutorial in creating a new LLVM backend from scratch. 
It is written in reStructuredText, and built using the Sphinx Python 
Documentation Generator.

本文件目的是為 LLVM 編寫後端提供一個簡潔扼要的教學。本文件以 reStructuredText
寫成，並以 Sphinx Python Documentation Generator 編譯而成。

You can download and build the document yourself by doing command below:

你可以下載文檔並透過底下指令自行編譯:

```
$ git clone git://github.com/azru0512/lbd.git
$ cd lbd
$ git submodule init; git submodule update
$ make html
```

If you would like to to view an up to date version of this book in your 
browser without checking out and building the book, please visit: 

  http://azru0512.github.com/lbd/

or

  http://people.cs.nctu.edu.tw/~chenwj/slide/lbd/

如果你不想要下載並編譯本文件的代碼，而只想要以瀏覽器閱讀本文件最新的版本，
請見:

   http://azru0512.github.com/lbd/

或是

   http://people.cs.nctu.edu.tw/~chenwj/slide/lbd/
