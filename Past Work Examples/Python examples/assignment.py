# Created by: Mark Brown
# Email: mb899115@ohio.edu
# Date: 1/2/2017 -> Last rev. 8/2/2017
# Description: This file is designed to convert a simple C++ program into Python3 ready code

# used for regular expression characters
import re
# used for checking the command line arguments
import sys


# This is called to clean all unnecessary characters in every line such as ';''s but also calls other funtions
# to correct the other differences between C++ and Python
def clean_scum(line):

	# removes all the characters that python doesn't use
	line = re.sub(';', '', line)
	line = re.sub('\s*{\n$', '', line)
	line = re.sub('\s*}$', '', line)
	line = re.sub('({|})', '', line)
	line = re.sub('//', '# ', line)
	line = re.sub('\|\|', 'or', line)
	line = re.sub('&&', 'and', line)
	line = re.sub('!([^=\n])', 'not \\1', line)
	line = re.sub('false', 'False', line)
	line = re.sub('true', 'True', line)
	line = re.sub('const ', ' ', line)
	line = re.sub(' const$', '', line)
	line = re.sub('if\s*\((.*)\)$', 'if \\1:', line)
	line = re.sub('^[\w:&<>\*]+\s+([\w:]+)\(([^\)]*\))$', 'def \\1( \\2:', line)
	line = re.sub('else\s+if', 'elif', line)
	line = re.sub('else\s*$', 'else:\n', line)
	
	# checks for while loops then places a ':' character at the end of that statement
	if re.search ('while', line):
		line = re.sub('\n', ':\n', line)

	# tracks for all letters and everything between to numbers and removes the leading and trailing 
	# variable names
	if re.search('[A-Za-z]+ . \d+', line):
		transfer = re.search('[A-Za-z]+ . \d+', line)
		line = transfer.group() + '\n'

	# remove the unnecessary commands/functions not used by Python
	if re.search("#\s*include", line):
		line = ''
	if re.search("using ", line):
		line = ''

	# check if pattern and then remove or replace if necessary
	if re.search("int|float|double|string", line):
		line = ''

	# corrects the cout statment to a print statement
	if re.search("cout", line):
		line = re.sub('cout', 'print(', line)
		line = re.sub('<<', '', line)
		line = re.sub('endl', '\n', line)
		line = re.sub('\n$', ')\n', line)

	# corrects the cin statement to input statement
	if re.search("cin", line):
		line = re.sub('\s*>>\s*', '', line)
		line = re.sub('>>', '', line)
		line = re.sub('cin', '', line)
		line = re.sub('([A-Za-z\d]+)', '\\1 = input( )\n', line)

	# removes the return in main
	if re.search("return\s*(EXIT_SUCCESS)|(\d+)", line):
		line = ''

	return line

def main():
	# checks the argument amount and sends an error message if in correct amount
	if len(sys.argv) > 3 or len(sys.argv) == 1:
		print ("Incorrect amount of command line arguments")
		print ("python3 assignment.py NAMEOFCPP.cc NAMEOFPYTHON.py")
		print ("OR python3 assignment.py NAMEOFCPP.cc and look for CpptPython.py")
	
	# checks the argument amount is equal to 2 and then enters the main portion of the program
	if len(sys.argv) == 2:
		inf = sys.argv[1]
		# opens the file name under argv[1] and standard name and passes the lines in one
		# line at a time to be checked then printed the outfile
		with open(inf, 'r') as infile, open("Cpp2Python.py", 'w+') as outfile:
			lines = infile.readlines()
			for line in lines:
				outfile.write(clean_scum(line))
			outfile.write("if __name__ == '__main__': \n\t main()")

	# checks the argument amount is equal to 3 and then enters the main portion of the program
	if len(sys.argv) == 3:
		inf = sys.argv[1]
		outf = sys.argv[2]
		# opens the file name under argv[1] and argv[2] and passes the lines in one
		# line at a time to be checked then printed the outfile
		with open(inf, 'r') as infile, open(outf, 'w+') as outfile:
			lines = infile.readlines()
			for line in lines:
				outfile.write(clean_scum(line))
			outfile.write("if __name__ == '__main__': \n\t main()")

# run def main()
if __name__ == '__main__':
	main()