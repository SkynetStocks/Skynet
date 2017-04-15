
import urllib2
source = urllib2.urlopen('http://www.marketwatch.com/investing/index/djia')
html =  source.readlines()
for i in html:
	place = i.find('"price"')
	if place !=-1:
		cont = True
		while cont:
			place += 1
			try:
				int(i[place])
				cont = False
			except:
				cont = True
		start = place
		while i[place] != '.':
			place += 1
		string = i[start:place+3]
		nstring = string.replace(',','')
		print float(nstring)
		break
# still need to remove ',' and convert to float
