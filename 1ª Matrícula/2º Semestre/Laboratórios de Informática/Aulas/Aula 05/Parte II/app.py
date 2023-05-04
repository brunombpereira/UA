# encoding=utf-8
#
# Example of a cherrypy application that serves static content as well as dynamic content.
#
# Adrego da Rocha - Fevereiro de 2023
#
# To run: python3 app.py

import os.path
import cherrypy
import time
from math import radians, cos, sin, asin, sqrt
import json
import hashlib

# The absolute path to this file's base directory
baseDir = os.path.abspath(os.path.dirname(__file__))

# Dictionary with this application's static directories configuration
config = {
			"/":		{	"tools.staticdir.root": baseDir },

			"/html":	{	"tools.staticdir.on": True, "tools.staticdir.dir": "html" },

			"/js":		{	"tools.staticdir.on": True, "tools.staticdir.dir": "js" },

			"/css":		{	"tools.staticdir.on": True, "tools.staticdir.dir": "css" },

			"/images":	{	"tools.staticdir.on": True, "tools.staticdir.dir": "images" },

			"/uploads":	{	"tools.staticdir.on": True, "tools.staticdir.dir": "uploads" },
}


def distance(lat, lon):
	lat1 = 38.752667
	lon1 = -9.184711
	lon, lat, lon1, lat1 = map(radians, [lon, lat, lon1, lat1]) # Degrees -> Radians
	dlon = lon - lon1
	dlat = lat - lat1
	a = sin(dlat/2)**2 + cos(lat1) * cos(lat) * sin(dlon/2)**2 # Haversine formula
	c = 2 * asin(sqrt(a))
	km = 6367 * c # Earth Ray = 6367 km

	cherrypy.response.headers["Content-Type"] = "application/json"
	return json.dumps({"distance": km}).encode("utf-8")


class Root(object):
	@cherrypy.expose
	def index(self):
		return open("html/index.html")

	# Clock
	@cherrypy.expose
	def clock(self):
		cherrypy.response.headers["Content-Type"] = "application/json"

		return time.strftime('{"date": "%d-%m-%Y", "time": "%H:%M:%S"}').encode("utf-8")

	# Distance
	@cherrypy.expose
	def distance(self, lat, lon):
		return distance(float(lat), float(lon))

	# UpLoad
	@cherrypy.expose
	def upload(self, myFile):
		# get the file extension
		ext = os.path.splitext(myFile.filename)[1]

		# create a sha256 hash of the file content
		hasher = hashlib.sha256()
		while True:
			data = myFile.file.read(8192)
			if not data:
				break
			hasher.update(data)
		hash_value = hasher.hexdigest()

		# save the file with the hash value as the filename
		filename = os.path.join("uploads", hash_value + ext)
		with open(filename, "wb") as f:
			while True:
				data = myFile.file.read(8192)
				if not data:
					break
				f.write(data)

		return "Upload successful!"


cherrypy.quickstart(Root(), "/", config)
