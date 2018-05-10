from django.conf.urls import url, include
from . import views
from django.conf import settings
from django.conf.urls.static import static
from django.contrib.auth import urls as auth_urls
urlpatterns = [
    #url(r'^index/$', views.cars, name='cars'),
    url(r'^criteria/$', views.cars_criteria, name='cars_criteria'),
    url(r'^criteria_weight/$', views.cars_criteria_weight, name='cars_criteria_weight'),
    url(r'^scores/$', views.cars_scores, name='cars_scores'),
    url(r'^results/$', views.cars_results, name='cars_results'),
    url(r'^auto_scores/$', views.cars_auto_scores, name='cars_auto_scores'),
    url(r'^details/$', views.details, name='recipe_details'),
    url(r'^calculate/$', views.calculate, name='recipe_calculate'),
]
