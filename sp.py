import urllib2
source = urllib2.urlopen('http://data.cnbc.com/quotes/.SPX')
html =  source.readlines()
for i in html:
	place = i.find('"last"')
	if place !=-1:
		# if "NASDAQ" is in line
		place+=1
		while place<len(i):
			try:
				int(i[place])
				break
			except:
				place+=1
		if place == len(i):
			continue
		first = place
		while place<len(i) and i[place] != '.':
			place+=1
		if place != len(i):
			print float(i[first:place+3])
			break
