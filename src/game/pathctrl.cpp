#include "game/scanpath.h"
extern "C" {
extern const __declspec(section ".sdata2") f32 lbl_8042DC28;
extern const __declspec(section ".sdata2") f32 lbl_8042DC2C;
extern const __declspec(section ".sdata2") f32 lbl_8042DC30;
extern const __declspec(section ".sdata2") f32 lbl_8042DC34;
extern const __declspec(section ".sdata2") f32 lbl_8042DC38;
extern const __declspec(section ".sdata2") f32 lbl_8042DC3C;
extern const __declspec(section ".sdata2") f32 lbl_8042DC40;
extern const __declspec(section ".sdata2") f32 lbl_8042DC44;
extern const __declspec(section ".sdata2") f32 lbl_8042DC48;
extern const __declspec(section ".sdata2") f32 lbl_8042DC4C;
extern const __declspec(section ".sdata2") f32 lbl_8042DC50;
extern const __declspec(section ".sdata2") f32 lbl_8042DC54;
extern const __declspec(section ".sdata2") f32 lbl_8042DC5C;
}

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

extern "C" {
extern TObjOldPlayer* lbl_802AD070[8];
extern TASKWK* lbl_802AD090[8];
extern MOTIONWK* lbl_802AD0B0[8];
extern PLAYERWK* lbl_802AD0D0[8];
extern TObjTeam* lbl_80303DC8[4];
extern TObjPathManage* lbl_8042C380;
extern RwV3d lbl_80242B38;

s32 fn_800DFD08(s32, PATHTAG*);
s32 fn_800DFB88(s32, PATHTAG*);
s32 fn_800DFA68(s32, PATHTAG*, f32);
void fn_800DF9F0(s32, PATHTAG*, f32);
void fn_8003E9B4(TASKWK*, RwV3d*);
f32 DistanceP2P__FPC5RwV3dPC5RwV3d(RwV3d*, RwV3d*);
f32 DistanceP2L__FPC5RwV3dPC8NJS_LINEP5RwV3d(RwV3d*, NJS_LINE*, RwV3d*);
f32 DistanceL2L__FPC8NJS_LINEPC8NJS_LINEP5RwV3dP5RwV3d(NJS_LINE*, NJS_LINE*, RwV3d*, RwV3d*);
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
	PATHTBL_P* ppp   = (PATHTBL_P*)pttp->pathtbl;
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
	s32 playerMask;
	u8 player;
	PATHTAG* tag;
	POSITION_REF* positionSource;
	TObjOldPlayer* playerObject;
	f32 positionX;
	s16 submode;
	s16 timer;
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
			pathwp->maxpos.x += lbl_8042DC38;
			pathwp->maxpos.y += lbl_8042DC38;
			pathwp->maxpos.z += lbl_8042DC38;
			pathwp->minpos.x -= lbl_8042DC38;
			pathwp->minpos.y -= lbl_8042DC38;
			pathwp->minpos.z -= lbl_8042DC38;
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
								__memcpy(&pos_Temp, &positionSource->pos, sizeof(pos_Temp));
								positionX = pos_Temp.x;
								if (!(positionX > pathwp->maxpos.x)
								    && !(pos_Temp.y > pathwp->maxpos.y)
								    && !(pos_Temp.z > pathwp->maxpos.z)
								    && !(positionX < pathwp->minpos.x)
								    && !(pos_Temp.y < pathwp->minpos.y)
								    && !(pos_Temp.z < pathwp->minpos.z)
								    && (SCPathPntNearToOnpos(
								            tag, &pos_Temp, &pos_Temp2, &hpos, lbl_8042DC28)
								        < lbl_8042DC38)
								    && (fn_800DFD08((u32)player, tag) != 0)) {
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
	pathwp->maxpos.x += lbl_8042DC3C;
	pathwp->maxpos.y += lbl_8042DC3C;
	pathwp->maxpos.z += lbl_8042DC3C;
	pathwp->minpos.x -= lbl_8042DC3C;
	pathwp->minpos.y -= lbl_8042DC3C;
	pathwp->minpos.z -= lbl_8042DC3C;
	pathwp->mode = 1;
	pathwp->n.x  = lbl_8042DC28;
	pathwp->n.y  = lbl_8042DC2C;
	pathwp->n.z  = lbl_8042DC28;
}

static void pathGlidingReg(CLASS_PATH* pathwp)
{
	s32 pl;
	TASKWK* pltwp;
	PLAYERWK* pwp;
	PATHINFO pi_Temp;
	NJS_LINE l_Temp;
	RwV3d pos;
	RwV3d pos_Player_On;
	RwV3d vFace_Player;
	RwV3d pos_Path_On;
	RwV3d pos_Temp2;
	RwV3d plpos;
	f32 hpos;
	f32 hpos2;
	PATHTAG* pttp;
	TASKWK* temp_r4;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f1_5;
	f32 temp_f1_7;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f3;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f5;
	f32 temp_f6;
	f32 temp_f7;
	f32 temp_f8;
	f32 temp_f9;
	f32 var_f1;
	f32 l;
	f32 l_checking;
	f32 var_f3;
	f32 var_f4;
	s16 temp_r0_2;
	s16 temp_r0_3;
	s16 temp_r3;
	s16 temp_r3_6;

	s32 changing_path;
	TObjPathManage* temp_r3_2;
	TObjPathManage* temp_r3_3;
	TObjPathManage* temp_r3_4;
	TObjPathManage* temp_r3_5;
	u8 temp_r0;

	pttp = pathwp->tagptr;
	if ((s8)(u8)pathwp->mode != 0) {
		if (((pathwp->n.z * lbl_80242B38.z)
		        + ((pathwp->n.x * lbl_80242B38.x) + (pathwp->n.y * lbl_80242B38.y)))
		    > lbl_8042DC44) {
			pathwp->mode = 2;
		} else {
			pathwp->mode = 1;
		}
	}
	temp_r0 = (u8)pathwp->mode;
	switch ((s8)temp_r0) {
		case 1:
			pl = 0;

			do {
				pltwp = lbl_802AD090[pl];
				if (pltwp != NULL) {
					pwp = lbl_802AD0D0[pl];
					if ((pathwp->flag & (1 << pl)) == 0) {
						temp_r3 = pathwp->player[pl];
						if (temp_r3 < 0xC) {
							++pathwp->player[pl];
							if ((s16)pathwp->player[pl] >= 4) {
								l_checking = lbl_8042DC28;
								goto block_17;
							}
						} else {
							if ((s16)pwp->nocontimer != 0) {
								l_checking = lbl_8042DC48;
							} else {
								l_checking = lbl_8042DC4C;
							}
						block_17:
							pathwp->player[pl] = 0xC;
							temp_r0_2          = pltwp->smode;
							if ((temp_r0_2 >= 0x41) || (temp_r0_2 < 0x3F)) {
								temp_f1 = pltwp->pos.x;
								if (!(temp_f1 > pathwp->maxpos.x)
								    && !(temp_f1 < pathwp->minpos.x)) {
									temp_f1_2 = pltwp->pos.z;
									if (!(temp_f1_2 > pathwp->maxpos.z)
									    && !(temp_f1_2 < pathwp->minpos.z)) {
										temp_f1_3 = pltwp->pos.y;
										if (!(temp_f1_3 > pathwp->maxpos.y)
										    && !(temp_f1_3 < pathwp->minpos.y)) {
											l = SCPathPntNearToOnpos(
											    pttp, &pltwp->pos, &pos, &hpos, lbl_8042DC28);
											if (!(l > lbl_8042DC50)) {
												pi_Temp.onpathpos = hpos;
												if (GetStatusOnPath(pttp, &pi_Temp) != 0) {
													if ((hpos >= (pttp->totallen - lbl_8042DC44))
													    || (hpos <= lbl_8042DC44)) {
														__memcpy(&vFace_Player, &pwp->spd,
														    sizeof(vFace_Player));
														vFace_Player.y = lbl_8042DC28;
														if (fn_801991B4(&vFace_Player)
														    < lbl_8042DC54) {
															vFace_Player.x = lbl_8042DC2C;
															vFace_Player.y = lbl_8042DC28;
															vFace_Player.z = lbl_8042DC28;
														} else {
															fn_801990E0((RwV3d*)&vFace_Player,
															    (RwV3d*)&vFace_Player);
														}
														fn_8003E9B4(pltwp, (RwV3d*)&vFace_Player);
														if (hpos <= lbl_8042DC44) {
															var_f3 = pi_Temp.front.x;
															var_f4 = pi_Temp.front.y;
															var_f1 = pi_Temp.front.z;
														} else {
															var_f3 = lbl_8042DC40 * pi_Temp.front.x;
															var_f4 = lbl_8042DC40 * pi_Temp.front.y;
															var_f1 = lbl_8042DC40 * pi_Temp.front.z;
														}
														if (!(((var_f1 * vFace_Player.z)
														          + ((var_f3 * vFace_Player.x)
														              + (var_f4 * vFace_Player.y)))
														        <= lbl_8042DC28)) {
															if (lbl_8042C380->dist_pl_Temp[pl]
															    < lbl_8042DC54) {
																l = DistanceP2P__FPC5RwV3dPC5RwV3d(
																    &pltwp->pos, &pos);
																goto block_49;
															}
															temp_r3_2 = lbl_8042C380;
															if (!(((temp_r3_2->dir_pl_Temp[pl].z
															           * pi_Temp.normal.z)
															          + ((temp_r3_2->dir_pl_Temp[pl]
															                     .x
															                 * pi_Temp.normal.x)
															              + (temp_r3_2
															                      ->dir_pl_Temp[pl]
															                      .y
															                  * pi_Temp.normal.y)))
															        > lbl_8042DC28)) {
																temp_f1_4
																    = DistanceP2L__FPC5RwV3dPC8NJS_LINEP5RwV3d(
																        &pos,
																        &lbl_8042C380
																            ->l_pl_Temp[pl],
																        &pos_Player_On);
																temp_r3_3 = lbl_8042C380;
																temp_f3   = pos_Player_On.x;
																if (!((((pos_Player_On.z
																            - temp_r3_3
																                ->pos_pl_Last[pl]
																                .z)
																           * (pos_Player_On.z
																               - pltwp->pos.z))
																          + (((temp_f3
																                  - temp_r3_3
																                      ->pos_pl_Last
																                          [pl]
																                      .x)
																                 * (temp_f3
																                     - pltwp->pos
																                         .x))
																              + ((pos_Player_On.y
																                     - temp_r3_3
																                         ->pos_pl_Last
																                             [pl]
																                         .y)
																                  * (pos_Player_On.y
																                      - pltwp->pos
																                          .y))))
																        > lbl_8042DC28)) {
																	l = temp_f1_4;
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
														if (lbl_8042C380->dist_pl_Temp[pl]
														    < lbl_8042DC54) {
															l = DistanceP2L__FPC5RwV3dPC8NJS_LINEP5RwV3d(
															    &pltwp->pos, &l_Temp,
															    &pos_Player_On);
															goto block_49;
														}
														changing_path
														    = (lbl_802AD070[pl])->field9E7;
														temp_r3_4 = lbl_8042C380;
														if (!(((temp_r3_4->dir_pl_Temp[pl].z
														           * pi_Temp.normal.z)
														          + ((temp_r3_4->dir_pl_Temp[pl].x
														                 * pi_Temp.normal.x)
														              + (temp_r3_4->dir_pl_Temp[pl]
														                      .y
														                  * pi_Temp.normal.y)))
														        > lbl_8042DC28)) {
															temp_f1_5
															    = DistanceL2L__FPC8NJS_LINEPC8NJS_LINEP5RwV3dP5RwV3d(
															        &l_Temp,
															        &lbl_8042C380->l_pl_Temp[pl],
															        &pos_Path_On, &pos_Player_On);
															temp_f2   = pos_Player_On.x;
															temp_r3_5 = lbl_8042C380;
															temp_f4   = temp_f2
															    - temp_r3_5->pos_pl_Last[pl].x;
															temp_f5 = pos_Player_On.y
															    - temp_r3_5->pos_pl_Last[pl].y;
															temp_f9 = pos_Player_On.z;
															temp_f6 = temp_f9
															    - temp_r3_5->pos_pl_Last[pl].z;
															temp_f7 = temp_f2 - pltwp->pos.x;
															temp_f8
															    = pos_Player_On.y - pltwp->pos.y;
															temp_f9 = temp_f9 - pltwp->pos.z;
															if (((temp_f6 * temp_f9)
															        + ((temp_f4 * temp_f7)
															            + (temp_f5 * temp_f8)))
															    > lbl_8042DC28) {
																if (((temp_f9 * temp_f9)
																        + ((temp_f7 * temp_f7)
																            + (temp_f8 * temp_f8)))
																    > ((temp_f6 * temp_f6)
																        + ((temp_f4 * temp_f4)
																            + (temp_f5
																                * temp_f5)))) {
																	if (changing_path != 0) {
																		goto nextGlidingPlayer;
																	}
																	goto block_49;
																} else {
																	goto block_49;
																}
															} else {
																l = temp_f1_5;
															block_49:
																if (lbl_8042DC28 == l_checking) {
																	if (lbl_8042DC2C < l) {
																		goto nextGlidingPlayer;
																	}
																	goto block_53;
																} else if (!(l_checking < l)) {
																block_53:
																	if (hpos >= pttp->totallen) {
																		hpos = pttp->totallen
																		    - lbl_8042DC30;
																	}
																	if (fn_800DFA68(pl, pttp, hpos)
																	    != 0) {
																		pathwp->flag
																		    = (u8)pathwp->flag
																		    | (1 << pl);
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
					} else if (((s32)(pltwp->flag & 0x2000) == 0)
					    || ((PATHTAG*)pwp->pathtag != pttp)) {
						pathwp->player[pl] = 0;
						pathwp->flag       = (u8)pathwp->flag & ~(1 << pl);
					}
				}

			nextGlidingPlayer:
				pl += 1;
			} while (pl < 8);
			return;
		case 2:
			pl = 0;

			do {
				temp_r4 = lbl_802AD090[pl];
				if (temp_r4 != NULL) {
					if ((pathwp->flag & (1 << pl)) == 0) {
						temp_r3_6 = pathwp->player[pl];
						if (temp_r3_6 < 0xC) {
							++pathwp->player[pl];
						} else {
							pathwp->player[pl] = 0xC;
							temp_r0_3          = (lbl_802AD090[pl])->smode;
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
											plpos   = temp_r4->pos;
											plpos.x = plpos.x - (9.0f * lbl_80242B38.x);
											plpos.y = plpos.y - (9.0f * lbl_80242B38.y);
											plpos.z = plpos.z - (9.0f * lbl_80242B38.z);
											if (!(lbl_8042DC34 < SCPathPntNearToOnpos(pttp,
											          (RwV3d*)&plpos, &pos_Temp2, &hpos2,
											          lbl_8042DC28))) {
												fn_800DF9F0(pl, pttp, hpos2);
												pathwp->flag = (u8)pathwp->flag | (1 << pl);
											}
										}
									}
								}
							}
						}
					} else if ((s32)(temp_r4->flag & 0x2000) == 0) {
						pathwp->player[pl] = 0;
						pathwp->flag       = (u8)pathwp->flag & ~(1 << pl);
					}
				}

				pl += 1;
			} while (pl < 8);
			return;
	}
}

static inline s32 pathCheckRangeWithinArea2(
    CLASS_PATH* pathwp, s32 pl, s32* p_point, f32 catch_dist)
{
	RwV3d pos;
	f32 h;
	PATHTAG* pttp = pathwp->tagptr;
	TASKWK* pltwp = lbl_802AD090[pl];
	if (!pltwp)
		return 0;
	if (pltwp->pos.x > pathwp->maxpos.x || pltwp->pos.y > pathwp->maxpos.y
	    || pltwp->pos.z > pathwp->maxpos.z || pltwp->pos.x < pathwp->minpos.x
	    || pltwp->pos.y < pathwp->minpos.y || pltwp->pos.z < pathwp->minpos.z)
		return 0;
	if (SCPathPntNearToOnpos(pttp, &pltwp->pos, &pos, &h, lbl_8042DC28) > catch_dist)
		return 0;
	if ((u32*)p_point != NULL)
		SCPathOnposToPntnmb(pttp, h, (u32*)p_point);
	return 1;
}

static inline s32 pathCheckRangeWithinArea3(
    CLASS_PATH* pathwp, s32 pl, s32* p_point, f32 catch_dist)
{
	s32 point_Temp;
	if (!pathCheckRangeWithinArea2(pathwp, pl, &point_Temp, catch_dist))
		return 0;
	MOTIONWK* motion = lbl_802AD0B0[pl];
	PATHTAG* tag     = pathwp->tagptr;
	s16 count;
	PATHTBL_P* table = (PATHTBL_P*)tag->pathtbl;
	count            = tag->points;
	if (count >= 2) {
		if (point_Temp == 0) {
			f32 delta = table->pos.z - table[1].pos.z;
			f32 z     = delta * motion->spd.z;
			delta     = table->pos.x - table[1].pos.x;
			f32 x     = delta * motion->spd.x;
			delta     = table->pos.y - table[1].pos.y;
			if (z + (x + delta * motion->spd.y) > lbl_8042DC28)
				return 0;
		} else if (point_Temp >= count - 2) {
			table += point_Temp;
			f32 delta = table->pos.z - table[-1].pos.z;
			f32 z     = delta * motion->spd.z;
			delta     = table->pos.x - table[-1].pos.x;
			f32 x     = delta * motion->spd.x;
			delta     = table->pos.y - table[-1].pos.y;
			if (z + (x + delta * motion->spd.y) > lbl_8042DC28)
				return 0;
		}
	}
	if (p_point)
		*p_point = point_Temp;
	return 1;
}

void pathSeeingPath(CLASS_PATH* pathwp)
{
	TASKWK* pltwp;
	PATHTAG* pttp;
	s32 team;
	s32 role;
	TObjTeam* pTeam;
	s16 temp_r3;
	s32 temp_r4;
	s32 var_r0_2;
	u8 temp_r0;
	u8 pl;

	pttp    = pathwp->tagptr;
	temp_r0 = (u8)pathwp->mode;
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
			pathwp->maxpos.x += lbl_8042DC5C;
			pathwp->maxpos.y += lbl_8042DC5C;
			pathwp->maxpos.z += lbl_8042DC5C;
			pathwp->minpos.x -= lbl_8042DC5C;
			pathwp->minpos.y -= lbl_8042DC5C;
			pathwp->minpos.z -= lbl_8042DC5C;
			pathwp->mode = 1;
			return;
		case 1:
			for (team = 0; team < 4; team++) {
				pTeam = lbl_80303DC8[team];
				if (pTeam != NULL) {
					for (role = 0; role < 3U; role++) {
						pl = (u8)pTeam->playerNo[fn_800927D0(pTeam, lbl_80253648[role])];
						if ((u8)(s8)pl <= 8U) {
							pltwp = lbl_802AD090[(u8)(s8)pl];
							if (pltwp != NULL) {
								temp_r4 = pltwp->flag & 0x2000;
								if (temp_r4 == 0) {
									if ((pathwp->flag & (1 << (u8)(s8)pl)) == 0) {
										temp_r3 = pathwp->player[(u8)(s8)pl];
										if (temp_r3 < 0x3C) {
											++pathwp->player[(u8)(s8)pl];
										} else if ((fn_800892B0(lbl_802AD070[(u8)(s8)pl]) != 0)
										    || ((s16)pTeam->field1FC != 0)
										    || (fn_800E27D8(pltwp, lbl_802AD0D0[(u8)(s8)pl], 0, 0)
										        != 0)
										    || ((s16)lbl_802AD0D0[(u8)(s8)pl]->nocontimer != 0)) {
											var_r0_2 = pathCheckRangeWithinArea3(
											    pathwp, (u8)(s8)pl, NULL, lbl_8042DC5C);
											if ((var_r0_2 != 0)
											    && (fn_800DFB88((u8)(s8)pl, pttp) != 0)) {
												pathwp->flag = (u8)pathwp->flag | (1 << (u8)(s8)pl);
											}
										}
									} else if (temp_r4 == 0) {
										pathwp->player[(u8)(s8)pl] = 0;
										pathwp->flag = (u8)pathwp->flag & ~(1 << (u8)(s8)pl);
									}
								}
							}
						}
					}
				}
			}
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

extern "C" {
extern const __declspec(section ".sdata2") f32 lbl_8042DC28 = 0.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC2C = 1.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC30 = 0.01f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC34 = 4.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC38 = 15.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC3C = 50.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC40 = -1.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC44 = 0.1f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC48 = 13.5f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC4C = 8.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC50 = 30.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC54 = 0.25f;
extern const __declspec(section ".sdata2") f32 lbl_8042DC5C = 40.0f;
}
