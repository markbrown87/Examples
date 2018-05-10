from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from .forms import *
#from .models import UserProfile, Decide, Item, Criteria
from django.shortcuts import render, redirect, render_to_response
from .book_api import *

def book_index(request):

    if request.method == 'POST':
        bookCriteriaForm = BookCriteriaForm(request.POST)
    else:
        bookCriteriaForm = BookCriteriaForm()

    return render(request,"books/books_index.html", {'bookCriteriaForm' : bookCriteriaForm})
