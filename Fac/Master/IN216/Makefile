CC=g++ -w
BUILD=_build


all: Intersection Jarvis Graham Triangulation

Intersection: Intersection.cc ARN.cc
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	$(CC) -o $(BUILD)/$@ $^

Jarvis: Jarvis.cc
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	$(CC) -o $(BUILD)/$@ $<

Graham: Graham.cc
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	$(CC) -o $(BUILD)/$@ $<

Triangulation: Triangulation.cc
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	$(CC) -o $(BUILD)/$@ $<

Delaunay: Delaunay.cc
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	$(CC) -o $(BUILD)/$@ $^

AlphaS: AlphaS.cc
	@ if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi
	$(CC) -o $(BUILD)/$@ $^

clean: 
	rm -rf $(BUILD)/*

