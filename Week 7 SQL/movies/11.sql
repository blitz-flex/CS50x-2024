-- write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Chadwick Boseman

SELECT title FROm movies, people, ratings, stars
WHERE movies.id = ratings.movie_id
AND people.id = stars.person_id
AND movies.id = stars.movie_id
AND name = 'Chadwick Boseman'
ORDER BY rating DESC LIMIT 5;

