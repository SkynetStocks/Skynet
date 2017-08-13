import urllib2
def anyStock(s):
	string = 'http://www.marketwatch.com/investing/stock/' + s
	source = urllib2.urlopen(string)
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
			return float(i[start:place+3])
			break

def nasdaq():
	source = urllib2.urlopen('http://www.nasdaq.com/')
	html =  source.readlines()
	# html has been read in
	counter = 0
	for i in html:
		# loop through the html line by line
		place = i.find('"NASDAQ"')
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


def dowjones():
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

def sp():
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



