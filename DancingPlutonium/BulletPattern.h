#pragma once

class BulletPattern
{
public:
	enum Angle
	{
		s_uninitialized,
		s_10Degree,
		s_15Degree,
		s_20Degree,
		s_30Degree,
		s_40Degree,
		s_45Degree,
		s_50Degree,
		s_60Degree,
		s_70Degree,
		s_75Degree,
		s_80Degree,
		s_90Degree,
		s_100Degree,
		s_105Degree,
		s_110Degree,
		s_120Degree,
		s_130Degree,
		s_135Degree,
		s_140Degree,
		s_150Degree,
		s_160Degree,
		s_165Degree,
		s_170Degree,
		s_180Degree,
		s_190Degree,
		s_195Degree,
		s_200Degree,
		s_210Degree,
		s_220Degree,
		s_225Degree,
		s_230Degree,
		s_240Degree,
		s_250Degree,
		s_260Degree,
		s_265Degree,
		s_270Degree,
		s_280Degree,
		s_290Degree,
		s_295Degree,
		s_300Degree,
		s_310Degree,
		s_320Degree,
		s_325Degree,
		s_330Degree,
		s_340Degree,
		s_350Degree,
		s_355Degree
	};

public:
	enum Pattern
	{
		s_noPattern,
		s_every10DegreeAngle,
		s_every15DegreeAngle,
		s_every20DegreeAngle,
		s_every30DegreeAngle,
		s_every45DegreeAngle,
		s_every60DegreeAngle,
		s_every90DegreeAngle,
		s_enemyStandard,
		s_playerStandard,
		s_enemyDouble,
		s_playerDouble,
		s_enemyTriple,
		s_playerTriple,
		s_enemyQuad,
		s_playerQuad,
		s_enemyCorkScrew,
		s_enemyHoming,
		s_playerHoming,
		s_enemyExpanding
	};

public:
	enum Source
	{
		s_enemy,
		s_player
	};

};