SELECT title FROM 
movies JOIN stars ON movies.id = stars.movie_id JOIN
people ON people.id = stars.person_id
WHERE movies.id IN (SELECT movie_id FROM stars JOIN
people ON stars.person_id = people.id
WHERE name = "Johnny Depp")
AND people.name = "Helena Bonham Carter";
