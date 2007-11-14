#!/usr/bin/python -t
#
# vim:set ts=4 sw=4:

"Forsaken pickup file (.PIC) editor"

from pprint import pprint
import struct

name_table = {
	 0: 'Trojax'
	,1: 'Pyrolite'
	,2: 'Transpulse'
	,3: 'SussGun'
	,4: 'Laser'
	,5: 'Mug'
	,6: 'Mugs'
	,7: 'Heatseaker'
	,8: 'HeatseakerPickup'
	,9: 'Thief'
	,10: 'Scatter'
	,11: 'Gravgon'
	,12: 'Launcher'
	,13: 'TitanStar'
	,14: 'PurgePickup'
	,15: 'PinePickup'
	,16: 'QuantumPickup'
	,17: 'SpiderPod'
	,18: 'Parasite'
	,19: 'Flare'
	,20: 'GeneralAmmo'
	,21: 'PyroliteAmmo'
	,22: 'SussGunAmmo'
	,23: 'PowerPod'
	,24: 'Shield'
	,25: 'Inv'
	,26: 'ExtraLife'
	,27: 'Computer'
	,28: 'Smoke'
	,29: 'Nitro'
	,30: 'Goggles'
	,31: 'Gold'
	,32: 'Mantle'
	,33: 'Crystal'
	,34: 'Orb'
	,35: 'GoldenPowerPod'
	,36: 'DNA'
	,37: 'SkeletonKey'
	,38: 'Bomb'
	,39: 'GoldFigure'
	,40: 'Flag'
	,41: 'Bounty'
	,42: 'Flag1'
	,43: 'Flag2'
	,44: 'Flag3'
	,45: 'Flag4'
}

class BinFile:
	"File which allows for easier reading from binary files."

	def __init__(self, source, mode='r'):
		if type(source) == str:
			self.source = open(source, mode)
		elif hasattr(source, 'read'):
			self.source = source
		else:
			raise ValueError('Source must be filename or something that can read()')
		self.close = self.source.close
		self.read = self.source.read
		self.seek = self.source.seek
		self.tell = self.source.tell
		self.write = self.source.write

	def binread(self, fmt):
		"Read little-endian binary data specified by fmt."
		fmt = '<' + fmt
		size = struct.calcsize(fmt)
		str = self.read(size)
		if len(str) < size:
			raise EOFError('Unexpected end of file (%d bytes read instead of %d)' % (len(str), size))
		t = struct.unpack(fmt, str)
		if len(t) == 1:
			return t[0]
		else:
			return t

	def read(self, n):
		return self.source.read(n)

	def seek(self, offset, whence=None):
		if whence is None:
			return self.source.seek(offset)
		else:
			return self.source.seek(offset, whence)

	def tell(self):
		return self.source.tell()

	def write(self, str):
		return self.source.write(str)

class PickupList:
	def __init__(self, source):
		self.read_from(source)

	def pprint(self):
		print 'Version: %d' % self.version
		print 'Number of pickups: %d' % self.num_pickups
		print 'Pickups:'
		pprint(self.pickups)

	def read_from(self, source):
		if type(source) == str:
			source = BinFile(source, 'r')
		elif not hasattr(source, 'binread'):
			raise ValueError('Source must be filename or something that can binread()')
		magic = source.binread('4s')
		if magic != 'PRJX':
			raise InvalidPICFileError('Invalid magic number ' + magic)
		self.version, self.num_pickups = source.binread('Ih')
		self.version = int(self.version)
		self.pickups = []
		for i in xrange(self.num_pickups):
			pickup = {}
			pickup['gen_type'], pickup['regen_type'], pickup['gen_delay'], \
				pickup['life_span'] = source.binread('HHff')
			pickup['pos'] = {}
			pickup['pos']['x'], pickup['pos']['y'], pickup['pos']['z'] \
				= source.binread('fff')
			pickup['group'], pickup['type'], pickup['trigger_mod'] \
				= source.binread('HHH')
			self.pickups.append(pickup)
		source.close()

	def write_to(self, target):
		if type(target) == str:
			target = BinFile(target, 'w')
		elif not hasattr(target, 'write'):
			raise ValueError('Target must be a filename or something we can write() to')
		target.write('PRJX')
		target.write(struct.pack('Ih', self.version, self.num_pickups))
		assert self.num_pickups == len(self.pickups)
		for pickup in self.pickups:
			target.write(struct.pack('HHff', pickup['gen_type'], \
				pickup['regen_type'], pickup['gen_delay'], \
				pickup['life_span']))
			target.write(struct.pack('fff', pickup['pos']['x'], \
				pickup['pos']['y'], pickup['pos']['z']))
			target.write(struct.pack('HHH', pickup['group'], pickup['type'], \
				pickup['trigger_mod']))
		target.close()

class InvalidPICFileError(Exception):
	def __init__(self, msg):
		self.msg = msg

	def __str__(self):
		return self.msg

if __name__ == '__main__':
	import sys
	import yaml

	if len(sys.argv) < 2:
		print 'Convert Forsaken PIC files to and from YAML'
		print 'Usage: %s <-pictoyaml|-yamltopic> [source] [> destination]' % sys.argv[0]
		sys.exit(0)
	elif len(sys.argv) < 3:
		source = BinFile(sys.stdin)
	else:
		source = BinFile(sys.argv[2])
	if sys.argv[1] == '-pictoyaml':
		pl = PickupList(source)
		sys.stdout.write(yaml.dump(pl))
	elif sys.argv[1] == '-yamltopic':
		pl = yaml.load(source)
		pl.write_to(sys.stdout)
	else:
		print 'first argument must be -pictoyaml or -yamltopic'
		sys.exit(1)
