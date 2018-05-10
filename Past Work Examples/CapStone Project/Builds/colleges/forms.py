from django import forms
from django.forms.formsets import formset_factory, BaseFormSet
from .college_api import *

LOCATION_CHOICES = [
    ('zip', 'ZIP Code'),
    ('state', 'State'),
    ('region', 'Region'),
    ]

class LocationFilterForm(forms.Form):
    location_filter = forms.CharField(label='How would you like to filter your choices?', widget=forms.Select(attrs={'class': 'form-control'},choices=LOCATION_CHOICES))

class ZipFilterForm(forms.Form):
    zip_code = forms.IntegerField(label = 'What zip code would you like to search from?',widget = forms.TextInput())
    distance = forms.IntegerField(label = 'How many miles from that would you like to search from?',widget = forms.TextInput())
    def clean(self):
        if self.cleaned_data['zip_code'] > 99950 or self.cleaned_data['zip_code'] < 501:
            raise forms.ValidationError(('Invalid zip code entered ' + str(self.cleaned_data['zip_code']) + ' is not a valid zip code'))


STATES = [("AL", "Alabama"), ("AK", "Alaska"), ("AZ","Arizona"), ("AR","Arkansas"), ("CA","California"),
        ("CO","Colorado"), ("CT","Connecticut"), ("DC","Delaware"), ("DE","Delaware"), ("FL","Florida"),
        ("GA","Georgia"), ("HI","Hawaii"), ("ID","Idaho"), ("IL","Illinois"), ("IN","Indiana"), ("IA","Iowa"),
        ("KS","Kansas"), ("KY","Kentucky"), ("LA","Louisana"), ("ME","Maine"), ("MD","Maryland"),
          ("MA","Massachusetts"), ("MI","Michigan"), ("MN","Minnesota"), ("MS","Mississippi"), ("MO","Missouri"),
          ("MT","Montana"), ("NE","Nebraska"), ("NV","Nevada"), ("NH","New Hampshire"), ("NJ","New Jersey"),
          ("NM","New Mexico"), ("NY","New York"), ("NC","North Carolina"), ("ND","North Dakota"), ("OH","Ohio"), ("OK","Oklahoma"),
          ("OR","Oregon"), ("PA","Pennsylvania"), ("RI","Rhode Island"), ("SC","South Carolina"),
          ("SD","South Dakota"), ("TN","Tennessee"), ("TX","Texas"), ("UT","Utah"), ("VT","Vermont"), ("VA","Virginia"), ("WA","Washington"),
          ("WV","West Virginia"), ("WI","Wisconsin"), ("WY","Wyoming")]

class StateFilterForm(forms.Form):
    state = forms.CharField(label='Which state would you like to search from?', widget=forms.Select(attrs={'class': 'form-control'}, choices=STATES))

REGIONS = [(0,"Zero - US Service Schools"),(1,"One - New England (CT,ME,MA,NH,RI,VT)"),(2,"Two - Mid East (DE, DC, MD, NJ, NY, PA)"),
            (3,"Three - Great Lakes (IL, IN, MI, OH, WI)"),(4,"Four - Plains (IA, KS, MN, MO, NE, ND, SD)"),
            (5,"Five - Southeast (AL, AR, FL, GA, KY, LA, MS, NC, SC, TN, VA, WV)"),(6,"Six - Southwest (AZ, MN, OK, TX)"),
            (7,"Seven - Rocky Mountains (CO, ID, MT, UT, WY)"),(8,"Eight - Far West (AK, CA, HI, NV, OR, WA)"),
            (9,"Nine - Outlying Areas (AS, FM, GU, MH, MP, PR, PW, VI)"),]

class RegionFilterForm(forms.Form):
    region = forms.CharField(label='Which region would you like to search from?', widget=forms.Select(attrs={'class': 'form-control'}, choices=REGIONS))

DECISION_CHOICES = [("car","Cars"),("college","Colleges"),("custom","Custom Decision")]
class IndexForm(forms.Form):
    decision_choice = forms.CharField(label='Which are you deciding on?', widget=forms.RadioSelect(choices=DECISION_CHOICES))

class CollegeCriteriaForm(forms.Form):
    def __init__(self, *args, **vargs):
        super(CollegeCriteriaForm,self).__init__(*args,**vargs)
        for i in range(len(APIT)):
                field = forms.BooleanField(label=APIT[i]['name'],required=False)
                self.fields[str(i)] = field

    def clean(self):
        count = 0
        for key, value in self.cleaned_data.items():
            if value:
                count = count + 1
        if count < 2:
            raise forms.ValidationError("You must select at least 2 criteria")

class CollegeCriteriaWeightForm(forms.Form):
    def __init__(self, *args, **vargs):
        criteria_list = vargs.pop('criteria_list')
        super(CollegeCriteriaWeightForm,self).__init__(*args,**vargs)
        for i in range(len(criteria_list)):
                field = forms.IntegerField(label=criteria_list[i],
                                        widget=forms.HiddenInput(attrs={
                                            'id':('weight_' + str(i))
                                            }))
                self.fields[str(i)] = field


AUTO_CHOICES = [(0, "Higher Values = Better Scores"),(1, "Lower Values = Better Scores"),(2,"Manually Assign Scores")]
AUTO_STR_CHOICES = [(2, "Can't Auto Assign Scores")]

class CollegeAutoScoreForm(forms.Form):
    def __init__(self, *args, **vargs):
        criteria_list = vargs.pop('criteria_list')
        super(CollegeAutoScoreForm,self).__init__(*args,**vargs)

        for i in range(len(criteria_list)):
                if criteria_list[i]['is_num']:
                    choice = AUTO_CHOICES
                else:
                    choice = AUTO_STR_CHOICES
                field = forms.IntegerField(label=criteria_list[i]['name'],
                                        widget=forms.Select(attrs={'class': 'form-control'},choices=choice))
                self.fields[str(i)] = field

OPTION_CHOICES = [(100, "Highly Like"), (75, "Like"), (50, "Neutral"), (25, "Dislike"), (0, "Highly Dislike")]

class CollegeScoreForm(forms.Form):
    def __init__(self, *args, **vargs):
        option_list = vargs.pop('the_option_list')
        super(CollegeScoreForm,self).__init__(*args,**vargs)
        for i in range(len(option_list)):
            field = forms.IntegerField(label=str(option_list[i]), widget=forms.Select(attrs={'class': 'form-control'}, choices=OPTION_CHOICES))
            self.fields[str(i)] = field

class CollegeDetailForm(forms.Form):
    name = forms.CharField(widget=forms.HiddenInput(attrs={'id' : 'collegedetails'}))