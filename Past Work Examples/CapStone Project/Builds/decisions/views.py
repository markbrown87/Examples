from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, redirect, render_to_response
from .forms import *
from django.core.mail import EmailMessage, send_mail, BadHeaderError
from django.contrib.auth.forms import PasswordChangeForm
from django.contrib.auth import login, update_session_auth_hash, authenticate
from django.contrib.sites.shortcuts import get_current_site
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.template.loader import render_to_string
from django.utils.encoding import force_bytes, force_text
from django.utils.http import urlsafe_base64_encode, urlsafe_base64_decode
from .tokens import account_activation_token
from .models import UserProfile, Decide, Item, Criteria
from django.urls import reverse
import json

#This functon handles the initial decision page.
def index(request):
    if request.method == 'POST':
        indexForm = IndexForm(request.POST)

        if indexForm.is_valid():
            choice = indexForm.cleaned_data['decision_choice']
            if choice == 'car':
                return render(request, 'cardecisions/car_index.html', {})
            elif choice == 'college':
                return HttpResponseRedirect('/college/')
            else:
                return HttpResponseRedirect('/custom/')
    else:
        indexForm = IndexForm()

    request.session.pop('itemList', None)
    request.session.pop('criteriaList', None)
    request.session.pop('colleges',None)
    request.session.pop('carss',None)
    request.session.pop('criteria_list',None)
    request.session.pop('restaurants',None)
    request.session.pop('movies',None)
    return render(request, 'decisions/index.html', {"indexForm" : indexForm})

#This functon handles the initial decision page.
def decision_index(request, autoFill = False):

    #Displays the Item page with the item form set
    if request.method == 'POST':
        decisionForm = DecideForm(request.POST)

        if decisionForm.is_valid():
            #The name of the decision is saved into the current session
            request.session['decisionName'] = decisionForm.cleaned_data['yourDecision']
            return HttpResponseRedirect('/items/')

    #Displays the initial decision page
    else:
        #Flush any potential session variables from previous sessions
        #for key in list(request.session.keys()):
            #del request.session[key]
        if "decisionName" in request.session and autoFill == True:
            decisionForm = DecideForm(initial={'yourDecision' : request.session["decisionName"]})
        else:
            decisionForm = DecideForm()

    return render(request, 'decisions/decision_index.html', {'decisionForm': decisionForm})

#This function handles the item page and redirects to the criteria page if the user submits valid items.
def items(request):
    if request.method == 'POST':
        itemFormSet = ItemFormSet(request.POST)

        #The items will be saved and the user will be redirected to the criteria
        #page is the itemFormSet is valid.
        if itemFormSet.is_valid():
            #itemList is populated with the items in the itemFormSet
            #The itemList is then added to the current session to be used later.
            itemList = []
            for form in itemFormSet:
                #Each item in item list is a tuple of the following form:
                #(ITEM_NAME,ITEM_SCORE)
                #ITEM_SCORE is initialized to 0
                itemList.append((form.cleaned_data['item_name'],0))
            request.session['itemList'] = itemList
            return HttpResponseRedirect('/criteria/')
    else:
        '''
        If itemList is in session then the user hit the back button.
        That means the list should be prepopulated with their original choices.
        '''
        if "itemList" in request.session:
            initial_list = []
            for item in request.session["itemList"]:
                initial_list.append({"item_name" : item[0]})
            itemFormSet = ItemFormSet(initial=initial_list)
        else:
            itemFormSet = ItemFormSet()

    return render(request, 'decisions/decision_items.html', {'request' : request, 'itemFormSet' : itemFormSet})

#This function handles the criteria page and redirects to the item page if the user submits valid criteria and weights
def criteria(request):
    if request.method == 'POST':
        criteriaFormSet = CriteriaFormSet(request.POST)

        if criteriaFormSet.is_valid():
            #criteriaList is populated with the items in the criteriaFormSet
            #The criteriaList is then added to the current session to be used later.
            criteriaList = []
            for form in criteriaFormSet:
                criteriaList.append((form.cleaned_data['criteria_name'],0))

            request.session['criteriaList'] = criteriaList
            return HttpResponseRedirect('/criteria_weight/')

    else:
        #Check if criteriaList is in session.
        #If so a user hit the back button so populate the list with
        #Their original choices.
        if "criteriaList" in request.session:
            initial_list = []
            for criteria in request.session["criteriaList"]:
                initial_list.append({"criteria_name" : criteria[0]})
            criteriaFormSet = CriteriaFormSet(initial=initial_list)
        else:
            criteriaFormSet = CriteriaFormSet()

    return render(request, 'decisions/decision_criteria.html', {'request' : request, 'criteriaFormSet' : criteriaFormSet})

def criteria_weight(request):
    if request.method == 'POST':
        criteriaWeightForm = CriteriaWeightForm(request.POST, criteria_list = request.session['criteriaList'])

        if criteriaWeightForm.is_valid():
            criteria_list = request.session['criteriaList']
            for i in range(len(criteria_list)):
                '''
                Criteria list holds 3-tuples representing each criteria options.
                [0] = APIT's dictionary information about the criteria
                [1] = integer representing weight of criteria
                [2] = auto-scoring option
                '''
                criteria_list[i] = (criteria_list[i][0],criteriaWeightForm.cleaned_data[str(i)],)
            request.session['criteriaList'] = criteria_list

            return HttpResponseRedirect('/scores/')
    else:
        criteriaWeightForm = CriteriaWeightForm(criteria_list = [i[0] for i in request.session['criteriaList']])
    criteriaList = [str(i[0]).replace(' ','+') for i in request.session['criteriaList']]
    criteriaList = json.dumps(criteriaList).replace(' ','')
    return render(request, 'college/college_criteria_weight.html', {"criteriaList" : criteriaList, "weightForm" : criteriaWeightForm})

#This function handles the scores page and redirects to the results if the user submits valid scores.
def scores(request):
    if request.method == 'POST':
        scoreForm = ScoreForm(request.POST,item_count = len(request.session['itemList']), criteria_count = len(request.session['criteriaList']))
        if scoreForm.is_valid():
            itemList = request.session['itemList']
            criteriaList = [i for i in request.session['criteriaList']]
            #Access an element by score[item][criteria]
            scores = [[0 for x in range(len(criteriaList))] for y in range(len(itemList))]
            #The scores are calculated for each item.
            for i in range(0,len(itemList)):
                score = 0
                for j in range(0,len(criteriaList)):
                    scores[i][j] = scoreForm.cleaned_data[str(i)+'_'+str(j)]
                    score += criteriaList[j][1] * scoreForm.cleaned_data[str(i)+'_'+str(j)]
                itemList[i] = (itemList[i][0],score/100)

            #The itemList is sorted by score values in descending order.
            itemList = sorted(itemList, key = lambda x: x[1],reverse=True)
            request.session['sortedItemList'] = itemList
            request.session['scores'] = scores
            request.session.modified = True
            return HttpResponseRedirect('/results/')
    else:
        #A score form with lenth(itemList) * lenth(criteria) form entries is created.
        scoreForm = ScoreForm(item_count = len(request.session['itemList']), criteria_count = len(request.session['criteriaList']))

    return render(request, 'decisions/decision_scores.html', {'request' : request, 'scoreForm' : scoreForm})

#The results are displayed here. Saving of the data will also be handled here later.
def results(request):
    #Saves the data to the database
    if request.method == 'POST':
        if request.user.is_authenticated():
            user = User.objects.get(username=request.user.username)
            profile = UserProfile.objects.get(user=user)
            newDecision = Decide(user_profile = profile, decisionName = request.session['decisionName'])
            newDecision.save()

            itemList = request.session['sortedItemList']
            criteriaList = request.session['criteriaList']

            for item in itemList:
                newItem = Item(itemName = item[0], itemScore = item[1], decision = newDecision)
                newItem.save()
            for criteria in criteriaList:
                newCriteria = Criteria(criteriaName = criteria[0], criteriaWeight = criteria[1], decision = newDecision)
                newCriteria.save()
        else:
            return HttpResponseRedirect('/login/')

        request.session['saved'] = True
    else:
        request.session['saved'] = False
    return render(request, 'results/results.html', {'request' : request, 'itemList' : request.session['sortedItemList'], 'length' : len(request.session['sortedItemList'])})

# couple basic functions to display pages
def base(request):
    return render(request, 'front/front.html')


'''
    This view is used to register a new user. Upon a get request it will send the user
    to a page containing a blank UserCreation form. Upon a post request it will check
    that the information is valid, if it is it will save the user account to the database
    and redirect the user to the decision page that contains a blank decision form.
    If the information isn't valid it will reload the page with a new blank form.
'''
def register(request):
    if request.method == 'POST':
        form = RegistrationForm(request.POST)
        if form.is_valid():
            new_user = form.save(commit=False)
            new_user.save()

            new_user = authenticate(username=form.cleaned_data['username'], password=form.cleaned_data['password1'])
            login(request, new_user)
            return redirect('/profile/home')
    else:
        form = RegistrationForm()
    return render(request, 'registration/reg_form.html', {'form':form})

def userResults(request):
    return render(request, 'profile/user_result.html')

def carQuery(request):
    return render(request, 'carquery.html')

'''
    Redirects user to their profile page
    once logged in.
'''
@login_required()
def userLogin(request):
    if request.method == 'POST':
        form = EditProfileForm(request.POST, instance=request.user)
        pwd = PasswordChangeForm(data=request.POST, user=request.user)
        if 'edit' in request.POST and form.is_valid():
            form.save()
        if 'pwd' in request.POST and pwd.is_valid():
            pwd.save()
            update_session_auth_hash(request, pwd.user)
            return redirect('/profile/home')
        else:
            return redirect('/profile/home')

    else:
        user = User.objects.get(username=request.user.username)
        profile = UserProfile.objects.get(user=user)
        all_decisions = profile.decide_set.all()
        userForm = UserForm(instance=request.user)
        profileForm = EditProfileForm(instance=request.user.profile)
        pwd = PasswordChangeForm(user=request.user)

        args = {'profileForm' : profileForm, 'userForm' : userForm, 'all_decisions' : all_decisions, 'profile' : profile, 'pwd' : pwd}

        return render(request, 'profile/user_profile.html', args)


@login_required
def updateProfile(request):
    if request.method == "POST":
        user_form = UserForm(request.POST, instance=request.user)
        profile_form = EditProfileForm(request.POST, instance=request.user.profile)
        if user_form.is_valid() and profile_form.is_valid():
            user_form.save()
            profile = profile_form.save(commit=False)
            profile.user = request.user
            profile.save()
        return redirect('/profile/home')
    else:
        user_form = UserForm(request.POST, instance=request.user)
        profile_form = EditProfileForm(request.POST, instance=request.user.profile)
        return redirect('/profile/home')

@login_required
def disableProfile(request):
    user = User.objects.get(pk=request.user.pk)
    user.is_active = False
    user.save()
    logout(request)
    return redirect('/login')



#Handles the contact us page.
def contact(request):
    #Checks to see if the page is being loaded for the first time or if
    #a contact form is being posted
    if request.method == 'POST':
        contactForm = ContactForm(request.POST)
        if contactForm.is_valid():
            subject = "MAUT Contact Form Submission"
            message_content = contactForm.cleaned_data['content']
            if contactForm.cleaned_data['contact_email']:
                from_email = contactForm.cleaned_data['contact_email']
            else:
                from_email = "n/a"

            message = "***This message is an automatically generated message from MAUT's contact page***\n" + "Name: " + contactForm.cleaned_data['contact_name'] + "\n" + "Email Address: " + from_email + "\n" + "Message: " + message_content + "\n"

            try:
                send_mail(subject, message, from_email, ['markamay@live.com','MAUtilityTheory@gmail.com','mark.brown8790@gmail.com'])
            except BadHeaderError:
                return HttpResponse('Invalid header found.')
            return render(request,'contact/thankyou.html', {})
        else:
            return render(request,'contact/contact.html', {'form': ContactForm()})

    else:
        contactForm = ContactForm()

    return render(request,'contact/contact.html', {'form': ContactForm()})
'''
Handles the calculation page.
Every element shown in the calculation page table is going to be packaged in this function beforehand.
matrix is going to store each element, including the titles, scores, and math operators.
'''
def calculation(request):
    if request.method=='POST':
        itemList = request.session['itemList']
        criteriaList = request.session['criteriaList']
        scores = request.session['scores']

        itemList.sort(key=lambda x: x[1], reverse = True)

        rows = len(itemList) + 1
        columns = 4 * len(criteriaList) + 3

        #Access an element by matrix[row(items)][column(criteria)]
        matrix = [[0 for x in range(columns)] for y in range(rows)]

        for column in range(columns-3):
            if column%4 == 0:
                matrix[0][column+1] = criteriaList[int(column/4)][0]
            elif column%4 == 1:
                matrix[0][column+1] = ("(" + str(criteriaList[int((column-1)/4)][1]) + "%)")
            else:
                matrix[0][column+1] = ""

        matrix[0][-1] = "Final Scores"
        matrix[0][-2] = ""
        matrix[0][0] = "Items/Criteria"

        for row in range(1,rows):
            matrix[row][0] = itemList[row-1][0]
            matrix[row][-1] = itemList[row-1][1]
            matrix[row][-2] = "="
            for column in range(1,columns-2):
                if column%4 == 1:
                    matrix[row][column] = "(" + str(scores[row-1][int((column-1)/4)])
                elif column%4 == 2:
                    matrix[row][column] = "*"
                elif column%4 == 3:
                    matrix[row][column] = str((criteriaList[int((column-3)/4)][1]/100)) + ")"
                else:
                    if column == columns - 3:
                        matrix[row][column] = ""
                    else:
                        matrix[row][column] = "   +   "
        #data = {'matrix': matrix, 'request' : request, 'rows' : range(rows), 'columns' : range(columns)}
        #js_data = serializers.serialize("json", data)
        return render(request,'decisions/decision_calculation.html', {'matrix': matrix, 'request' : request, 'rows' : range(rows), 'columns' : range(columns)})
    else:
        return index(request)


'''Handles the tutorial information and front page '''
def example(request):
    if request.method == 'POST':
        contactForm = ContactForm(request.POST)		
        if contactForm.is_valid():
            subject = "MAUT Contact Form Submission"
            message_content = contactForm.cleaned_data['content']
            if contactForm.cleaned_data['contact_email']:
                from_email = contactForm.cleaned_data['contact_email']
            else:
                from_email = "n/a"

            message = "***This message is an automatically generated message from MAUT's contact page***\n" + "Name: " + contactForm.cleaned_data['contact_name'] + "\n" + "Email Address: " + from_email + "\n" + "Message: " + message_content + "\n"

            try:
                send_mail(subject, message, from_email, ['markamay@live.com','MAUtilityTheory@gmail.com','mark.brown8790@gmail.com'])
            except BadHeaderError:
                return HttpResponse('Invalid header found.')
            return render(request,'contact/thankyou.html', {})
        else:
			# error sending email page: not yet implemented
            return render(request,'front/front.html', {'form': ContactForm()})

    else:
        contactForm = ContactForm()

    # return render(request,'contact/contact.html', {'form': ContactForm()})

    return render(request, 'front/front.html', {'form': ContactForm()})


@login_required()
def deleteDecision(request, pk):
    user = User.objects.get(pk=request.user.pk)
    profile = UserProfile.objects.get(user=user)
    Decide.objects.filter(pk=pk).delete()

    return redirect('/profile/home')

@login_required()
def updateDecision(request, pk):
    user = User.objects.get(pk=request.user.pk)
    profile = UserProfile.objects.get(user=user)
    myDecision = Decide.objects.get(pk=pk)

    itemList = []
    for item in myDecision.item.all():
        itemList.append((item.itemName,item.itemScore))

    criteriaList = []
    for criteria in myDecision.criteria.all():
        criteriaList.append((criteria.criteriaName,criteria.criteriaWeight))

    request.session["decisionName"] = myDecision.decisionName
    request.session["itemList"] = itemList
    request.session["criteriaList"] = criteriaList

    return decision_index(request, autoFill = True)

@login_required()
def renameDecision(request,pk,name):
    user = User.objects.get(pk=request.user.pk)
    profile = UserProfile.objects.get(user=user)
    myDecision = Decide.objects.get(pk=pk)
    myDecision.decisionName = name
    myDecision.save()

    return redirect('/profile/home')
	
