
import copy
from collections import deque

class PersistentQueue:
	def __init__(self):
		self.last_version = 0
		self.versions = {0: deque()}

	def push(self, version: int, value):
		self.last_version += 1
		self.versions[self.last_version] = copy.deepcopy(self.versions[version])
		self.versions[self.last_version].append(value)

		return self.last_version

	def pop(self, version: int):
		self.last_version += 1
		self.versions[self.last_version] = copy.deepcopy(self.versions[version])
		return self.versions[self.last_version].popleft(), self.last_version


def main():
	q = PersistentQueue()

	q.push(0, 15)
	q.push(1, 10)
	q.push(0, 11)
	q.push(1, 25)

	print(q.pop(1))
	print(q.pop(4))
	print(q.pop(6))

if __name__ == '__main__':
	main()

