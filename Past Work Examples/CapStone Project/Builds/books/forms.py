from django import forms
from .book_api import *

class BookCriteriaForm(forms.Form):
    thing = forms.BooleanField(label="Shoelaces",required=False)
