#!/usr/bin/python
import sys
for element in sys.argv :
	print element
if len(sys.argv)<2 :
	print "Pas assez d'arguments !" 
else :
	print "Bonjour", sys.argv[1], "!"
