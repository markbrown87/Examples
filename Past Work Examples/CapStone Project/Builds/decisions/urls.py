
from django.conf.urls import url, include
from . import views
from django.conf import settings
from django.conf.urls.static import static
from django.contrib.auth import urls as auth_urls
urlpatterns = [
    url(r'^$', views.example, name='home'),
    url(r'^$', views.example, name='front'),
	url(r'^index/$', views.index, name ='index'),
    url(r'^custom/$',views.decision_index,name='custom'),
    url(r'^results/$', views.results, name = 'results'),
    url(r'^items/$', views.items, name = 'items'),
    #url(r'^$', views.base, name= 'home'),
    url(r'', include(auth_urls)),
    url(r'^register/$', views.register, name = 'register'),
    url(r'^profile/home/$', views.userLogin, name='userHome'),
    url(r'^profile/decision/$', views.index, name='UserDecisionView'),
    url(r'^profile/results/$', views.userResults, name='userResults'),
	url(r'^profile/updateprofile', views.updateProfile, name='updateProfile'),
    url(r'^profile/disable', views.disableProfile, name='disableProfile'),
    url(r'^criteria/$',views.criteria,name='criteria'),
    url(r'^scores/$',views.scores,name='scores'),
    url(r'^api/$', views.carQuery, name='carQuery'),
    url(r'^contact/$', views.contact, name='contact'),
    url(r'^calculation/$', views.calculation, name='calculation'),
    url(r'^profile/(?P<pk>[0-9]+)/update', views.updateDecision, name='updateDecision'),
    url(r'^profile/(?P<pk>[0-9]+)/delete', views.deleteDecision, name='deleteDecision'),
    url(r'^criteria_weight/$', views.criteria_weight, name='criteriaWeight'),
    url(r'^profile/(?P<pk>[0-9]+)/(?P<name>([^\/]+))/rename', views.renameDecision, name='renameDecision')
    #url(r'^activate/(?P<uidb64>[0-9A-Za-z_\-]+)/(?P<token>[0-9A-Za-z]{1,13}-[0-9A-Za-z]{1,20})/$', views.activate, name='activate'),
]
