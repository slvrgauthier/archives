CC=g++ -w
TMPFOLDER=tmp
BUILDFOLDER=_build


all: Compresseur

Compresseur: Compresseur.o Image.o
	@ if [ ! -d $(BUILDFOLDER) ]; then mkdir $(BUILDFOLDER); fi
	@ if [ ! -d $(TMPFOLDER) ]; then mkdir $(TMPFOLDER); fi
	@ $(CC) $(TMPFOLDER)/Compresseur.o $(TMPFOLDER)/Image.o -o $(BUILDFOLDER)/Compresseur

Compresseur.o: Compresseur.cpp
	@ if [ ! -d $(TMPFOLDER) ]; then mkdir $(TMPFOLDER); fi
	$(CC) -o $(TMPFOLDER)/Compresseur.o -c $<

Image.o: Image.cpp Image.h
	$(CC) -o $(TMPFOLDER)/Image.o -c Image.cpp

clean: 
	rm -rf $(TMPFOLDER)/*.o
	rm -rf $(BUILDFOLDER)/*

