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

	def orbit(self, dart, list_of_alpha_value):
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
		list_of_alpha_value = []
		for i in range(0,degree):
			list_of_alpha_value.append(i)
		orbit1 = self.orbit(dart1, list_of_alpha_value)
		orbit2 = self.orbit(dart2, list_of_alpha_value)
		if len(orbit1) == len(orbit2):
			for d1 in orbit1:
				for d2 in orbit2:
					if d1 in self.positions and d2 in self.positions and self.positions[d1] == self.positions[d2]:
						if degree == 0:
							self.link_dart(degree, d1, d2)
						elif self.positions[self.alpha_0[d1]] == self.positions[self.alpha_0[d2]]:
							if degree == 1:
								self.link_dart(degree, d1, d2)
							elif self.positions[self.alpha_1[d1]] == self.positions[self.alpha_1[d2]]:
								if degree == 2:
									self.link_dart(degree, d1, d2)

	def nb_elements(self, degree):
		if degree == 0:
			return len(self.alpha_0)
		if degree == 1:
			return len(self.alpha_1)
		if degree == 2:
			return len(self.alpha_2)

def cube(xsize,ysize,zsize):
	gmap = GMap()
	
	# front face
	for i in range(0,48):
		gmap.add_dart(i)
	for i in range(0,24):
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
	
	# left face
	gmap.set_position(16, [-xsize, -ysize, +zsize])
	gmap.set_position(17, [-xsize, +ysize, +zsize])
	gmap.set_position(18, [-xsize, +ysize, +zsize])
	gmap.set_position(19, [-xsize, +ysize, -zsize])
	gmap.set_position(20, [-xsize, +ysize, -zsize])
	gmap.set_position(21, [-xsize, -ysize, -zsize])
	gmap.set_position(22, [-xsize, -ysize, -zsize])
	gmap.set_position(23, [-xsize, -ysize, +zsize])
	
	# right face
	gmap.set_position(24, [+xsize, -ysize, -zsize])
	gmap.set_position(25, [+xsize, +ysize, -zsize])
	gmap.set_position(26, [+xsize, +ysize, -zsize])
	gmap.set_position(27, [+xsize, +ysize, +zsize])
	gmap.set_position(28, [+xsize, +ysize, +zsize])
	gmap.set_position(29, [+xsize, -ysize, +zsize])
	gmap.set_position(30, [+xsize, -ysize, +zsize])
	gmap.set_position(31, [+xsize, -ysize, -zsize])
	
	# down face
	gmap.set_position(32, [-xsize, -ysize, +zsize])
	gmap.set_position(33, [-xsize, -ysize, -zsize])
	gmap.set_position(34, [-xsize, -ysize, -zsize])
	gmap.set_position(35, [+xsize, -ysize, -zsize])
	gmap.set_position(36, [+xsize, -ysize, -zsize])
	gmap.set_position(37, [+xsize, -ysize, +zsize])
	gmap.set_position(38, [+xsize, -ysize, +zsize])
	gmap.set_position(39, [-xsize, -ysize, +zsize])
	
	# up face
	gmap.set_position(40, [-xsize, +ysize, -zsize])
	gmap.set_position(41, [-xsize, +ysize, +zsize])
	gmap.set_position(42, [-xsize, +ysize, +zsize])
	gmap.set_position(43, [+xsize, +ysize, +zsize])
	gmap.set_position(44, [+xsize, +ysize, +zsize])
	gmap.set_position(45, [+xsize, +ysize, -zsize])
	gmap.set_position(46, [+xsize, +ysize, -zsize])
	gmap.set_position(47, [-xsize, +ysize, -zsize])
	
	#sew
	gmap.sew_dart(2, 0, 16)
	gmap.sew_dart(2, 0, 24)
	gmap.sew_dart(2, 0, 32)
	gmap.sew_dart(2, 0, 40)
	
	gmap.sew_dart(2, 8, 16)
	gmap.sew_dart(2, 8, 24)
	gmap.sew_dart(2, 8, 32)
	gmap.sew_dart(2, 8, 40)
	
	gmap.sew_dart(2, 16, 32)
	gmap.sew_dart(2, 16, 40)
	
	gmap.sew_dart(2, 24, 32)
	gmap.sew_dart(2, 24, 40)
	
	return gmap

def eulercharacteristic (gmap):
	#FIXME calculer les 6 et 4... positions individuelles ?
	S = len(gmap.points) / 6
	A = gmap.nb_elements(0) / 4
	F = 6
	return S - A + F

def display(gmap):
	display_face(gmap.darts(), range(0,8), [255,0,0])
	display_face(gmap.darts(), range(8,16), [255,255,0])
	display_face(gmap.darts(), range(16,24), [0,255,0])
	display_face(gmap.darts(), range(24,32), [0,255,255])
	display_face(gmap.darts(), range(32,40), [0,0,255])
	display_face(gmap.darts(), range(40,48), [255,0,255])

def display_face(pointlist, indexlist, color):
	sc = Scene([Shape(FaceSet(pointlist,indexlist),Material(color))])
	Viewer.display(sc)

gmap = cube(10, 10, 10)
print "darts() :", len(gmap.darts()), "points"
print "alpha_0 :", gmap.nb_elements(0), "points"
print "alpha_1 :", gmap.nb_elements(1), "points"
print "alpha_2 :", gmap.nb_elements(2), "points"
print "is_valid() :", gmap.is_valid()
print "orbit(0, [0,1]) :", len(gmap.orbit(0, [0,1])), "points"
print "orbit(0, [1,2]) :", len(gmap.orbit(0, [1,2])), "points"
print "orbit(0, [0,2]) :", len(gmap.orbit(0, [0,2])), "points"
print "orbit(0, [0,1,2]) :", len(gmap.orbit(0, [0,1,2])), "points"
print "euler() :", eulercharacteristic(gmap)
#display(gmap)