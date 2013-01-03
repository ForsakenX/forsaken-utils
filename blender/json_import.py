#!BPY

"""
Name: 'pxwgl loader (.pxwgl)...'
Blender: 242
Group: 'Import'
Tooltip: 'Custom Import (.pxwgl)'
"""

__author__ = "Daniel Aquino aka Methods"
__url__ = ("http://fly.thruhere.net")
__version__ = "0.1"
__bpydoc__ = """\
Imports json files used in pxwgl.
Usage: Execute this script from the "File->Import" menu
"""

# ***** BEGIN GPL LICENSE BLOCK *****
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
# ***** END GPL LICENCE BLOCK *****

import sys
import Blender
import re
from Blender import Mathutils
from Blender.Mathutils import *

#
# data = {
#   verts = [ # list of uniq verts
#     [0,0,0] # vert
#   ], 
#   faces = [
#     {
#       indices = [0,0,0], # index into verts array
#       tcords  = [[0,0],[0,0],[0,0]], # tv/tu
#       colors  = [[0,0,0,0],[0,0,0,0],[0,0,0,0]]
#       texture = "path"
#     }
#   ]
# }
#

def create_mesh(data):
	mesh = Blender.Mesh.New()
	mesh.vertexColors = 1 # enable colors
	mesh.name = data['name']
	mesh.verts.extend(data['verts'])
	mesh.faces.extend([face['indices'] for face in data['faces']])
	for f in range(len(mesh.faces)):
		face = mesh.faces[f]
		face.uv = data['faces'][f]['tcords']
		for v in range(3):
			face.col[v].r = data['faces'][f]['colors'][v][0]
			face.col[v].g = data['faces'][f]['colors'][v][1]
			face.col[v].b = data['faces'][f]['colors'][v][2]
			face.col[v].a = data['faces'][f]['colors'][v][2]
		texture = data['faces'][f]['texture']
		if texture:
			try: face.image = Blender.Image.Load(texture)
			except: print "failed to load texture: " + texture
	return mesh

def parse_pxwgl(data):
	import json
	data    = json.load(data)
	faces   = []
	verts   = []
	indexes = {}
	index   = 0
	for i in range(len(data['vertices'])/9):
		faces.append({})
		face = faces[i]
		face['indices'] = [0,0,0]
		face['colors']  = [[0,0,0,0],[0,0,0,0],[0,0,0,0]]
		face['tcords']  = [Vector(0,0),Vector(0,0),Vector(0,0)]
		face['texture'] = None
		v = i * 3
		for start, count, texture in data['indices']:
			if v >= start and v < (start + count):
				face['texture'] = texture
				break
		row = i * 9
		for group in range(3):
			col = row + (group * 3)
			vert = (
				data['vertices'][col],
				data['vertices'][col+1],
				data['vertices'][col+2]
			)
			if vert in indexes:
				current = indexes[vert]
			else:
				current = indexes[vert] = index
				index += 1
				verts.append(vert)
			face['indices'][group] = current
			crow = i * 12
			ccol = crow + (group * 4)
			face['colors'][group][0] = int(data['colors'][ccol+0]*255)
			face['colors'][group][1] = int(data['colors'][ccol+1]*255)
			face['colors'][group][2] = int(data['colors'][ccol+2]*255)
			face['colors'][group][3] = int(data['colors'][ccol+3]*255)
			trow = i * 6
			tcol = trow + (group * 2)
			face['tcords'][group] = Vector(
				 data['tcords'][tcol],  # tu
				-data['tcords'][tcol+1] # tv
			)
	return { 'verts':verts, 'faces':faces }

def parse(filename):
	name,ext = Blender.sys.splitext(
		Blender.sys.basename( filename ))
	if ext == ".pxwgl":
		data = parse_pxwgl(open(filename,'rb'))
	elif re.match(r'^.mx[av]?',ext):
		print "forsaken file format not yet supported"
		return {}
	else:
		print "unsupported file extension " + ext
		return {}
	data['path'],data['name'],data['ext'] = filename, name, ext
	return data

def handle(filename):
	t = Blender.sys.time()
	scene = Blender.Scene.GetCurrent()
	for obj in scene.objects:
		obj.sel = 0
	obj = scene.objects.new(create_mesh(parse(filename)))
	size = 0.01
	obj.setSize(size,size,-size)
	scene.update()
	Blender.Redraw()
	print 'imported "%s" in %.4f seconds' % (
		Blender.sys.basename(filename),
		Blender.sys.time()-t)

def main():
	Blender.Window.FileSelector(
		handle, 'PXWGL Import', Blender.sys.makename(ext='.pxwgl'))

if __name__=='__main__':
	main()
