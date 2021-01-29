SELECT DISTINCT name FROM people
JOIN stars on people.id = stars.person_id
JOIN movies on stars.movie_id = movies.id
WHERE movie_id IN
(SELECT movie_id FROM people
JOIN stars on people.id = stars.person_id
JOIN movies on stars.movie_id = movies.id
WHERE birth = 1958 AND name = "Kevin Bacon")
AND name != "Kevin Bacon";
