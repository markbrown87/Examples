from django.conf.urls import url, include
from . import views
from django.conf import settings
from django.conf.urls.static import static
from django.contrib.auth import urls as auth_urls
urlpatterns = [
	url(r'^genres/$', views.movie_genres, name='movie_genres'),
    url(r'^criteria/$', views.movie_criteria, name='movie_criteria'),
    url(r'^criteria_weight/$', views.movie_criteria_weight, name='criteria_weight'),
    url(r'^auto_scores/$', views.movie_auto_scores, name='movie_auto_scores'),
    url(r'^scores/$', views.movie_scores, name='movie_scores'),
    url(r'^details/$', views.movie_details, name='movie_details'),
    url(r'^calculate/$', views.calculate, name='movie_calculate'),
    #url(r'^results/$', views.movie_results, name='movie_results'),
]