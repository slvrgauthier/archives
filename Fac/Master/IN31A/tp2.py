from openalea.plantgl.all import *
from sets import Set

class GMap:
	def __init__(self):
		self.brins = []
		self.alpha_0 = {}
		self.alpha_1 = {}
		self.alpha_2 = {}
		self.positions = {}

	def darts(self):
		""" Return a list of id representing the darts of the structure """
		return self.brins

	def add_dart(self, element):
		""" Create a new dart and return its id """
		self.brins.append(element)
		return self.brins.index(element)

	def is_valid(self):
		""" Test the validity of the structure."""
		""" Check if there is pending dart for alpha_0 and alpha_1 (fixed point) """
		for element in self.brins :
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
				if d not in seen:
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
		return list(orbit)

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
	
	for i in range(0,48):
		gmap.add_dart(i)
	for i in range(0,24):
		gmap.link_dart(0,2*i,2*i+1)
		if (2*i+2)%8 == 0:
			gmap.link_dart(1,2*i+1,2*i-6)
		else:
			gmap.link_dart(1,2*i+1,2*i+2)
	
	# down
	gmap.set_position(0, [-xsize, -ysize, -zsize])
	gmap.set_position(1, [-xsize, +ysize, -zsize])
	gmap.set_position(2, [-xsize, +ysize, -zsize])
	gmap.set_position(3, [+xsize, +ysize, -zsize])
	gmap.set_position(4, [+xsize, +ysize, -zsize])
	gmap.set_position(5, [+xsize, -ysize, -zsize])
	gmap.set_position(6, [+xsize, -ysize, -zsize])
	gmap.set_position(7, [-xsize, -ysize, -zsize])
	
	# up
	gmap.set_position(8, [-xsize, -ysize, +zsize])
	gmap.set_position(9, [-xsize, +ysize, +zsize])
	gmap.set_position(10, [-xsize, +ysize, +zsize])
	gmap.set_position(11, [+xsize, +ysize, +zsize])
	gmap.set_position(12, [+xsize, +ysize, +zsize])
	gmap.set_position(13, [+xsize, -ysize, +zsize])
	gmap.set_position(14, [+xsize, -ysize, +zsize])
	gmap.set_position(15, [-xsize, -ysize, +zsize])
	
	# back
	gmap.set_position(16, [-xsize, -ysize, +zsize])
	gmap.set_position(17, [-xsize, +ysize, +zsize])
	gmap.set_position(18, [-xsize, +ysize, +zsize])
	gmap.set_position(19, [-xsize, +ysize, -zsize])
	gmap.set_position(20, [-xsize, +ysize, -zsize])
	gmap.set_position(21, [-xsize, -ysize, -zsize])
	gmap.set_position(22, [-xsize, -ysize, -zsize])
	gmap.set_position(23, [-xsize, -ysize, +zsize])
	
	# front
	gmap.set_position(24, [+xsize, -ysize, -zsize])
	gmap.set_position(25, [+xsize, +ysize, -zsize])
	gmap.set_position(26, [+xsize, +ysize, -zsize])
	gmap.set_position(27, [+xsize, +ysize, +zsize])
	gmap.set_position(28, [+xsize, +ysize, +zsize])
	gmap.set_position(29, [+xsize, -ysize, +zsize])
	gmap.set_position(30, [+xsize, -ysize, +zsize])
	gmap.set_position(31, [+xsize, -ysize, -zsize])
	
	# left
	gmap.set_position(32, [-xsize, -ysize, +zsize])
	gmap.set_position(33, [-xsize, -ysize, -zsize])
	gmap.set_position(34, [-xsize, -ysize, -zsize])
	gmap.set_position(35, [+xsize, -ysize, -zsize])
	gmap.set_position(36, [+xsize, -ysize, -zsize])
	gmap.set_position(37, [+xsize, -ysize, +zsize])
	gmap.set_position(38, [+xsize, -ysize, +zsize])
	gmap.set_position(39, [-xsize, -ysize, +zsize])
	
	# right
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
	S = []
	for p in gmap.positions.values():
		if p not in S:
			S.append(p)
	S = len(S)
	
	# double liaison pour chaque couple de brins et double arete pour chaque arete visible donc /4
	A = gmap.nb_elements(0) / 4
	
	F = []
	for b in gmap.brins:
		o = gmap.orbit(b,[0,1])
		# les orbites sont triees donc comparaison possible
		if o not in F:
			F.append(o)
	F = len(F)
	
	print S,"sommets,",A,"aretes,",F,"faces : euler() =",S - A + F
	return S - A + F

def display(gmap):
	shapes = []
	shapes.append(display_face([gmap.positions[0],gmap.positions[2],gmap.positions[4],gmap.positions[6]], [[0,1,2,3]], [255,0,0]))
	shapes.append(display_face([gmap.positions[8],gmap.positions[10],gmap.positions[12],gmap.positions[14]], [[0,1,2,3]], [255,255,0]))
	shapes.append(display_face([gmap.positions[16],gmap.positions[18],gmap.positions[20],gmap.positions[22]], [[0,1,2,3]], [0,255,0]))
	shapes.append(display_face([gmap.positions[24],gmap.positions[26],gmap.positions[28],gmap.positions[30]], [[0,1,2,3]], [0,255,255]))
	shapes.append(display_face([gmap.positions[32],gmap.positions[34],gmap.positions[36],gmap.positions[38]], [[0,1,2,3]], [0,0,255]))
	shapes.append(display_face([gmap.positions[40],gmap.positions[42],gmap.positions[44],gmap.positions[46]], [[0,1,2,3]], [255,0,255]))
	Viewer.display(Scene(shapes))

def display_face(pointlist, indexlist, color):
	return Shape(FaceSet(pointlist,indexlist),Material(color))

gmap = cube(5, 5, 5)
print "darts() :", len(gmap.darts()), "brins"
print "alpha_0 :", gmap.nb_elements(0), "brins"
print "alpha_1 :", gmap.nb_elements(1), "brins"
print "alpha_2 :", gmap.nb_elements(2), "brins"
print "is_valid() :", gmap.is_valid()
print "\norbit(0, [0,1]) :", len(gmap.orbit(0, [0,1])), "brins"
print "orbit(0, [1,2]) :", len(gmap.orbit(0, [1,2])), "brins"
print "orbit(0, [0,2]) :", len(gmap.orbit(0, [0,2])), "brins"
print "orbit(0, [0,1,2]) :", len(gmap.orbit(0, [0,1,2])), "brins\n"
eulercharacteristic(gmap)
display(gmap)