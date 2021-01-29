SELECT movies.title, ratings.rating
FROM ratings JOIN movies on ratings.movie_id = movies.id
WHERE year = 2010
ORDER by rating DESC, title;