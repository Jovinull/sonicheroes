// bMachineGunBullet's Alive and Move (the PS2 build's names): a bullet is
// alive until its life runs out; Move adds the velocity, moves the collision
// along (its previous position kept, no turn) and enters it, and counts the
// life down. Included by rel/hawk_mgun.inc (inline) and by
// rel/hawk_mgun_bullet.cpp (out of line).

// {0, 0, 0}, the collision's turn. Not const: CalcBullet copies it again for
// every bullet, which the compiler would hoist from a const object.
extern "C" sAngle hawkMGunBulletTurn;

HAWK_MGUN_BULLET_MOVE_INLINE HAWK_MGUN_ALIVE_TYPE bMachineGunBullet::Alive()
{
	return life >= 0;
}

HAWK_MGUN_BULLET_MOVE_INLINE void bMachineGunBullet::Move()
{
	sAngle turn = hawkMGunBulletTurn;

	pos.x += vel.x;
	pos.y += vel.y;
	pos.z += vel.z;
	if (info != NULL) {
		pre_pos      = C_COLLI::pos;
		C_COLLI::pos = pos;
		ang          = turn;
		Entry();
	}
	life--;
}
