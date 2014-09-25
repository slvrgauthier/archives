#!/usr/bin/python
# -*- coding: utf-8 -*-
import os,re
fd=os.popen("last")
connexions={}
for line in fd.readlines() :
	resultat=re.search("^(\w+).{33}(\w+\W+\w+\W+\w+).{17}(\d\d).{1}(\d\d)",line)
	if resultat :
		login=resultat.group(1)
		date=resultat.group(2)
		heure=resultat.group(3)
		minute=resultat.group(4)
		if connexions.has_key(login) :
			if connexions[login].has_key(date) :
				connexions[login][date][0]=connexions[login][date][0]+1
				connexions[login][date][1]=connexions[login][date][1]+int(heure)
				connexions[login][date][2]=connexions[login][date][2]+int(minute)
				if connexions[login][date][2]>59 :
					  connexions[login][date][1]=connexions[login][date][1]+1
					  connexions[login][date][2]=connexions[login][date][2]-60
			else :
				connexions[login][date]={}
				connexions[login][date][0]=1
				connexions[login][date][1]=int(heure)
				connexions[login][date][2]=int(minute)
		else :
			connexions[login]={}
			connexions[login][date]={}
			connexions[login][date][0]=1
			connexions[login][date][1]=int(heure)
			connexions[login][date][2]=int(minute)
for login in connexions.keys() :
	print login,"s'est connecté les :"
	for date in connexions[login].keys() :
		print "\t",date,":",connexions[login][date][0],"fois, temps de connexion total :",connexions[login][date][1],"h",connexions[login][date][2],"min"