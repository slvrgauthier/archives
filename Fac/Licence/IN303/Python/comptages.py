#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, sys
suffixes = {}

def parcours(repertoire) :
	liste = os.listdir(repertoire)
	for fichier in liste :
		if os.path.isdir(repertoire+'/'+fichier) :
			parcours(repertoire+'/'+fichier)
		else :
			extension = os.path.splitext(repertoire+'/'+fichier)[1]
			if not(extension) :
				extension = 'pas de suffixe'
			if suffixes.has_key(extension) :
				suffixes[extension] = suffixes[extension] + 1
			else :
				suffixes[extension] = 1
      
parcours (sys.argv[1])
total = 0
for extension in suffixes.keys() :
	print extension,':',suffixes[extension]
	total = total + suffixes[extension]
print "TOTAL :",total