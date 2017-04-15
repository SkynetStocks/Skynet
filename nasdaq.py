import urllib2
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
				
