from tmdbv3api import TMDb, Discover

user = TMDb()
user.api_key = 'fafd60cac475460a4bfc030ff2ac0db4'
discover = Discover()

APIT = [ 
{'name' : 'Year of Release', 'is_num' : True},
{'name' : 'TMDb User Score', 'is_num' : True},
{'name' : 'Popularity', 'is_num' : True}]

genre_dict = {'Action' : "28",
              'Adventure' : "12",
              'Animation' : "16",
              'Comedy' : "35",
              'Crime' : "80",
              'Documentary' : "99",
              'Drama' : "18",
              'Family' : "10751",
              'Fantasy' : "14",
              'History' : "36",
              'Horror' : "27",
              'Musical' : "10402",
              'Mystery' : "9648",
              'Romance' : "10749",
              'Science Fiction' : "878",
              'Thriller' : "53",
              'War' : "10752",
              'Western' : "37"
             }

def get_movies(genres=None):
	query = {'sort_by' : 'popularity.desc', 'include_adult' : 'false', 'page' : '1'}
	movie_dict = {}
	movies = []
	if genres is not None:
		query['with_genres'] = ''
		for genre in genres:
			query['with_genres'] += genre + '|'
	for i in range(1,11):
		query['page'] = str(i)
		movie_query = discover.discover_movies(query)
		for movie in movie_query:
			movie_dict['Title'] = movie.title
			movie_dict['Year of Release'] = int(movie.release_date[0:4])
			movie_dict['TMDb User Score'] = int(movie.vote_average)
			movie_dict['Popularity'] = int(movie.popularity)
			movie_dict['Overview'] = movie.overview
			movie_dict['Score'] = 0
			movies.append(movie_dict.copy())
	return movies

