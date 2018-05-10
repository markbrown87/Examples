from urllib.request import Request, urlopen
from urllib.error import URLError
import json

#This is the link for the College API used with the key
REQUEST_URL = "https://api.data.gov/ed/collegescorecard/v1/schools.json?api_key=XR0O0IAXgeNIPZKCyBnjCLODxG4MZwnpyfkOiz3g"
#State abbreviations matched with their FIPS number
STATE_CODES = {
    'WA': '53', 'DE': '10', 'DC': '11', 'WI': '55', 'WV': '54', 'HI': '15',
    'FL': '12', 'WY': '56', 'PR': '72', 'NJ': '34', 'NM': '35', 'TX': '48',
    'LA': '22', 'NC': '37', 'ND': '38', 'NE': '31', 'TN': '47', 'NY': '36',
    'PA': '42', 'AK': '02', 'NV': '32', 'NH': '33', 'VA': '51', 'CO': '08',
    'CA': '06', 'AL': '01', 'AR': '05', 'VT': '50', 'IL': '17', 'GA': '13',
    'IN': '18', 'IA': '19', 'MA': '25', 'AZ': '04', 'ID': '16', 'CT': '09',
    'ME': '23', 'MD': '24', 'OK': '40', 'OH': '39', 'UT': '49', 'MO': '29',
    'MN': '27', 'MI': '26', 'RI': '44', 'KS': '20', 'MT': '30', 'MS': '28',
    'SC': '45', 'KY': '21', 'OR': '41', 'SD': '46'
}
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
    {
    'name' : 'Years to Earn a Degree',
    'api_variable' : 'school.institutional_characteristics.level',
    'units' : "institution level",
    "is_num" : False,
    "needs_table" : True,
    "table" : {1 : "4 years", 2 : "2 years", 3 : "Less than 2 years"}
    },
    {
    "name" : "Out of State Tuition",
    "api_variable" : '2015.cost.tuition.out_of_state',
    "units" : "dollars",
    "is_num" : True,
    "needs_table" : False
    },
    {
    "name" : "In State Tuition",
    "api_variable" : '2015.cost.tuition.in_state',
    "units" : "dollars",
    "is_num" : True,
    "needs_table" : False
    },
    {
    "name" : "Retention Rate",
    "api_variable" : '2013.student.retention_rate.four_year.full_time',
    "units" : "",
    "is_num" : True,
    "needs_table" : False
    },
    {
    "name" : "Average Age",
    "api_variable" : "2015.student.demographics.age_entry",
    "units" : "years old",
    "is_num" : True,
    "needs_table" : False
    },
    {
    "name" : "Number of Students",
    "api_variable" : "2015.student.size",
    "units" : "students",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Admission Rate",
    "api_variable" : "2015.admissions.admission_rate.overall",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Carnegie Classification",
    "api_variable" : "school.carnegie_basic",
    "units" : "",
    "is_num" : False,
    "needs_table" : True,
    "table" : { None : "Not applicable", -3 : "Not applicable", -2 : "Not applicable", -1 : "Not Applicable", 0 : "Not classified", 1 : "Associate's Colleges: High Transfer-High Traditional",
                2 : "Associate's Colleges: High Transfer-Mixed Traditional/Nontraditional",
                3 : "Associate's Colleges: High Transfer-High Nontraditional", 4 : "Associate's Colleges: Mixed Transfer/Vocational & Technical-High Traditional",
                5 : "Associate's Colleges: Mixed Transfer/Vocational & Technical-Mixed Traditional/Nontraditional", 6 : "Associate's Colleges: Mixed Transfer/Vocational & Technical-High Nontraditional",
                7 : "Associate's Colleges: High Vocational & Technical-High Traditional", 8 : "Associate's Colleges: High Vocational & Technical-Mixed Traditional/Nontraditional",
                9: "Associate's Colleges: High Vocational & Technical-High Nontraditional", 10 : "Special Focus Two-Year: Health Professions", 11 : "Special Focus Two-Year: Technical Professions",
                12 : "Special Focus Two-Year: Arts & Design", 13: "Special Focus Two-Year: Other Fields", 14 : "Baccalaureate/Associate's Colleges: Associate's Dominant",
                15 : "Doctoral Universities: Highest Research Activity", 16 : "Doctoral Universities: Higher Research Activity", 17 : "Doctoral Universities: Moderate Research Activity",
                18 : "Master's Colleges & Universities: Larger Programs", 19 : "Master's Colleges & Universities: Medium Programs", 20 : "Master's Colleges & Universities: Small Programs",
                21 : "Baccalaureate Colleges: Arts & Sciences Focus", 22 : "Baccalaureate Colleges: Diverse Fields", 23 : "Baccalaureate/Associate's Colleges: Mixed Baccalaureate/Associate's",
                24 : "Special Focus Four-Year: Faith-Related Institutions", 25 : "Special Focus Four-Year: Medical Schools & Centers", 26 : "Special Focus Four-Year: Other Health Professions Schools",
                27 : "Special Focus Four-Year: Engineering Schools", 28 : "Special Focus Four-Year: Other Technology-Related Schools", 29: "Special Focus Four-Year: Business & Management Schools",
                30: "Special Focus Four-Year: Arts, Music & Design Schools", 31 : "Special Focus Four-Year: Law Schools", 32 : "Special Focus Four-Year: Other Special Focus Institutions",
                33 : "Tribal Colleges",},
    },
    {
    "name" : "Average Faculty Salary",
    "api_variable" : "school.faculty_salary",
    "units" : "dollars",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Percentage of Students who received a Pell Grant",
    "api_variable" : "2015.aid.pell_grant_rate",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Percentage of Students who graduated within Four Years",
    "api_variable" : "2013.completion.title_iv.completed_by.4yrs",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Percentage of Students who are first-generation",
    "api_variable" : "2015.student.share_firstgeneration",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Median Debt for Students who have completed college",
    "api_variable" : "2015.aid.median_debt.completers.overall" ,
    "units" : "dollars",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Percentage of Students who are female",
    "api_variable" : "2015.student.demographics.female_share",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Percentage of Students who are married",
    "api_variable" : "2015.student.demographics.married",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Percentage of Students who are veterans",
    "api_variable" : "2015.student.demographics.veteran",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
    {
    "name" : "Percentage of Students who are dependents",
    "api_variable" : "2015.student.demographics.veteran",
    "units" : "",
    "is_num" : True,
    "needs_table" : False,
    },
]


class CollegeAPI:
    def __init__(self):
        self.request_filter = "&_fields=id,school.name,school.school_url"
        self.location_filter = ""

    def criteriaFilter(self,criteria):
        for item in APIT:
                self.request_filter += "," + item["api_variable"]


    """
    Returns schools from/near a certain location.

    Depending on the filter used a different location variable type will be given.

    If filter is "ZIP" then results within 'distance' miles of the zip code 'location' will be returned
    If filter is "STATE" then results within state 'location' will be returned
    If filter is "REGION then results within state 'location' will be returned
    If filter is "NONE" then all results will be returned
    """
    def locationFilter(self,location="NONE",distance=0,filter="NONE"):
        if filter == "ZIP":
            self.location_filter = "&_zip=" + str(location) + "&_distance=" + str(distance)
        elif filter == "STATE":
            self.location_filter = "&school.state_fips=" + STATE_CODES[location]
        elif filter == "REGION":
            self.location_filter = "&school.region_id=" + str(location)
        else:
            self.location_filter = ""

    """
    Pulls all the schools that match the current search query
    """
    def pull(self):
        url = REQUEST_URL + self.location_filter + self.request_filter
        request = Request(url)
        response = urlopen(request)
        json_obj = json.loads(response.read().decode('utf-8'))
        return json_obj['results']
