/*
* Mark Brown
* 04/04/2016
* The program is designed to supply "homes" for animals using the list container with pointers.
* The basic idea is to demanstrate polymorphism containers.
*/

#include "homes.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctype.h>


using namespace std;
//basic constructor for homes parent class
homes::homes(){
	price = 1.50;
}
//start of charmander class
//constructor for charmander class to input from file
charmander::charmander(istream& ins){
	char tmp = 'n';
	if(ins.peek() == '\n')
		ins.ignore();
	getline(ins, material);
	ins.get(tmp);
	if(tmp == 'y'){
		bed == true;
		tmp = 'n';}
	else
		bed = false;
	ins.ignore();
	ins.get(tmp);
	if(tmp == 'y'){
		lavaPool == true;
		tmp = 'n';}
	else
		lavaPool = false;
	ins.ignore();
	ins.get(tmp);
	if(tmp == 'y'){
		mailbox == true;
		tmp = 'n';}
	else
		mailbox = false;
	ins.ignore();
	ins >> width;
	ins.ignore();
	ins >> length;
	ins.ignore();
	ins >> base;
	ins.ignore();
	ins.ignore();
	getline(ins,post_region);
	if(ins.peek() == '\n')
		ins.ignore();
	getline(ins, post_code);
	if(ins.peek() == '\n')
		ins.ignore();
}
//basic constructor
charmander::charmander(){
	width = 1;
	length = 1;
	base = 1;
	bed=false;
	lavaPool=false;
	mailbox=false;
	material= "";
	post_code = "";
	post_region = 'N';
}
//input function used to input all variables for the class
void charmander::input(){
	char ans = 'n', tmp = 'n';
	cout <<"You have selected Charmander. Charmander is a Fire-type lizard thus he'll live in a home near a volcano.\n";
	while(ans != 'y'){
	cout << "What dimensions would you like for Charmander's home beginning with Width? (All measurements are in meters): ";
	cin >> width;
	cout << "And now the length?";
	cin >> length;
	cout << "Finally, the base length?";
	cin >> base;
	cout <<"How about the type of material the home is made out of? The program doesn't limit you on the type of material - with great power comes great responibility -- ";
	cin >> material;
	cout <<"Below you will be asked about three different items you would like to have with the home. Please answer with a [y] for yes and a [n] for no.\n"
		<<"Would you like a bed?(y/n)";
	cin >> tmp;
	if(tmp == 'y'){bed == true;tmp = 'n';}
	cout <<"Would you like a lava pool?(y/n)";
	cin >> tmp;
	if(tmp == 'y'){lavaPool == true;tmp = 'n';}
	cout <<"Would you like a mailbox (all Pokemon get the choice of a mailbox)?(y/n)";
	cin >> tmp;
	if(tmp == 'y'){mailbox == true;tmp = 'n';}
	cout <<"Please provide the region Charmander will be living in? (N, NE, E, SE, S, SW, W, NW)";
	cin >> post_region;
	cout<<"Finally, please provide a postal code for the charmander to receive mail?";
	cin >> post_code;
	cout <<"Pokemon specis: ";
	output(cout);
	cout <<"Are these correct?(y/n)";
	cin >> ans;
	}
}
//output function that takes the cout or fout and decided rather to be placed to screen or file
void charmander::output(ostream& outs){
	if(&outs == &cout){
		string bt, lpt, mbt, tmp;
		//changes the true and false into yes or no.
		if(bed == true)
			bt = "Yes";
		else 
			bt = "No";

		if(lavaPool == true)
			lpt = "Yes";
		else 
			lpt = "No";

		if(mailbox == true)
			mbt = "Yes";
		else 
			mbt = "No";
		//used to correct the value post_region string to the correct notation i.e (N becomes Northern)
		if(post_region == "N")
			tmp = "Northern";
		else if (post_region == "NE")
			tmp = "Northeastern";
		else if (post_region == "E")
			tmp = "Eastern";
		else if (post_region == "SE")
			tmp = "Southeastern";
		else if (post_region == "S")
			tmp = "Southern";
		else if (post_region == "SW")
			tmp = "Southwestern";
		else if (post_region == "W")
			tmp = "Western";
		else if (post_region == "NW")
			tmp = "Northwestern";
		else
			tmp = "somewhere?";//basic default
		cout << "Charmander\n"
		<< "Building Material: " << material << endl
		<< "Bed: " << bt << ", " << "Lava Pool: " << lpt << ", " << "Mailbox: " << mbt << endl
		<< "Width: " << width << "m by Length: " << length << "m by Base: " << base << "m"<< endl
		<< "Living in the " << tmp << " hemishpere of the Johto region. Located at postal code: "<< post_code << endl << endl;
	}
	else{
		char bt, lpt, mbt;
		//changes the true and false into yes or no.
		if(bed == true)
			bt = 'y';
		else 
			bt = 'n';

		if(lavaPool == true)
			lpt = 'y';
		else 
			lpt = 'n';

		if(mailbox == true)
			mbt = 'y';
		else 
			mbt = 'n';
		
		outs << "Charmander\n"
		<< material << endl
		<< bt << "," << lpt << "," << mbt << endl
		<< width << "W" << length << "L" << base << "B" << endl
		<< post_region << endl << post_code << endl;
	}
}//end of charmander class
//start of bulbasaur class
//constructor for bulbasaur class to input from file
bulbasaur::bulbasaur(istream& ins){
	if(ins.peek() == '\n')
		ins.ignore();
	getline(ins, favPark);
	if(ins.peek() == '\n')
		ins.ignore();
	getline(ins, colourL);
	ins >> feed_lbs;
	ins.ignore();
	ins.ignore();
	ins.ignore();
	ins.ignore();
	ins >> length;
	ins.ignore();
	ins >> width;
	ins.ignore();
	ins >> id_num;
	ins.ignore();
}
//basic constructor
bulbasaur::bulbasaur(){
	length = 1;
	width = 1;
	id_num = 0;
	favPark = "";
	colourL = "";
	feed_lbs = 0;
}
//input function used to input all variables for the class
void bulbasaur::input(){
	char ans = 'n';
	cout <<"You have selected Bulbasaur.\n" 
		 <<"Bulbasaur is a Grass-type toad thus he'll be provided a cozy prebuilt home with a garden\n"
		 <<"that is mapped out by you. As well as a few other unique items.\n";
	while(ans != 'y'){
	cout << "To Begin, I would like to mention that this Bulbasaur likes to go on walks.\n"
		<<"If you could provide the name of a park you normally visit? It's so we can check if it will be safe for this little Bulbasaur: ";
	if(cin.peek() == '\n')
		cin.ignore();
	getline(cin,favPark);
	cout << "Thank you so much.\nSo it looks like "<< favPark << " is a safe location.\n"
		<<"It's now time to map out the dimensions of his personal garden - provided free of charge.\n"
		<<"What length would you like it to be? (All measurements in meters): ";
	cin >> length;
	cout << "And now the width?";
	cin >> width;
	cout << "Awesome. So you entered " << length << "m by " << width << "m. You will be given the option to change these later if incorrect.\n\n";
	cout <<"I forgot to mention - if you'll be walking this cute Bulbasaur then what colour leash would you like? ";
	cin >> colourL;
	cout <<"A " << colourL <<" leash is a perfect colour for him. Good choice!\n\n"
		<<"If you could provide a numerical set of preferred numbers for his ID tag I can start\n"
		<<"printing that out and attach that to him as soon as it's finished: ";
	cin>>id_num;
	cout<<"As per all local adoption services there will be a bag of food provided for first time Bulbasaur owners. What size of bag would you like? (in lbs): ";
	cin>>feed_lbs;
	cout <<"Awesome! You have completed all the questions required for Bulbasaur. Just to be sure - are all the sections correct below?\n";
	cout <<"Pokemon specis: ";
	output(cout);
	//cout <<"Are these correct?(y/n)";
	cin >> ans;
	}
}
//output function that takes the cout or fout and decided rather to be placed to screen or file
void bulbasaur::output(ostream& outs){
	if(&outs == &cout){
		cout << "Bulbasaur\n"
		<< "Local walking Park: " << favPark << endl
		<< "Provided walking Leash colour: " << colourL << endl
		<< "The ID that will be printed on the tag: " << id_num << endl
		<< "The poundage of feed provided: " << feed_lbs << "lbs\n"
		<< "Dimensions of the garden: Length " << length << "m by width " << width << "m\n\n";
	}
	else{
		outs << "Bulbasaur\n"
		<< favPark << endl
		<< colourL << endl
		<< feed_lbs << "lbs\n"
		<< length << "L" << width << "W" <<  endl
		<< id_num << endl;
	}
}//end of squirtle class
//start of squirtle class
//constructor for squirtle class to input from file
squirtle::squirtle(istream& ins){
	char tmp;
	if(ins.peek() == '\n')
		ins.ignore();
	getline(ins, phone_num);
	ins.get(tmp);
	if(tmp == 'y')
		glasses = true;
	else
		glasses = false;
	ins.ignore();
	ins.get(tmp);
	if(tmp == 'y')
		crew = true;
	else 
		crew = false;
	ins.ignore();
	ins >> card_limit;
	ins.ignore();
	ins >> pin;
	ins.ignore();
}
//basic constructor
squirtle::squirtle(){
	phone_num = "";
	card_limit = 0;
	pin = 0;
	glasses = false;
	crew = false;
}
//input function used to input all variables for the class
void squirtle::input(){
	char ans = 'n';
	cout <<"You have selected Squirtle. Squirtle is a Water-type turtle but not just any turtle. This Squirtle is the rad-ist turtle you've ever had the pleasure to meet.\n";
	while(ans != 'y'){
	cout << "This Squirtle is a little trouble maker. He likes to run with with crew of other Squirtles and cause destruction around the town of Athens.\n"
		 << "Speaking of trouble - The Squirtle is here. Oh he wants me to refer to him as Tom. Tom has a few questions for you.\n"
		 << "Tom would like me to tell you... oh this is awkward. He has stated that he has knicked your credit card. He wants to know how much cash you have on the card: ";
	cin >>card_limit;
	cout << "He seems impressed with the amount you have on your card. Huh - smart little guy - he wants to know your pin for the card now: ";
	cin >> pin;
	cout << "Oh good - now he's gone away with his pals. Most likely to take all that money of yours. No worries, I slipped him a cellphone that you can call him at.\n"
		 << "Oh shoot. I have to activate it - they want to know what cell number to give the phone. Would you mind helping out? [example input '(555)555-5555']: ";
	if(cin.peek()=='\n')
		cin.ignore();
	getline(cin,phone_num);
	cout << "Seeing as he now has mostly emptied your account and you DID pick Squirtle so\n"
	<<"Congratulations on the adoption. Would you like some glasses for your 'cool' Squirtle?(y/n): ";
	cin >> ans;
	if(ans == 'y')
		glasses = true;
	else
		glasses = false;
	cout << "What about a photo of the cute little Squirtle to hang up in the shed since he's probably long gone? (y/n): ";
	cin >> ans;
	if(ans == 'y')
		crew = true;
	else
		crew = false;
	ans = 'n';
	cout << "What a wonderful day to adopt, eh? Sorry about your crap luck though. Anyway, is this what you ordered?\n";
	cout <<"Pokemon specis: ";
	output(cout);
	cout <<"Are these correct?(y/n)";
	cin >> ans;
	}
}
//output function that takes the cout or fout and decided rather to be placed to screen or file
void squirtle::output(ostream& outs){
	if(&outs == &cout){
		string tmp1, tmp2;
		if(glasses == true)
			tmp1 = "Yes";
		else
			tmp1 = "No";
		if(crew == true)
			tmp2 = "Yes";
		else
			tmp2 = "No";
		cout << "Squirtle\n"
		<< "Phone number: " << phone_num << endl
		<< "Free glasses: " << tmp1 << endl
		<< "Also a Free photo of Squirtle: " << tmp2 << endl
		<< "For cancellation purposes. The card that was stolen by Squirtle has an amount of: " << card_limit << endl
		<< "And the pin was: " << pin << endl << endl;
	}
	else{
		char tmp1, tmp2;
		if(glasses== true)
			tmp1 = 'y';
		else
			tmp1 = 'n';
		if(crew == true)
			tmp2 = 'y';
		else
			tmp2 = 'n';
		outs << "Squirtle\n"
		<< phone_num << endl
		<< tmp1 << "0" << tmp2 << endl
		<< card_limit<<endl
		<< pin << endl;
	}
}//end of squirtle class
//start of pidgey class
//constructor for pidgey class to input from file
pidgey::pidgey(istream& ins){
	char tmp;
	
	if(ins.peek() == '\n')
		ins.ignore();
	getline(ins, mig_loc);
	if(ins.peek() == '\n')
		ins.ignore();
	ins >> radius;
	ins.ignore();
	ins.ignore();
	if(ins.peek() == '\n')
		ins.ignore();
	getline(ins, tree_type);
	if(ins.peek() == '\n')
		ins.ignore();
	ins >> tree_height;
	ins.ignore();
	ins.ignore();
	ins.get(item1);
	ins.ignore();
	ins.get(item2);
	ins.ignore();
	ins.get(tmp);
	if(tmp == 'y')
		gps = true;
	else 
		gps = false;
	ins.ignore();
	ins.get(tmp);
	if(tmp == 'y')
		call = true;
	else 
		call = false;
	ins.ignore();
}
//basic constructor
pidgey::pidgey(){
	radius = 1;
	tree_height = 0;
	tree_type = "";
	mig_loc = "";
	item1 = 'a';
	item2 = 'a';
	gps = false;
	call = false;
}
//input function used to input all variables for the class
void pidgey::input(){
	char ans = 'n';
	cout <<"You have selected Pidgey. Pidgey is a Normal-type bird thus he'll live in a nest high up in the public trees away from annoying creatures.\n";
	while(ans != 'y'){
	cout << "We will be providing Pidgey with a nest but it will be up to you to create the holder and we will proivde some items.\n"
		 << "Let's begin with asking about what location do you like to 'Migrate' when the weather becomes cold. This is so we can better\n"
		 << "tune Pidgey's migration habits to head towards your favourite location when you leave: ";
	if(cin.peek() == '\n')
		cin.ignore();
	getline(cin, mig_loc);
	cout << "Good. " << mig_loc<< " sounds like a very interesting location.\n"
		 << "Now, let's create the platform for Pidgey. What is the radius you would? (in meters): ";
	cin >> radius;
	cout << "A radius of " << radius << "m is a reasonable amount.\n"
		 << "What about the tree preferred tree height: ";
	cin >> tree_height;
	cout << "And the tree type: ";
	if(cin.peek() == '\n')
		cin.ignore();
	getline(cin, tree_type);
	cout << "Okay, so a preferred tree type of " << tree_type << " and height of " << tree_height << "m.\n"
	<< "Great! Here are some other things we can include - given the budget you can only select two, one at a time. Binoculars [B], Food stand [S], allow friends [F], or a personalized bird mentor[M]?: ";
	cin >> item1;
	cout << "And the other item: ";
	cin >> item2;
	cout << "Since you've been so busy grading - opps, I mean building a home for Pidgey, we can offer some items for you.\n"
		 << "First, a GPS tracker for Pidgey (y/n): ";
	cin >> ans;
	if(ans == 'y'){
		gps = true;
		ans = 'n';
	}
	cout << "And finally a bird call that calls your Pidgey and only your Pidgey: ";
	cin >> ans;
	if(ans == 'y'){
		call = true;
		ans = 'n';
	}
	cout << "Okay now to review:\n";
	cout <<"Pokemon specis: ";
	output(cout);
	cout <<"Are these correct?(y/n)";
	cin >> ans;
	}
}
//output function that takes the cout or fout and decided rather to be placed to screen or file
void pidgey::output(ostream& outs){
	if(&outs == &cout){
		string tmp1, tmp2, temp1, temp2;
		//converts item1 into the selected item
		if(item1 == 'B')
			tmp1 = "Binoculars";
		else if(item1 == 'S')
			tmp1 = "Food Stand";
		else if(item1 == 'F')
			tmp1 = "Friend";
		else if(item1 == 'M')
			tmp1 = "Mentor";
		else
			tmp1 = "Opps-item1:(";
		//converts item2 into the selected item
		if(item2 == 'B')
			tmp2 = "Binoculars";
		else if(item2 == 'S')
			tmp2 = "Food Stand";
		else if(item2 == 'F')
			tmp2 = "Friend";
		else if(item2 == 'M')
			tmp2 = "Mentor";
		else
			tmp1 = "Opps-item2 :(";
		//converst the bool variables into yes and no
		if(gps == true)
			temp1 = "Yes";
		else
			temp1 = "No";
		if(call == true)
			temp2 = "Yes";
		else
			temp2 = "No";
		cout << "Pidgey\n"
		<< "Migration Location: " << mig_loc << endl
		<< "Radius: " << radius << "m\n"
		<< "Preferred Tree type: " << tree_type << endl
		<< "Tree height: " << tree_height << "m\n"
		<< "You'll be receiving a " << tmp1 << " and a " << tmp2 << " as per your request.\n"
		<< "GPS tracking: " << temp1 << " and Personalized Bird Call: " << temp2 << endl << endl;
	}
	else{
		char temp1, temp2;
		if(gps == true)
			temp1 = 'y';
		else
			temp1 = 'n';
		if(call == true)
			temp2 = 'y';
		else
			temp2 = 'n';
		outs << "Pidgey\n"
		<< mig_loc<< endl
		<< radius << "R\n"
		<< tree_type << endl
		<< tree_height << "m\n"
		<< item1 << "0" << item2 << endl
		<< temp1 << "8" << temp2 << endl;
	}
}//end of pidgey class
//start of caterpie class
//constructor for caterpie class to input from file
caterpie::caterpie(istream& ins){
	if(ins.peek() == '\n')
		ins.ignore();
	ins >> ip_tele;
	ins.ignore();
	ins.get(item);
	ins.ignore();
}
//basic constructor
caterpie::caterpie(){
	item = 'a';
	ip_tele = 0;
}
//input function used to input all variables for the class
void caterpie::input(){
	char ans = 'n';
	while(ans != 'y'){
	cout <<"You have selected Caterpie. Caterpie is a Bug-type worm - gross - but this Caterpie is special.\n"
		 <<"This Caterpie has been selected for a special mission to Mars. So, we have will be providing his house for free.\n"
		 <<"The cool part is he'll be provided with a teleporter for his personal use. If you could provide a double value\n"
		 <<"that will act as a passcode for this Caterpie as well a location saver. Remember since it's a double please\n"
		 <<"make sure it has a decimal point in it for added security: ";
	cin >> ip_tele;
	cout <<"Thank you. Isn't this wonderful? You have a NASA trained caterpillar? huh - sounds strange. Oh well, my project, my rules!\n"
		 <<"If you could select an item for Caterpie to take with him on his space jounry that would be wonderful.\n"
		 <<"Just select the item by using the first digit of the item as indication. Remember - only one so pick wisely.\n"
		 <<"items are as follows: Ray gun[R], Photon shield[P], Cell phone for selfies[C]: ";
	cin >> item;
	if(item == 'C')
		cout << "What a great choice! Now he will be able to send you selfies while being chased down by hostile aliens!";
	else
		cout <<"Good choice! I believe he might have wanted the camera phone but oh well - better safe then to selfie, am I right?\n";
	cout << "To review we have:\n";
	cout <<"Pokemon specis: ";
	output(cout);
	cout <<"Are these correct?(y/n)";
	cin >> ans;
	}
}
//output function that takes the cout or fout and decided rather to be placed to screen or file
void caterpie::output(ostream& outs){
	if(&outs == &cout){
		string tmp;
		if(item == 'C')
			tmp = "Cell Phone";
		else if (item == 'P')
			tmp = "Photon Shield";
		else if (item == 'R')
			tmp = "Ray Gun";
		cout << "Caterpie\n"
		<< "Passcode (only for your eyes): " << ip_tele << endl
		<< "The item you selected for Caterpie to take was : " << tmp << endl << endl;
	}
	else{
		outs << "Caterpie\n"
		<< ip_tele << endl
		<< item << endl;
	}
}//end of caterpie class
//start of arcanine class
//constructor for arcanine class to input from file
arcanine::arcanine(istream& ins){
	char tmp = 'n';
	if(ins.peek() == '\n')
		ins.ignore();
	getline(ins, nickName);
	ins.get(tmp);
	if(tmp == 'y')
		namePlate = true;
	else
		namePlate = false;
	ins.ignore();
	ins.get(tmp);
	if(tmp == 'y')
		firePit = true;
	else
		firePit = false;
	ins.ignore();
	ins.get(tmp);
	if(tmp == 'y')
		perAst = true;
	else
		perAst = false;
	ins.ignore();
	ins >> base;
	ins.ignore();
	ins >> height;
	ins.ignore();
	ins >> width;
	ins.ignore();
	ins >> peak;
	ins.ignore();
	ins.ignore();
	getline(ins,post_region);
	if(ins.peek() == '\n')
		ins.ignore();
	getline(ins, post_code);
	if(ins.peek() == '\n')
		ins.ignore();
}
//basic constructor
arcanine::arcanine(){
	base = 1;
	width = 1;
	height = 1;
	peak=1;
	namePlate=false;
	firePit=false;
	perAst=false;
	nickName= "";
	post_code = "";
}
//input function used to input all variables for the class
void arcanine::input(){
	char ans = 'n', tmp = 'n';
	cout <<"You have selected Arcanine. Arcanine is a Fire-type Wolf. As Arcanine is my personal favourite he'll get the best treatment. Arcanine lives in a Dog house surrounded by fire to keep him warm (fire-type). \n";
	while(ans != 'y'){
	cout << "What is the length of the base?";
	cin >> base;
	cout << "What is the height of the sides?";
	cin >> height;
	cout << "What is the width of the sides?";
	cin >> width;
	cout << "Finally, what is the length of the peak on the house?";
	cin >> peak;
	cout <<"Since Arcanine is a huge fire wolf, he gets a badass Nickname - so you decide his Nickname: \n";
	cin >> nickName;
	cout <<"Below you will be asked about three different items you would like to have with the home. Please answer with a [y] for yes and a [n] for no.\n"
		<<"Would you like a Fire pit for the fire wolf?(y/n)";
	cin >> tmp;
	if(tmp == 'y'){firePit == true;}
	cout <<"What about a name plate to hang over the entrance of his home?(y/n)";
	cin >> tmp;
	if(tmp == 'y'){namePlate == true;}
	cout <<"Arcanine is so big he might need a personal assistant to follow him around - keep him out of trouble. Would you like to add this feature?(y/n)";
	cin >> tmp;
	if(tmp == 'y'){perAst == true;}
	cout <<"Please provide the region Arcanine will be living in? (N, NE, E, SE, S, SW, W, NW)";
	cin >> post_region;
	cout<<"Finally, please provide a postal code for the Arcanine to receive mail?";
	cin >> post_code;
	cout <<"Pokemon specis: ";
	output(cout);
	cout <<"Are these correct?(y/n)";
	cin >> ans;
	}
}
//output function that takes the cout or fout and decided rather to be placed to screen or file
void arcanine::output(ostream& outs){
	if(&outs == &cout){
		string npt, fpt, pat, tmp;
		//changes the true and false into yes or no.
		if(namePlate == true)
			npt = "Yes";
		else 
			npt = "No";

		if(firePit == true)
			fpt = "Yes";
		else 
			fpt = "No";

		if(perAst == true)
			pat = "Yes";
		else 
			pat = "No";
		//used to correct the value post_region string to the correct notation i.e (N becomes Northern)
		if(post_region == "N")
			tmp = "Northern";
		else if (post_region == "NE")
			tmp = "Northeastern";
		else if (post_region == "E")
			tmp = "Eastern";
		else if (post_region == "SE")
			tmp = "Southeastern";
		else if (post_region == "S")
			tmp = "Southern";
		else if (post_region == "SW")
			tmp = "Southwestern";
		else if (post_region == "W")
			tmp = "Western";
		else if (post_region == "NW")
			tmp = "Northwestern";
		else
			tmp = "somewhere?";//basic default
		cout << "Arcanine\n"
		<< "Nickname: " << nickName << endl
		<< "Name Plate: " << npt << ", " << "Fire Pit: " << fpt << ", " << "Personal Groomer: " << pat << endl
		<< "Base: " << base << "m by Height: " << height << "m by Width: " << width <<"m by Peak height: " << peak << "m" <<endl
		<< "Living in the " << tmp << " hemishpere of the Johto region. Located at postal code: "<< post_code << endl << endl;	
	}
	else{
		char npt, fpt, pat;
		
		if(namePlate == true)
			npt = 'y';
		else 
			npt = 'n';

		if(firePit == true)
			fpt = 'y';
		else 
			fpt = 'n';

		if(perAst == true)
			pat = 'y';
		else 
			pat = 'n';
		outs << "Arcanine\n"
		<< nickName << endl
		<< npt << "," << fpt << "," << pat << endl
		<< base <<"B"<< height << "H" << width << "W" << peak << "P" <<endl
		<< post_region << endl << post_code << endl;
	}
}//end of arcanine class
