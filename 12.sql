SELECT title FROM people
JOIN stars on people.id = stars.person_id
JOIN movies on stars.movie_id = movies.id
WHERE name = "Johnny Depp"
INTERSECT
SELECT title FROM people
JOIN stars on people.id = stars.person_id
JOIN movies on stars.movie_id = movies.id
WHERE name = "Helena Bonham Carter";