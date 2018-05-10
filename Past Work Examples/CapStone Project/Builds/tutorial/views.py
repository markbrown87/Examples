from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
#from .forms import *
#from .models import UserProfile, Decide, Item, Criteria
from django.shortcuts import render, redirect, render_to_response
#from .restaurant_api import *

# Create your views here.

def tutorial(request):
    #if request.method == 'POST':
        #zipFilterForm = ZipFilterForm(request.POST)

        #if zipFilterForm.is_valid():
            #request.session['decision'] = RestaurantAPI()
            #request.session['decision'].locationFilter(zipFilterForm.cleaned_data['zip_code'])

            #return HttpResponseRedirect('/restaurants/criteria/')

    #else:
        #zipFilterForm = ZipFilterForm()

    return render(request, 'tutorial/index.html')