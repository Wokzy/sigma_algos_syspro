

def format_table(rows:list[str], columns:list[str], data:list[...], name='Benchmark') -> str:

	for i in range(len(rows)):
		data[i].insert(0, rows[i])

	columns.insert(0, name)

	sizes = [len(columns[i]) + 2 for i in range(len(columns))]
	sm = 0
	for i in range(len(columns)):
		for j in range(len(data)):
			data[j][i] = str(data[j][i])
			if len(data[j][i]) + 2 > sizes[i]:
				sizes[i] = len(data[j][i]) + 2

		sm += sizes[i]

	res = '|'

	for i in range(len(columns)):
		res += f' {columns[i]:<{sizes[i] - 1}}|'

	res += '\n|' + '-'*(sm + len(columns) - 1) + '|'
	for i in range(len(data)):
		res += '\n|'
		for j in range(len(data[i])):
			res += f' {data[i][j]:<{sizes[j] - 1}}|'

	return res
