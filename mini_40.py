

'''

(ver, val)

'''

class Node:
	def __init__(self, version, value, left, right):
		

class PersistentQueue:
	def __init__(self):
		self.queue = []
		self.version_to_index = {0: None}
		self.last_version = 0

	def __check_version(version: int) -> None:
		if version > last_version or version < 0:
			raise ValueError('version should be in [0...last_version]')

	def push(version: int, value: int) -> int:
		self.__check_version(version)

		if self.version_to_index[version] is None:
			if len(self.queue) == 0: # this happens only when version is 0
				assert version == 0

				self.queue.append({1: value})
				self.version_to_index[1] = (0, 0)
				return 1

			self.queue[0][version + 1] = value
			self.version_to_index[version + 1] = (0, 0)
			return version + 1

		end_pos = self.version_to_index[version][1]
		if end_pos + 1 == len(queue):
			queue.append({version: value})
		self.queue[end_pos + 1][version] = value

		self.version_to_index[version]

	def pop(version: int) -> int:
		pass
