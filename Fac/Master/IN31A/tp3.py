from openalea.plantgl.all import norm, Vector3
import math

class Kdnode:
	def __init__(self):
		location,left_child,right_child,parent = None,None,None,None

def createkdtree(point_list, depth, minbucketsize, parent = None):
	if len(point_list) <= minbucketsize or depth == 0:
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

def closestpoint(kdtree, p, depth = 0):
	axis = depth % 3
	if isinstance(kdtree, Kdnode):
		""" Parcours descendant """
		if p[axis] > kdtree.location[axis]:
			candidat = closestpoint(kdtree.right_child, p, depth+1)
		else:
			candidat = closestpoint(kdtree.left_child, p, depth+1)
			
		""" Parcours ascendant """
		if candidat == None or norm(p-kdtree.location) < norm(p-candidat):
			candidat = kdtree.location
		if kdtree.parent == None or norm(p-candidat) < abs(p[axis]-kdtree.location[axis]):
			return candidat
		else:
			if kdtree.parent.left_child == kdtree:
				other_candidat = closestpoint(kdtree.right_child, p, depth-1)
			else:
				other_candidat = closestpoint(kdtree.left_child, p, depth-1)
			if other_candidat == None or norm(p-candidat) < norm(p-other_candidat):
				return candidat
			else:
				return other_candidat
	else:
		""" Feuille """
		candidat = None
		for c in kdtree:
			if candidat == None or norm(p-c) < norm(p-candidat):
				candidat = c
		return candidat

def brute_force_closest(point, pointlist):
	""" Find the closest points of 'point' in 'pointlist' using a brute force approach """
	import sys
	pid, d = -1, sys.maxint
	for p in pointlist:
		nd = norm(point-p) 
		if nd < d:
			d = nd
			pid = p
	return pid

def generate_random_point(size = [1,1,1]):
	from random import uniform
	return Vector3(uniform(-size[0],size[0]), uniform(-size[1],size[1]), uniform(-size[2],size[2])) 

def generate_random_pointlist(size = [1,1,1], nb = 100):
	return [generate_random_point(size) for i in xrange(nb)]

def test_kdtree(create_kdtree_func, closestpoint_func, nbtest = 100, nbpoints = 100, depth = 4, minbucketsize = 5):
	points = generate_random_pointlist(nb = nbpoints)
	mkdtree = create_kdtree_func(points, depth, minbucketsize)
	for i in xrange(nbtest):
		testpoint = generate_random_point()
		kpid = closestpoint_func(mkdtree, testpoint)
		bfpid = brute_force_closest(testpoint, points)
		print kpid, bfpid
		if kpid != bfpid: 
			"raise ValueError('Invalid closest point')"
			print 'Invalid closest point\n'

test_kdtree(createkdtree, closestpoint, 10, 100, 4, 5)