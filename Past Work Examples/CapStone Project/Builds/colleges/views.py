from django.views.decorators.csrf import ensure_csrf_cookie
from django.http import HttpResponse, HttpResponseRedirect
from .forms import *
#from .models import UserProfile, Decide, Item, Criteria
from django.shortcuts import render, redirect, render_to_response
from .college_api import *
import json
from decisions.models import *

# Create your views here.
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
            return HttpResponseRedirect('/college/filter/')
    else:
        locationFilterForm = LocationFilterForm()

        request.session.pop('saved',None)
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

            return HttpResponseRedirect('/college/criteria/')

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
            criteria_options = []
            for i in range(len(APIT)):
                if collegeCriteriaForm.cleaned_data[str(i)]:
                    criteria_options.append(APIT[i])

            request.session['decision'].criteriaFilter(criteria_options)
            request.session['criteria_list'] = criteria_options

            return HttpResponseRedirect('/college/criteria_weight/')
    else:
        collegeCriteriaForm = CollegeCriteriaForm()

    return render(request, 'college/college_criteria.html', {"collegeCriteriaForm" : collegeCriteriaForm})


def college_criteria_weight(request):
    if request.method == 'POST':
        collegeCriteriaWeightForm = CollegeCriteriaWeightForm(request.POST, criteria_list = [i['name'] for i in request.session['criteria_list']])

        if collegeCriteriaWeightForm.is_valid():
            criteria_list = request.session['criteria_list']
            for i in range(len(criteria_list)):
                '''
                Criteria list holds 3-tuples representing each criteria options.
                [0] = APIT's dictionary information about the criteria
                [1] = integer representing weight of criteria
                [2] = auto-scoring option
                '''
                criteria_list[i] = (criteria_list[i],collegeCriteriaWeightForm.cleaned_data[str(i)],0)
            print([i[1] for i in criteria_list])
            request.session['criteria_list'] = criteria_list

            return HttpResponseRedirect('/college/auto_scores/')
    else:
        collegeCriteriaWeightForm = CollegeCriteriaWeightForm(criteria_list = [i['name'] for i in request.session['criteria_list']])
    criteriaList = [i['name'].replace(' ','+') for i in request.session['criteria_list']]
    criteriaList = json.dumps(criteriaList).replace(' ','')
    return render(request, 'college/college_criteria_weight.html', {"criteriaList" : criteriaList, "weightForm" : collegeCriteriaWeightForm})

def college_auto_scores(request):
    if request.method=='POST':
        collegeAutoScoreForm = CollegeAutoScoreForm(request.POST, criteria_list = [i[0] for i in request.session['criteria_list']])

        if collegeAutoScoreForm.is_valid():
            criteria_list = request.session['criteria_list']
            for i in range(len(criteria_list)):
                criteria_list[i] = (criteria_list[i][0], criteria_list[i][1], collegeAutoScoreForm.cleaned_data[str(i)])

            request.session['criteria_list'] = criteria_list

            return HttpResponseRedirect('/college/scores/')

    else:
        collegeAutoScoreForm = CollegeAutoScoreForm(criteria_list = [i[0] for i in request.session['criteria_list']])

    return render(request, 'college/college_auto_scores.html', {"collegeAutoScoreForm" : collegeAutoScoreForm})

def auto_scorer(num,max,min,asc):
    #If max = min then there is only one option and therefore the only option is the best
    if max==min:
        return 100
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
            unweighted_scores = []
            for i in range(len(request.session['option_list'])):
                unweighted_scores.append(((collegeScoreForm.cleaned_data[str(i)]),request.session['option_list'][i][1]))

            colleges = request.session['colleges']
            weight = (request.session['criteria_list'][request.session['remaining']][1])

            for key, value in colleges.items():
                for i in range(len(unweighted_scores)):
                    if value[1] == unweighted_scores[i][1]:
                        new_score = value[2] + (unweighted_scores[i][0]*weight)
                        colleges[key][2] = new_score
                        colleges[key][3].append(unweighted_scores[i][0])

            request.session['colleges'] = colleges

            if request.session['remaining'] > 0:
                cont = True
                while cont and request.session['remaining'] > 0:
                    option_list = []
                    '''
                    Criteria is a 3-tuple representing a criteria option.
                    [0] = APIT's dictionary information about the criteria
                    [1] = integer representing weight of criteria
                    [2] = auto-scoring option
                    '''
                    criteria = request.session['criteria_list'][request.session['remaining']-1]
                    '''
                        Option list stores all the possible values for every criteria.
                        Each college in colleges stores the index of its criteria option in the option list.
                    '''
                    for key, value in colleges.items():
                        if value[0][criteria[0]['api_variable']] in option_list:
                            colleges[key][1] = option_list.index(value[0][criteria[0]['api_variable']])
                        else:
                            option_list.append(value[0][criteria[0]['api_variable']])
                            colleges[key][1] = len(option_list) - 1

                    for i in range(0,len(option_list)):
                        option_list[i] = (option_list[i], i)

                    option_list = sorted(option_list, key=lambda x: (x[0] is None, x[0]))

                    if criteria[2] != 2:
                        min = option_list[0][0]
                        if option_list[-1][0] == None:
                            max = option_list[-2][0]
                        else:
                            max = option_list[-1][0]

                        for i in range(len(option_list)):
                            if option_list[i][0] == None:
                                option_list[i] = (0,option_list[i][1])
                            else:
                                option_list[i] = (auto_scorer(option_list[i][0],max,min,criteria[2]==0),option_list[i][1])

                        for key, value in colleges.items():
                            for i in range(len(option_list)):
                                if value[1] == option_list[i][1]:
                                    new_score = value[2] + (option_list[i][0]*request.session['criteria_list'][request.session['remaining']-1][1])
                                    colleges[key][2] = new_score
                                    colleges[key][3].append(option_list[i][0])

                        request.session['remaining'] = request.session['remaining'] - 1
                        request.session['colleges'] = colleges

                    else:
                        cont = False
                        request.session['colleges'] = colleges

                        option_list_names = []
                        for option in option_list:
                            if criteria[0]["needs_table"]:
                                option_list_names.append(criteria[0]["table"][option[0]])
                            else:
                                option_list_names.append(option[0])

                        collegeScoreForm = CollegeScoreForm(the_option_list=option_list_names)

                if request.session['remaining'] <= 0:
                    return HttpResponseRedirect('/college/results/')


                request.session['colleges'] = colleges
                request.session['option_list'] = option_list
                request.session['remaining'] = request.session['remaining'] - 1

            else:
                return HttpResponseRedirect('/college/results/')

    else:
        request.session['remaining'] = len(request.session['criteria_list'])
        college_info_list = request.session['decision'].pull()

        '''
            colleges is a dictionary with all the college information and their scores.
            The keys are the school names and the values are a LIST:
            college[0] = the json object with all the college information
            college[1] = is the index for the college's score for the current criteria being scored in option_list
            college[2] = the college's current score with the criteria already scored
            college[3] = their scores for each criteria
        '''
        colleges = {}
        for college in college_info_list:
            colleges[college['school.name']] = [college, 0, 0, []]

        cont = True

        while cont and request.session['remaining'] > 0:
            option_list = []
            '''
            Criteria is a 3-tuple representing a criteria option.
            [0] = APIT's dictionary information about the criteria
            [1] = integer representing weight of criteria
            [2] = auto-scoring option
            '''
            criteria = request.session['criteria_list'][request.session['remaining']-1]

            '''
                Option list stores all the possible values for every criteria.
                Each college in colleges stores the index of its criteria option in the option list.
            '''
            for key, value in colleges.items():
                if value[0][criteria[0]['api_variable']] in option_list:
                    colleges[key][1] = option_list.index(value[0][criteria[0]['api_variable']])
                else:
                    option_list.append(value[0][criteria[0]['api_variable']])
                    colleges[key][1] = len(option_list) - 1

            for i in range(0,len(option_list)):
                option_list[i] = (option_list[i], i)

            option_list = sorted(option_list, key=lambda x: (x[0] is None, x[0]))

            if criteria[2] != 2:
                min = option_list[0][0]
                if option_list[-1][0] == None:
                    max = option_list[-2][0]
                else:
                    max = option_list[-1][0]

                for i in range(len(option_list)):
                    if option_list[i][0] == None:
                        option_list[i] = (0,option_list[i][1])
                    else:
                        option_list[i] = (auto_scorer(option_list[i][0],max,min,criteria[2]==0),option_list[i][1])

                for key, value in colleges.items():
                    for i in range(len(option_list)):
                        if value[1] == option_list[i][1]:
                            new_score = value[2] + (option_list[i][0]*request.session['criteria_list'][request.session['remaining']-1][1])
                            colleges[key][2] = new_score
                            colleges[key][3].append(option_list[i][0])

                request.session['remaining'] = request.session['remaining'] - 1
                request.session['colleges'] = colleges
            else:
                cont = False
                request.session['colleges'] = colleges

                option_list_names = []
                for option in option_list:
                    if criteria[0]["needs_table"]:
                        option_list_names.append(criteria[0]["table"][option[0]])
                    else:
                        option_list_names.append(option[0])

                collegeScoreForm = CollegeScoreForm(the_option_list=option_list_names)

        if request.session['remaining'] <= 0:
            return HttpResponseRedirect('/college/results/')

        request.session['colleges'] = colleges
        request.session['option_list'] = option_list
        request.session['remaining'] = request.session['remaining'] - 1

    if criteria[0]["units"] == "":
        units = ""
    else:
        units = " " + criteria[0]["units"]

    return render(request, 'college/college_scores.html', {"collegeScoreForm" : collegeScoreForm, "criteria_name" : criteria[0]['name'], "criteria_units" : units})


def college_results(request):
    if request.method == 'POST':
        user = User.objects.get(username=request.user.username)
        profile = UserProfile.objects.get(user=user)
        newDecision = Decide(user_profile = profile, decisionName = "College")
        newDecision.save()

        collegeList = request.session['collegeList']
        criteriaList = request.session['criteria_list']

        for college in collegeList:
            newItem = Item(itemName = college[0], itemScore = college[1], decision = newDecision)
            newItem.save()
        for criteria in criteriaList:
            newCriteria = Criteria(criteriaName = criteria[0]['name'], criteriaWeight = criteria[1], decision = newDecision)
            newCriteria.save()

        request.session['saved'] = True

    else:
        request.session['saved'] = False
        collegeList = []

        for key,value in request.session['colleges'].items():
            collegeList.append((key,(round((value[2]/100),2)),value[0]["school.school_url"]))

        collegeList = sorted(collegeList, key = lambda x: x[1],reverse=True)

        request.session['collegeList'] = collegeList

    collegeDetailForm = CollegeDetailForm()
    return render(request, 'college/college_results.html', {"request" : request, "collegeList" : collegeList, "length" : len(collegeList), "detailForm" : collegeDetailForm})

def college_details(request):
    if request.method == 'POST':
        collegeDetailForm = CollegeDetailForm(request.POST)
        if collegeDetailForm.is_valid():
            college_name = collegeDetailForm.cleaned_data['name']
            college_info = request.session['colleges'][college_name][0]
            college_info_list = []
            for item in APIT:
                if item['api_variable'] in college_info:
                    if item['needs_table']:
                        college_info_list.append((item['name'],item['table'][college_info[item['api_variable']]]))
                    else:
                        detail = college_info[item['api_variable']]
                        if isinstance(detail,float):
                            college_info_list.append((item['name'],round(detail,2)))
                        else:
                            college_info_list.append((item['name'],detail))

        return render(request, 'college/college_details.html', {"name" : college_name, "info" : sorted(college_info_list)})
    else:
        return college(request)

def calculate(request):
    if request.method == 'POST':
        itemList = []

        for key, value in request.session['colleges'].items():
            itemList.append(([key]+value))

        itemList.sort(key=lambda x: x[3], reverse = True)

        criteriaList = request.session['criteria_list']

        rows = len(itemList) + 1
        columns = 4 * len(criteriaList) + 3

        #Access an element by matrix[row(items)][column(criteria)]
        matrix = [[0 for x in range(columns)] for y in range(rows)]

        for column in range(columns-3):
            if column%4 == 0:
                matrix[0][column+1] = criteriaList[int(column/4)][0]['name']
            elif column%4 == 1:
                matrix[0][column+1] = ("(" + str(criteriaList[int((column-1)/4)][1]) + "%)")
            else:
                matrix[0][column+1] = ""

        matrix[0][-1] = "Final Scores"
        matrix[0][-2] = ""
        matrix[0][0] = "Items/Criteria"

        for row in range(1,rows):
            matrix[row][0] = itemList[row-1][0] #item name
            matrix[row][-1] = round(itemList[row-1][3]/100,2) #item final score
            matrix[row][-2] = "="
            for column in range(1,columns-2):
                if column%4 == 1:
                    matrix[row][column] = "(" + str(round(itemList[row-1][4][int((column-1)/4)],2))
                elif column%4 == 2:
                    matrix[row][column] = "*"
                elif column%4 == 3:
                    matrix[row][column] = str((criteriaList[int((column-3)/4)][1]/100)) + ")"
                else:
                    if column == columns - 3:
                        matrix[row][column] = ""
                    else:
                        matrix[row][column] = "   +   "

        return render(request,'decisions/decision_calculation.html', {'matrix': matrix, 'request' : request, 'rows' : range(rows), 'columns' : range(columns)})
    else:
        return college(request)