-- Reorder concepts
UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_HAPPINESS',
	InsertBefore = 'CONCEPT_HAPPINESS_LOCAL_HAPPINESS'
WHERE Type = 'CONCEPT_HAPPINESS_CAUSES_HAPPINESS';

UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_HAPPINESS_LOCAL_HAPPINESS',
	InsertBefore = 'CONCEPT_HAPPINESS_NEED_THRESHOLDS'
WHERE Type = 'CONCEPT_HAPPINESS_CAUSES_UNHAPPINESS';

UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_MOVING_GREAT_PEOPLE',
	InsertBefore = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_ARTIST'
WHERE Type = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_WRITER';

UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_WRITER',
	InsertBefore = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_ENGINEER'
WHERE Type = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_ARTIST';

UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_ARTIST',
	InsertBefore = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_MUSICIAN'
WHERE Type = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_ENGINEER';

UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_ENGINEER',
	InsertBefore = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_SCIENTIST'
WHERE Type = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_MUSICIAN';

UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_MUSICIAN',
	InsertBefore = 'CONCEPT_GREAT_PROPHET'
WHERE Type = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_SCIENTIST';

UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_SCIENTIST',
	InsertBefore = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_GENERAL'
WHERE Type = 'CONCEPT_GREAT_PROPHET';

UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_GREAT_PROPHET',
	InsertBefore = 'CONCEPT_GREAT_ADMIRAL'
WHERE Type = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_GENERAL';

UPDATE Concepts
SET
	InsertAfter = 'CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_GREAT_GENERAL',
	InsertBefore = 'CONCEPT_GREAT_DIPLOMAT'
WHERE Type = 'CONCEPT_GREAT_ADMIRAL';

-- Delete concepts
CREATE TEMP TABLE ConceptNukes (
	Concept TEXT
);

INSERT INTO ConceptNukes
VALUES
	('CONCEPT_HAPPINESS_STARTING'),
	('CONCEPT_HAPPINESS_HAPPINESS_LEVELS'),
	('CONCEPT_HAPPINESS_UNHAHPPY'),
	('CONCEPT_HAPPINESS_VERY_UNHAPPY'),
	('CONCEPT_HAPPINESS_REVOLT'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_CUSTOMS_HOUSE'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_TRADE_MISSION'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_MANUFACTORY'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_HURRY_PRODUCTION'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_ACADEMY'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_LEARN_NEW_TECH'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_MUSICIAN_CREATEGW'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_CONCERT_TOUR'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_ART_CREATEGW'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_CULTURE_BOMB'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_WRITER_CREATEGW'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_TREATISE'),
	('CONCEPT_GREAT_ADMIRAL_ABILITY'),
	('CONCEPT_GREAT_ADMIRAL_ABILITY2'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_CITADEL'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_COMBAT_BONUS'),
	('CONCEPT_GREAT_PROPHET_IMPROVEMENT'),
	('CONCEPT_GREAT_PROPHET_ABILITY'),
	('CONCEPT_SPECIALISTS_AND_GREAT_PEOPLE_GREAT_PEOPLE_LANDMARK');

DELETE FROM Concepts_RelatedConcept
WHERE ConceptType IN (SELECT Concept FROM ConceptNukes)
OR RelatedConcept IN (SELECT Concept FROM ConceptNukes);

DELETE FROM Concepts
WHERE Type IN (SELECT Concept FROM ConceptNukes);

DROP TABLE ConceptNukes;
