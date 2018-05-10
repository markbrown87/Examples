import requests
from urllib.request import Request, urlopen
from urllib.error import URLError
import json


'''
APIT is a list that stores a list of all the criteria options.
Each criteria option is represented as a dictionary with the following information
{
'name' : User-friendly string with name of the criteria
'api_variable' : String containing the info that needs to be appended to the query to get that criteria info
'units' : String saying how that criteria is measured (for example tuition would be dollars, distance would be miles/inches/etc)
'is_num' : Bool saying whether the criteria is measured as a number. Used to see if automatic scoring is possible.
'needs_table' : Bool saying whether or not the information in the database is the actual information
                or represents different information. For example a criteria representing the institutions level
                (whether it is a 2 year school, 4 year, etc) might store the information as 1 for 2 year, 2 for 4 year,
                and 3 as other. Because of this you might need a table hardcoded here to translate the 1 to 2 year and 2
                to 4 year and 3 to other.
'table' : Dictionary mapping the criteria's database value to its actual value. Only used if needs_table is true
}
FOR COPY AND PASTE:
    {
    "name" : ,
    "api_variable" : ,
    "units" : ,
    "is_num" : ,
    "needs_table" : ,

    },
'''

APIT = [
    {
    "name" : "Time" ,
    "api_variable" : "totalTimeInSeconds",
    "units" : "" ,
    "is_num" : True,
    "needs_table" : False,

    },
    {
    "name" : "Rating",
    "api_variable" : "rating",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Sweet" ,
    "api_variable" : "sweet",
    "api_variable2" : "flavors",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Spicy" ,
    "api_variable" : "piquant",
    "api_variable2" : "flavors",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Bitter" ,
    "api_variable" : "bitter",
    "api_variable2" : "flavors",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Sour" ,
    "api_variable" : "sour",
    "api_variable2" : "flavors",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Meaty" ,
    "api_variable" : "meaty",
    "api_variable2" : "flavors",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Salty" ,
    "api_variable" : "salty",
    "api_variable2" : "flavors",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },

]


URL='https://api.yummly.com/v1/api/recipes?_app_id=28058e3b&_app_key=97cc1c1261eb786ace7ee2eea91abf98&maxResult=50'

class CarsAPI:
    def __init__(self):
        self.params = {'maxResults' : '1000'}

    """
    def locationFilter(self,zipcode):
        google_api = "https://maps.googleapis.com/maps/api/geocode/json?key=AIzaSyC-enO3ECdoTTn5_L6p2q8CgKELVIhySm8&address="
        search = google_api + str(zipcode)
        request = Request(search)
        response = urlopen(request)
        json_obj = json.loads(response.read().decode('utf-8'))
        location = json_obj['results'][0]['geometry']['location']
        self.params += [
                    ('lat', str(location['lat'])),
                    ('lon', str(location['lng'])),
                ]
    """

    def pull(self):
        response = requests.get(URL)
        json_obj = response.json()
        matches = json_obj['matches']

        del_list = []

        for i in range(len(matches)):
            if 'flavors' in matches[i]:
                if matches[i]['flavors'] == None:
                    del_list.append(matches[i])
            else:
                del_list.append(matches[i])

        for i in del_list:
            matches.remove(i)

        del_list = []

        for i in range(len(matches)):
            if 'totalTimeInSeconds' in matches[i]:
                if matches[i]['totalTimeInSeconds'] == None:
                    del_list.append(matches[i])
            else:
                del_list.append(matches[i])

        for i in del_list:
            matches.remove(i)

        del_list = []

        for i in range(len(matches)):
            if 'rating' in matches[i]:
                if matches[i]['rating'] == None:
                    del_list.append(matches[i])
            else:
                del_list.append(matches[i])

        for i in del_list:
            matches.remove(i)

        return matches