
from django import forms
from decisions.models import UserProfile
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm, UserChangeForm
from django.forms.formsets import formset_factory, BaseFormSet

class RegistrationForm(UserCreationForm):
    email = forms.EmailField(required=True)
    class Meta:
        model= User
        fields = (
        'username',
        'first_name',
        'last_name',
        'email',
        'password1',
        'password2'
        )
    def save(self, commit=True):
        user=super(RegistrationForm, self).save(commit=False)
        user.first_name = self.cleaned_data['first_name']
        user.last_name = self.cleaned_data['last_name']
        user.email = self.cleaned_data['email']

        if commit:
            user.save()
        return user

class UserForm(forms.ModelForm):
    class Meta:
        model = User
        fields = ['first_name', 'last_name', 'email']


class EditProfileForm(forms.ModelForm):
    class Meta:
        model = UserProfile
        fields = ['city','state','age','gender','income','race','ethnicity']
    


class ItemForm(forms.Form):

    item_name = forms.CharField(
                            max_length=100,
                            widget=forms.TextInput())

class BaseItemFormSet(BaseFormSet):
    def __init__(self, *args, **kwargs):
        super(BaseItemFormSet, self).__init__(*args, **kwargs)
        for form in self.forms:
            form.empty_permitted = False

    def clean(self):
        #Check if any of the individual forms have errors.
        #If so then return because there is no point in checking for more errors.
        if any(self.errors):
            return

        #Check to see if there are at least 2 items to decide between
        if self.data['form-TOTAL_FORMS'] < '2':
            raise forms.ValidationError('There must be at least 2 items to decide between.')


class CriteriaForm(forms.Form):
    criteria_name = forms.CharField(
                            max_length=100,
                            widget=forms.TextInput())

class BaseCriteriaFormSet(BaseFormSet):
    def __init__(self, *args, **kwargs):
        super(BaseCriteriaFormSet, self).__init__(*args, **kwargs)
        for form in self.forms:
            form.empty_permitted = False


'''
Form that only takes as input the name of the user's decision.
'''
class DecideForm(forms.Form):
    yourDecision = forms.CharField(label = 'What are you deciding on?', max_length=100)


'''
This is the form for the scores of each item based on each criteria.
This form is dynamic and takes as input arguments called criteria_count and item_count.

Ex: myform = ScoreForm(criteria_count = 8, item_count = 4)

Each element is stored in the fields dictionary with the key ITEMINDEX_CRITERIAINDEX.
'''
class ScoreForm(forms.Form):
    def __init__(self, *args, **vargs):
        #Popping the criteria_count and item_count variables before calling the parent's constructor
        criteria_count = vargs.pop('criteria_count')
        item_count = vargs.pop('item_count')
        super(ScoreForm,self).__init__(*args,**vargs)
        for i in range(0,item_count):
            for j in range(0,criteria_count):
                field = forms.IntegerField()
                self.fields[str(i) + '_' + str(j)] = field

    def clean(self):
        #check to make sure each score is between 0 and 100
        if self.cleaned_data:
            for key in self.cleaned_data:
                if self.cleaned_data[key] > 100 or self.cleaned_data[key] < 0:
                    raise forms.ValidationError(('Invalid Score Submitted. ' + str(self.cleaned_data[key]) + ' is not between 0 and 100'))


#The Criteria and Item formsets are defined here so it doesn't have to be done in the view
CriteriaFormSet = formset_factory(CriteriaForm,min_num=1,extra=0,formset=BaseCriteriaFormSet)
ItemFormSet = formset_factory(ItemForm,min_num=1,extra=0,formset=BaseItemFormSet)

#All the information used in the 'Contact Us' page.
class ContactForm(forms.Form):
    contact_name = forms.CharField(label = "Name",required=True,
                                widget = forms.TextInput(attrs={
                                'placeholder':'Name', 'class':'form-control'
                                }))
    contact_email = forms.EmailField(label = "Email",required=False,
                                widget = forms.TextInput(attrs={
                                    'placeholder': 'Email (optional)', 'class':'form-control'
                                    }))
    content = forms.CharField(label = "Message",
        required=True,
        widget=forms.Textarea(attrs={
                                'placeholder': 'Message', 'rows':'8', 'class':'form-control'
                              })
    )


LOCATION_CHOICES = [
    ('zip', 'ZIP Code'),
    ('state', 'State'),
    ('region', 'Region'),
    ]

class LocationFilterForm(forms.Form):
    location_filter = forms.CharField(label='How would you like to filter your choices?', widget=forms.RadioSelect(choices=LOCATION_CHOICES))

class ZipFilterForm(forms.Form):
    zip_code = forms.IntegerField(label = 'What zip code would you like to search from?',widget = forms.TextInput())
    distance = forms.IntegerField(label = 'How many miles from the zip code would you like to search from?',widget = forms.TextInput())
    def clean(self):
        if self.cleaned_data:
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
    institution_level = forms.BooleanField(required=False,label="Institution Level (2 yr, 4 yr, etc)")
    out_of_state_tuition = forms.BooleanField(required=False,label="Out of State Tuition")
    in_state_tuition = forms.BooleanField(required=False,label="In State Tuition")
    retention_rate = forms.BooleanField(required=False,label="Retention Rate")
    avg_age = forms.BooleanField(required=False,label="Average Age of Students Entering")
    num_students = forms.BooleanField(required=False,label="Number of Undergraduate Students")
    admission_rate = forms.BooleanField(required=False,label="Admission Rate")

class CollegeCriteriaWeightForm(forms.Form):
    def __init__(self, *args, **vargs):
        criteria_list = vargs.pop('criteria_list')
        super(CollegeCriteriaWeightForm,self).__init__(*args,**vargs)
        iter = 0
        for key, value in criteria_list.items():
                field = forms.IntegerField(label=value[1],
                                        widget=forms.TextInput(attrs={
                                            'id':('weight_' + str(iter)),
                                            'placeholder':'Weight',
                                            'onblur' : 'calculate()',
                                            }))
                self.fields[key] = field
                iter+=1

AUTO_CHOICES = [(0, "Higher Values = Better Scores"),(1, "Lower Values = Better Scores"),(2,"Manually Assign Scores")]

class CollegeAutoScoreForm(forms.Form):
    def __init__(self, *args, **vargs):
        criteria_list = vargs.pop('criteria_list')
        super(CollegeAutoScoreForm,self).__init__(*args,**vargs)
        iter = 0
        for item in criteria_list:
                field = forms.IntegerField(label=item[1],
                                        widget=forms.RadioSelect(choices=AUTO_CHOICES))
                self.fields[item[0]] = field
                iter+=1

OPTION_CHOICES = [(100, "Highly Like"), (75, "Like"), (50, "Neutral"), (25, "Dislike"), (0, "Highly Dislike")]

class CollegeScoreForm(forms.Form):
    def __init__(self, *args, **vargs):
        option_list = vargs.pop('the_option_list')
        super(CollegeScoreForm,self).__init__(*args,**vargs)
        for i in range(len(option_list)):
            field = forms.IntegerField(label=str(option_list[i]), widget=forms.Select(attrs={'class': 'form-control'}, choices=OPTION_CHOICES))
            self.fields[str(i)] = field

class CriteriaWeightForm(forms.Form):
    def __init__(self, *args, **vargs):
        criteria_list = vargs.pop('criteria_list')
        super(CriteriaWeightForm,self).__init__(*args,**vargs)
        for i in range(len(criteria_list)):
                field = forms.IntegerField(label=criteria_list[i],
                                        widget=forms.HiddenInput(attrs={
                                            'id':('weight_' + str(i))
                                            }))
                self.fields[str(i)] = field