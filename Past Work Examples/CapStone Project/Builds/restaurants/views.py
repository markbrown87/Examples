from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from .forms import *
#from .models import UserProfile, Decide, Item, Criteria
from django.shortcuts import render, redirect, render_to_response
from .restaurant_api import *
from decisions.models import *

def restaurant(request):
    if request.method == 'POST':
        zipFilterForm = ZipFilterForm(request.POST)

        if zipFilterForm.is_valid():
            request.session['decision'] = RestaurantAPI()
            request.session['decision'].locationFilter(zipFilterForm.cleaned_data['zip_code'])

            return HttpResponseRedirect('/restaurants/criteria/')

    else:
        zipFilterForm = ZipFilterForm()

    return render(request, 'restaurant/index.html', {'zipFilterForm': zipFilterForm})

def criteria(request):
    if request.method == 'POST':
        restaurantCriteriaForm = RestaurantCriteriaForm(request.POST)

        if restaurantCriteriaForm.is_valid():
            criteria_options = []
            for i in range(len(APIT)):
                if restaurantCriteriaForm.cleaned_data[str(i)]:
                    criteria_options.append(APIT[i])

            request.session['criteria_list'] = criteria_options

            return HttpResponseRedirect('/restaurants/criteria_weights/')

    else:
        restaurantCriteriaForm = RestaurantCriteriaForm()

    return render(request, 'restaurant/criteria.html', {'restaurantCriteriaForm' : restaurantCriteriaForm})

def criteria_weights(request):
    if request.method == 'POST':
        restaurantCriteriaWeightForm = RestaurantCriteriaWeightForm(request.POST,criteria_list = [i['name'] for i in request.session['criteria_list']])

        if restaurantCriteriaWeightForm.is_valid():
            criteria_list = request.session['criteria_list']
            for i in range(len(criteria_list)):
                '''
                Criteria list holds 3-tuples representing each criteria options.
                [0] = APIT's dictionary information about the criteria
                [1] = integer representing weight of criteria
                [2] = auto-scoring option
                '''
                criteria_list[i] = (criteria_list[i],restaurantCriteriaWeightForm.cleaned_data[str(i)],0)

            request.session['criteria_list'] = criteria_list

            return HttpResponseRedirect('/restaurants/auto_scores/')
    else:
        restaurantCriteriaWeightForm = RestaurantCriteriaWeightForm(criteria_list = [i['name'] for i in request.session['criteria_list']])
    criteriaList = [i['name'].replace(' ','+') for i in request.session['criteria_list']]
    criteriaList = json.dumps(criteriaList).replace(' ','')
    return render(request, 'restaurant/criteria_weight.html', {"criteriaList" : criteriaList, "weightForm" : restaurantCriteriaWeightForm})

def auto_scores(request):
    if request.method=='POST':
        restaurantAutoScoreForm = RestaurantAutoScoreForm(request.POST, criteria_list = [i[0] for i in request.session['criteria_list']])

        if restaurantAutoScoreForm.is_valid():
            criteria_list = request.session['criteria_list']
            for i in range(len(criteria_list)):
                criteria_list[i] = (criteria_list[i][0], criteria_list[i][1], restaurantAutoScoreForm.cleaned_data[str(i)])

            request.session['criteria_list'] = criteria_list

            return HttpResponseRedirect('/restaurants/scores/')

    else:
        restaurantAutoScoreForm = RestaurantAutoScoreForm(criteria_list = [i[0] for i in request.session['criteria_list']])

    return render(request, 'restaurant/auto_scores.html', {"restaurantAutoScoreForm" : restaurantAutoScoreForm})

def auto_scorer(num,max,min,asc):
    #If max = min then there is only one option and therefore the only option is the best
    if max==min:
        return 100
    if asc:
        return ((100*(float(num)-float(min)))/(float(max)-float(min)))
    else:
        return((100*(float(max)-float(num)))/(float(max)-float(min)))

def scores(request):
    if request.method == 'POST':
        restaurantScoreForm = RestaurantScoreForm(request.POST,the_option_list=request.session['option_list'])

        if restaurantScoreForm.is_valid():
            #The next section of code takes the scores the user inputted and assigns them
            #to any item that fits that score.
            unweighted_scores = []
            for i in range(len(request.session['option_list'])):
                unweighted_scores.append(((restaurantScoreForm.cleaned_data[str(i)]),request.session['option_list'][i][1]))
                weight = (request.session['criteria_list'][request.session['remaining']][1])

            restaurants = request.session['restaurants']
            if request.session['criteria_list'][request.session['remaining']][0]['is_list']:
                for key, value in restaurants.items():
                    total = len(value[1])
                    if total==0:
                        total = 1
                    sum_of_options = 0
                    for i in range(len(unweighted_scores)):
                        if unweighted_scores[i][1] in value[1]:
                            sum_of_options = sum_of_options + unweighted_scores[i][0]
                    restaurants[key][2] = ((sum_of_options/total)*weight)
                    restaurants[key][3].append(sum_of_options/total)
            else:
                for key, value in restaurants.items():
                    for i in range(len(unweighted_scores)):
                        if value[1] == unweighted_scores[i][1]:
                            new_score = value[2] + unweighted_scores[i][0]
                            restaurants[key][2] = new_score
                            restaurants[key][3].append(unweighted_scores[i][0])

            request.session['restaurants'] = restaurants

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
                        Checks if the return result from the API for the given variable returns a list (encoded as a string)
                    '''
                    if criteria[0]['is_list']:
                        '''
                            Option list stores all the possible values for every criteria.
                            Each restaurant in restaurant stores the index of all its criteria options in the option list.
                        '''
                        for key,value in restaurants.items():
                            restaurants[key] = (restaurants[key][0], [], restaurants[key][2])
                            for option in value[0][criteria[0]['api_variable']].split(','):
                                if option != "":
                                    if option in option_list:
                                        restaurants[key][1] = restaurants[key][1]+[option_list.index(option)]
                                    else:
                                        option_list.append(option)
                                        restaurants[key][1] = restaurants[key][1]+[(len(option_list)-1)]
                    else:
                        '''
                            Option list stores all the possible values for every criteria.
                            Each restaurant in restaurants stores the index of its criteria option in the option list.
                        '''
                        for key, value in restaurants.items():
                            if 'api_variable2' in criteria[0]:
                                if value[0][criteria[0]['api_variable']][criteria[0]['api_variable2']] in option_list:
                                    restaurants[key][1] = option_list.index(value[0][criteria[0]['api_variable']][criteria[0]['api_variable2']])
                                else:
                                    option_list.append(value[0][criteria[0]['api_variable']][criteria[0]['api_variable2']])
                                    restaurants[key][1] = len(option_list) - 1
                            else:
                                if value[0][criteria[0]['api_variable']] in option_list:
                                    restaurants[key][1] = option_list.index(value[0][criteria[0]['api_variable']])
                                else:
                                    option_list.append(value[0][criteria[0]['api_variable']])
                                    restaurants[key][1] = len(option_list) - 1


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

                        for key, value in restaurants.items():
                            for i in range(len(option_list)):
                                if value[1] == option_list[i][1]:
                                    new_score = value[2] + (option_list[i][0]*request.session['criteria_list'][request.session['remaining']-1][1])
                                    restaurants[key][2] = new_score
                                    restaurants[key][3].append(option_list[i][0])

                        request.session['remaining'] = request.session['remaining'] - 1
                        request.session['restaurants'] = restaurants

                    else:
                        cont = False
                        request.session['restaurants'] = restaurants

                        option_list_names = []
                        for option in option_list:
                            if criteria[0]["needs_table"]:
                                option_list_names.append(criteria[0]["table"][option[0]])
                            else:
                                option_list_names.append(option[0])

                        restaurantScoreForm = RestaurantScoreForm(the_option_list=option_list_names)

                if request.session['remaining'] <= 0:
                    return HttpResponseRedirect('/restaurants/results/')


                request.session['restaurants'] = restaurants
                request.session['option_list'] = option_list
                request.session['remaining'] = request.session['remaining'] - 1

            else:
                return HttpResponseRedirect('/restaurants/results/')

    else:
        request.session['remaining'] = len(request.session['criteria_list'])
        restaurant_info_list = request.session['decision'].pull()


        '''
            restaurants is a dictionary with all the restaurant information and their scores.
            The keys are the school names and the values are a LIST:
            restaurant[0] = the json object with all the restaurant information
            restaurant[1] = is the index for the restaurant's score for the current criteria being scored in option_list
            restaurant[2] = the restaurant's current score with the criteria already scored
            restaurant[3] = the restaurant's scores for each criteria
        '''
        restaurants = {}
        for restaurant in restaurant_info_list:
            restaurants[restaurant['restaurant']['name']] = [restaurant['restaurant'], 0, 0,[]]

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
                Checks if the return result from the API for the given variable returns a list (encoded as a string)
            '''
            if criteria[0]['is_list']:
                '''
                    Option list stores all the possible values for every criteria.
                    Each restaurant in restaurant stores the index of all its criteria options in the option list.
                '''
                for key,value in restaurants.items():
                    restaurants[key][1] = []
                    for option in value[0][criteria[0]['api_variable']].split(','):
                        if option != "":
                            if option.lstrip() in option_list:
                                restaurants[key][1] = restaurants[key][1]+[option_list.index(option.lstrip())]
                            else:
                                option_list.append(option.lstrip())
                                restaurants[key][1] = restaurants[key][1]+[(len(option_list)-1)]
            else:
                '''
                    Option list stores all the possible values for every criteria.
                    Each restaurant in restaurants stores the index of its criteria option in the option list.
                '''
                for key, value in restaurants.items():
                    if 'api_variable2' in criteria[0]:
                        if value[0][criteria[0]['api_variable']][criteria[0]['api_variable2']] in option_list:
                            restaurants[key][1]= option_list.index(value[0][criteria[0]['api_variable']][criteria[0]['api_variable2']])
                        else:
                            option_list.append(value[0][criteria[0]['api_variable']][criteria[0]['api_variable2']])
                            restaurants[key][1] = len(option_list) - 1
                    else:
                        if value[0][criteria[0]['api_variable']] in option_list:
                            restaurants[key][1] = option_list.index(value[0][criteria[0]['api_variable']])
                        else:
                            option_list.append(value[0][criteria[0]['api_variable']])
                            restaurants[key][1] = len(option_list) - 1

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

                for key, value in restaurants.items():
                    for i in range(len(option_list)):
                        if value[1] == option_list[i][1]:
                            new_score = value[2] + (option_list[i][0]*request.session['criteria_list'][request.session['remaining']-1][1])
                            restaurants[key][2] = new_score
                            restaurants[key][3].append(option_list[i][0])


                request.session['remaining'] = request.session['remaining'] - 1
                request.session['restaurants'] = restaurants
            else:
                cont = False
                request.session['restaurants'] = restaurants

                option_list_names = []
                for option in option_list:
                    if criteria[0]["needs_table"]:
                        option_list_names.append(criteria[0]["table"][option[0]])
                    else:
                        option_list_names.append(option[0])

                restaurantScoreForm = RestaurantScoreForm(the_option_list=option_list_names)

        if request.session['remaining'] <= 0:
            return HttpResponseRedirect('/restaurants/results/')

        request.session['restaurants'] = restaurants
        request.session['option_list'] = option_list
        request.session['remaining'] = request.session['remaining'] - 1

    if criteria[0]["units"] == "":
        units = ""
    else:
        units = " " + criteria[0]["units"]

    return render(request, 'restaurant/restaurant_scores.html', {"restaurantScoreForm" : restaurantScoreForm, "criteria_name" : criteria[0]['name'], "criteria_units" : units})

def results(request):
    if request.method == 'POST':
        user = User.objects.get(username=request.user.username)
        profile = UserProfile.objects.get(user=user)
        newDecision = Decide(user_profile = profile, decisionName = "restaurant")
        newDecision.save()

        restaurantList = request.session['restaurantlist']
        criteriaList = request.session['criteria_list']

        for restaurant in restaurantList:
            newItem = Item(itemName = restaurant[0], itemScore = restaurant[1], decision = newDecision)
            newItem.save()
        for criteria in criteriaList:
            newCriteria = Criteria(criteriaName = criteria[0]['name'], criteriaWeight = criteria[1], decision = newDecision)
            newCriteria.save()

        request.session['saved'] = True

    else:
        request.session['saved'] = False
        restaurantList = []

        for key,value in request.session['restaurants'].items():
            restaurantList.append((key,(round((value[2]/100),2))))

        restaurantList = sorted(restaurantList, key = lambda x: x[1],reverse=True)

        request.session['restaurantlist'] = restaurantList

    restaurantDetailForm = RestaurantDetailForm()
    return render(request, 'restaurant/results.html', {"detailForm" : restaurantDetailForm, "request" : request, "restaurantList" : restaurantList, "length" : len(restaurantList)})

def details(request):
    if request.method == 'POST':
        restaurantDetailForm = RestaurantDetailForm(request.POST)
        if restaurantDetailForm.is_valid():
            restaurant_name = restaurantDetailForm.cleaned_data['name']
            restaurant_info = request.session['restaurants'][restaurant_name][0]
            restaurant_info_list = []
            for item in APIT:
                if item['api_variable'] in restaurant_info:
                    if item['needs_table']:
                        restaurant_info_list.append((item['name'],item['table'][restaurant_info[item['api_variable']]]))
                    elif 'api_variable2' in item:
                        restaurant_info_list.append((item['name'],restaurant_info[item['api_variable']][item['api_variable2']]))
                    else:
                        restaurant_info_list.append((item['name'],restaurant_info[item['api_variable']]))
                        
        return render(request, 'college/college_details.html', {"name" : restaurant_name, "info" : sorted(restaurant_info_list)})
    else:
        return restaurant(request)

def calculate(request):
    if request.method == 'POST':
        itemList = []

        for key, value in request.session['restaurants'].items():
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