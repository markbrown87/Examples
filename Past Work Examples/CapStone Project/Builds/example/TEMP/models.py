from django.db import models
from django.contrib.auth.models import User
from django.db.models.signals import post_save
from django.dispatch import receiver

class Decide(models.Model):
    decisionName = models.CharField(max_length=100, default='')

    def __str__(self):
        return self.decisionName

class Criteria(models.Model):
    criteriaName = models.CharField(max_length=100, default='')
    criteriaWeight = models.IntegerField(default=0)
    decision = models.ForeignKey(Decide, on_delete=models.CASCADE)

    def __str__(self):
        return self.criteriaName

class Item(models.Model):
    itemName = models.CharField(max_length=100,default='')
    itemScore = models.IntegerField(default=0)
    decision = models.ForeignKey(Decide, on_delete=models.CASCADE)

    def __str__(self):
        return self.itemName

'''
    This model saves the user profile. This profile
    has a one to one link with the django User model.
    It is created automatically when a User is created.
'''
class UserProfile(models.Model):
    user = models.OneToOneField(User, related_name='profile', on_delete=models.CASCADE)
    firstName = models.CharField(max_length=100, default='First name')
    lastName = models.CharField(max_length=100, default='Last name')
    city = models.CharField(max_length=100, default='City')
    state = models.CharField(max_length=100, default='State')
    #avatar = models.ImageField(upload_to='img/')
    email = models.EmailField(max_length=128)

    def __str__(self):
        return self.user.username


def create_profile(sender, **kwargs):
    if kwargs['created']:
        user_profile = UserProfile.objects.create(user=kwargs['instance'])
post_save.connect(create_profile, sender=User)

class Decide(models.Model):
    decisionName = models.CharField(max_length=100, default='')
    user_profile = models.ForeignKey(UserProfile, on_delete=models.CASCADE)

    def __str__(self):
        return self.decisionName

class Criteria(models.Model):
    criteriaName = models.CharField(max_length=100, default='')
    criteriaWeight = models.IntegerField(default=0)
    decision = models.ForeignKey(Decide, on_delete=models.CASCADE,related_name='criteria')

    def __str__(self):
        return self.criteriaName + " " + str(self.criteriaWeight)

class Item(models.Model):
    itemName = models.CharField(max_length=100,default='')
    itemScore = models.IntegerField(default=0)
    decision = models.ForeignKey(Decide, on_delete=models.CASCADE,related_name='item')

    def __str__(self):
        return self.itemName + " " + str(self.itemScore)

'''
    This function creates a UserProfile model. that has a one
    to one link with a User model. This is automatically done
    when a new User is created.
'''
def create_profile(sender, **kwags):
    if kwags['created']:
        user_profile = UserProfile.objects.create(user=kwags['instance'])

post_save.connect(create_profile, sender=User) # signal to call create profile when User is created
