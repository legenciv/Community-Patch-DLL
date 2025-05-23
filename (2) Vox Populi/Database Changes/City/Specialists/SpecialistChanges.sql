-- Base yields
UPDATE SpecialistYields SET Yield = 1 WHERE SpecialistType = 'SPECIALIST_CITIZEN';

UPDATE Specialists
SET
	CulturePerTurn = 3,
	IconAtlas = 'SPECIALIST_ATLAS_VP',
	PortraitIndex = 0
WHERE Type = 'SPECIALIST_WRITER';

UPDATE Specialists
SET CulturePerTurn = 3
WHERE Type = 'SPECIALIST_ARTIST';

UPDATE Specialists
SET
	CulturePerTurn = 5,
	IconAtlas = 'SPECIALIST_ATLAS_VP',
	PortraitIndex = 1
WHERE Type = 'SPECIALIST_MUSICIAN';

UPDATE SpecialistYields SET Yield = 3 WHERE SpecialistType = 'SPECIALIST_SCIENTIST';

UPDATE SpecialistYields SET Yield = 4 WHERE SpecialistType = 'SPECIALIST_MERCHANT';

UPDATE SpecialistYields SET Yield = 4 WHERE SpecialistType = 'SPECIALIST_ENGINEER';

UPDATE Specialists SET CulturePerTurn = 1 WHERE Type = 'SPECIALIST_CIVIL_SERVANT';
INSERT INTO SpecialistYields
	(SpecialistType, YieldType, Yield)
VALUES
	('SPECIALIST_CIVIL_SERVANT', 'YIELD_GOLD', 2),
	('SPECIALIST_CIVIL_SERVANT', 'YIELD_SCIENCE', 2);

-- Tech boosts
INSERT INTO Tech_SpecialistYieldChanges
	(TechType, SpecialistType, YieldType, Yield)
VALUES
	('TECH_CIVIL_SERVICE', 'SPECIALIST_CITIZEN', 'YIELD_GOLD', 1),
	('TECH_FERTILIZER', 'SPECIALIST_CITIZEN', 'YIELD_PRODUCTION', 2),
	('TECH_INDUSTRIALIZATION', 'SPECIALIST_CITIZEN', 'YIELD_GOLD', 1),
	('TECH_PRINTING_PRESS', 'SPECIALIST_WRITER', 'YIELD_CULTURE', 1),
	('TECH_MILITARY_SCIENCE', 'SPECIALIST_WRITER', 'YIELD_CULTURE', 1),
	('TECH_INTERNET', 'SPECIALIST_WRITER', 'YIELD_CULTURE', 2),
	('TECH_ARCHITECTURE', 'SPECIALIST_ARTIST', 'YIELD_CULTURE', 1),
	('TECH_PLASTIC', 'SPECIALIST_ARTIST', 'YIELD_CULTURE', 1),
	('TECH_COMPUTERS', 'SPECIALIST_ARTIST', 'YIELD_CULTURE', 1),
	('TECH_RADIO', 'SPECIALIST_MUSICIAN', 'YIELD_CULTURE', 2),
	('TECH_TELECOM', 'SPECIALIST_MUSICIAN', 'YIELD_CULTURE', 2),
	('TECH_ENGINEERING', 'SPECIALIST_ENGINEER', 'YIELD_PRODUCTION', 1),
	('TECH_METAL_CASTING', 'SPECIALIST_ENGINEER', 'YIELD_PRODUCTION', 1),
	('TECH_MACHINERY', 'SPECIALIST_ENGINEER', 'YIELD_PRODUCTION', 1),
	('TECH_INDUSTRIALIZATION', 'SPECIALIST_ENGINEER', 'YIELD_PRODUCTION', 2),
	('TECH_BALLISTICS', 'SPECIALIST_ENGINEER', 'YIELD_PRODUCTION', 1),
	('TECH_LASERS', 'SPECIALIST_ENGINEER', 'YIELD_PRODUCTION', 3),
	('TECH_CURRENCY', 'SPECIALIST_MERCHANT', 'YIELD_GOLD', 1),
	('TECH_GUILDS', 'SPECIALIST_MERCHANT', 'YIELD_GOLD', 1),
	('TECH_ECONOMICS', 'SPECIALIST_MERCHANT', 'YIELD_GOLD', 2),
	('TECH_CORPORATIONS', 'SPECIALIST_MERCHANT', 'YIELD_GOLD', 2),
	('TECH_INTERNET', 'SPECIALIST_MERCHANT', 'YIELD_GOLD', 3),
	('TECH_ASTRONOMY', 'SPECIALIST_SCIENTIST', 'YIELD_SCIENCE', 1),
	('TECH_SCIENTIFIC_THEORY', 'SPECIALIST_SCIENTIST', 'YIELD_SCIENCE', 1),
	('TECH_PENICILIN', 'SPECIALIST_SCIENTIST', 'YIELD_SCIENCE', 1),
	('TECH_NUCLEAR_FUSION', 'SPECIALIST_SCIENTIST', 'YIELD_SCIENCE', 3),
	('TECH_NAVIGATION', 'SPECIALIST_CIVIL_SERVANT', 'YIELD_GOLD', 1),
	('TECH_REPLACEABLE_PARTS', 'SPECIALIST_CIVIL_SERVANT', 'YIELD_SCIENCE', 1),
	('TECH_INTERNET', 'SPECIALIST_CIVIL_SERVANT', 'YIELD_CULTURE', 1);
