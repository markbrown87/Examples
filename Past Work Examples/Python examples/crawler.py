# Created: Mark Brown
# Date: 10/2/2017
# Description: crawls a particular URL for important information to scrap. The information gather
#  is First and Last name as well as email address. This is then stored in a SQLite3 database with
#   unique numbers to be accessed with later on.

import urllib.request
import re
import sys
import sqlite3


# Gather information in string form from website (URL) and return the page in text form
def gather_info(url):
	page = urllib.request.urlopen(url)
	text = page.read()
	text = str(text)
	
	return text

# Scrap the text page for email information then sends to clean() to be formatted correctly
def email_scrape(page):
	# "<a href="mailto:andrews@ohio.edu">andrews@ohio.edu</a>" format for email
	email = re.findall(r'mailto:[a-z0-9]+@ohio.edu', page)
	
	tempList = email

	email = [clean(email[0])]
	count = 1
	
	while (count < len(tempList)):
		email.append(clean(tempList[count]))
		count = count + 1	

	return email

# Scrap the text page for name information then sends to clean() to be formatted correctly
def name_scrape(page):
	# "Becky\xc2\xa0Andrews" format for name
	fullName = re.findall(r'[A-Za-z]+\\xc2\\xa0[A-Za-z]+', page)
	

	tempList = fullName

	fullName = [clean(fullName[0])]
	
	count = 1

	while (count < len(tempList)):
		fullName.append(clean(tempList[count]))
		count = count + 1

	return fullName

# Cleans the scrapped information as to be inserted into database correctly
def clean(line):

	if re.search ('mailto:', line):
		line = re.sub('mailto:', '' , line)

	if re.search (r'\\xc2\\xa0', line):
		line = re.sub(r'\\xc2\\xa0', ' ' , line)

	return line

# Temp stage to convert the important information into string values to be inserted
def inputARecord(id, first, last, email):
	id = id
	first = first
	last = last
	email = email
	return (id, first, last, email)

# Main function that calls the list of functions
def main( ):
	
	if len(sys.argv) != 2:
		print("Incorrect amount of arguments used")
		exit(1)

	url = 'https://www.ohio.edu/engineering/about/people'

	namedb = sys.argv[1]

	# Tries to create a database named 'name' (from input) and if it fails
	# then it will print an error message
	try:
		con = sqlite3.connect(namedb)
	except sqlite3.Error:
		print ("Error opening database: " + namedb)
		exit(1)

	cur = con.cursor()

	# Creates a database table
	#if not (SELECT name FROM sqlite_master WHERE type='table' AND name='information'):
	
	cur.execute("""create table information (id int primary key, first text, last text, email text)""")

	page = gather_info(url)
	email_info = email_scrape(page)
	name_info = name_scrape(page)
	
	# imports the information into a database
	i = 0
	while (i < len(email_info)):
		record = inputARecord(i, name_info[i].split()[0], name_info[i].split()[1], email_info[i])
		sqlStatement = "insert into information values" + str(record)
		cur.execute(sqlStatement)
		i = i + 1
	
	# asks the user if they want the information printed to the screen
	answer = input("Would you like to print the table to the screen? (y/n) ")
	if answer == 'y' or answer == 'Y' or answer == 'YES' or answer == 'Yes' or answer == 'yes':
		cur.execute("select * from information")
		informations = cur.fetchall()
		for record in informations:
			print(record)

	con.commit()
	con.close()


# Calls main()
if __name__ == '__main__':
	main()