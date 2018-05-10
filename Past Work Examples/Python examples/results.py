
# Mark Brown




# below are the declared variables
# remainders

# calculation variables below 


# start of program 
def main( ):
	# ask for inputs
	print(  "Please enter the amount of time (in seconds only): ")
	  secs = input( )



	# caculate inputs 
	# calculation for finding days 
	days = (secs / CALDAY)
	remx = (secs % CALDAY)

	# calculation for finding hours 
	hours = (remx / CALHOUR)
	remy = (remx % CALHOUR)

	# calculation for finding minutes 
	mins = (remy / CALMIN)
	remx = (remy % CALMIN)

	# remainder is equal to seconds 
	secs = remx

	# output response 
	print(  days  "d:"  hours  "h:"  mins  "m:"  secs  "s"  )
)

	# testing function
	while (fred != george):
		print(  "This is just a test")


	return False

if __name__ == '__main__': 
	 main()