import requests
from urllib.request import Request, urlopen
from urllib.error import URLError
import json

#This is the link for the Restaurant API used with the key
REQUEST_URL = "https://developers.zomato.com/api/v2.1/geocode"

HEADERS = {
    'Accept': 'application/json',
    'user-key': '4fea2919115b79cf54b1c1ce0d897331',
}


'''
APIT is a list that stores a list of all the criteria options.
Each criteria option is represented as a dictionary with the following information
{
'name' : User-friendly string with name of the criteria
'api_variable' : String containing the info that needs to be appended to the query to get that criteria info
'api_variable2' : Optional string if the desired value is within an additional dictionary
'units' : String saying how that criteria is measured (for example tuition would be dollars, distance would be miles/inches/etc)
'is_num' : Bool saying whether the criteria is measured as a number. Used to see if automatic scoring is possible.
'needs_table' : Bool saying whether or not the information in the database is the actual information
                or represents different information. For example a criteria representing the institutions level
                (whether it is a 2 year school, 4 year, etc) might store the information as 1 for 2 year, 2 for 4 year,
                and 3 as other. Because of this you might need a table hardcoded here to translate the 1 to 2 year and 2
                to 4 year and 3 to other.
'table' : Dictionary mapping the criteria's database value to its actual value. Only used if needs_table is true
'is_list' : Bool saying whether ot not the information returned is actually a list (contained in a string separated by commas)
}
FOR COPY AND PASTE:
    {
    "name" : ,
    "api_variable" : ,
    "units" : ,
    "is_num" : ,
    "needs_table" : ,
    "table" : ,
    "is_list" : ,
    },
'''

APIT = [
    {
    "name" : "Price Range",
    "api_variable" : "price_range",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    "is_list" : False,
    },
    {
    "name" : "User Rating",
    "api_variable" : "user_rating",
    "api_variable2" : "aggregate_rating",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    "is_list" : False,
    },
    {
    "name" : "Is Delivering Now",
    "api_variable" : "is_delivering_now",
    "units" : "",
    "is_num" : False,
    "needs_table" : True,
    "table" : {
        0 : "restaurant isn't delivering right now",
        1 : "restaurant is delivering right now"
    },
    "is_list" : False,
    },

    {
    "name" : "Currency",
    "api_variable" : "currency",
    "units" : "",
    "is_num" : False,
    "needs_table" : False,
    "is_list" : False,
    },
    {
    "name" : "Cuisine Type",
    "api_variable" : "cuisines",
    "units" : "",
    "is_num" : False,
    "needs_table" : False,
    "is_list" : True,
    },
]


class RestaurantAPI:
    def __init__(self):
        self.params = ()


    def locationFilter(self,zipcode):
        google_api = "https://maps.googleapis.com/maps/api/geocode/json?key=AIzaSyC-enO3ECdoTTn5_L6p2q8CgKELVIhySm8&address="
        search = google_api + str(zipcode)
        request = Request(search)
        response = urlopen(request)
        json_obj = json.loads(response.read().decode('utf-8'))
        location = json_obj['results'][0]['geometry']['location']
        self.params = (
                    ('lat', str(location['lat'])),
                    ('lon', str(location['lng'])),
                )

    """
    Pulls all the schools that match the current search query
    """
    def pull(self):
        response = requests.get(REQUEST_URL,headers=HEADERS,params=self.params)
        json_obj = response.json()
        return json_obj['nearby_restaurants']
