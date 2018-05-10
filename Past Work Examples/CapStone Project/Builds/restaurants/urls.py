from django.conf.urls import url, include
from . import views
from django.conf import settings
from django.conf.urls.static import static
from django.contrib.auth import urls as auth_urls
urlpatterns = [
    url(r'^index/$', views.restaurant, name='restaurant'),
    url(r'^criteria/$', views.criteria, name='criteria'),
    url(r'^criteria_weights/$', views.criteria_weights, name='criteria_weights'),
    url(r'^auto_scores/$', views.auto_scores, name = 'auto_scores'),
    url(r'^scores/$', views.scores, name='scores'),
    url(r'^results/$', views.results, name='results'),
    url(r'^restuarant/$', views.details, name='restaurant_details'),
    url(r'^calculate/$', views.calculate, name='restaurant_calculate'),
]