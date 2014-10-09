<<<<<<< HEAD
import math

class Point:
	x,y,z = 0,0,0
	
	def __init__(self, x, y, z):
		self.x,self.y,self.z = x,y,z
		
	def __getitem__(self, key):
		return [self.x, self.y, self.z][key]
	
	def __repr__(self):
		return repr((self.x, self.y, self.z))

class Kdnode:
	def __init__(self):
		location,left_child,right_child,parent = None,None,None,None

def createkdtree(point_list, depth, minbucketsize, parent = None):
	if len(point_list) < minbucketsize or depth == 0:
		return point_list
	axis = depth % 3
	point_list.sort(key=lambda point: point[axis])
	median = len(point_list)/2
	node = Kdnode()
	node.location = point_list[median]
	node.left_child = createkdtree(point_list[:median], depth-1, minbucketsize, node)
	node.right_child = createkdtree(point_list[median+1:], depth-1, minbucketsize, node)
	node.parent = parent
	return node

def closestpoint(kdtree, p, depth = 0, pivot = None, candidat = None):
	axis = depth % 3
	if isinstance(kdtree, Kdnode):
		if candidat == None:
			""" Parcours descendant """
			if p[axis] > kdtree.location[axis]:
				return closestpoint(kdtree.right_child, p, depth+1, kdtree)
			else:
				return closestpoint(kdtree.left_child, p, depth+1, kdtree)
		else:
			""" Parcours ascendant """
			candidatdist = math.sqrt(pow(p.x-candidat.x, 2) + pow(p.y-candidat.y, 2) + pow(p.z-candidat.z, 2))
			plandist = math.sqrt(pow(p[axis]-pivot.location[axis], 2))
			if pivot.parent == None or candidatdist < plandist:
				return candidat
			else:
				if pivot.parent.left_child == pivot:
					return closestpoint(pivot.parent.right_child, p, depth-1, pivot.parent, candidat)
				else:
					return closestpoint(pivot.parent.left_child, p, depth-1, pivot.parent, candidat)
	else:
		""" Subdivision du point """
		candidat = None
		for c in kdtree:
			cdist = math.sqrt(pow(p.x-c.x, 2) + pow(p.y-c.y, 2) + pow(p.z-c.z, 2))
			if candidat == None or cdist < math.sqrt(pow(p.x-candidat.x, 2) + pow(p.y-candidat.y, 2) + pow(p.z-candidat.z, 2)):
				candidat = c
				
		pivotdist = math.sqrt(pow(p.x-pivot.location.x, 2) + pow(p.y-pivot.location.y, 2) + pow(p.z-pivot.location.z, 2))
		if candidat == None or pivotdist < math.sqrt(pow(p.x-candidat.x, 2) + pow(p.y-candidat.y, 2) + pow(p.z-candidat.z, 2)):
			candidat = pivot.location
			return closestpoint(pivot, p, depth-1, pivot.parent, candidat)
		else:
			return candidat

kdtree = createkdtree([Point(0, 1, 2), Point(8, 7, 6), Point(3, 4, 5)], 3, 1)
print closestpoint(kdtree, Point(1,18,18))
=======
class GMap:
	def _init_(self):
		self.liste = None
		self.alpha_0 = None
		self.alpha_1 = None 

	def darts():
		""" Return a list of id representing the darts of the structure """
		return liste
	   
	def add_dart(element):
		""" Create a new dart and return its id """
		liste.append(element)
		return liste.index(element)
	   
	def is_valid():
		""" Test the validity of the structure."""
		""" Check if there is pending dart for alpha_0 and alpha_1 (fixed point) """
		for element in liste :
			if alpha_0[alpha_0[element]] != element:
				return false
			if alpha_1[alpha_1[element]] != element:
				return false
	   
	def link_dart(degree, dart1, dart2):
		""" Link the two darts with a relation alpha_degree """
		if degree == 0:
			alpha_0[dart1] = dart2
			alpha_0[dart2] = dart1
		if degree == 1:
			alpha_1[dart1] = dart2
			alpha_1[dart2] = dart1
	   	
	def set_position(dart, position) :
		""" Associate coordinates with the vertex &lt;alpha_1,alpha_2&gt;(dart) """
		
	   
	def orbit(dart,list_of_alpha_value):
		""" Return the orbit of dart using a list of alpha relation."""
		""" Example of use. gmap.orbit(0,[0,1])."""
		""" In python, you can use the set structure to process only once all darts of the orbit.  """
		
	   
	def sew_dart(degree, dart1, dart2, merge_attribute = True):
		""" Sew two elements of degree 'degree' that start at dart1 and dart2."""
		""" Determine first the orbits of dart to sew."""
		"""   Check if they are compatible"""
		"""   Sew pairs of corresponding darts """
		

>>>>>>> 427ea63e29a5b240774def67bef905e4ea225bb0
