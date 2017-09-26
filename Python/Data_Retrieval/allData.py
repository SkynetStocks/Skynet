import urllib2

# global variables that store html for all URls used more than once
stockData = ''
companyData = ''
tinoData = '' 

#function that assigns the above three variables to the most up to date html
def updateUrl(s):
	#assigning stockData
	try:
		#the url being used
		string = 'http://www.marketwatch.com/investing/stock/' + s
		# opening the url
		source = urllib2.urlopen(string)
		#assigning source to the global variable stock data
		global stockData
		stockData = source.readlines()
	
		#same as above but for companydata
		string = 'http://www.marketwatch.com/investing/stock/'+s+'/profile'
		source = urllib2.urlopen(string)
		global companyData
		companyData =  source.readlines()

		#same as above but for tinoData
		string = 'https://weather.com/weather/today/l/37.32,-122.03?temp=f&par=google'
		source = urllib2.urlopen(string)
		global tinoData
		tinoData =  source.readlines()
	except:
		return -1

# stock data: value, volume, NASDAQ, dow jones, s&p
def anyStock(s):
	html =  stockData
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
			s = i[start:place+3].replace(',','')
			return float(s)
			break

def anyVolume(s):
	html =stockData
	for i in range(0,len(html)):
		if (html[i].find('Average Volume')) != (-1):
			place = 0
			cont = True
			while cont:
				place += 1
				try:
					int(html[i+1][place])
					cont = False
				except:
					cont = True
			return float(html[i+1][place:place+5])
			break
			
	# cant use this because value will be on i + 1 if 'Average Volume' is found on i
def nasdaq():
	try:
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
					return float(i[first:place+3])
					break
	except:
		return -1


def dowjones():
	try:
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
				return float(nstring)
				break
	except:
		return -1

def sp():
	try:
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
					return float(i[first:place+3])
					break
	except:
		return -1


#company data: revenue, employees, and net income
def anyRev(s):
	html =  companyData
	for i in range(0,len(html)):
		place = html[i].find('>Revenue<')
		if place !=-1:
			place = html[i+1].find('">')
			end = html[i+1].find('</')
			str1 = html[i+1]
			return float(str1[place+3:end-1])
def anyEmp(s):
	html =  companyData
	for i in range(0,len(html)):
		place = html[i].find('>Employees<')
		if place !=-1:
			end = html[i+2].find('</')
			str1 = html[i+2]
			return float(str1[8:end].replace(',',''))
			#fix this, remove punctuation and turn to double

def anyInc(s):
	html =  companyData
	for i in range(0,len(html)):
		place = html[i].find('>Net Income<')
		if place !=-1:
			place = html[i+1].find('">')
			end = html[i+1].find('</')
			str1 = html[i+1]
			return float(str1[place+3:end-1])


# cupertino weather data: temp, humidity, visibility, wind speed
def cupertinoTemp():
	html =  tinoData
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


def tinoHumid():
	html =  tinoData
	for i in html:
		correctLine = i.find('window.__data')
		if correctLine !=-1:
			place = i.find('"humidity":')
			cont = True
			start = place +11
			place = start
			while cont:
				try:
					int(i[place])
					place+=1
				except:
					cont = False
			s = i[start:place]
			return float(s)

def tinoVis():
	html =  tinoData
	for i in html:
		correctLine = i.find('window.__data')
		if correctLine !=-1:
			place = i.find('"visibility":')
			cont = True
			start = place +13
			place = start
			while cont:
				try:
					int(i[place])
					place+=1
				except:
					cont = False
			s = i[start:place]
			return float(s)


def tinoWind():
	html =  tinoData
	for i in html:
		correctLine = i.find('window.__data')
		place = i.find('"windSpeed"')
		if place != -1:
			cont = True
			start = place+12
			place = start
			while cont:
				try:
					int(i[place])
					place+=1
				except:
					cont = False
			return float(i[start:place])



#new york weather: temp
def NYTemp():
	try:
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
				break
	except:
		return -1


def displayAll(s):
	print 'the value of ' + s + ' is: ' + str(anyStock(s))
	print 'the volume of ' + s + ' traded is: ' + str(anyVolume(s))
	print 'the value of the NASDAQ is: ' + str(nasdaq())
	print 'the value of the s&p is: ' + str(sp())
	print 'the value of the dowJones is: ' + str(dowjones())
	print 'the net income of ' + s + ' is: ' + str(anyInc(s))
	print 'the number of people ' + s + ' employs is: ' + str(anyEmp(s))
	print 'the revenue of ' + s + ' is: ' + str(anyRev(s))
	print 'the temperature in Cupertino is: ' + str(cupertinoTemp())
	print 'the humidity in Cupertino is: ' + str(tinoHumid())
	print 'the visibility in Cupertino is: ' + str(tinoVis())
	print 'the wind speed in Cupertino is: ' + str(tinoWind())
	print 'the temperature in New York City is: ' + str(NYTemp())










