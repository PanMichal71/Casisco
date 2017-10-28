from os import listdir
from os.path import isfile, join
import sys
import re
class AddVirtualToRequest:
	def __init__(self):
		self.protoFiles = {}
		self.grpcFiles = {}
		self.rpcs = {}
		self.protoFilesLocation = sys.argv[1]
		self.grpcFilesLocation = sys.argv[2]

	def run(self):
		self.findProtoFiles()
		self.findRpcsInProtoFiles()
		self.findGrpcFiles()
		self.addVirtualInGeneratedGrpcFiles()

	def findProtoFiles(self):
		self.findFiles(self.protoFiles, self.protoFilesLocation, ".proto")

	def findGrpcFiles(self):
		self.findFiles(self.grpcFiles, self.grpcFilesLocation, ".grpc.pb.h")

	def findFiles(self, resultContainer, path, extension):
		print( "Searching for {} files in {}".format(extension, path))
		for file in listdir(path):
			if file.endswith(extension):
				fullFileName = join(path,file)
				resultContainer[file.replace(extension, "")] = fullFileName
				print("Found: {}".format(fullFileName))

	def readFileToList(self, fileName):
		with open(fileName, 'r') as file:
			return file.readlines()

	def saveListToFile(self, fileName, data):
		with open(fileName, 'w') as file:
			for line in data: 
				file.write(str(line))
				# print line

	def addToMap(self, key, value):
		if(self.rpcs.has_key(key)):
			self.rpcs[key].extend(value)
		else:
			self.rpcs[key] = value

	def findRpcsInProtoFiles(self):
		for protoFile, path in self.protoFiles.iteritems():
			print ("Searching for rpc names in {}".format(path))
			data = self.readFileToList(path)
			for line in data:
				if "rpc" in line:
					request = re.findall(r'rpc (.*?)\(', line)
					self.addToMap(protoFile, request)
					print ("\tfound rpc: {} in {}".format(request, protoFile))

	def getGrpcFileName(self, fileName):
		return fileName + ".grpc.pb.h"

	def addVirtualInGeneratedGrpcFiles(self):
		print self.grpcFiles
		for grpcFile, grpcPath in self.grpcFiles.iteritems():
			print("Searching for requests in {}".format(grpcPath))
			if not self.rpcs.has_key(grpcFile): continue

			data = self.readFileToList(grpcPath)
			requests = self.rpcs[grpcFile]
			shouldSave = 0
			for request in requests:
				for idx, line in enumerate(data):
					if line is None: continue
					fullReq = "Request"+request
					if not fullReq in line: continue

					if "virtual" in line: continue
					print("Adding virtual keyword for {} in {}".format(fullReq, self.getGrpcFileName(grpcFile)))
					shouldSave = 1
					data[idx] = self.addVirtual(line)

			if shouldSave: 
				print ("Saving {}".format(grpcPath))
				self.saveListToFile(grpcPath, data)
							
	def addVirtual(self, line):
		line = line.strip()
		return "    virtual " + line + "\n"

if __name__ == '__main__':
    AddVirtualToRequest().run()
