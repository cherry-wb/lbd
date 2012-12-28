# MakeFile for building all the docs at once.
# Inspired by the Makefile used by bazaar. 
# http://bazaar.launchpad.net/~bzr-pqm/bzr/2.3/
 
PYTHON = python
 
.PHONY: all clean html latexpdf epub htmlhelp
 
# Dependencies to perform before running other builds.
SPHINX_DEPENDENCIES = \
	zh/Makefile
 
# Copy-paste the english Makefile everwhere its needed.
%/Makefile : en/Makefile
	$(PYTHON) -c "import shutil; shutil.copyfile('$<', '$@')"
 
# Make the HTML version of the documentation with correctly nested language folders.
html: $(SPHINX_DEPENDENCIES)
	cd en && make html LANG=en
	cd zh && make html LANG=zh
 
htmlhelp: $(SPHINX_DEPENDENCIES)
	cd en && make htmlhelp LANG=en
 
epub: $(SPHINX_DEPENDENCIES)
	cd en && make epub LANG=en
 
latexpdf: $(SPHINX_DEPENDENCIES)
	cd en && make latexpdf LANG=en
 
clean:
	rm -rf build/*

gh-pages:
	git checkout gh-pages
	rm -rf build _sources _static _images
	git checkout master $(GH_PAGES_SOURCES)
	git reset HEAD
	tar -zcvf LLVMBackendTutorialExampleCode.tar.gz LLVMBackendTutorialExampleCode
	make html latexpdf epub
	mv -fv build/html/* ./
	mv -fv build/latex/WriteAnLLVMBackendTutorialForCpu0.pdf "./WriteAnLLVMBackendTutorialForCpu0.pdf"
	mv -fv build/epub/WriteAnLLVMBackendTutorialForCpu0.epub "./WriteAnLLVMBackendTutorialForCpu0.epub"
	rm -rf $(GH_PAGES_SOURCES) build
	#git add -A
	#git commit -m "Generated gh-pages for `git log master -1 --pretty=short --abbrev-commit`" && git push origin gh-pages ; git checkout master
