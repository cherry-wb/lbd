lbd: llvm backend document
==========================

This document aims to provide a simple, concise, and clear step-by-step 
tutorial in creating a new LLVM backend from scratch. It is written in
reStructuredText, and built using the
[Sphinx Python Documentation Generator] (http://sphinx-doc.org/).

本文件目的是為 LLVM 編寫後端提供一個簡潔扼要的教學。本文件以 reStructuredText
寫成，並以 [Sphinx Python Documentation Generator](http://sphinx-doc.org/)
編譯而成。

We use our pygments extension [TblgenLexer](https://github.com/azru0512/tblgenlexer)
to hightlight LLVM tblgen syntax, so you have to install the extension first. The Makefile
has been slightly modified so that you can build the document under [virtual python
environment] (http://peak.telecommunity.com/DevCenter/EasyInstall#creating-a-virtual-python).
Please follow commands below to install [TblgenLexer](https://github.com/azru0512/tblgenlexer)
extension:

我們使用自定的 pygments 外掛 [TblgenLexer](https://github.com/azru0512/tblgenlexer)
，它是個 LLVM tblgen 語法高亮外掛，你必須先安裝它。Makefile 已被稍加修改，你可以
在 [virtual python environment] (http://peak.telecommunity.com/DevCenter/EasyInstall#creating-a-virtual-python).
 底下編譯本文件。請透過底下指令安裝外掛:

    $ git clone git://github.com/azru0512/tblgenlexer.git
    $ cd tblgenlexer
    $ python setup.py bdist_egg
    $ python setup.py install

You can download and build the document yourself by doing command below:

你可以下載文檔並透過底下指令自行編譯:

    $ git clone git://github.com/azru0512/lbd.git
    $ cd lbd
    $ git submodule init; git submodule update
    $ make html

If you would like to to view an up to date version of this book in your 
browser without checking out and building the book, please visit: 

如果你不想要下載並編譯本文件的代碼，而只想要以瀏覽器閱讀本文件最新的版本，
請見:

*  http://azru0512.github.com/lbd/
*  http://people.cs.nctu.edu.tw/~chenwj/slide/lbd/
