from django.conf.urls import url, include
from . import views
from django.conf import settings
from django.conf.urls.static import static
from django.contrib.auth import urls as auth_urls
urlpatterns = [
    url(r'^index/$', views.college, name='college'),
    url(r'^filter/$', views.college_filter, name='college_filter'),
    url(r'^criteria/$', views.college_criteria, name='college_criteria'),
    url(r'^criteria_weight/$', views.college_criteria_weight, name='college_criteria_weight'),
    url(r'^scores/$', views.college_scores, name='college_scores'),
    url(r'^results/$', views.college_results, name='college_results'),
    url(r'^auto_scores/$', views.college_auto_scores, name='college_auto_scores'),
    url(r'^details/$',views.college_details, name='college_details'),
    url(r'^calculate/$', views.calculate, name='college_calculate'),
]
