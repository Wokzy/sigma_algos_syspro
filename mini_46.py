
class Node:
	def __init__(self, total_patterns: int, parent, from_parent: str):
		self.terminal = ""
		self.invalidation_counter = total_patterns
		self.prefix_go = {}
		self.suffix_go = {}

		self.parent = parent
		self.from_parent = from_parent
		self.sufflink = None
		self.all_patterns = []


def suf(v, root):

	if (v.sufflink is None):
		if v is root or v.parent is root:
			v.sufflink = root
		else:
			v.sufflink = next(suf(v.parent, root), v.from_parent, root)

	return v.sufflink

def next(v, c, root):
	if (c in v.prefix_go):
		return v.prefix_go[c]

	if v is root:
		return root

	if c in v.suffix_go:
		return v.suffix_go[c]

	v.suffix_go[c] = next(suf(v, root), c, root)
	return v.suffix_go[c]


def add_new_pattern(root, pattern: str):
	current_node = root

	for c in pattern:
		if (c not in current_node.prefix_go):
			current_node.prefix_go[c] = Node(root.invalidation_counter, current_node, c)
		current_node = current_node.prefix_go[c]

	assert len(current_node.terminal) == 0

	current_node.terminal = pattern
	root.all_patterns.append(pattern)


def count_sufflink(node, counter, root):

	while node != root:
		if node.terminal:
			counter[node.terminal] += 1

		node = suf(node, root)

def findall(root, string):

	counter = {}
	for s in root.all_patterns:
		counter[s] = 0

	current_node = root
	for c in string:
		current_node = next(current_node, c, root)
		count_sufflink(current_node, counter, root)
		# if current_node.terminal:
		# 	counter[current_node.terminal] += 1


	for key, value in counter.items():
		print(f'{key}: {value}')



def main():
	root = Node(0, None, 0)

	add_new_pattern(root, "aab")
	add_new_pattern(root, "abba")
	add_new_pattern(root, "bbab")
	add_new_pattern(root, "bbbab")

	# check_suff_link(root, "bbbab")

	text = "bbbaabbbbab"
	findall(root, text)
	print('bbab' in text)

if __name__ == '__main__':
	main()

