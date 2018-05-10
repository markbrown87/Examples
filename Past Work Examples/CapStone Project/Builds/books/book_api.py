from urllib.request import Request, urlopen
from urllib.error import URLError
import json

#This is the link for the Book API
REQUEST_URL = ""


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
    "table" : ,
    },
'''

APIT = [


]


class CollegeAPI:
    def __init__(self):
        self.request_filter = "&_fields=id,school.name,school.school_url"
        self.location_filter = ""

    def criteriaFilter(self,criteria):
        for item in criteria:
                self.request_filter += "," + item["api_variable"]

    def pull(self):
        url = REQUEST_URL + self.location_filter + self.request_filter
        request = Request(url)
        response = urlopen(request)
        json_obj = json.loads(response.read().decode('utf-8'))
        return json_obj['results']
