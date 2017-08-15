import urllib2
def cupertinoTemp():
	string = 'https://weather.com/weather/today/l/37.32,-122.03?temp=f&par=google'
	source = urllib2.urlopen(string)
	html =  source.readlines()
	for i in html:
		correctLine = i.find('window.__data')
		if correctLine !=-1:
			place = i.find('"temperature":')
			cont = True
			start = place +14
			place = start
			while cont:
				try:
					int(i[place])
					place+=1
				except:
					cont = False
			s = i[start:place]
			return float(s)
def NYTemp():		
	string = 'https://weather.com/weather/today/l/USNY0996:1:US'
	source = urllib2.urlopen(string)
	html =  source.readlines()
	for i in html:
		correctLine = i.find('window.__data')
		if correctLine !=-1:
			place = i.find('"temperature":')
			cont = True
			start = place +14
			place = start
			while cont:
				try:
					int(i[place])
					place+=1
				except:
					cont = False
			s = i[start:place]
			return float(s)
