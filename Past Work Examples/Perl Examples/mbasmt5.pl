/* 	Created by Mark Brown
	Date: 14/10/2017
	Description: A prolog program designed to aid a user in selection a particular vacation location. Each destination 
		has traits and variables that make it unique for different user input.
*/

/* A camp ground by a lake */
sleep_in_tent_CGL(camp_ground_by_lake).
needs_travel_CGL(camp_ground_by_lake).
kids_playground(camp_ground_by_lake).
swimming_activity(camp_ground_by_lake).

/*backyard tent and camp fire*/
sleep_in_tent_BYS(backyard_understars).
low_prices_BYS(backyard_understars).

/* Disneyland */
rollar_coasters_DL(disneyland).
high_prices_DL(disneyland).

/* Universal themepark */
rollar_coasters_U(universal_TP).
high_prices_U(universal_TP).

/* Jurassic Park */
active_running_JP(jurassic_park).
meet_historical_Dino(jurassic_park).
high_prices_JP(jurassic_park).

/* WWI visit */
see_past_event_WEI(witness_WWI).
low_prices_WEI(witness_WWI).

/* WWII visit */
see_past_event_WEII(witness_WWII).
low_prices_WEII(witness_WWII).

/* The Big Bang Visist */
see_past_event_WEBG(witness_Big_Bang).
high_prices_WEBG(witness_Big_Bang).

/* The Moon */
space_witness_moon(go_to_the_Moon).

/* Mars */
space_witness_mars(go_to_Mars).

/* Family Visit */
kids_family_visit(family_visit).
needs_travel_FV(family_visit).

/* Hunting trip */
sleep_in_cabin_hunt(hunting_trip).

/* Musicial tour */
in_city_travel(tour_with_band).

/* Stay at home and do nothing */
in_city_home(stay_home).
low_price(stay_home).

/*Guitar lessons with Angus Young */
high_prices_GL(angus_young_guitar_lessons).
meet_historical_AY(angus_young_guitar_lessons).

/*History lessons from George Washington */
high_prices_HL(GW_history_lessons).
meet_historical_GW(GW_history_lessons).

/* Cheap campground near the city */
sleep_in_cabin(camp_ground_by_city).
park_games_activity(camp_ground_by_city).
kids_pool(camp_ground_by_city).
in_city(camp_ground_by_city).

/* Go to las Vegas to waste money on gambling and sleep in a hotel room */
sleep_in_hotel(las_vegas).
not_active(las_vegas).
waste_money(las_vegas).

/* Go to the cabin by the lake */
adult_cabin(log_cabin_by_lake).

/* Canada's Wonderland. */
rollar_coasters_CW(canadas_wonderland).
low_prices_CW(canadas_wonderland).



/* Subcategories for particular questions */
kids_ok(V) :- has_kids(no), waste_money(V).
kids_ok(V) :- has_kids(no), adult_cabin(V). 
kids_ok(V) :- has_kids(yes), kids_playground(V).
kids_ok(V) :- has_kids(yes), kids_pool(V).
kids_ok(V) :- has_kids(yes), kids_family_visit(V).

travel_ok(V) :- has_car(no), in_city(V).
travel_ok(V) :- has_car(no), in_city_home(V).
travel_ok(V) :- has_car(yes), needs_travel_CGL(V).
travel_ok(V) :- has_car(yes), needs_travel_FV(V).


active_ok(V) :- not_active(V).
active_ok(V) :- wants_active(yes), swimming_activity(V).
active_ok(V) :- wants_active(yes), park_games_activity(V).
active_ok(V) :- wants_active(yes), active_running_JP(V).

sleep_ok(V) :- sleep_in_hotel(V).
sleep_ok(V) :- will_sleep_in_tent(yes),sleep_in_tent_BYS(V).
sleep_ok(V) :- will_sleep_in_tent(yes),sleep_in_tent_CGL(V).
sleep_ok(V) :- will_sleep_in_cabin(yes),sleep_in_cabin(V).
sleep_ok(V) :- will_sleep_in_cabin(yes), sleep_in_cabin_hunt(V).


price_ok(V) :- will_spend(no), high_prices_GL(V).
price_ok(V) :- will_spend(no), high_prices_HL(V).
price_ok(V) :- will_spend(no), high_prices_DL(V).
price_ok(V) :- will_spend(no), high_prices_JP(V).
price_ok(V) :- will_spend(no), high_prices_U(V).
price_ok(V) :- will_spend(no), high_prices_WEBG(V).
price_ok(V) :- will_spend(yes), low_prices_BYS(V).
price_ok(V) :- will_spend(yes), low_prices_CW(V).
price_ok(V) :- will_spend(yes), low_prices_WEI(V).
price_ok(V) :- will_spend(yes), low_prices_WEII(V).
price_ok(V) :- will_spend(yes), low_price(V).

time_travel(V) :- will_visit(no).
time_travel(V) :- will_visit(yes), meet_historical_AY(V).
time_travel(V) :- will_visit(yes), meet_historical_GW(V).
time_travel(V) :- will_visit(yes), meet_historical_Dino(V).


past_event_ok(V) :- past_event(no).
past_event_ok(V) :- past_event(yes), see_past_event_WEI(V).
past_event_ok(V) :- past_event(yes), see_past_event_WEII(V).
past_event_ok(V) :- past_event(yes), see_past_event_WEBG(V).

vomit_ok(V) :- will_vomit(no).
vomit_ok(V) :- will_vomit(yes), rollar_coasters_DL(V).
vomit_ok(V) :- will_vomit(yes), rollar_coasters_CW(V).
vomit_ok(V) :- will_vomit(yes), rollar_coasters_U(V).

space_travel(V) :- will_travel(no).
space_travel(V) :- will_travel(yes), space_witness_mars(V).
space_travel(V) :- will_travel(yes), space_witness_moon(V).


/*Find all vacation locations*/
vacation_location(V) :- travel_ok(V), kids_ok(V), active_ok(V), sleep_ok(V), price_ok(V), time_travel(V), past_event_ok(V), vomit_ok(V), space_travel(V).


/* Basic questions to ask the user */
advise :- write('Do you have a car?  '), read(Car), nl,
          assert(has_car(Car)),
          write('Do you have kids?  '), read(Kids), nl,
          assert(has_kids(Kids)),
		  write('Do you want to be active?  '), read(Active), nl,
          assert(wants_active(Active)),
		  write('Do you want to sleep in a tent?  '), read(Tent), nl,
          assert(will_sleep_in_tent(Tent)),
		  write('Do you want to sleep in a log cabin?  '), read(Cabin), nl,
          assert(will_sleep_in_cabin(Cabin)),
		  write('Are you okay will spending a lot of money?  '), read(Money), nl,
          assert(will_spend(Money)),
		  write('Want to meet someone historical and learn something new?  '), read(Learn), nl,
          assert(will_visit(Learn)),
		  write('Want to see a past event?  '), read(Event), nl,
          assert(past_event(Event)),
		  write('Could I interest you in riding rollar coasters until you vomit?  '), read(Vomit), nl,
          assert(will_vomit(Vomit)),
		  write('Maybe you want to do some space travel?  '), read(Space), nl,
          assert(will_travel(Space)),
		  
		  
          findall(V,vacation_location(V),Vs),
          write('Here are some locations you may want to visit for your vacation: '), nl,
          writelist(Vs),
          retract(has_car(Car)), retract(has_kids(Kids)), retract(wants_active(Active)), retract(will_sleep_in_tent(tent)), 
		  retract(will_sleep_in_cabin(Cabin)), retract(will_spend(Money)), retract(will_visit(Learn)), retract(past_event(Event)),
		  retract(will_vomit(Vomit)), retract(will_travel(Space)).

writelist([]).
writelist([H|T]) :- writeonce(H,T), writelist(T).  
writeonce(H,T) :- member(H,T).
writeonce(H,T) :- not(member(H,T)), write(H), nl.