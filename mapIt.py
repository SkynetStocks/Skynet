"""read in data
put in arrays for each piece
find largest and smallest
map each piece to new arrays 
"""


def mapIt(fname):
	"""read in data"""
	with open(fname) as f:
	    content = f.readlines()
	content.pop(0)
	outer = []
	for i in range(0,len(content)):
		cur = content[i]
		temp = []
		countS = 0
		countF = 1
		while(countF<(len(cur)-2)):
			while(cur[countF] != ','):
				countF +=1
			temp.append(cur[countS:countF])
			countS = countF +1
			countF = countF +1
		outer.append(temp)
	"""find range
	range is correct
	"""
	mapHi = []
	mapLow = []
	for i in outer:
		hi = float(i[0])
		low = float(i[0])
		for j in i:
			if float(j)<low:
				low = float(j)
			if float(j)>hi:
				hi = float(j)
		mapHi.append(hi)
		mapLow.append(low)
	"""map values to new array"""
	mapped = []
	for i in range(0,len(outer)):
		temp = []
		for j in range(0,len(outer[i])):
			num = float(outer[i][j])
			val = translate(num, mapLow[i],mapHi[i],0, 1)
			temp.append(val)
		mapped.append(temp)
	return mapped
"""mapping function"""
def translate(value, givenMin, givenMax, finalMin, finalMax):
	if givenMax == givenMin:
		return 0
	return (value-givenMin)/(givenMax-givenMin)




