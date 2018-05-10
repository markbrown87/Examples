from django.conf.urls import url, include
from . import views
from django.conf import settings
from django.conf.urls.static import static
from django.contrib.auth import urls as auth_urls
urlpatterns = [
    url(r'^index/$', views.tutorial, name='tutorial'),
]