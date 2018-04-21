#pragma once

namespace DancingPlutonium
{
	/* Movement enum encapsulates the 8-direction style possible movements from the WASD (or potentially configurable ULDR) keys */
	enum Movement
	{
		s_noMovement,
		s_north,
		s_northEast,
		s_east,
		s_southEast,
		s_south,
		s_southWest,
		s_west,
		s_northWest,
	};

	/* ProjectilePatterns enum encapsulates the types of projectile PATTERNS that can be found in DancingPlutonium (the advanced bullet patterns) */
	enum ProjectilePattern
	{
		NoBullet,
		BasicShot,
		DoubleShot,
		TripleShot,
		QuadShot,
		AimedShot,
		GrowingShot,
		HomingShot,
		IncendiaryShot,
		PhotonPacket,
		PhotonStream,
		PhotonTriplet,
		PhotonQuartet,
		StandardLazer,
		JoesLazer,
		IMMAFIRINMAHLAZOR,
	};
}