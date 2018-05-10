from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, redirect, render_to_response
from .forms import *
from django.core.mail import EmailMessage, send_mail, BadHeaderError



from django.contrib.auth.forms import PasswordChangeForm
from django.contrib.auth import login, update_session_auth_hash
from django.contrib.sites.shortcuts import get_current_site
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.template.loader import render_to_string

from django.utils.encoding import force_bytes, force_text
from django.utils.http import urlsafe_base64_encode, urlsafe_base64_decode
from .tokens import account_activation_token

from .models import UserProfile, Decide, Item, Criteria


# Create your views here.

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
                #Each item in item list is a tuple of the following form:
                #(CRITERIA_NAME,CRITERIA_WEIGHT)
                criteriaList.append((form.cleaned_data['criteria_name'],form.cleaned_data['criteria_weight']))

            request.session['criteriaList'] = criteriaList
            return HttpResponseRedirect('/scores/')

    else:
        #Check if criteriaList is in session.
        #If so a user hit the back button so populate the list with
        #Their original choices.
        if "criteriaList" in request.session:
            initial_list = []
            for criteria in request.session["criteriaList"]:
                initial_list.append({"criteria_name" : criteria[0], "criteria_weight" : criteria[1]})
            criteriaFormSet = CriteriaFormSet(initial=initial_list)
        else:
            criteriaFormSet = CriteriaFormSet()

    return render(request, 'decisions/decision_criteria.html', {'request' : request, 'criteriaFormSet' : criteriaFormSet})

#This function handles the scores page and redirects to the results if the user submits valid scores.
def scores(request):
    if request.method == 'POST':
        scoreForm = ScoreForm(request.POST,item_count = len(request.session['itemList']), criteria_count = len(request.session['criteriaList']))
        if scoreForm.is_valid():
            itemList = request.session['itemList']
            criteriaList = request.session['criteriaList']
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
        user = User.objects.get(username=request.user.username)
        profile = UserProfile.objects.get(user=user)
        newDecision = Decide(user_profile = profile, decisionName = request.session['decisionName'])
        newDecision.save()

        itemList = request.session['itemList']
        criteriaList = request.session['criteriaList']

        for item in itemList:
            newItem = Item(itemName = item[0], itemScore = item[1], decision = newDecision)
            newItem.save()
        for criteria in criteriaList:
            newCriteria = Criteria(criteriaName = criteria[0], criteriaWeight = criteria[1], decision = newDecision)
            newCriteria.save()

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
            new_user.is_active = False
            new_user.save()
            current_site = get_current_site(request)
            mail_subject = 'Activate your MAUT account'
            message = render_to_string('registration/acc_active_email.html', {
                'user': new_user,
                'domain': current_site.domain,
                'uid':urlsafe_base64_encode(force_bytes(new_user.pk)),
                'token':account_activation_token.make_token(new_user),
                })
            to_email = form.cleaned_data.get('email')
            email = EmailMessage(
                        mail_subject, message, to=[to_email]
            )
            email.send()

            message = "Thank you for registering. You must confirm your email address before logging in."

            return render(request, 'registration/message.html', {'message' : message})
            '''
            new_user = authenticate(username=form.cleaned_data['username'], password=form.cleaned_data['password1'])
            login(request, new_user)
            return redirect('/profile/home')
            '''
    else:
        form = RegistrationForm()
    return render(request, 'registration/reg_form.html', {'form':form})

def activate(request, uidb64, token):
    try:
        uid = force_text(urlsafe_base64_decode(uidb64))
        user = User.objects.get(pk=uid)
    except(TypeError, ValueError, OverflowError, User.DoesNotExist):
        user = None
    if user is not None and account_activation_token.check_token(user, token):
        user.is_active = True
        user.save()
        login(request, user)
        message = "Thank you for confirming your email address. You may now log in."
    else:
        message = "Your activation link is invalid!"

    return render(request, 'registration/message.html', {'message' : message})

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
    #template = loader.get_template('profile/user_profile.html')
        user = User.objects.get(username=request.user.username)
        profile = UserProfile.objects.get(user=user)
        all_decisions = profile.decide_set.all()
        form = EditProfileForm(instance=request.user)
        pwd = PasswordChangeForm(user=request.user)

        args = {'form': form, 'all_decisions' : all_decisions, 'profile' : profile, 'pwd' : pwd}

        return render(request, 'profile/user_profile.html', args)



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

@login_required()
def deleteDecision(request, pk):
    user = User.objects.get(pk=request.user.pk)
    profile = UserProfile.objects.get(user=user)
    Decide.objects.filter(pk=pk).delete()
    all_decisions = profile.decide_set.all()
    return render(request, 'profile/user_profile.html', { 'all_decisions' : all_decisions})



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
'''
    This function handles the first page of the college decision process.
    The first page is the page that prompts the user for which method of location
    filtering they would like to do. (By ZIP, by State, or by Region)
'''
def college(request):

    if request.method == 'POST':
        locationFilterForm = LocationFilterForm(request.POST)

        if locationFilterForm.is_valid():
            request.session['filter'] = locationFilterForm.cleaned_data['location_filter']
            return HttpResponseRedirect('/college_filter/')
    else:
        locationFilterForm = LocationFilterForm()

    return render(request, 'college/college_index.html', {'locationFilterForm': locationFilterForm})

'''
    This function handles the page for the specific location filtering the user wants.
'''
def college_filter(request):
    if request.method == 'POST':
        if request.session['filter'] == 'zip':
            locationFilter = ZipFilterForm(request.POST)
        elif request.session['filter'] == 'state':
            locationFilter = StateFilterForm(request.POST)
        else:
            locationFilter = RegionFilterForm(request.POST)

        if locationFilter.is_valid():
            decision = CollegeAPI()
            if request.session['filter'] == 'zip':
                location = locationFilter.cleaned_data['zip_code']
                distance = locationFilter.cleaned_data['distance']
                decision.locationFilter(location=location,distance=distance,filter="ZIP")
            elif request.session['filter'] == 'state':
                location = locationFilter.cleaned_data['state']
                decision.locationFilter(location=location,filter="STATE")
            else:
                location = locationFilter.cleaned_data['region']
                decision.locationFilter(location=location,filter="REGION")

            request.session['decision'] = decision

            return HttpResponseRedirect('/college_criteria/')

    else:
        if request.session['filter'] == 'zip':
            locationFilter = ZipFilterForm()
        elif request.session['filter'] == 'state':
            locationFilter = StateFilterForm()
        else:
            locationFilter = RegionFilterForm()


    return render(request, 'college/college_filter.html', {'locationFilter': locationFilter})

def college_criteria(request):
    if request.method == 'POST':
        collegeCriteriaForm = CollegeCriteriaForm(request.POST)

        if collegeCriteriaForm.is_valid():
            '''
            criteria_options is a dictionary that stores key value pairs such that keys
            are the 'variable name' of a criteria option and the valeus are tuples such that
            value[0] = a boolean value, true means the user wants to use that option, false means they don't
            value[1] = the user friendly string of the criteria name
            value[2] = the units of the criteria options
            '''
            criteria_options = {}
            criteria_options['institution_level'] = (collegeCriteriaForm.cleaned_data['institution_level'], "Institution Level", "year(s)")
            criteria_options['out_of_state_tuition'] = (collegeCriteriaForm.cleaned_data['out_of_state_tuition'], "Out of State Tuition", "dollar(s)")
            criteria_options['in_state_tuition'] = (collegeCriteriaForm.cleaned_data['in_state_tuition'], "In State Tuition", "dollar(s)")
            criteria_options['retention_rate'] = (collegeCriteriaForm.cleaned_data['retention_rate'], "Retention Rate", "")
            criteria_options['avg_age'] = (collegeCriteriaForm.cleaned_data['avg_age'], "Average Age", "year(s) old")
            criteria_options['num_students'] = (collegeCriteriaForm.cleaned_data['num_students'], "Number of Students", "student(s)")
            criteria_options['admission_rate'] = (collegeCriteriaForm.cleaned_data['admission_rate'], "Admission Rate", "")

            request.session['decision'].criteriaFilter(criteria_options)

            criteria_list = {}
            for key,value in criteria_options.items():
                if value[0]:
                    criteria_list[key] = (0, value[1], value[2])

            request.session['criteria_list'] = criteria_list

            return HttpResponseRedirect('/college_criteria_weight/')
    else:
        collegeCriteriaForm = CollegeCriteriaForm()

    return render(request, 'college/college_criteria.html', {"collegeCriteriaForm" : collegeCriteriaForm})

def college_criteria_weight(request):
    if request.method == 'POST':
        collegeCriteriaWeightForm = CollegeCriteriaWeightForm(request.POST, criteria_list = request.session['criteria_list'])

        if collegeCriteriaWeightForm.is_valid():
            criteria_dict = request.session['criteria_list']
            criteria_list = []
            for key, value in criteria_dict.items():
                '''
                Criteria list holds 4-tuples representing each criteria options.
                [0] = string holding 'variable' name of criteria options
                [1] = integer representing weight of criteria
                [2] = string holding 'english' name of variable
                [3] = units of the criteria options
                '''
                criteria_list.append((key, collegeCriteriaWeightForm.cleaned_data[key], value[1], value[2]))

            request.session['criteria_list'] = criteria_list

            return HttpResponseRedirect('/college_auto_scores/')
    else:
        collegeCriteriaWeightForm = CollegeCriteriaWeightForm(criteria_list = request.session['criteria_list'])

    return render(request, 'college/college_criteria_weight.html', {"collegeCriteriaWeightForm" : collegeCriteriaWeightForm})

def college_auto_scores(request):
    if request.method=='POST':
        collegeAutoScoreForm = CollegeAutoScoreForm(request.POST, criteria_list = [(i[0],i[2]) for i in request.session['criteria_list']])

        if collegeAutoScoreForm.is_valid():
            criteria_list = []
            for item in request.session['criteria_list']:
                '''
                Criteria list now holds 5-tuples representing each criteria option.
                [0] = string holding 'variable' name of criteria options
                [1] = integer representing weight of criteria
                [2] = string holding 'english' name of variables
                [3] = units of the criteria options
                [4] = auto sorting option. 0 = higher values get higher scores, 1 = higher values get lower scores, 2 = user manually assign values
                '''
                criteria_list.append((item[0],item[1],item[2],item[3],collegeAutoScoreForm.cleaned_data[item[0]]))


            request.session['criteria_list'] = criteria_list

            return HttpResponseRedirect('/college_scores/')

    else:
        collegeAutoScoreForm = CollegeAutoScoreForm(criteria_list = [(i[0],i[2]) for i in request.session['criteria_list']])

    return render(request, 'college/college_auto_scores.html', {"collegeAutoScoreForm" : collegeAutoScoreForm})

def auto_scorer(num,max,min,asc):
    if asc:
        return ((100*(num-min))/(max-min))
    else:
        return((100*(max-num))/(max-min))

def college_scores(request):
    if request.method == 'POST':
        collegeScoreForm = CollegeScoreForm(request.POST,the_option_list=request.session['option_list'])

        if collegeScoreForm.is_valid():
            #The next section of code takes the scores the user inputted and assigns them
            #to any item that fits that score.
            weighted_scores = []
            for i in range(len(request.session['option_list'])):
                weighted_scores.append(((collegeScoreForm.cleaned_data[str(i)])*(request.session['criteria_list'][request.session['remaining']][1]),request.session['option_list'][i][1]))

            colleges = request.session['colleges']

            for key, value in colleges.items():
                for i in range(len(weighted_scores)):
                    if value[1] == weighted_scores[i][1]:
                        new_score = value[2] + weighted_scores[i][0]
                        colleges[key] = (colleges[key][0], colleges[key][1], new_score)

            request.session['colleges'] = colleges

            if request.session['remaining'] > 0:
                cont = True
                while cont and request.session['remaining'] > 0:
                    option_list = []

                    criteria_name = APIT[request.session['criteria_list'][request.session['remaining']-1][0]]
                    real_criteria_name = request.session['criteria_list'][request.session['remaining']-1][2]
                    criteria_units = request.session['criteria_list'][request.session['remaining']-1][3]
                    auto_option = request.session['criteria_list'][request.session['remaining']-1][4]


                    '''
                        Option list stores all the possible values for every criteria.
                        Each college in colleges stores the index of its criteria option in the option list.
                    '''
                    for key, value in colleges.items():
                        if value[0][criteria_name] in option_list:
                            colleges[key] = (colleges[key][0],option_list.index(value[0][criteria_name]),colleges[key][2])
                        else:
                            option_list.append(value[0][criteria_name])
                            colleges[key] = (colleges[key][0],len(option_list) - 1,colleges[key][2])

                    for i in range(0,len(option_list)):
                        option_list[i] = (option_list[i], i)

                    option_list = sorted(option_list, key=lambda x: (x[0] is None, x[0]))

                    if auto_option != 2:
                        min = option_list[0][0]
                        if option_list[-1][0] == None:
                            max = option_list[-2][0]
                        else:
                            max = option_list[-1][0]

                        for i in range(len(option_list)):
                            if option_list[i][0] == None:
                                option_list[i] = (0,option_list[i][1])
                            else:
                                option_list[i] = (auto_scorer(option_list[i][0],max,min,auto_option==0),option_list[i][1])

                        for key, value in colleges.items():
                            for i in range(len(option_list)):
                                if value[1] == option_list[i][1]:
                                    new_score = value[2] + (option_list[i][0]*request.session['criteria_list'][request.session['remaining']-1][1])
                                    colleges[key] = (colleges[key][0], colleges[key][1], new_score)

                        request.session['remaining'] = request.session['remaining'] - 1
                        request.session['colleges'] = colleges

                    else:
                        cont = False
                        request.session['colleges'] = colleges

                        option_list_names = []
                        for option in option_list:
                            option_list_names.append(option[0])

                        collegeScoreForm = CollegeScoreForm(the_option_list=option_list_names)

                if request.session['remaining'] <= 0:
                    return HttpResponseRedirect('/college_results/')


                request.session['colleges'] = colleges
                request.session['option_list'] = option_list
                request.session['remaining'] = request.session['remaining'] - 1

            else:
                return HttpResponseRedirect('/college_results/')

    else:
        request.session['remaining'] = len(request.session['criteria_list'])
        college_info_list = request.session['decision'].pull()

        '''
            colleges is a dictionary with all the college information and their scores.
            The keys are the school names and the values are a tuple:
            college[0] = the json object with all the college information
            college[1] = is the index for the college's score for the current criteria being scored in option_list
            college[2] = the college's current score with the criteria already scored
        '''
        colleges = {}
        for college in college_info_list:
            colleges[college['school.name']] = (college, 0, 0)

        cont = True

        while cont and request.session['remaining'] > 0:
            option_list = []

            criteria_name = APIT[request.session['criteria_list'][request.session['remaining']-1][0]]
            real_criteria_name = request.session['criteria_list'][request.session['remaining']-1][2]
            criteria_units = request.session['criteria_list'][request.session['remaining']-1][3]
            auto_option = request.session['criteria_list'][request.session['remaining']-1][4]


            '''
                Option list stores all the possible values for every criteria.
                Each college in colleges stores the index of its criteria option in the option list.
            '''
            for key, value in colleges.items():
                if value[0][criteria_name] in option_list:
                    colleges[key] = (colleges[key][0],option_list.index(value[0][criteria_name]),colleges[key][2])
                else:
                    option_list.append(value[0][criteria_name])
                    colleges[key] = (colleges[key][0],len(option_list) - 1,colleges[key][2])

            for i in range(0,len(option_list)):
                option_list[i] = (option_list[i], i)

            option_list = sorted(option_list, key=lambda x: (x[0] is None, x[0]))

            if auto_option != 2:
                min = option_list[0][0]
                if option_list[-1][0] == None:
                    max = option_list[-2][0]
                else:
                    max = option_list[-1][0]

                for i in range(len(option_list)):
                    if option_list[i][0] == None:
                        option_list[i] = (0,option_list[i][1])
                    else:
                        option_list[i] = (auto_scorer(option_list[i][0],max,min,auto_option==0),option_list[i][1])

                for key, value in colleges.items():
                    for i in range(len(option_list)):
                        if value[1] == option_list[i][1]:
                            new_score = value[2] + (option_list[i][0]*request.session['criteria_list'][request.session['remaining']-1][1])
                            colleges[key] = (colleges[key][0], colleges[key][1], new_score)

                request.session['remaining'] = request.session['remaining'] - 1
                request.session['colleges'] = colleges
            else:
                cont = False
                request.session['colleges'] = colleges

                option_list_names = []
                for option in option_list:
                    option_list_names.append(option[0])

                collegeScoreForm = CollegeScoreForm(the_option_list=option_list_names)

        if request.session['remaining'] <= 0:
            return HttpResponseRedirect('/college_results/')

        request.session['colleges'] = colleges
        request.session['option_list'] = option_list
        request.session['remaining'] = request.session['remaining'] - 1

    return render(request, 'college/college_scores.html', {"collegeScoreForm" : collegeScoreForm, "criteria_name" : real_criteria_name, "criteria_units" : criteria_units})


def college_results(request):
    if request.method == 'POST':
        user = User.objects.get(username=request.user.username)
        profile = UserProfile.objects.get(user=user)
        newDecision = Decide(user_profile = profile, decisionName = "College")
        newDecision.save()

        collegeList = request.session['colleges']
        criteriaList = request.session['criteria_list']

        for college in collegeList:
            newItem = Item(itemName = college[0], itemScore = college[1], decision = newDecision)
            newItem.save()
        for criteria in criteriaList:
            newCriteria = Criteria(criteriaName = criteria[2], criteriaWeight = criteria[1], decision = newDecision)
            newCriteria.save()

        request.session['saved'] = True

    else:
        request.session['saved'] = False
        collegeList = []

        for key,value in request.session['colleges'].items():
            collegeList.append((key,(value[2]/100)))

        collegeList = sorted(collegeList, key = lambda x: x[1],reverse=True)

        request.session['colleges'] = collegeList

    return render(request, 'college/college_results.html', {"request" : request, "collegeList" : collegeList, "length" : len(collegeList)})
