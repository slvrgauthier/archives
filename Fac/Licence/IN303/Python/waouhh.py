#!/usr/bin/python
import sys
import re
if len(sys.argv)<2 :
	print "Pas assez d'arguments !" 
elif re.search("a",sys.argv[1]) or re.search("p",sys.argv[1]) :
	if open("/auto_home/sgauthier/.bashrc","r") :
		f = open("/auto_home/sgauthier/.bashrc","r")
		fichier = f.readlines()
		if re.search("a",sys.argv[1]) :
			for line in fichier :
				if re.search("^alias",line) :
					print line
		if re.search("p",sys.argv[1]) :
			for line in fichier :
				if re.search("PATH=",line) :
					print line
		f.close()
	else :
		print "Erreur d'ouverture"
else :
	print "pas d'option valide"