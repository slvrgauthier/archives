from openalea.plantgl.all import *
from sets import Set

class GMap:
	def __init__(self):
		self.points = []
		self.alpha_0 = {}
		self.alpha_1 = {}
		self.alpha_2 = {}
		self.positions = {}

	def darts(self):
		""" Return a list of id representing the darts of the structure """
		return self.points

	def add_dart(self, element):
		""" Create a new dart and return its id """
		self.points.append(element)
		return self.points.index(element)

	def is_valid(self):
		""" Test the validity of the structure."""
		""" Check if there is pending dart for alpha_0 and alpha_1 (fixed point) """
		for element in self.points :
			if element in self.alpha_0 and self.alpha_0[self.alpha_0[element]] != element:
				return False
			if element in self.alpha_1 and self.alpha_1[self.alpha_1[element]] != element:
				return False
		return True

	def link_dart(self, degree, dart1, dart2):
		""" Link the two darts with a relation alpha_degree """
		if degree == 0:
			self.alpha_0[dart1] = dart2
			self.alpha_0[dart2] = dart1
		if degree == 1:
			self.alpha_1[dart1] = dart2
			self.alpha_1[dart2] = dart1
		if degree == 2:
			self.alpha_2[dart1] = dart2
			self.alpha_2[dart2] = dart1
	
	def set_position(self, dart, position) :
		""" Associate coordinates with the vertex &lt;alpha_1,alpha_2&gt;(dart) """
		self.positions[dart] = position

	def orbit(self, dart,list_of_alpha_value):
		""" Return the orbit of dart using a list of alpha relation."""
		""" Example of use. gmap.orbit(0,[0,1])."""
		""" In python, you can use the set structure to process only once all darts of the orbit."""
		orbit = Set()
		orbit.add(dart)
		seen = {}
		stop = False
		while not(stop):
			stop = True
			l_orbit = orbit.copy()
			for d in l_orbit:
				if not(d in seen):
					seen[d] = True
					for a in list_of_alpha_value:
						if a == 0 and d in self.alpha_0:
							stop = False
							orbit.add(self.alpha_0[d])
						if a == 1 and d in self.alpha_1:
							stop = False
							orbit.add(self.alpha_1[d])
						if a == 2 and d in self.alpha_2:
							stop = False
							orbit.add(self.alpha_2[d])
		return orbit

	def sew_dart(self, degree, dart1, dart2, merge_attribute = True):
		""" Sew two elements of degree 'degree' that start at dart1 and dart2."""
		""" Determine first the orbits of dart to sew."""
		"""   Check if they are compatible"""
		"""   Sew pairs of corresponding darts """

def cube(xsize,ysize,zsize):
	gmap = GMap()
	
	# front face
	for i in range(0,16):
		gmap.add_dart(i)
	for i in range(0,8):
		gmap.link_dart(0,2*i,2*i+1)
		if (2*i+2)%8 == 0:
			gmap.link_dart(1,2*i+1,2*i-6)
		else:
			gmap.link_dart(1,2*i+1,2*i+2)
	gmap.set_position(0, [-xsize, -ysize, -zsize])
	gmap.set_position(1, [-xsize, +ysize, -zsize])
	gmap.set_position(2, [-xsize, +ysize, -zsize])
	gmap.set_position(3, [+xsize, +ysize, -zsize])
	gmap.set_position(4, [+xsize, +ysize, -zsize])
	gmap.set_position(5, [+xsize, -ysize, -zsize])
	gmap.set_position(6, [+xsize, -ysize, -zsize])
	gmap.set_position(7, [-xsize, -ysize, -zsize])
	
	# back face
	gmap.set_position(8, [-xsize, -ysize, +zsize])
	gmap.set_position(9, [-xsize, +ysize, +zsize])
	gmap.set_position(10, [-xsize, +ysize, +zsize])
	gmap.set_position(11, [+xsize, +ysize, +zsize])
	gmap.set_position(12, [+xsize, +ysize, +zsize])
	gmap.set_position(13, [+xsize, -ysize, +zsize])
	gmap.set_position(14, [+xsize, -ysize, +zsize])
	gmap.set_position(15, [-xsize, -ysize, +zsize])
		
	return gmap
	
def nb_elements(degree): pass
def eulercharacteristic (gmap): pass
def display(gmap): pass

def display_face(pointlist, indexlist, color):
	sc = Scene([Shape(FaceSet(pointlist,indexlist),Material(color))])
	Viewer.display(sc)

gmap = cube(10, 10, 10)
print "darts() :", gmap.darts()
#print "alpha_0 :", gmap.alpha_0
#print "alpha_1 :", gmap.alpha_1
print "is_valid() :", gmap.is_valid()
print "orbit(0, [0,1]) :", gmap.orbit(0, [0,1])