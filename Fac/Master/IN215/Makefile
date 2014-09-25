CC=g++ -w
TMPFOLDER=tmp
BUILDFOLDER=_build


all: $(ARG)

$(ARG): $(ARG).o ImageBase.o
	@ if [ ! -d $(BUILDFOLDER) ]; then mkdir $(BUILDFOLDER); fi
	@ if [ ! -d $(TMPFOLDER) ]; then mkdir $(TMPFOLDER); fi
	@ $(CC) $(TMPFOLDER)/$(ARG).o $(TMPFOLDER)/ImageBase.o -o $(BUILDFOLDER)/$(ARG)

$(ARG).o: $(ARG).cpp
	@ if [ ! -d $(TMPFOLDER) ]; then mkdir $(TMPFOLDER); fi
	$(CC) -o $(TMPFOLDER)/$(ARG).o -c $<

ImageBase.o: ImageBase.cpp ImageBase.h
	$(CC) -o $(TMPFOLDER)/ImageBase.o -c ImageBase.cpp

clean: 
	rm -rf $(TMPFOLDER)/*.o
	rm -rf $(BUILDFOLDER)/*

