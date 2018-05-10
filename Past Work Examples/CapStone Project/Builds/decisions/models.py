
from django.db import models
from django.contrib.auth.models import User
from django.db.models.signals import post_save
from django.dispatch import receiver
from django.core.validators import MaxValueValidator, MinValueValidator

'''
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

'''
    This model saves the user profile. This profile
    has a one to one link with the django User model.
    It is created automatically when a User is created.
'''
genderChoices = (('M','Male'), ('F','Female'), ('Other','Other'), (None,'Prefer not to answer'))
raceChoices = (('American Indian or Alaskan Native', 'American Indian or Alaskan Native'),
                ('Asian', 'Asian'), ('Black or African American','Black or African American'), ('Native Hawaiian or Other Pacific Islander', 'Native Hawaiian or Other Pacific Islander'),
                ('White', 'White'), (None,'Prefer not to answer'))
ethnicityChoices = (('Hispanic or Latino','Hispanic or Latino' ), ('Not Hispanic or Latino', 'Not Hispanic or Latino'),
                    (None,'Prefer not to answer'))

class UserProfile(models.Model):
    user = models.OneToOneField(User, related_name='profile', on_delete=models.CASCADE)
    firstName = models.CharField(max_length=100, default='First')
    lastName = models.CharField(max_length=100, default='Last')
    city = models.CharField(max_length=100, null=True, blank=True)
    state = models.CharField(max_length=100, null=True, blank=True)
    age = models.PositiveIntegerField(validators=[MaxValueValidator(100), MinValueValidator(13)], null=True, blank=True)
    gender = models.CharField(max_length=25,choices=genderChoices, null=True, blank=True)
    income = models.PositiveIntegerField(validators=[MaxValueValidator(1000000000), MinValueValidator(0)], null=True, blank=True)
    race = models.CharField(max_length=50,choices=raceChoices, null=True, blank=True)
    ethnicity = models.CharField(max_length=50,choices=ethnicityChoices, null=True, blank=True)

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