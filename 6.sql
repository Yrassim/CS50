SELECT avg(rating) as "2012_rate_avg"
FROM ratings JOIN movies on ratings.movie_id = movies.id
WHERE year = 2012;