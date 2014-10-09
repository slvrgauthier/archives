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