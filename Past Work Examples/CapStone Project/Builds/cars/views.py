from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from .forms import *
#from .models import UserProfile, Decide, Item, Criteria
from django.shortcuts import render, redirect, render_to_response
from .cars_api import *
from decisions.models import *
# Create your views here.


def cars(request):
    if request.method == 'POST':
        carsSearchForm = CarsSearchForm(request.POST)

        if carsSearchForm.is_valid():
            request.session['decision'] = CarsAPI()

            return HttpResponseRedirect('/recipes/criteria/')

    else:
        carsSearchForm = CarsSearchForm()

    return render(request, 'recipes/index.html', {'carsSearchForm': carsSearchForm} )


def cars_criteria(request):
    if request.method == 'POST':
        carsCriteriaForm = CarsCriteriaForm(request.POST)
        if carsCriteriaForm.is_valid():
            request.session['decision'] = CarsAPI()
            criteria_options = []
            for i in range(len(APIT)):
                if carsCriteriaForm.cleaned_data[str(i)]:
                    criteria_options.append(APIT[i])

            request.session['criteria_list'] = criteria_options

            return HttpResponseRedirect('/recipes/criteria_weight/')
    else:
        carsCriteriaForm = CarsCriteriaForm()

    return render(request, 'cars/cars_criteria.html', {"carsCriteriaForm" : carsCriteriaForm})

def cars_criteria_weight(request):
    if request.method == 'POST':
        carsCriteriaWeightForm = CarsCriteriaWeightForm(request.POST, criteria_list = [i['name'] for i in request.session['criteria_list']])

        if carsCriteriaWeightForm.is_valid():
            criteria_list = request.session['criteria_list']
            for i in range(len(criteria_list)):
                '''
                Criteria list holds 3-tuples representing each criteria options.
                [0] = APIT's dictionary information about the criteria
                [1] = integer representing weight of criteria
                [2] = auto-scoring option
                '''
                criteria_list[i] = (criteria_list[i],carsCriteriaWeightForm.cleaned_data[str(i)],0)

            request.session['criteria_list'] = criteria_list

            return HttpResponseRedirect('/recipes/auto_scores/')
    else:
        carsCriteriaWeightForm = CarsCriteriaWeightForm(criteria_list = [i['name'] for i in request.session['criteria_list']])
    criteriaList = [i['name'].replace(' ','+') for i in request.session['criteria_list']]
    criteriaList = json.dumps(criteriaList).replace(' ','')
    return render(request, 'cars/cars_criteria_weight.html', {"criteriaList" : criteriaList, "weightForm" : carsCriteriaWeightForm})

def cars_auto_scores(request):
    if request.method=='POST':
        carsAutoScoreForm = CarsAutoScoreForm(request.POST, criteria_list = [i[0] for i in request.session['criteria_list']])

        if carsAutoScoreForm.is_valid():
            criteria_list = request.session['criteria_list']
            for i in range(len(criteria_list)):
                criteria_list[i] = (criteria_list[i][0], criteria_list[i][1], carsAutoScoreForm.cleaned_data[str(i)])
            request.session['criteria_list'] = criteria_list

            return HttpResponseRedirect('/recipes/scores/')

    else:
        carsAutoScoreForm = CarsAutoScoreForm(criteria_list = [i[0] for i in request.session['criteria_list']])

    return render(request, 'cars/cars_auto_scores.html', {"carsAutoScoreForm" : carsAutoScoreForm})

def auto_scorer(num,max,min,asc):
    #If max = min then there is only one option and therefore the only option is the best
    if max==min:
        return 100
    if asc:
        return ((100*(num-min))/(max-min))
    else:
        return((100*(max-num))/(max-min))

def auto_scorer_2(actual, ideal, greatest):
    if greatest == 0:
        return 100
    else:
        return (100*(1-(abs(actual-ideal)/greatest)))

def cars_scores(request):
    if request.method == 'POST':
        carsScoreForm = CarsScoreForm(request.POST,the_option_list=request.session['option_list'])

        if carsScoreForm.is_valid():
            #The next section of code takes the scores the user inputted and assigns them
            #to any item that fits that score.
            unweighted_scores = []
            for i in range(len(request.session['option_list'])):
                unweighted_scores.append(((carsScoreForm.cleaned_data[str(i)]),request.session['option_list'][i][1]))
                weight = (request.session['criteria_list'][request.session['remaining']][1])
            carss = request.session['carss']
            if request.session['criteria_list'][request.session['remaining']][0]['is_list']:
                for key, value in carss.items():
                    total = len(value[1])
                    if total==0:
                        total = 1
                    sum_of_options = 0
                    for i in range(len(unweighted_scores)):
                        if unweighted_scores[i][1] in value[1]:
                            sum_of_options = sum_of_options + unweighted_scores[i][0]
                    carss[key][2] = (sum_of_options/total)*weight
                    carss[key][3].append(sum_of_options/total)
            else:
                for key, value in carss.items():
                    for i in range(len(unweighted_scores)):
                        if value[1] == unweighted_scores[i][1]:
                            new_score = value[2] + unweighted_scores[i][0]
                            carss[key][2] = new_score * weight
                            carss[key][3].append(new_score)

            request.session['carss'] = carss

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
                            Each cars in cars stores the index of all its criteria options in the option list.
                        '''
                        for key,value in carss.items():
                            carss[key][1] = []
                            for option in value[0][criteria[0]['api_variable']].split(','):
                                if option != "":
                                    if option in option_list:
                                        carss[key][1] = carss[key][1]+[option_list.index(option)]
                                    else:
                                        option_list.append(option)
                                        carss[key][1] = carss[key][1]+[(len(option_list)-1)]
                    else:
                        '''
                            Option list stores all the possible values for every criteria.
                            Each cars in carss stores the index of its criteria option in the option list.
                        '''
                        for key, value in carss.items():
                            if 'api_variable2' in criteria[0]:
                                if value[0][criteria[0]['api_variable']][criteria[0]['api_variable2']] in option_list:
                                    carss[key][1] = option_list.index(value[0][criteria[0]['api_variable']][criteria[0]['api_variable2']])
                                else:
                                    option_list.append(value[0][criteria[0]['api_variable']][criteria[0]['api_variable2']])
                                    carss[key][1] = len(option_list) - 1
                            else:
                                if value[0][criteria[0]['api_variable']] in option_list:
                                    carss[key][1] = option_list.index(value[0][criteria[0]['api_variable']])
                                else:
                                    option_list.append(value[0][criteria[0]['api_variable']])
                                    carss[key][1] = len(option_list) - 1


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

                        for key, value in carss.items():
                            for i in range(len(option_list)):
                                if value[1] == option_list[i][1]:
                                    new_score = value[2] + (option_list[i][0]*request.session['criteria_list'][request.session['remaining']-1][1])
                                    carss[key][2] = new_score
                                    carss[key][3].append(option_list[i][0])

                        request.session['remaining'] = request.session['remaining'] - 1
                        request.session['carss'] = carss

                    else:
                        cont = False
                        request.session['carss'] = carss

                        option_list_names = []
                        for option in option_list:
                            if criteria[0]["needs_table"]:
                                option_list_names.append(criteria[0]["table"][option[0]])
                            else:
                                option_list_names.append(option[0])

                        carsScoreForm = CarsScoreForm(the_option_list=option_list_names)

                if request.session['remaining'] <= 0:
                    return HttpResponseRedirect('/recipes/results/')


                request.session['carss'] = carss
                request.session['option_list'] = option_list
                request.session['remaining'] = request.session['remaining'] - 1

            else:
                return HttpResponseRedirect('/recipes/results/')

    else:
        request.session['remaining'] = len(request.session['criteria_list'])
        cars_info_list = request.session['decision'].pull()


        '''
            carss is a dictionary with all the cars information and their scores.
            The keys are the school names and the values are a LIST:
            cars[0] = the json object with all the cars information
            cars[1] = is the index for the cars's score for the current criteria being scored in option_list
            cars[2] = the cars's current score with the criteria already scored
            cars[3] = the list of the recipes scores for each criteria
        '''
        carss = {}
        for cars in cars_info_list:
            carss[cars['recipeName']] = [cars, 0, 0, []]

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
            if 'is_list' in criteria[0]:
                '''
                    Option list stores all the possible values for every criteria.
                    Each cars in cars stores the index of all its criteria options in the option list.
                '''
                for key,value in carss.items():
                    carss[key][1] = []
                    for option in value[0][criteria[0]['api_variable']].split(','):
                        if option != "":
                            if option.lstrip() in option_list:
                                carss[key][1] = carss[key][1]+[option_list.index(option.lstrip())]
                            else:
                                option_list.append(option.lstrip())
                                carss[key][1] = carss[key][1]+[(len(option_list)-1)]
            else:
                '''
                    Option list stores all the possible values for every criteria.
                    Each cars in carss stores the index of its criteria option in the option list.
                '''
                for key, value in carss.items():
                    if 'api_variable2' in criteria[0]:
                        if value[0][criteria[0]['api_variable2']][criteria[0]['api_variable']] in option_list:
                            carss[key][1] = option_list.index(value[0][criteria[0]['api_variable2']][criteria[0]['api_variable']])
                        else:
                            option_list.append(value[0][criteria[0]['api_variable2']][criteria[0]['api_variable']])
                            carss[key][1] = len(option_list) - 1
                    else:
                        if value[0][criteria[0]['api_variable']] in option_list:
                            carss[key][1] = option_list.index(value[0][criteria[0]['api_variable']])
                        else:
                            option_list.append(value[0][criteria[0]['api_variable']])
                            carss[key][1] = len(option_list) - 1

            for i in range(0,len(option_list)):
                option_list[i] = (option_list[i], i)

            option_list = sorted(option_list, key=lambda x: (x[0] is None, x[0]))

            if True:
                ideal = int(criteria[2])/100
                greatest = 0
                for i in range(len(option_list)):
                    if abs(option_list[i][0] - ideal) > greatest:
                        greatest = abs(option_list[i][0] - ideal)

                for i in range(len(option_list)):
                    if option_list[i][0] == None:
                        option_list[i] = (0,option_list[i][1])
                    else:
                        option_list[i] = (auto_scorer_2(option_list[i][0],ideal,greatest),option_list[i][1])

                for key, value in carss.items():
                    for i in range(len(option_list)):
                        if value[1] == option_list[i][1]:
                            new_score = value[2] + (option_list[i][0]*request.session['criteria_list'][request.session['remaining']-1][1])
                            carss[key][2] = new_score
                            carss[key][3].append(option_list[i][0])

                request.session['remaining'] = request.session['remaining'] - 1
                request.session['carss'] = carss
            else:
                cont = False
                request.session['carss'] = carss

                option_list_names = []
                for option in option_list:
                    if criteria[0]["needs_table"]:
                        option_list_names.append(criteria[0]["table"][option[0]])
                    else:
                        option_list_names.append(option[0])

                carsScoreForm = CarsScoreForm(the_option_list=option_list_names)

        if request.session['remaining'] <= 0:
            return HttpResponseRedirect('/recipes/results/')

        request.session['carss'] = carss
        request.session['option_list'] = option_list
        request.session['remaining'] = request.session['remaining'] - 1

    if criteria[0]["units"] == "":
        units = ""
    else:
        units = " " + criteria[0]["units"]

    return render(request, 'cars/cars_scores.html', {"carsScoreForm" : carsScoreForm, "criteria_name" : criteria[0]['name'], "criteria_units" : units})

def cars_results(request):
    if request.method == 'POST':
        user = User.objects.get(username=request.user.username)
        profile = UserProfile.objects.get(user=user)
        newDecision = Decide(user_profile = profile, decisionName = "Recipes")
        newDecision.save()

        carsList = request.session['carslist']
        criteriaList = request.session['criteria_list']

        for cars in carsList:
            newItem = Item(itemName = cars[0], itemScore = cars[1], decision = newDecision)
            newItem.save()
        for criteria in criteriaList:
            newCriteria = Criteria(criteriaName = criteria[0]['name'], criteriaWeight = criteria[1], decision = newDecision)
            newCriteria.save()

        request.session['saved'] = True

    else:
        yummly = "www.yummly.com/recipe/"
        request.session['saved'] = False
        carsList = []

        for key,value in request.session['carss'].items():
            carsList.append((key,(round((value[2]/100),2)),yummly+value[0]['id']))

        carsList = sorted(carsList, key = lambda x: x[1],reverse=True)

        request.session['carslist'] = carsList

    the_cars = request.session['carss']
    if 'smallImageUrls' in the_cars[carsList[0][0]][0] and the_cars[carsList[0][0]][0]['smallImageUrls'] != None:
        first_pic = the_cars[carsList[0][0]][0]['smallImageUrls'][0]
    else:
        first_pic = "fail"
    if 'smallImageUrls' in the_cars[carsList[1][0]][0] and the_cars[carsList[1][0]][0]['smallImageUrls'] != None:
        second_pic = the_cars[carsList[1][0]][0]['smallImageUrls'][0]    
    else:
        second_pic = "fail"
    if 'smallImageUrls' in the_cars[carsList[2][0]][0] and the_cars[carsList[2][0]][0]['smallImageUrls'] != None:
        third_pic = the_cars[carsList[2][0]][0]['smallImageUrls'][0]
    else:
        third_pic = "fail"

    recipeDetailForm = RecipeDetailForm()
    return render(request, 'cars/cars_results.html', {"first_pic" : first_pic, "second_pic" : second_pic, "third_pic" : third_pic, "detailForm" : recipeDetailForm, "request" : request, "carsList" : carsList, "length" : len(carsList)})

def details(request):
    if request.method == 'POST':
        recipeDetailForm = RecipeDetailForm(request.POST)
        if recipeDetailForm.is_valid():
            recipe_name = recipeDetailForm.cleaned_data['name']
            recipe_info = request.session['carss'][recipe_name][0]
            recipe_info_list = []
            for item in APIT:
                if item['api_variable'] in recipe_info:
                    if item['needs_table']:
                        info = item['table'][recipe_info[item['api_variable']]]
                        if isinstance(info,float):
                            recipe_info_list.append((item['name'],round(info,2)))
                        else:
                            recipe_info_list.append((item['name'],info))
                    else:
                        info = recipe_info[item['api_variable']]
                        if isinstance(info,float):
                            recipe_info_list.append((item['name'], round(info,2)))
                        else:
                            recipe_info_list.append((item['name'], info))
                elif 'api_variable2' in item and item['api_variable2'] in recipe_info: 
                    info = recipe_info[item['api_variable2']][item['api_variable']]
                    if isinstance(info,float):                               
                        recipe_info_list.append((item['name'],round(info,2)))
                    else:
                        recipe_info_list.append((item['name'], info))

        return render(request, 'college/college_details.html', {"name" : recipe_name, "info" : sorted(recipe_info_list)})
    else:
        return recipe(request)

def calculate(request):
    if request.method == 'POST':
        itemList = []

        for key, value in request.session['carss'].items():
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