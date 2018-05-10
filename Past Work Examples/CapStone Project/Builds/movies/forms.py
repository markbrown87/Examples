from django import forms
from .movies_api import APIT, genre_dict

class MovieGenreForm(forms.Form):
    def __init__(self, *args, **vargs):
        super(MovieGenreForm,self).__init__(*args,**vargs)
        movie_genres = []
        for key, value in genre_dict.items():
            movie_genres.append(key)
        for key in sorted(movie_genres):
            field = forms.BooleanField(label=key,required=False)
            self.fields[key] = field

class MovieCriteriaForm(forms.Form):
	def __init__(self, *args, **vargs):
		super(MovieCriteriaForm,self).__init__(*args,**vargs)
		for i in range(len(APIT)):
			field = forms.BooleanField(label=APIT[i]['name'],required=False)
			self.fields[str(i)] = field

class MovieCriteriaWeightForm(forms.Form):
    def __init__(self, *args, **vargs):
        criteria_list = vargs.pop('criteria_list')
        super(MovieCriteriaWeightForm,self).__init__(*args,**vargs)
        for i in range(len(criteria_list)):
                field = forms.IntegerField(label=criteria_list[i],
                                        widget=forms.HiddenInput(attrs={
                                            'id':('weight_' + str(i))
                                            }))
                self.fields[str(i)] = field


AUTO_CHOICES = [(0, "Higher Values = Better Scores"),(1, "Lower Values = Better Scores")]

class MovieAutoScoreForm(forms.Form):
    def __init__(self, *args, **vargs):
        criteria_list = vargs.pop('criteria_list')
        super(MovieAutoScoreForm,self).__init__(*args,**vargs)
        for i in range(len(criteria_list)):
                field = forms.IntegerField(label=criteria_list[i]['name'],
                                        widget=forms.Select(attrs={'class': 'form-control'},choices=AUTO_CHOICES))
                self.fields[str(i)] = field

class MovieDetailForm(forms.Form):
    name = forms.CharField(widget=forms.HiddenInput(attrs={'id' : 'moviedetails'}))