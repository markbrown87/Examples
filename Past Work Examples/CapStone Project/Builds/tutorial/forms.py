from django import forms
from django.forms.formsets import formset_factory, BaseFormSet
#from .restaurant_api import *

# class ZipFilterForm(forms.Form):
    # zip_code = forms.IntegerField(label = 'What zip code would you like to search from?',widget = forms.TextInput())

    # def clean(self):
        # if self.cleaned_data['zip_code'] > 99950 or self.cleaned_data['zip_code'] < 501:
            # raise forms.ValidationError(('Invalid zip code entered ' + str(self.cleaned_data['zip_code']) + ' is not a valid zip code'))

# class RestaurantCriteriaForm(forms.Form):
    # def __init__(self, *args, **vargs):
        # super(RestaurantCriteriaForm,self).__init__(*args,**vargs)
        # for i in range(len(APIT)):
                # field = forms.BooleanField(label=APIT[i]['name'],required=False)
                # self.fields[str(i)] = field

# class RestaurantCriteriaWeightForm(forms.Form):
    # def __init__(self, *args, **vargs):
        # criteria_list = vargs.pop('criteria_list')
        # super(RestaurantCriteriaWeightForm,self).__init__(*args,**vargs)
        # for i in range(len(criteria_list)):
                # field = forms.IntegerField(label=criteria_list[i],
                                        # widget=forms.TextInput(attrs={
                                            # 'id':('weight_' + str(i)),
                                            # 'placeholder':'Weight',
                                            # 'onblur' : 'calculate()',
                                            # }))
                # self.fields[str(i)] = field

    # def clean(self):
        # if self.cleaned_data:
            # sum = 0
            # for key in self.cleaned_data:
                # if self.cleaned_data[key] > 100 or self.cleaned_data[key] < 0:
                    # raise forms.ValidationError(('Invalid Weight Submitted. ' + str(self.cleaned_data[key]) + ' is not between 0 and 100'))
                # else:
                    # sum = sum + self.cleaned_data[key]
            # if sum != 100:
                # raise forms.ValidationError('All the weights must sum to 100.')

# AUTO_CHOICES = [(0, "Higher Values = Better Scores"),(1, "Lower Values = Better Scores"),(2,"Manually Assign Scores")]
# AUTO_STR_CHOICES = [(2, "Can't Auto Assign Scores")]

# class RestaurantAutoScoreForm(forms.Form):
    # def __init__(self, *args, **vargs):
        # criteria_list = vargs.pop('criteria_list')
        # super(RestaurantAutoScoreForm,self).__init__(*args,**vargs)
        # for i in range(len(criteria_list)):
                # if criteria_list[i]['is_num']:
                    # choice = AUTO_CHOICES
                # else:
                    # choice = AUTO_STR_CHOICES
                # field = forms.IntegerField(label=criteria_list[i]['name'],
                                        # widget=forms.Select(attrs={'class': 'form-control'},choices=choice))
                # self.fields[str(i)] = field

# class RestaurantScoreForm(forms.Form):
    # def __init__(self, *args, **vargs):
        # option_list = vargs.pop('the_option_list')
        # super(RestaurantScoreForm,self).__init__(*args,**vargs)
        # for i in range(len(option_list)):
            # field = forms.IntegerField(label=str(option_list[i]), widget=forms.Select(attrs={'class': 'form-control'}, choices=OPTION_CHOICES))
            # self.fields[str(i)] = field