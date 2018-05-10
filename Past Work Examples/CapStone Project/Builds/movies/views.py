from django.views.decorators.csrf import ensure_csrf_cookie
from django.http import HttpResponse, HttpResponseRedirect
from .forms import *
#from .models import UserProfile, Decide, Item, Criteria
from django.shortcuts import render, redirect, render_to_response
from .movies_api import genre_dict, get_movies
from decisions.models import *
import json

def movie_genres(request):
	if request.method == 'POST':
		movieGenreForm = MovieGenreForm(request.POST)
		if movieGenreForm.is_valid():
			genre_list = []
			for genre, genre_id in genre_dict.items():
				if movieGenreForm.cleaned_data[genre]:
					genre_list.append(genre_id)
			request.session['genre_list'] = genre_list
			return HttpResponseRedirect('/movies/criteria/')
	else:
		movieCriteriaForm = MovieGenreForm()
	return render(request, 'movies/movie_genres.html', {'MovieGenreForm' : movieCriteriaForm})




def movie_criteria(request):
	if request.method == 'POST':
		movieCriteriaForm = MovieCriteriaForm(request.POST)
		if movieCriteriaForm.is_valid():
			criteria_options = []
			for i in range(len(APIT)):
				if movieCriteriaForm.cleaned_data[str(i)]:
					criteria_options.append(APIT[i])
			request.session['criteria_list'] = criteria_options
			return HttpResponseRedirect('/movies/criteria_weight/')

	else:
		movieCriteriaForm = MovieCriteriaForm()

	return render(request, 'movies/movie_criteria.html',{'movieCriteriaForm' : movieCriteriaForm})

def movie_criteria_weight(request):
	if request.method == 'POST':
		movieCriteriaWeightForm = MovieCriteriaWeightForm(request.POST, criteria_list = [i['name'] for i in request.session['criteria_list']])
		if movieCriteriaWeightForm.is_valid():
			criteria_list = request.session['criteria_list']
			for i in range(len(criteria_list)):
				criteria_list[i] = (criteria_list[i],movieCriteriaWeightForm.cleaned_data[str(i)],0)
			request.session['criteria_list'] = criteria_list
			print(request.session['criteria_list'])
			return HttpResponseRedirect('/movies/auto_scores/')

	else:
		movieCriteriaWeightForm = MovieCriteriaWeightForm(criteria_list = [i['name'] for i in request.session['criteria_list']])
	criteriaList = [i['name'].replace(' ','+') for i in request.session['criteria_list']]
	criteriaList = json.dumps(criteriaList).replace(' ','')
	return render(request, 'movies/movie_criteria_weight.html', {"criteriaList" : criteriaList, "weightForm" : movieCriteriaWeightForm})

def movie_auto_scores(request):
	if request.method=='POST':
		movieAutoScoreForm = MovieAutoScoreForm(request.POST, criteria_list = [i[0] for i in request.session['criteria_list']])
		if movieAutoScoreForm.is_valid():
			criteria_list = request.session['criteria_list']
			for i in range(len(criteria_list)):
				criteria_list[i] = (criteria_list[i][0], criteria_list[i][1], movieAutoScoreForm.cleaned_data[str(i)])
			request.session['criteria_list'] = criteria_list
			print(request.session['criteria_list'])
			return HttpResponseRedirect('/movies/scores/')
	else:
		movieAutoScoreForm = MovieAutoScoreForm(criteria_list = [i[0] for i in request.session['criteria_list']])
	return render(request, 'movies/movie_auto_scores.html', {"movieAutoScoreForm" : movieAutoScoreForm})

def auto_scorer(num,maximum,minimum,asc):
	if max==min:
		return 100
	if asc:
		return((100*(maximum-num))/(maximum-minimum))
	else:
		return ((100*(num-minimum))/(maximum-minimum))


def movie_scores(request):
	if request.method == 'POST':
		movieList = request.session['movieList']

		user = User.objects.get(username=request.user.username)
		profile = UserProfile.objects.get(user=user)
		newDecision = Decide(user_profile = profile, decisionName = "Movies")
		newDecision.save()

		collegeList = request.session['movieList']
		criteriaList = request.session['criteria_list']

		for movie in movieList:
		    newItem = Item(itemName = movie[0], itemScore = round(movie[1],2), decision = newDecision)
		    newItem.save()
		for criteria in criteriaList:
		    newCriteria = Criteria(criteriaName = criteria[0]['name'], criteriaWeight = criteria[1], decision = newDecision)
		    newCriteria.save()

		request.session['saved'] = True
	else:
		movies = get_movies(request.session['genre_list'])
		criteria_list = request.session['criteria_list']
		for movie in movies:
			movie['criteria'] = []
		for criteria in criteria_list:
			weight = float(criteria[1]/100)
			key = criteria[0]['name']
			maxValue = movies[0][key]
			minValue = movies[0][key]
			for movie in movies:
				if movie[key] > maxValue:
					maxValue = movie[key]
				elif movie[key] < minValue:
					minValue = movie[key]
			for movie in movies:
				raw_score = auto_scorer(movie[key],maxValue,minValue,criteria[2])
				movie['Score'] += weight * raw_score
				movie['criteria'].append(raw_score)
		movieList = []
		movieDict = {}
		for movie in movies:
			movieList.append([movie['Title'], round(movie['Score'],2), movie['Overview'] ])
			movieDict[movie['Title']] = [movie,0,round(movie['Score'],2),movie['criteria']]
		movieList.sort(key=lambda x: x[1], reverse=True)
		request.session['movieList'] = movieList
		request.session['movies'] = movieDict

	movieDetailForm = MovieDetailForm()
	return render(request, 'movies/movie_results.html', {"detailForm" : movieDetailForm, "request" : request, "movieList" : movieList, "length" : len(movieList)})


def movie_details(request):
    if request.method == 'POST':
        movieDetailForm = MovieDetailForm(request.POST)
        if movieDetailForm.is_valid():
            movie_name = movieDetailForm.cleaned_data['name']
            movie_info = request.session['movies'][movie_name][0]
            movie_info_list = []
            movie_info_list.append(('Overview',movie_info['Overview']))
            movie_info_list.append(('TMDb User Score',movie_info['TMDb User Score']))
            movie_info_list.append(('Popularity',movie_info['Popularity']))
            movie_info_list.append(('Year of Release',movie_info['Year of Release']))
        return render(request, 'college/college_details.html', {"name" : movie_name, "info" : sorted(movie_info_list)})
    else:
        return movie_genres(request)

def calculate(request):
    if request.method == 'POST':
        itemList = []

        for key, value in request.session['movies'].items():
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
            matrix[row][-1] = round(itemList[row-1][3],2) #item final score
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