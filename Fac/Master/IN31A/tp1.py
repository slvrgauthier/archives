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
		

