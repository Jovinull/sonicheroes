#include "game/pathctrl.h"

// GameCube external object views: named fields follow metadata where corroborated;
// unnamed gaps and field offsets describe only the observed GameCube layout.
typedef struct TASKWK {
	s16 mode, modeLast, smode, flag;
	u16 wtimer;
	u8 padA[2];
	sAngle ang;
	RwV3d pos, scl;
} TASKWK;
typedef struct POSITION_REF {
	u8 pad0[8];
	RwV3d pos;
} POSITION_REF;
typedef struct TObjOldPlayer {
	u8 pad0[0x38];
	POSITION_REF* positionSource;
	u8 pad3C[0x6F0 - 0x3C];
	TASKWK task;
	u8 pad720[0x9E7 - 0x720];
	s8 field9E7;
} TObjOldPlayer;
typedef struct PLAYERWK {
	u8 pad0[0x14];
	s16 nocontimer;
	u8 pad16[0x60 - 0x16];
	RwV3d spd;
	u8 pad6C[0xC4 - 0x6C];
	PATHTAG* pathtag;
} PLAYERWK;
typedef struct MOTIONWK {
	RwV3d spd, acc;
	sAngle ang_aim, ang_spd;
	s32 ang_shoulder;
	u32 reserve[3];
} MOTIONWK;
typedef struct TObjTeam {
	u8 pad0[0x110];
	s8 playerNo[3];
	u8 pad113[0x1FC - 0x113];
	s16 field1FC;
} TObjTeam;
typedef struct PATHINFO {
	s32 slangx, slangz, slangax, slangaz;
	f32 onpathpos;
	RwV3d pos, normal, normala, front;
} PATHINFO;
typedef struct TObjPathManage {
	u8 object[0x28];
	PATHTAG** tagTblTopPtr;
	CLASS_PATH* pPath;
	NJS_LINE l_pl_Temp[8];
	RwV3d pos_pl_Last[8], diff_pl_Temp[8], dir_pl_Temp[8];
	f32 dist_pl_Temp[8];
} TObjPathManage;

extern "C" {
extern TObjOldPlayer* lbl_802AD070[8];
extern TASKWK* lbl_802AD090[8];
extern MOTIONWK* lbl_802AD0B0[8];
extern PLAYERWK* lbl_802AD0D0[8];
extern TObjTeam* lbl_80303DC8[4];
extern TObjPathManage* lbl_8042C380;
extern RwV3d lbl_80242B38;

f32 fn_800AEF48(PATHTAG*, RwV3d*, RwV3d*, f32*, f32);
s32 fn_800AF2E4(PATHTAG*, s32*, f32);
s32 fn_800AF3AC(PATHTAG*, PATHINFO*);
s32 fn_800DFD08(u8, PATHTAG*);
s32 fn_800DFB88(u8, PATHTAG*);
s32 fn_800DFA68(s32, PATHTAG*, f32);
void fn_800DF9F0(s32, PATHTAG*, f32);
void fn_8003E9B4(TASKWK*, RwV3d*);
f32 fn_800D7218(RwV3d*, RwV3d*);
f32 fn_800D7044(RwV3d*, NJS_LINE*, RwV3d*);
f32 fn_800D605C(NJS_LINE*, NJS_LINE*, RwV3d*, RwV3d*);
s32 fn_800927D0(TObjTeam*, s32);
s32 fn_800892B0(TObjOldPlayer*);
s32 fn_800E27D8(TASKWK*, PLAYERWK*, s32, s32);
void fn_801990E0(RwV3d*, RwV3d*);
f32 fn_801991B4(RwV3d*);

s32 lbl_80253648[3] = { 0, 1, 2 };
}
static void pathGlidingReg(CLASS_PATH*);

static inline void pathCalcRoughArea(CLASS_PATH* pathwp)
{
	PATHTAG* pttp    = pathwp->tagptr;
	PATHTBL_P* ppp   = pttp->pathtbl;
	pathwp->minpos.x = pathwp->maxpos.x = ppp->pos.x;
	pathwp->minpos.y = pathwp->maxpos.y = ppp->pos.y;
	pathwp->minpos.z = pathwp->maxpos.z = ppp->pos.z;
	for (s32 i = 0; i < pttp->points; ++ppp, ++i) {
		if (ppp->pos.x > pathwp->maxpos.x)
			pathwp->maxpos.x = ppp->pos.x;
		if (ppp->pos.y > pathwp->maxpos.y)
			pathwp->maxpos.y = ppp->pos.y;
		if (ppp->pos.z > pathwp->maxpos.z)
			pathwp->maxpos.z = ppp->pos.z;
		if (ppp->pos.x < pathwp->minpos.x)
			pathwp->minpos.x = ppp->pos.x;
		if (ppp->pos.y < pathwp->minpos.y)
			pathwp->minpos.y = ppp->pos.y;
		if (ppp->pos.z < pathwp->minpos.z)
			pathwp->minpos.z = ppp->pos.z;
	}
}

void pathSpin1D(CLASS_PATH* pathwp)
{
	RwV3d pos_Temp;
	RwV3d pos_Temp2;
	f32 hpos;
	u8 player;
	PATHTAG* tag;
	POSITION_REF* positionSource;
	TObjOldPlayer* playerObject;
	f32 positionX;
	s16 submode;
	s16 timer;
	s32 playerMask;
	u8 mode;

	tag  = pathwp->tagptr;
	mode = (u8)pathwp->mode;
	switch ((s8)mode) {
		case 0:
			pathwp->flag      = 0;
			pathwp->player[0] = 0x14;
			pathwp->player[1] = 0x14;
			pathwp->player[2] = 0x14;
			pathwp->player[3] = 0x14;
			pathwp->player[4] = 0x14;
			pathwp->player[5] = 0x14;
			pathwp->player[6] = 0x14;
			pathwp->player[7] = 0x14;
			pathCalcRoughArea(pathwp);
			pathwp->maxpos.x += 15.0f;
			pathwp->maxpos.y += 15.0f;
			pathwp->maxpos.z += 15.0f;
			pathwp->minpos.x -= 15.0f;
			pathwp->minpos.y -= 15.0f;
			pathwp->minpos.z -= 15.0f;
			pathwp->mode = 1;
			return;
		case 1:
			player = 0;
			while (player < 8U) {
				playerObject = lbl_802AD070[player];
				if (playerObject != NULL) {
					if ((pathwp->flag & (playerMask = 1 << player)) == 0) {
						timer = pathwp->player[player];
						if (timer < 0x14) {
							++pathwp->player[player];
						} else {
							submode = playerObject->task.smode;
							if (((submode >= 0x41) || (submode < 0x3F))
							    && ((s16)playerObject->task.mode != 0x12)) {
								positionSource = playerObject->positionSource;
								pos_Temp       = positionSource->pos;
								positionX      = pos_Temp.x;
								if (!(positionX > pathwp->maxpos.x)
								    && !(pos_Temp.y > pathwp->maxpos.y)
								    && !(pos_Temp.z > pathwp->maxpos.z)
								    && !(positionX < pathwp->minpos.x)
								    && !(pos_Temp.y < pathwp->minpos.y)
								    && !(pos_Temp.z < pathwp->minpos.z)
								    && (fn_800AEF48(tag, &pos_Temp, &pos_Temp2, &hpos, 0.0f)
								        < 15.0f)
								    && (fn_800DFD08(player, tag) != 0)) {
									pathwp->flag = (u8)pathwp->flag | playerMask;
								}
							}
						}
					} else if ((s32)(playerObject->task.flag & 0x2000) == 0) {
						pathwp->player[player] = 0;
						pathwp->flag           = (u8)pathwp->flag & ~playerMask;
					}
				}
				player += 1;
			}
			return;
	}
}

void pathGliding(CLASS_PATH* pathwp)
{

	if ((s8)(u8)pathwp->mode != 0) {
		pathGlidingReg(pathwp);
		return;
	}
	pathwp->flag      = 0;
	pathwp->player[0] = 0xC;
	pathwp->player[1] = 0xC;
	pathwp->player[2] = 0xC;
	pathwp->player[3] = 0xC;
	pathwp->player[4] = 0xC;
	pathwp->player[5] = 0xC;
	pathwp->player[6] = 0xC;
	pathwp->player[7] = 0xC;
	pathCalcRoughArea(pathwp);
	pathwp->maxpos.x += 50.0f;
	pathwp->maxpos.y += 50.0f;
	pathwp->maxpos.z += 50.0f;
	pathwp->minpos.x -= 50.0f;
	pathwp->minpos.y -= 50.0f;
	pathwp->minpos.z -= 50.0f;
	pathwp->mode = 1;
	pathwp->n.x  = 0.0f;
	pathwp->n.y  = 1.0f;
	pathwp->n.z  = 0.0f;
}

static void pathGlidingReg(CLASS_PATH* pathwp)
{
	PATHINFO pi_Temp;
	NJS_LINE l_Temp;
	RwV3d pos;
	RwV3d pos_Player_On;
	RwV3d vFace_Player;
	RwV3d pos_Path_On;
	RwV3d pos_Temp2;
	RwV3d pos2;
	f32 hpos;
	f32 hpos2;
	s16* var_r24_2;
	s16* var_r27;
	PATHTAG* temp_r31;
	PLAYERWK** var_r28;
	PLAYERWK* temp_r19;
	TASKWK** var_r23_2;
	TASKWK** var_r29;
	TASKWK* temp_r20;
	TASKWK* temp_r4;
	TObjOldPlayer** var_r23;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f1_5;
	f32 temp_f1_6;
	f32 temp_f1_7;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f2_3;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f5;
	f32 temp_f6;
	f32 temp_f7;
	f32 temp_f8;
	f32 temp_f9;
	f32 var_f1;
	f32 var_f31;
	f32 var_f30;
	f32 var_f3;
	f32 var_f4;
	s16 temp_r0_2;
	s16 temp_r0_3;
	s16 temp_r3;
	s16 temp_r3_6;
	s32 temp_r22;
	s32 temp_r22_2;
	s32 var_r21;

	s32 var_r25_2;

	s8 temp_r19_2;
	TObjPathManage* temp_r3_2;
	TObjPathManage* temp_r3_3;
	TObjPathManage* temp_r3_4;
	TObjPathManage* temp_r3_5;
	u8 temp_r0;

	temp_r31 = pathwp->tagptr;
	if ((s8)(u8)pathwp->mode != 0) {
		if (((pathwp->n.z * lbl_80242B38.z)
		        + ((pathwp->n.x * lbl_80242B38.x) + (pathwp->n.y * lbl_80242B38.y)))
		    > 0.1f) {
			pathwp->mode = 2;
		} else {
			pathwp->mode = 1;
		}
	}
	temp_r0 = (u8)pathwp->mode;
	switch ((s8)temp_r0) {
		case 1:
			var_r21 = 0;
			var_r29 = lbl_802AD090;
			var_r28 = lbl_802AD0D0;
			var_r27 = pathwp->player;

			var_r23 = lbl_802AD070;
			do {
				temp_r20 = *var_r29;
				if (temp_r20 != NULL) {
					temp_r19 = *var_r28;
					if ((pathwp->flag & (temp_r22 = 1 << var_r21)) == 0) {
						temp_r3 = *var_r27;
						if (temp_r3 < 0xC) {
							++*var_r27;
							if ((s16)*var_r27 >= 4) {
								var_f30 = 0.0f;
								goto block_17;
							}
						} else {
							if ((s16)temp_r19->nocontimer != 0) {
								var_f30 = 13.5f;
							} else {
								var_f30 = 8.0f;
							}
						block_17:
							*var_r27  = 0xC;
							temp_r0_2 = temp_r20->smode;
							if ((temp_r0_2 >= 0x41) || (temp_r0_2 < 0x3F)) {
								temp_f1 = temp_r20->pos.x;
								if (!(temp_f1 > pathwp->maxpos.x)
								    && !(temp_f1 < pathwp->minpos.x)) {
									temp_f1_2 = temp_r20->pos.z;
									if (!(temp_f1_2 > pathwp->maxpos.z)
									    && !(temp_f1_2 < pathwp->minpos.z)) {
										temp_f1_3 = temp_r20->pos.y;
										if (!(temp_f1_3 > pathwp->maxpos.y)
										    && !(temp_f1_3 < pathwp->minpos.y)) {
											var_f31 = fn_800AEF48(
											    temp_r31, &temp_r20->pos, &pos, &hpos, 0.0f);
											if (!(var_f31 > 30.0f)) {
												pi_Temp.onpathpos = hpos;
												if (fn_800AF3AC(temp_r31, &pi_Temp) != 0) {
													if ((hpos >= (temp_r31->totallen - 0.1f))
													    || (hpos <= 0.1f)) {
														vFace_Player.x = temp_r19->spd.x;
														vFace_Player.y = temp_r19->spd.y;
														vFace_Player.z = temp_r19->spd.z;
														vFace_Player.y = 0.0f;
														if (fn_801991B4(&vFace_Player) < 0.25f) {
															vFace_Player.x = 1.0f;
															vFace_Player.y = 0.0f;
															vFace_Player.z = 0.0f;
														} else {
															fn_801990E0((RwV3d*)&vFace_Player,
															    (RwV3d*)&vFace_Player);
														}
														fn_8003E9B4(
														    temp_r20, (RwV3d*)&vFace_Player);
														if (hpos <= 0.1f) {
															var_f3 = pi_Temp.front.x;
															var_f4 = pi_Temp.front.y;
															var_f1 = pi_Temp.front.z;
														} else {
															var_f3 = -1.0f * pi_Temp.front.x;
															var_f4 = -1.0f * pi_Temp.front.y;
															var_f1 = -1.0f * pi_Temp.front.z;
														}
														if (!(((var_f1 * vFace_Player.z)
														          + ((var_f3 * vFace_Player.x)
														              + (var_f4 * vFace_Player.y)))
														        <= 0.0f)) {
															if (lbl_8042C380->dist_pl_Temp[var_r21]
															    < 0.25f) {
																var_f31 = fn_800D7218(
																    &temp_r20->pos, &pos);
																goto block_49;
															}
															temp_r3_2 = lbl_8042C380;
															if (!(((temp_r3_2->dir_pl_Temp[var_r21]
															               .z
															           * pi_Temp.normal.z)
															          + ((temp_r3_2
															                     ->dir_pl_Temp
															                         [var_r21]
															                     .x
															                 * pi_Temp.normal.x)
															              + (temp_r3_2
															                      ->dir_pl_Temp
															                          [var_r21]
															                      .y
															                  * pi_Temp.normal.y)))
															        > 0.0f)) {
																temp_f1_4 = fn_800D7044(&pos,
																    &lbl_8042C380
																        ->l_pl_Temp[var_r21],
																    &pos_Player_On);
																temp_r3_3 = lbl_8042C380;
																temp_f3   = pos_Player_On.x;
																if (!((((pos_Player_On.z
																            - temp_r3_3
																                ->pos_pl_Last
																                    [var_r21]
																                .z)
																           * (pos_Player_On.z
																               - temp_r20->pos.z))
																          + (((temp_f3
																                  - temp_r3_3
																                      ->pos_pl_Last
																                          [var_r21]
																                      .x)
																                 * (temp_f3
																                     - temp_r20->pos
																                         .x))
																              + ((pos_Player_On.y
																                     - temp_r3_3
																                         ->pos_pl_Last
																                             [var_r21]
																                         .y)
																                  * (pos_Player_On.y
																                      - temp_r20
																                          ->pos
																                          .y))))
																        > 0.0f)) {
																	var_f31 = temp_f1_4;
																}
																goto block_49;
															}
														}
													} else {
														l_Temp.p.x = pos.x;
														l_Temp.p.y = pos.y;
														l_Temp.p.z = pos.z;
														l_Temp.v.x = pi_Temp.front.x;
														l_Temp.v.y = pi_Temp.front.y;
														l_Temp.v.z = pi_Temp.front.z;
														if (lbl_8042C380->dist_pl_Temp[var_r21]
														    < 0.25f) {
															var_f31 = fn_800D7044(&temp_r20->pos,
															    &l_Temp, &pos_Player_On);
															goto block_49;
														}
														temp_r19_2 = (s8)(u8)(*var_r23)->field9E7;
														temp_r3_4  = lbl_8042C380;
														if (!(((temp_r3_4->dir_pl_Temp[var_r21].z
														           * pi_Temp.normal.z)
														          + ((temp_r3_4
														                     ->dir_pl_Temp[var_r21]
														                     .x
														                 * pi_Temp.normal.x)
														              + (temp_r3_4
														                      ->dir_pl_Temp[var_r21]
														                      .y
														                  * pi_Temp.normal.y)))
														        > 0.0f)) {
															temp_f1_5 = fn_800D605C(&l_Temp,
															    &lbl_8042C380->l_pl_Temp[var_r21],
															    &pos_Path_On, &pos_Player_On);
															temp_f2   = pos_Player_On.x;
															temp_r3_5 = lbl_8042C380;
															temp_f4   = temp_f2
															    - temp_r3_5->pos_pl_Last[var_r21].x;
															temp_f5 = pos_Player_On.y
															    - temp_r3_5->pos_pl_Last[var_r21].y;
															temp_f6 = pos_Player_On.z
															    - temp_r3_5->pos_pl_Last[var_r21].z;
															temp_f7 = temp_f2 - temp_r20->pos.x;
															temp_f8
															    = pos_Player_On.y - temp_r20->pos.y;
															temp_f9
															    = pos_Player_On.z - temp_r20->pos.z;
															if (((temp_f6 * temp_f9)
															        + ((temp_f4 * temp_f7)
															            + (temp_f5 * temp_f8)))
															    > 0.0f) {
																if (((temp_f9 * temp_f9)
																        + ((temp_f7 * temp_f7)
																            + (temp_f8 * temp_f8)))
																    > ((temp_f6 * temp_f6)
																        + ((temp_f4 * temp_f4)
																            + (temp_f5
																                * temp_f5)))) {
																	if (temp_r19_2 == 0) {
																		goto block_49;
																	}
																} else {
																	goto block_49;
																}
															} else {
																var_f31 = temp_f1_5;
															block_49:
																if (0.0f == var_f30) {
																	if (!(1.0f < var_f31)) {
																		goto block_53;
																	}
																} else if (!(var_f30 < var_f31)) {
																block_53:
																	temp_f1_6 = temp_r31->totallen;
																	if (hpos >= temp_f1_6) {
																		hpos = temp_f1_6 - 0.01f;
																	}
																	if (fn_800DFA68(
																	        var_r21, temp_r31, hpos)
																	    != 0) {
																		pathwp->flag
																		    = (u8)pathwp->flag
																		    | temp_r22;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					} else if (((s32)(temp_r20->flag & 0x2000) == 0)
					    || ((PATHTAG*)temp_r19->pathtag != temp_r31)) {
						*var_r27     = 0;
						pathwp->flag = (u8)pathwp->flag & ~temp_r22;
					}
				}
				var_r29++;
				var_r28++;
				var_r27++;

				var_r23++;
				var_r21 += 1;
			} while (var_r21 < 8);
			return;
		case 2:
			var_r25_2 = 0;
			var_r23_2 = lbl_802AD090;
			var_r24_2 = pathwp->player;
			do {
				temp_r4 = *var_r23_2;
				if (temp_r4 != NULL) {
					if ((pathwp->flag & (temp_r22_2 = 1 << var_r25_2)) == 0) {
						temp_r3_6 = *var_r24_2;
						if (temp_r3_6 < 0xC) {
							++*var_r24_2;
						} else {
							*var_r24_2 = 0xC;
							temp_r0_3  = (*var_r23_2)->smode;
							if ((temp_r0_3 >= 0x41) || (temp_r0_3 < 0x3F)) {
								temp_f4_2 = temp_r4->pos.x;
								if (!(temp_f4_2 > pathwp->maxpos.x)) {
									temp_f1_7 = temp_r4->pos.y;
									if (!(temp_f1_7 > pathwp->maxpos.y)) {
										temp_f2_2 = temp_r4->pos.z;
										if (!(temp_f2_2 > pathwp->maxpos.z)
										    && !(temp_f4_2 < pathwp->minpos.x)
										    && !(temp_f1_7 < pathwp->minpos.y)
										    && !(temp_f2_2 < pathwp->minpos.z)) {
											pos2.x    = temp_f4_2;
											temp_f3_2 = temp_r4->pos.y;
											pos2.y    = temp_f3_2;
											temp_f2_3 = temp_r4->pos.z;
											pos2.z    = temp_f2_3;
											pos2.x    = temp_f4_2 - (9.0f * lbl_80242B38.x);
											pos2.y    = temp_f3_2 - (9.0f * lbl_80242B38.y);
											pos2.z    = temp_f2_3 - (9.0f * lbl_80242B38.z);
											if (!(4.0f < fn_800AEF48(temp_r31, (RwV3d*)&pos2,
											          &pos_Temp2, &hpos2, 0.0f))) {
												fn_800DF9F0(var_r25_2, temp_r31, hpos2);
												pathwp->flag = (u8)pathwp->flag | temp_r22_2;
											}
										}
									}
								}
							}
						}
					} else if ((s32)(temp_r4->flag & 0x2000) == 0) {
						*var_r24_2   = 0;
						pathwp->flag = (u8)pathwp->flag & ~temp_r22_2;
					}
				}
				var_r23_2++;
				var_r24_2++;
				var_r25_2 += 1;
			} while (var_r25_2 < 8);
			return;
	}
}

void pathSeeingPath(CLASS_PATH* pathwp)
{
	RwV3d pos;
	s32 point;
	f32 h;
	MOTIONWK* temp_r5_2;
	PATHTAG* temp_r25;
	PATHTAG* temp_r26_2;
	PATHTAG* temp_r4_3;
	PATHTBL_P* temp_r3_2;
	PATHTBL_P* temp_r3_3;
	TASKWK* temp_r26;
	TASKWK* temp_r4_2;
	TObjTeam** var_r30;
	TObjTeam* temp_r22;
	f32 temp_f1_7;
	f32 temp_f2;
	f32 temp_f3;
	s16 temp_r3;
	s16 temp_r4_4;
	s32* var_r31;
	s32 temp_r27;
	s32 temp_r4;
	s32 var_r0;
	s32 var_r0_2;
	s32 var_r24;
	u32 var_r23;
	u8 temp_r0;
	u8 temp_r0_2;

	temp_r25 = pathwp->tagptr;
	temp_r0  = (u8)pathwp->mode;
	switch ((s8)temp_r0) {
		case 0:
			pathwp->flag      = 0;
			pathwp->player[0] = 0x3C;
			pathwp->player[1] = 0x3C;
			pathwp->player[2] = 0x3C;
			pathwp->player[3] = 0x3C;
			pathwp->player[4] = 0x3C;
			pathwp->player[5] = 0x3C;
			pathwp->player[6] = 0x3C;
			pathwp->player[7] = 0x3C;
			pathCalcRoughArea(pathwp);
			pathwp->maxpos.x += 40.0f;
			pathwp->maxpos.y += 40.0f;
			pathwp->maxpos.z += 40.0f;
			pathwp->minpos.x -= 40.0f;
			pathwp->minpos.y -= 40.0f;
			pathwp->minpos.z -= 40.0f;
			pathwp->mode = 1;
			return;
		case 1:
			var_r24 = 0;
			var_r30 = lbl_80303DC8;
			do {
				temp_r22 = *var_r30;
				if (temp_r22 != NULL) {
					var_r23 = 0U;
					var_r31 = lbl_80253648;
					do {
						temp_r0_2 = (u8)temp_r22->playerNo[fn_800927D0(temp_r22, *var_r31)];
						if ((u8)(s8)temp_r0_2 <= 8U) {
							temp_r26 = lbl_802AD090[(u8)(s8)temp_r0_2];
							if (temp_r26 != NULL) {
								temp_r4 = temp_r26->flag & 0x2000;
								if (temp_r4 == 0) {
									if ((pathwp->flag & (temp_r27 = 1 << (u8)(s8)temp_r0_2)) == 0) {
										temp_r3 = pathwp->player[(u8)(s8)temp_r0_2];
										if (temp_r3 < 0x3C) {
											++pathwp->player[(u8)(s8)temp_r0_2];
										} else if ((fn_800892B0(lbl_802AD070[(u8)(s8)temp_r0_2])
										               != 0)
										    || ((s16)temp_r22->field1FC != 0)
										    || (fn_800E27D8(
										            temp_r26, lbl_802AD0D0[(u8)(s8)temp_r0_2], 0, 0)
										        != 0)
										    || ((s16)lbl_802AD0D0[(u8)(s8)temp_r0_2]->nocontimer
										        != 0)) {
											temp_r26_2 = pathwp->tagptr;
											temp_r4_2  = lbl_802AD090[(u8)(s8)temp_r0_2];
											if (temp_r4_2 == NULL) {
												var_r0 = 0;
											} else {
												temp_f1_7 = temp_r4_2->pos.x;
												if ((temp_f1_7 > pathwp->maxpos.x)
												    || (temp_f2 = temp_r4_2->pos.y,
												        (temp_f2 > pathwp->maxpos.y))
												    || (temp_f3 = temp_r4_2->pos.z,
												        (temp_f3 > pathwp->maxpos.z))
												    || (temp_f1_7 < pathwp->minpos.x)
												    || (temp_f2 < pathwp->minpos.y)
												    || (temp_f3 < pathwp->minpos.z)) {
													var_r0 = 0;
												} else if (fn_800AEF48(temp_r26_2, &temp_r4_2->pos,
												               &pos, &h, 0.0f)
												    > 40.0f) {
													var_r0 = 0;
												} else {
													if (&point != NULL) {
														fn_800AF2E4(temp_r26_2, &point, h);
													}
													var_r0 = 1;
												}
											}
											if (var_r0 == 0) {
												var_r0_2 = 0;
											} else {
												temp_r5_2 = lbl_802AD0B0[(u8)(s8)temp_r0_2];
												temp_r4_3 = pathwp->tagptr;
												temp_r3_2 = temp_r4_3->pathtbl;
												temp_r4_4 = temp_r4_3->points;
												if (temp_r4_4 >= 2) {
													if (point == 0) {
														if ((((temp_r3_2->pos.z
														          - temp_r3_2[1].pos.z)
														         * temp_r5_2->spd.z)
														        + (((temp_r3_2->pos.x
														                - temp_r3_2[1].pos.x)
														               * temp_r5_2->spd.x)
														            + ((temp_r3_2->pos.y
														                   - temp_r3_2[1].pos.y)
														                * temp_r5_2->spd.y)))
														    > 0.0f) {
															var_r0_2 = 0;
														} else {
															goto block_56;
														}
													} else if ((point >= (s32)(temp_r4_4 - 2))
													    && (temp_r3_3 = &temp_r3_2[point],
													        (((((temp_r3_3->pos.z
													                - temp_r3_3[-1].pos.z)
													               * temp_r5_2->spd.z)
													              + (((temp_r3_3->pos.x
													                      - temp_r3_3[-1].pos.x)
													                     * temp_r5_2->spd.x)
													                  + ((temp_r3_3->pos.y
													                         - temp_r3_3[-1].pos.y)
													                      * temp_r5_2->spd.y)))
													            > 0.0f)))) {
														var_r0_2 = 0;
													} else {
														goto block_56;
													}
												} else {
												block_56:
													var_r0_2 = 1;
												}
											}
											if ((var_r0_2 != 0)
											    && (fn_800DFB88((u8)(s8)temp_r0_2, temp_r25)
											        != 0)) {
												pathwp->flag = (u8)pathwp->flag | temp_r27;
											}
										}
									} else if (temp_r4 == 0) {
										pathwp->player[(u8)(s8)temp_r0_2] = 0;
										pathwp->flag = (u8)pathwp->flag & ~temp_r27;
									}
								}
							}
						}
						var_r31++;
						var_r23 += 1;
					} while (var_r23 < 3U);
				}
				var_r30++;
				var_r24 += 1;
			} while (var_r24 < 4);
			return;
	}
}

void CLASS_PATH::Exec()
{
	if (execfunc)
		execfunc(this);
}
void CLASS_PATH::Reset()
{
	mode  = 0;
	flag  = 0;
	timer = 0;
	for (s32 i = 0; i < 8; ++i)
		player[i] = 0;
}
CLASS_PATH::~CLASS_PATH()
{
	next = 0;
	last = 0;
}
CLASS_PATH::CLASS_PATH(void (*pathtask)(CLASS_PATH*))
{
	execfunc    = pathtask;
	useCopyData = 0;
	Reset();
	tagptr = 0;
	next   = 0;
	last   = 0;
}
