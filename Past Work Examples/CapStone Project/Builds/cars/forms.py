from django import forms
from django.forms.widgets import NumberInput
from django.forms.formsets import formset_factory, BaseFormSet
from .cars_api import *


class RangeInput(NumberInput):
    input_type = 'range'

class CarsSearchForm(forms.Form):
    cars = forms.CharField(label = 'Enter the name of something you\'d like a cars for')


class CarsCriteriaForm(forms.Form):
    def __init__(self, *args, **vargs):
        super(CarsCriteriaForm,self).__init__(*args,**vargs)
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

class CarsCriteriaWeightForm(forms.Form):
    def __init__(self, *args, **vargs):
        criteria_list = vargs.pop('criteria_list')
        super(CarsCriteriaWeightForm,self).__init__(*args,**vargs)
        for i in range(len(criteria_list)):
                field = forms.IntegerField(label=criteria_list[i],
                                        widget=forms.HiddenInput(attrs={
                                            'id':('weight_' + str(i))
                                            }))
                self.fields[str(i)] = field

    def clean(self):
        if self.cleaned_data:
            sum = 0
            for key in self.cleaned_data:
                if self.cleaned_data[key] > 100 or self.cleaned_data[key] < 0:
                    raise forms.ValidationError(('Invalid Weight Submitted. ' + str(self.cleaned_data[key]) + ' is not between 0 and 100'))
                else:
                    sum = sum + self.cleaned_data[key]
            if sum != 100:
                raise forms.ValidationError('All the weights must sum to 100.')


AUTO_CHOICES = [(0, "Higher Values = Better Scores"),(1, "Lower Values = Better Scores"),(2,"Manually Assign Scores")]
AUTO_STR_CHOICES = [(2, "Can't Auto Assign Scores")]

class CarsAutoScoreForm(forms.Form):
    def __init__(self, *args, **vargs):
        criteria_list = vargs.pop('criteria_list')
        super(CarsAutoScoreForm,self).__init__(*args,**vargs)
        for i in range(len(criteria_list)):
                if criteria_list[i]['is_num']:
                    choice = AUTO_CHOICES
                else:
                    choice = AUTO_STR_CHOICES
                field = forms.IntegerField(label=criteria_list[i]['name'],
                                        widget=RangeInput(attrs={'class': 'form-control', 'onchange' : 'rangevalue.value=value'}))
                self.fields[str(i)] = field

OPTION_CHOICES = [(100, "Highly Like"), (75, "Like"), (50, "Neutral"), (25, "Dislike"), (0, "Highly Dislike")]

class CarsScoreForm(forms.Form):
    def __init__(self, *args, **vargs):
        option_list = vargs.pop('the_option_list')
        super(CarsScoreForm,self).__init__(*args,**vargs)
        for i in range(len(option_list)):
            field = forms.IntegerField(label=str(option_list[i]), widget=forms.Select(attrs={'class': 'form-control'}, choices=OPTION_CHOICES))
            self.fields[str(i)] = field

class RecipeDetailForm(forms.Form):
    name = forms.CharField(widget=forms.HiddenInput(attrs={'id' : 'recipedetails'}))