#include <Windows.h>

// Uso este header para armazenar as funções descompiladas que 
// Consulto/pretendo consultar constantemente 
// Desta forma posso ver como foi feito e pensar numa maneira de fazer 
// Bem feito

// Addr base cMob:  0x15C69B8
// Addr base cUser: 0x7B318C8

					case 0x36C: //_MSG_Attack
					case 0x39D: //_MSG_AttackOne
					case 0x39E: //_MSG_AttackTwo
					{
						//00430DE4
						MSG_Attack* pAttack = (MSG_Attack*)msg; //230
						int pSize = pAttack->Header.Size; //234
						pAttack->Header.ClientId = 0x7530;
						if(pUser[conn].Mode != USER_PLAY)
						{
							SendHpMode(conn);
							return;
						}

						//00430E2D
						if(pMob[conn].MOB.CurrentScore.Hp <= 0 || pUser[conn].Mode != USER_PLAY)
						{
							SendHpMode(conn);
							AddCrackError(conn, 1, 8);
							return;
						}

						//00430E74
						short unknow[MAX_TARGET]; //250
						memset(unknow, 0x0, MAX_TARGET * 2);

						unsigned int pTimestamp = pAttack->Header.TimeStamp; //254
						if(pTimestamp != 0x0E0A1ACA && pUser[conn].LastAttackTick != 0x0E0A1ACA)
						{
							if(pTimestamp < pUser[conn].LastAttackTick + 900)
							{
								AddCrackError(conn, 4, 7);
								pUser[conn].LastAttackTick = pTimestamp;
								pUser[conn].LastAttack = pAttack->SkillIndex;
							}
						}

						//00430F11
						if(pTimestamp != 0x0E0A1ACA)
						{
							int curTime; //258
							if(CurrentTime <= 120000)
								curTime = 0;
							else
								curTime = CurrentTime - 120000;

							if(pTimestamp > CurrentTime + 15000 || pTimestamp < curTime)
							{
								Log("etc, clienttime faster than 15 sec - MSG_ATTACK", pUser[conn].AccountName, pUser[conn].IP);
								AddCrackError(conn, 1, 107);
								return;
							}

							//00430FAE
							pUser[conn].LastAttackTick = pTimestamp;
						}

						//00430FC3
						int skillId = pAttack->SkillIndex; //25c
						int targetX = pAttack->TargetX; //260
						int targetY = pAttack->TargetY; //264
						if(pTimestamp != 0x0E0A1ACA && skillId != 42)
						{
							BASE_GetHitPosition(pAttack->PosX, pAttack->PosY, &targetX, &targetY, *pHeightGrid);
							//00431049
							if(targetX != pAttack->TargetX || targetY != pAttack->TargetY)
							{
								sprintf(temp, "err, hitposition %d,%d - %d,%d - %d,%d", pAttack->PosX, pAttack->PosY, pAttack->TargetX, pAttack->TargetY, targetX, targetY);
								Log(temp, pUser[conn].AccountName, pUser[conn].IP);
								AddCrackError(conn, 2, 9);
								return;
							}
						}

						//0043110B
						if(skillId < -1 || skillId > MAX_SKILLLIST)
						{
							Log("MSG_Attack, skillnum out of range", pUser[conn].AccountName, pUser[conn].IP);
							return;
						}

						//0043114E
						if(skillId >= 0 && skillId < MAX_SKILLLIST && pTimestamp != 0x0E0A1ACA)
						{
							if(g_pSpell[skillId].Passive == TRUE)
								return;

							//0043118F
							int skillTick = pUser[conn].LastSkillTick[skillId]; //268
							if(skillTick != -1 && pTimestamp != 0x0E0A1ACA)
							{
								int calcTimestamp = pTimestamp - skillTick; //26c
								int skillDelay = g_pSpell[skillId].Delay; //270
								if(pMob[conn].MOB.AffectInfo & RSV_CAST != 0 && skillDelay >= 2)
									skillDelay--;

								skillDelay = skillDelay * 1000;
								if(calcTimestamp < skillDelay - 100)
								{
									AddCrackError(conn, 10, 30);
									sprintf(temp, "skill delay skillnum: %d-%d", pTimestamp, calcTimestamp);
									Log(temp, pUser[conn].AccountName, pUser[conn].IP);
									return;
								}
							}

							//004312A3
							pUser[conn].LastSkillTick[skillId] = pAttack->Header.TimeStamp;
							int calcClassInfo = pTimestamp / 24; //274
							if(calcClassInfo != pMob[conn].MOB.ClassInfo)
							{
								Log("MSG_Attack, Request other class skill", pUser[conn].AccountName, pUser[conn].IP);
								return;
							}
						}

						//00431320
						int Special = FALSE; //278
						int skillDelay = 100; //27c
						int saveSpecial = FALSE; //280
						if(skillId >= 0 && skillId < 96)
						{
							//00431358
							int getSkillMaster = ((skillId % 24) / 8) + 1; //284
							if(pTimestamp != 0x0E0A1ACA)
							{
								int learn = skillId % 24; //288
								int learnedSkill = 1 << learn; //28c
								if(pAttack->Header.TimeStamp != 0x0E0A1ACA && (pMob[conn].MOB.Learn & learnedSkill) == FALSE && AddCrackError(conn, 8, 10) != FALSE)
									return;

								//004313FD
								if(getSkillMaster <= 0 || getSkillMaster > 3)
								{
									Log("Skill kind out of bound - MSG_ATTACK", pUser[conn].AccountName, pUser[conn].IP);
									return;
								}
							}

							//00431440
							Special = pMob[conn].MOB.CurrentScore.Master[getSkillMaster];
							skillDelay = skillDelay + Special;
							saveSpecial = Special;
						}
						else 
						{
							if(skillId >= 96 && skillId <= 100)//00431481
							{
								//0043149B
								if(skillId == 97)
								{
									//004314A8
									if(pAttack->PosX > 0 && pAttack->PosX < 4096 && pAttack->PosY > 0 && pAttack->PosY < 4096)
									{
										//004314FF
										int itemId = pItemGrid[pAttack->PosX][pAttack->PosY]; //290
										if(itemId > 0 && itemId < MAX_ITEMLIST && pItemBuffer[itemId].ITEM.Index == 746)
											pAttack->Motion = MOVE_NORMAL;
										else
										{
											//00431562
											Log("err, mortar invalid", pUser[conn].AccountName, pUser[conn].IP);
											return;
										}
									}
									else
									{
										//00431596
										Log("err, mortar invalid", pUser[conn].AccountName, pUser[conn].IP);
										return;
									}
								}
								else
								{
									//004315CA
									int learn = skillId - 72; //294
									int learnedSkill = 1 << learn; //298
									if(pAttack->Header.TimeStamp != 0x0E0A1ACA && (pMob[conn].MOB.Learn & learnedSkill) == FALSE && AddCrackError(conn, 208, 1) != FALSE)
										return;
								}

								//0043163B
								Special = pMob[conn].MOB.CurrentScore.Level;
								skillDelay = skillDelay + Special;
								saveSpecial = Special;
							}
						}

						//0043166F
						if(skillId == 85) // Atualizado na 7xx o id do escudo dourado e 85
						{
							int skillGoldAbsorption = Special * 100; //29c
							if(pMob[conn].MOB.Gold < skillGoldAbsorption)
								return;

							//004316A3
							pMob[conn].MOB.Gold = pMob[conn].MOB.Gold - skillGoldAbsorption;
							SendEtc(conn);
						}

						//004316D3
						int mp = pMob[conn].MOB.CurrentScore.Mp; //2a0
						int countMp = pUser[conn].CountMp; //2a4
						if(skillId >= 0 && skillId < 98)
						{
							//00431718
							int mpGasto = BASE_GetManaSpent(skillId, pMob[conn].MOB.SaveMana, Special); //2a8
							if((pMob[conn].MOB.CurrentScore.Mp - mpGasto) < 0)
							{
								SendSetHpMp(conn);
								return;
							}

							//00431771
							pMob[conn].MOB.CurrentScore.Mp = pMob[conn].MOB.CurrentScore.Mp - mpGasto;
							pUser[conn].CountMp = pUser[conn].CountMp - mpGasto;
							SetReqMp(conn);
						}

						//004317C7
						pAttack->CurrentMp = pMob[conn].MOB.CurrentScore.Mp;
						pAttack->ReqMp = pUser[conn].CountMp;
							
						int calcskillmaster3 = 0; //2ac
						if(pMob[conn].MOB.ClassInfo == 0 && (pMob[conn].MOB.Learn & LEARN_14) != 0)
						{
							calcskillmaster3 = pMob[conn].MOB.CurrentScore.Master[2] / 20;
							if(calcskillmaster3 < 0)
								calcskillmaster3 = 0;
							if(calcskillmaster3 > 15)
								calcskillmaster3 = 15;
						}

						//00431878
						if(pMob[conn].MOB.ClassInfo == 3)
							DoRemoveHide(conn);

						//0043189A
						int unk = 0; //2B0
						int pLevel = pMob[conn].MOB.CurrentScore.Level; //2b4
						unsigned char pAttribute = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY); //2b8
						pAttribute = pAttribute & PVP;

						int pHp = pMob[conn].MOB.CurrentScore.Hp; //2bc
						int unk1 = 0; //2C0
						unsigned char doubleCritical; //2c4
						for(int i = 0; i < MAX_TARGET; i++) //2c8
						{
							if(i >= 1 && pSize <= sizeof MSG_AttackOne)
								break;

							if(i >= 2 && pSize <= sizeof MSG_AttackTwo)
								break;

							int pTarget = pAttack->Dam[i].TargetID; //2cc
							if(pTarget <= 0 || pTarget >= MAX_MOB)
								continue;

							//004319A2
							if(pMob[pTarget].Mode == MOB_EMPTY)
							{
								SendRemoveMob(conn, pTarget, 1, FALSE);
								continue;
							}

							//004319D3
							if(pMob[conn].MOB.CurrentScore.Hp <= 0)
							{
								pAttack->Dam[i].TargetID = MOB_EMPTY;
								pAttack->Dam[i].Damage = 0;
								SendRemoveMob(conn, pTarget, 1, FALSE);
								continue;
							}

							//00431A2C
							if(skillId != 42 || pMob[conn].TargetX < pMob[pTarget].TargetX - 23 || pMob[conn].TargetX > pMob[pTarget].TargetX + 23 || pMob[conn].TargetY < pMob[pTarget].TargetY - 23 || pMob[conn].TargetY > pMob[pTarget].TargetY + 23)
							{
								SendRemoveMob(conn, pTarget, 1, FALSE);
								continue;
							}

							//00431AED
							int pDamage = pAttack->Dam[i].Damage; //2d0
							if(pDamage != -2 && pDamage != -1 && pDamage != 0)
							{
								pAttack->Dam[i].Damage = 0;
								AddCrackError(conn, 10, 77);
								continue;
							}

							//00431B47
							int pLeader = pMob[conn].Leader; //2d4
							if(pLeader == MOB_EMPTY)
								pLeader = conn;

							int pTargetLeader = pMob[pTarget].Leader; //2d8
							if(pTargetLeader == MOB_EMPTY)
								pTargetLeader = pTarget;

							//00431B9B
							int pGuildId = pMob[conn].MOB.GuildIndex; //2dc
							if(pMob[conn].GuildDisable != FALSE)
								pGuildId = 0;

							int pTargetGuildId = pMob[pTarget].MOB.GuildIndex; //2e0
							if(pMob[pTarget].GuildDisable != FALSE)
								pTargetGuildId = 0;

							if(pGuildId == 0 && pTargetGuildId == 0)
								pGuildId = -1;

							//00431C2C
							if(BrState != 0 && BRItem > 0)
							{
								int pTargetX = pMob[conn].TargetX; //2e4
								int pTargetY = pMob[conn].TargetY; //2e8
								if(pTargetX >= 2604 && pTargetY >= 1708 && pTargetX <= 2648 && pTargetY <= 1744)
									pGuildId = -1;
							}

							//00431C9B
							int pCapeInfo = pMob[conn].MOB.CapeInfo; //2ec
							int pTargetCapeInfo = pMob[pTarget].MOB.CapeInfo; //2f0
							int flagCapeInfo = FALSE; //2f4
							if(pCapeInfo == 7 && pTargetCapeInfo == 7 || pCapeInfo == 8 && pTargetCapeInfo == 8)
								flagCapeInfo = TRUE;

							//00431D02
							if(pDamage == -2)
							{
								int pDistance = BASE_GetDistance(pAttack->PosX, pAttack->PosY, pAttack->TargetX, pAttack->TargetY); //2f8
								if(pDistance > pUser[conn].Range || pDistance > 7)
									return;

								//00431D76
								pDamage = 0;
								if(i > 0 && pSize < sizeof MSG_AttackTwo || pMob[conn].MOB.ClassInfo != 3 || (pMob[conn].MOB.Learn & LEARN_06) == FALSE)
								{
									AddCrackError(conn, 10, 24);
									continue;
								}

								//00431DD3
								int flagDoubleCritical = FALSE; //2fc
								if(i == 0)
									flagDoubleCritical = BASE_GetDoubleCritical(&pMob[conn].MOB, &pUser[conn].AttackCount, (unsigned short*)pAttack->Progress, &doubleCritical);

								//00431E24
								pDamage = pMob[conn].MOB.CurrentScore.Attack;
								if(doubleCritical & 2 != FALSE)
								{
									if(pTarget < MAX_PLAYER)
										pDamage = (((rand() % 3) + 13) * pDamage) / 10;
									else
										pDamage = (((rand() % 4) + 15) * pDamage) / 10;
								}

								//00431EA9
								int pDefense = pMob[pTarget].MOB.CurrentScore.Defense; //300
								if(pTarget < MAX_PLAYER)
									pDefense = pDefense << 1;

								//00431ED9
								pDamage = BASE_GetDamage(pDamage, pDefense, calcskillmaster3);

								//00431EFC
								if(i == 0 && pSize >= sizeof MSG_AttackTwo && pMob[conn].MOB.ClassInfo == 3 && (pMob[conn].MOB.Learn & LEARN_21) != FALSE && (rand() % 4) == 0)
								{
									//00431F66
									int calcSkillDamage = (pMob[conn].MOB.CurrentScore.STR + pMob[conn].MOB.CurrentScore.Master[3]) >> 1; //304
									unsigned int pLearn = 0; //308
									if(pTarget >= MAX_PLAYER && pMob[pTarget].MOB.BaseScore.Level >= 300)
									{
										pLearn = pMob[pTarget].MOB.Learn;
										calcSkillDamage = ((100 - pLearn) * calcSkillDamage) / 100; 
									}

									//00431FFC
									pAttack->Dam[1].TargetID = MOB_EMPTY;
									pAttack->Dam[1].Damage = calcSkillDamage;
									doubleCritical = doubleCritical | 4;
									pDamage = pDamage + calcSkillDamage;
								}

								//00432040
								if(doubleCritical & 1 != FALSE)
									pDamage = pDamage << 1;

								pAttack->DoubleCritical = doubleCritical;
							}
							else if(pDamage == -1 && skillId >= 0 && skillId <= 100) //00432075
							{
								pDamage = 0;
								int skillMaxTarget = g_pSpell[skillId].MaxTarget; //30c
								if(pTimestamp != 0x0E0A1ACA && i >= skillMaxTarget)
								{
									AddCrackError(conn, 10, 28);
									sprintf(temp, "skill target max num %d", pTimestamp);
									Log(temp, pUser[conn].AccountName, pUser[conn].IP);
									continue;
								}

								//0043212F
								if(g_pSpell[skillId].bParty != 0 && pLeader != pTargetLeader && pGuildId != pTargetGuildId)
								{
									AddCrackError(conn, 10, 27);
									sprintf(temp, "party skill - skill:%d leader:%d tleader:%d", pTimestamp, pLeader, pTargetLeader);
									Log(temp, pUser[conn].AccountName, pUser[conn].IP);
									continue;
								}

								//004321CA
								int unk2 = 0; //310
								int skillInstanceType = g_pSpell[skillId].InstanceType; //314
								if(skillInstanceType >= 0 && skillInstanceType <= 5)
								{
									//00432203
									int curWeather = CurrentWeather; //318
									int rangeWeather; //2088
									if(pMob[conn].TargetX >> 7 < 12 && pMob[conn].TargetY >> 7 > 25)
										rangeWeather = 1;
									else
										rangeWeather = 0;

									if(rangeWeather != 0)
										curWeather = 0;

									//00432266
									if(pTimestamp == 0x0E0A1ACA && pAttack->Motion == 254 && (pAttack->SkillIndex == 32 || pAttack->SkillIndex == 34 || pAttack->SkillIndex == 36))
									{
										//004322BE
										int pLevel = pMob[conn].MOB.CurrentScore.Level; //31c
										int petSanc = BASE_GetItemSanc(&pMob[conn].MOB.Equip[PET]); //320
										switch(pAttack->SkillIndex)
											case 32:
												pDamage = (petSanc * 200) + (pLevel * 8);
												break;
											case 34:
												pDamage = (petSanc * 300) + (pLevel * 8);
												break;
											case 36:
												pDamage = (petSanc * 350) + (pLevel * 8);
												break;
									}
									else //00432376
									{
										pDamage = BASE_GetSkillDamage(skillId, &pMob[conn].MOB, curWeather, pMob[conn].WeaponDamage);
									}

									//004323B2
									int def = pMob[conn].MOB.CurrentScore.Defense; //324
									if(pTarget < MAX_PLAYER)
										def = def << 1;

									//004323E2
									if(pMob[conn].MOB.ClassInfo == 1 || pMob[conn].MOB.ClassInfo == 2)
										def = (def << 1) / 3;

									//00432424
									pDamage = BASE_GetSkillDamage(pDamage, def, calcskillmaster3);
									if(skillInstanceType == 1) //Fanatismo, Carga, Golpe_Mortal, Espada_da_Fênix, Golpe_Duplo, Contra_Ataque, Ataque_da_Alma, Punhalada_Venenosa, Nevoa_Venenosa, Som_das_Fadas, 
									{//Fúria_de_Gaia, Ataque_Fatal, Tempestade_De_Raios, Golpe_Felino, Explosão_Etérea, Lâmina_das_Sombras, Proteção_Das_Sombras
										int calcTdamage = 0; //328
										if(pTarget >= MAX_PLAYER)
											calcTdamage = pMob[pTarget].MOB.Learn;
										else
											calcTdamage = 10;

										pDamage = ((100 - calcTdamage) * pDamage) / 100; 
									}
									else //004324AB
									{
										if(skillInstanceType >= 2 && skillInstanceType <= 5) //2-Destino, 2-Espada_Flamejante, 3-Lamina_Congelada, 2-Exterminar, 2-Tempestade_De_Gelo, 4-Choque_Divino, 4-Julgamento_Divino, 2-Ataque_de_Fogo, 5-Relâmpago, 
										{//3-Lança_de_Gelo, 2-Tempestade_de_Meteoro, 3-Nevasca, 2-Fênix_de_Fogo, 2-Inferno, 2-Fera_Flamejante, 2-Espirito_Vingador, 2-Canhão_Guardião
											int getSkillInstanceType = skillInstanceType - 2; //32c
											int pResist = pMob[pTarget].MOB.Resist1 + getSkillInstanceType; //330
											if(pTarget < MAX_PLAYER)
												pResist = pResist / 2;

											pDamage = ((100 - pResist) * pDamage) / 100;
										}
									}

									//00432528
									if(skillInstanceType == 2) //Destino, Espada_Flamejante, Exterminar, Tempestade_De_Gelo, Ataque_de_Fogo, Fera_Flamejante
									{//
										int calc = 10 - i; //334
										if(calc < 0)
										{
											calc = 0;
											pAttack->Dam[i].TargetID = MOB_EMPTY;
										}

										pDamage = (pDamage * calc) / 10;
									}
									else //00432585
									{
										if(skillInstanceType == 4) //Giro_da_Fúria, Flecha_Mágica, Choque_Divino, Julgamento_Divino
										{
											int calc = i << 1 - 10; //338
											if(calc < 0)
											{
												calc = 0;
												pAttack->Dam[i].TargetID = MOB_EMPTY;
											}

											pDamage = (pDamage * calc) / 10;
										}
									}
								}
								else if(skillInstanceType == 6) //004325E9 - Cura, Recuperar, Renascimento
								{
									if(pMob[pTarget].MOB.CapeInfo == 4)
										continue;

									unsigned char getAttribute = GetAttribute(pMob[pTarget].TargetX, pMob[pTarget].TargetY); //33c
									getAttribute = getAttribute & PVP;
									if(pAttribute == 0 && getAttribute == 1)
									{
										pAttack->Dam[i].TargetID = MOB_EMPTY;
										pAttack->Dam[i].Damage = 0;
										continue;
									}

									//004326A0
									if(skillId == 27) //Cura
										pDamage = (saveSpecial * 2) + g_pSpell[skillId].InstanceValue;
									else
										pDamage = ((saveSpecial * 3) / 2) + g_pSpell[skillId].InstanceValue;

									pDamage = -pDamage;
									if(pDamage < 0 && pDamage > -6)
										pDamage = -6;

									int pTargetHP = pMob[pTarget].MOB.CurrentScore.Hp; //340
									if(pMob[pTarget].MOB.Equip[PET].Index == 786)
									{
										int pTargetItemSanc = BASE_GetItemSanc(&pMob[pTarget].MOB.Equip[PET]); //344
										if(pTargetItemSanc < 2)
											pTargetItemSanc = 2;

										pMob[pTarget].MOB.CurrentScore.Hp = pMob[pTarget].MOB.CurrentScore.Hp - (pDamage / pTargetItemSanc);
									}
									else //004327B7
									{
										pMob[pTarget].MOB.CurrentScore.Hp = pMob[pTarget].MOB.CurrentScore.Hp - pDamage;
									}

									//004327E3
									if(pMob[pTarget].MOB.CurrentScore.Hp > pMob[pTarget].MOB.CurrentScore.MaxHp)
										pMob[pTarget].MOB.CurrentScore.Hp = pMob[pTarget].MOB.CurrentScore.MaxHp;

									if(pTarget > 0 && pTarget < MAX_PLAYER)
										SetReqHp(pTarget);

									int pTargetHpFinal = pMob[pTarget].MOB.CurrentScore.Hp; //348
									int calc = (pTargetHpFinal - pTargetHP) >> 3; //34c
									if(calc > 120)
										calc = 120;
									if(calc < 0)
										calc = 0;

									//004328AE
									if(calc > 0 && conn != pTarget && conn > MOB_EMPTY && conn < MAX_PLAYER)
									{
										int getVillage = BASE_GetVillage(pMob[pTarget].TargetX, pMob[pTarget].TargetY); //350
										if(getVillage < 0 || getVillage >= 5)
										{
											if(unk1 < calc)
												unk1 = calc;
										}
									}
								}
								else if(skillInstanceType == 7) //00432933 - Flash
								{
									//0043293C
									pMob[pTarget].Mode = MOB_PEACE;
									pMob[pTarget].CurrentTarget = MOB_EMPTY;
									for(int j = MOB_EMPTY; j < MAX_ENEMY; j++) //354
										pMob[pTarget].EnemyList[j] = MOB_EMPTY;
								}
								else if(skillInstanceType == 8) //004329AE - Desintoxicar,
								{
									//004329BB
									int flagSkillOff = FALSE; //358
									for(int k = 0; k < MAX_AFFECT; k++) //35c
									{
										int skillAffectType = pMob[pTarget].MOB.Affect[k].Type;
										if(skillAffectType == 1 || skillAffectType == 3 || skillAffectType == 5 || skillAffectType == 7 || skillAffectType == 10 || skillAffectType == 12 || skillAffectType == 20)
										{
											pMob[pTarget].MOB.Affect[k].Type = 0;
											flagSkillOff = TRUE;
										}
									}

									if(flagSkillOff == TRUE)
									{
										pMob[pTarget].GetCurrentScore(pTarget);
										SendScore(pTarget);
									}
								}
								else if(skillInstanceType == 9) //00432AB2 - Teleporte,
								{
									//00432ABF
									if(pMob[pTarget].MOB.CurrentScore.Hp <= 0)
									{
										SendClientMessage(conn, g_pMessageStringTable[48]); //Não é possível summonar personagem morto.
										return;
									}

									//00432AEC
									unsigned char getAtt = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY); //364
									if(getAtt & CANTSUMMON != FALSE && pMob[conn].MOB.CurrentScore.Level < 1000)
									{
										SendClientMessage(conn, g_pMessageStringTable[49]); //Área restrita para uso.
										continue;
									}

									//00432B5A
									if(pMob[pTarget].MOB.CurrentScore.Hp > pMob[conn].MOB.CurrentScore.Hp + Special + 30)
									{
										SendClientMessage(conn, g_pMessageStringTable[50]); //Level muito alto para summonar.
										continue;
									}

									//00432BA1
									if((pMob[pTarget].TargetX & 0xFF00) == 0 && (pMob[pTarget].TargetY & 0xFF00) == 0)
									{
										SendClientMessage(conn, g_pMessageStringTable[96]); //Não pode usar aqui.
										return;
									}

									//00432BEF
									if(pTarget < MAX_PLAYER && pUser[pTarget].Mode == USER_PLAY)
									{
										DoSummon(pTarget, pMob[pTarget].TargetX, pMob[pTarget].TargetY);
										sprintf(temp, g_pMessageStringTable[52], pMob[conn].MOB.Name); //Você foi summonado por %s.
										SendClientMessage(pTarget, temp);
									}
								}
								else if(skillInstanceType == 10 && pTarget < MAX_PLAYER) //00432C76
								{
									for(int l = MAX_PLAYER; l < MAX_MOB; l++) //368
									{
										if(pMob[l].Mode == MOB_COMBAT && pMob[l].CurrentTarget == pTarget) //36c
										{
											for(int m = MOB_EMPTY; m < MAX_ENEMY; m++)
											{
												if(pMob[l].EnemyList[m] == pTarget)
													pMob[l].EnemyList[m] = conn;
											}

											pMob[l].CurrentTarget = conn;
										}
									}
								}
								else if(skillInstanceType == 11) //00432D76 - Evocar_Condor, Evocar_Javali_Selvagem, Evocar_Lobo_Selvagem,
								{//Evocar_Urso_Selvagem, Evocar_Grande_Tigre, Evocar_Gorila_Gigante, Evocar_Dragão_Negro, Evocar_Succubus
									//00432D83
									int skillInstanceValue = g_pSpell[skillId].InstanceValue; //370
									if(skillInstanceValue >= 1 && skillInstanceValue <= 50)
									{
										int genSummon = GenerateSummon(conn, skillInstanceValue - 1, 0); //374
										if(genSummon == 0)
										{
											pMob[conn].MOB.CurrentScore.Mp = mp;
											pUser[conn].CountMp = countMp;
										}
									}

									//00432DFD
									pDamage = 0;
								}
								else if(skillInstanceType == 12) //00432E0C - Chamas_Etéreas
								{
									//00432E19
									int targetLevel = pMob[pTarget].MOB.CurrentScore.Level; //378
									int level = pMob[conn].MOB.CurrentScore.Level; //37c

									int calcLevel = 100; //380
									if(targetLevel + 10 > pLevel)
									{
										int getCalcLevel = (targetLevel + 10) - pLevel; //384
										calcLevel = (getCalcLevel << 2) - calcLevel;
									}

									//00432E8F
									int Rand = rand() % 100; //388
									if(Rand > calcLevel || pTarget < MAX_PLAYER || pMob[pTarget].MOB.CurrentScore.Hp < pMob[pTarget].MOB.CurrentScore.MaxHp || pMob[pTarget].MOB.CapeInfo == 6)
										continue;

									//00432EE8
									RemoveParty(pTarget);
									pMob[pTarget].MOB.CapeInfo = 4;
									pMob[pTarget].RouteType = 5;
									pMob[pTarget].CurrentTarget = MOB_EMPTY;
									pMob[pTarget].MOB.BaseScore.Level = level;
									pMob[pTarget].MOB.CurrentScore.Level = level;
									memset(pMob[pTarget].EnemyList, 0x0, MAX_ENEMY * 2);
									pMob[pTarget].Mode = MOB_PEACE;

									int memberPartyCount = 0; //38c
									int n; //390
									for(n = MOB_EMPTY; n < MAX_PARTY; n++)
									{
										int pLeaderPartyId = pMob[pLeader].PartyList[n]; //394
										if(pLeaderPartyId == MOB_EMPTY)
											continue;

										memberPartyCount++;
									}

									//00433023
									if(memberPartyCount == MOB_EMPTY)
										SendAddParty(pLeader, pLeader, 0);

									for(n = MOB_EMPTY; n < MAX_PARTY; n++) //390
									{
										int otherLeaderPartyId = pMob[pLeader].PartyList[n]; //398
										if(otherLeaderPartyId == MOB_EMPTY)
											break;
									}

									if(n < MAX_PARTY)
									{
										//004330A2
										pMob[pLeader].PartyList[n] = pTarget;
										pMob[pTarget].Leader = pLeader;
										SendAddParty(pLeader, pTarget, n + 1);
										for(int o = MOB_EMPTY; o < MAX_PARTY; o++) //39c
										{
											int memberPartyId = pMob[pLeader].PartyList[o]; //3a0
											if(memberPartyId <= MOB_EMPTY || memberPartyId >= MAX_PLAYER)
												continue;

											SendAddParty(memberPartyId, pTarget, n + 1);
										}
									}

									//00433175
									pMob[pTarget].MOB.Affect[0].Type = 24;
									pMob[pTarget].MOB.Affect[0].Value = 0;
									pMob[pTarget].MOB.Affect[0].Level = 0;
									pMob[pTarget].MOB.Affect[0].Time = 20;

									pMob[pTarget].Summoner = conn;
									int baseDefense = pMob[pTarget].MOB.BaseScore.Defense; //3a4
									int baseAttack = pMob[pTarget].MOB.BaseScore.Attack; //3a8
									pMob[pTarget].MOB.BaseScore.Defense = (baseAttack + baseAttack) - 400;
									pMob[pTarget].MOB.BaseScore.Attack = (baseDefense / 2) + 200;
									pMob[pTarget].GetCurrentScore(pTarget);

									MSG_STANDARDPARM pSetClan; //3ac - 3b8
									pSetClan.Header.PacketId = _MSG_SetClan;
									pSetClan.Header.Size = sizeof MSG_STANDARDPARM;
									pSetClan.Header.ClientId = pTarget;
									pSetClan.Parm1 = pMob[pTarget].MOB.CapeInfo;

									if(pTimestamp == 0x0E0A1ACA)
										pAttack->Header.TimeStamp = CurrentTime;
									
									//004332C5
									GridMulticast(pMob[pTarget].TargetX, pMob[pTarget].TargetY, (MSG_STANDARD*)&pSetClan, 0);
								}

								//004332FC
								if(skillId == 6) //Fúria_Divina
								{
									//00433309
									if(pTarget >= MAX_PLAYER && pMob[pTarget].MOB.Merchant != 0)
										break;

									if(pMob[pTarget].MOB.CapeInfo == 6)
										break;

									pMob[pTarget].Route[0] = 0;
									int tX = pMob[conn].TargetX; //3bc
									if(tX < pMob[pTarget].TargetX)
										tX++;

									if(tX > pMob[pTarget].TargetX)
										tX--;

									int tY = pMob[conn].TargetY; //3c0
									if(tY < pMob[pTarget].TargetY)
										tY++;

									if(tY > pMob[pTarget].TargetY)
										tY--;

									if(GetEmptyMobGrid(pTarget, &tX, &tY) == FALSE)
										break;

									int skillMaster2 = pMob[conn].MOB.CurrentScore.Master[1]; //3c4
									int calcskillmaster2 = (skillMaster2 / 10) + 40; //3c8
									if(pTarget > MAX_PLAYER)
										calcskillmaster2 = (skillMaster2 / 5) + 60;

									//004334A0
									int restLevel = pMob[conn].MOB.CurrentScore.Level - pMob[pTarget].MOB.CurrentScore.Level; //3cc
									restLevel = restLevel >> 1;

									if(rand() % 100 >= calcskillmaster2 + restLevel)
										break;

									MSG_Action pAction; //3cc - 400
									GetAction(pTarget, tX, tY, &pAction);
									pAction.Type = 7;
									pAction.Speed = 2;

									GridMulticast(pTarget, tX, tY, (MSG_STANDARD*)&pAction);

									if(pTarget < MAX_PLAYER)
										pUser[pTarget].cSock.AddMessage((char*)&pAction, sizeof MSG_Action);

									break;
								}
								
								if(skillId == 22) //00433587 //Exterminar
								{
									//00433594
									int curMp = pMob[conn].MOB.CurrentScore.Mp; //404
									pMob[conn].MOB.CurrentScore.Mp = 0;
									pUser[conn].CountMp = 0;
									pAttack->CurrentMp = 0;

									int skillMaster4 = pMob[conn].MOB.CurrentScore.Master[3]; //408
									int curSTR = pMob[conn].MOB.CurrentScore.STR; //40c
									pDamage = (pDamage + curMp) + (curSTR / 2);

									int tX = pMob[pTarget].TargetX; //410
									int tY = pMob[pTarget].TargetY; //414
									int tXx = tX; //418
									int tYy = tY; //41c
									if(GetEmptyMobGrid(conn, &tXx, &tYy) != 0 && pMob[pTarget].MOB.Equip[FACE].Index != 219 && pMob[pTarget].MOB.Equip[FACE].Index != 220)
									{
										//004336CE
										MSG_Action pAction; //420 - 450
										GetAction(pTarget, tXx, tYy, &pAction);
										pAction.Type = 2;
										pAction.Speed = 2;

										GridMulticast(pTarget, tXx, tYy, (MSG_STANDARD*)&pAction);
										if(pTarget < MAX_PLAYER)
											pUser[pTarget].cSock.AddMessage((char*)&pAction, sizeof MSG_Action);

										GetAction(conn, tX, tY, &pAction);
										pAction.Type = 2;
										pAction.Speed = 2;

										GridMulticast(conn, tX, tY, (MSG_STANDARD*)&pAction);
										pUser[conn].cSock.AddMessage((char*)&pAction, sizeof MSG_Action);
									}
								}
								else if(skillId == 30) //004337CB //Julgamento_Divino
								{
									//004337D4
									pDamage = pDamage + pHp;
									pMob[conn].MOB.CurrentScore.Hp = (pMob[conn].MOB.CurrentScore.Hp * 2) / 3;
									pUser[conn].CountHp = pMob[conn].MOB.CurrentScore.Hp;
								}
								else if(skillId == 41) //00433834 //Velocidade
								{
									//00433841
									int calcEnemy = (Special / 25) + 2; //454
									if(calcEnemy >= MAX_TARGET)
										calcEnemy = MAX_TARGET;

									if(calcEnemy <= 1)
										calcEnemy = 2;

									for(int p = MOB_EMPTY; p < calcEnemy && (p < 1 || pSize > sizeof MSG_AttackOne) && (p < 2 || pSize > sizeof MSG_AttackTwo); p++) //458
									{
										//004338D6
										int getTargetId = pAttack->Dam[calcEnemy].TargetID; //45c
										if(getTargetId <= MOB_EMPTY || getTargetId >= MAX_PLAYER)
											continue;

										if(pUser[getTargetId].Mode != USER_PLAY)
											continue;

										if(SetAffect(getTargetId, skillId, skillDelay, Special) == 0)
											continue;

										SendScore(getTargetId);
									}

									break;
								}
								else if(skillId == 44) //00433957 //Arma_Mágica
								{
									//00433964
									int calcEnemy = (Special / 25) + 2; //460
									if(calcEnemy >= MAX_TARGET)
										calcEnemy = MAX_TARGET;

									if(calcEnemy <= 1)
										calcEnemy = 2;

									for(int q = MOB_EMPTY; q < calcEnemy && (q < 1 || pSize > sizeof MSG_AttackOne) && (q < 2 || pSize > sizeof MSG_AttackTwo); q++) //464
									{
										//004339F9
										int getTargetId = pAttack->Dam[calcEnemy].TargetID; //468
										if(getTargetId <= MOB_EMPTY || getTargetId >= MAX_PLAYER)
											continue;

										if(pUser[getTargetId].Mode != USER_PLAY)
											continue;

										if(SetAffect(getTargetId, skillId, skillDelay, Special) == 0)
											continue;

										SendScore(getTargetId);
									}

									break;
								}

								//00433A7A
								int skillAggressive = g_pSpell[skillId].Aggressive; //46c
								int flagRegenMp = TRUE; //470
								if(skillAggressive != 0)
								{
									if(pLeader == pTargetLeader || pGuildId == pTargetGuildId)
										flagRegenMp = FALSE;

									int skillAffectResist = g_pSpell[skillId].AffectResist; //474
									int difLevel = pMob[pTarget].MOB.CurrentScore.Level - pMob[conn].MOB.CurrentScore.Level; //478
									difLevel = difLevel / 2;
									if(skillAffectResist >= 1 && skillAffectResist <= 4)
									{
										int random = rand() % 100; //47c
										if(random < pMob[pTarget].MOB.RegenMP + skillAffectResist + difLevel)
											flagRegenMp = FALSE;
									}

									//00433B74
									if((pMob[pTarget].MOB.AffectInfo & RSV_IMUNIT) != FALSE)
										flagRegenMp = FALSE;

									if(conn < MAX_PLAYER && pMob[pTarget].MOB.CapeInfo == 6)
										flagRegenMp = FALSE;
								}

								//00433BC3
								if(flagRegenMp != FALSE)
								{
									if(SetAffect(pTarget, skillId, skillDelay, Special) != 0)
										unk2 = TRUE;

									if(SetTick(pTarget, skillId, skillDelay, Special) != 0)
										unk2 = TRUE;

									if(unk2 != FALSE)
									{
										pMob[pTarget].GetCurrentScore(pTarget);
										SendScore(pTarget);
									}
								}

								//00433C6A
								if(skillId == 64 || skillId == 66 || skillId == 68 || skillId == 70 || skillId == 71)
									SendScore(conn);
							}
							else //00433C9E
							{
								Log("err, dam not -2, -1 msg_attack", pUser[conn].AccountName, pUser[conn].IP);
								return;
							}

							//00433CD0
							pAttack->Dam[i].Damage = pDamage;
							if(pDamage <= 0)
								continue;

							if(pTarget < MAX_PLAYER || pMob[pTarget].MOB.CapeInfo == 4) // calculo do dano adicional do bonus de perfuração
							{
								//00433D17
								if(pAttack->DoubleCritical & 4 != FALSE)
								{
									int calcSecondDamage = pDamage - pAttack->Dam[1].Damage; //480
									calcSecondDamage = calcSecondDamage >> 2;
									pDamage = pAttack->Dam[1].Damage + calcSecondDamage;
								}
								else
								{
									pDamage = pDamage >> 2;
								}
							}

							//00433D85
							if(pMob[conn].ForceDamage != 0)
							{
								//00433D97
								if(pDamage == 1)
									pDamage = pMob[conn].ForceDamage;
								else
								{
									if(pDamage > 0)
										pDamage = pDamage + pMob[conn].ForceDamage;
								}

								pAttack->Dam[i].Damage = pDamage;
							}

							//00433DF3
							if(pTargetLeader == pLeader || pTargetGuildId == pGuildId)
								pDamage = 0;

							if(pTarget >= MAX_PLAYER && flagCapeInfo != FALSE)
								pDamage = 0;

							int pTargetSummoner = pTarget; //484
							if(pTarget >= MAX_PLAYER && pMob[pTarget].MOB.CapeInfo == 4 && pMob[pTarget].Summoner > MOB_EMPTY && pMob[pTarget].Summoner < MAX_PLAYER && pUser[pMob[pTarget].Summoner].Mode == USER_PLAY)
								pTargetSummoner = pMob[pTarget].Summoner;

							//00433ECF
							if(pTargetSummoner < MAX_PLAYER)
							{
								//00433EDC
								int pPkPoint = GetPKPoint(conn); //488
								int pSummonerPkPoint = GetPKPoint(pTargetSummoner); // 48c
								int pArena = BASE_GetArena(pMob[conn].TargetX, pMob[conn].TargetY); //490
								int pVillage = BASE_GetVillage(pMob[conn].TargetX, pMob[conn].TargetY); //494
								int divTargetX = pMob[conn].TargetX >> 7; //498
								int divTargetY = pMob[conn].TargetY >> 7; //49c
								int otherflag = FALSE; //4a0
								int flagGuildWar = FALSE; //4a4
								int pGuildIndex = pMob[conn].MOB.GuildIndex; //4a8
								int pSummonerGuildIndex = pMob[pTargetSummoner].MOB.GuildIndex; //4ac
								int MaxGuildIndex = MAX_GUILDINDEX; //4b0

								//00433FEC
								if(pGuildIndex > 0 && pGuildIndex < MaxGuildIndex && pSummonerGuildIndex > 0 && pSummonerGuildIndex < MaxGuildIndex && g_pGuildWar[pGuildIndex] == pSummonerGuildIndex && g_pGuildWar[pSummonerGuildIndex] == pGuildIndex)
									flagGuildWar = TRUE;

								//00434054
								if(CastleState != 0 && divTargetX == 8 && divTargetY == 13)
									flagGuildWar = TRUE;

								//00434079
								if(divTargetX == 1 && divTargetY == 31)
									otherflag = TRUE;

								//00434095
								if(pArena == MAX_GUILDZONE && pVillage == MAX_GUILDZONE && otherflag == FALSE && flagGuildWar == FALSE)
								{
									if(pPkPoint <= 10 && pSummonerPkPoint > 10)
									{
										sprintf(temp, g_pMessageStringTable[209], pPkPoint); //Você não pode matar esse personagem.
										SendClientMessage(conn, temp);
										pDamage = 0;
									}
									else
									{
										//00434114
										int pTargetSummonerGuilty = GetGuilty(pTargetSummoner); //4b4
										int pGuilty = GetGuilty(conn); //4b8
										if(pTargetSummonerGuilty == 0 && pSummonerPkPoint > 10 && pDamage > 0)
										{
											SetGuilty(conn, 8);
											if(pGuilty == 0)
											{
												MSG_CreateMob pCreateMob; // 4bc - 524
												GetCreateMob(conn, &pCreateMob);
												GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&pCreateMob, FALSE);
											}
										}
									}
								}

								//004341B1
								int pTargetParry = GetParryRate(&pMob[pTarget].MOB, pMob[pTarget].Parry); //528
								int pRand = rand() % 1000; //52c
								if(pRand < pTargetParry)
								{
									pDamage = -3;
									if(pMob[pTarget].MOB.AffectInfo & RSV_IMUNIT != 0 && pRand < 100)
										pDamage = -4;
								}
							}

							//00434241 - codigo atualizado - reconhecendo as evoluções e os MAX_LEVEL
							if(((pMob[conn].MOB.MobType == MORTAL || pMob[conn].MOB.MobType == ARCH) && pLevel == MAX_LEVELMA) || (pMob[conn].MOB.MobType >= CELESTIAL && pLevel == MAX_LEVELCSH))
							{
								if(pTarget < MAX_PLAYER || pMob[pTarget].MOB.CapeInfo == 4 || pMob[pTarget].MOB.CapeInfo != 0)
								{
									//0043428D
									unsigned char pTargetMapAttribute = GetAttribute(pMob[pTarget].TargetX, pMob[pTarget].TargetY); //530
									unsigned char pMapAttribute = GetAttribute(pMob[conn].TargetX, pMob[conn].TargetY); //534
									if(pTargetMapAttribute & VILLAGE != 0 || pTargetMapAttribute & PVP == 0)
										pDamage = 0;

									if(pMapAttribute & VILLAGE != 0 || pMapAttribute & PVP == 0)
										pDamage = 0;
								}
							}

							//0043434E - codigo atualizado
							if(pMob[pTarget].MOB.CapeInfo == 6 && ((pMob[conn].MOB.MobType == MORTAL || pMob[conn].MOB.MobType == ARCH) && pLevel < MAX_LEVELMA) || (pMob[conn].MOB.MobType >= CELESTIAL && pLevel < MAX_LEVELCSH))
								pDamage = 0;

							pAttack->Dam[i].Damage = pDamage;
							if(pDamage <= 0)
								continue;

							//004343A2
							if(pMob[conn].MOB.AffectInfo & RSV_FROST != FALSE)
							{
								int _pRand = rand() % 2; //53c
								if(_pRand == 0)
								{
									int pSkillMaster1 = pMob[conn].MOB.CurrentScore.Master[1];
									if(SetAffect(pTarget, 36, pSkillMaster1 + 100, pSkillMaster1) != 0)
										SendScore(pTarget);
								}
							}

							//00434426
							int pHpOurDamage; //208c
							if(pMob[pTarget].MOB.CurrentScore.Hp < pDamage)
								pHpOurDamage = pMob[pTarget].MOB.CurrentScore.Hp;
							else
								pHpOurDamage = pDamage;

							//00434468
							int _pHpOurDamage = pHpOurDamage; //540
							int calcExp = (pMob[pTarget].MOB.Exp * _pHpOurDamage) / pMob[pTarget].MOB.CurrentScore.MaxHp; //544
							calcExp = GetExpApply(calcExp, conn, pTarget);
							if(pMob[pTarget].MOB.CapeInfo == 4)
								calcExp = 0;

							if(pTarget >= MAX_PLAYER)
								unk = unk + calcExp;

							if(pTarget > 0 && pTarget < MAX_PLAYER && pDamage > 0)
							{
								if(pMob[pTarget].ReflectDamage > 0)
									pDamage = pDamage - pMob[pTarget].ReflectDamage;

								if(pDamage <= 0)
								{
									pDamage = 0;
									pAttack->Dam[i].Damage = pDamage;
									continue;
								}

								pAttack->Dam[i].Damage = pDamage;
							}

							//004345BE
							int _pDamage = pDamage; //548
							int _calcDamage = 0; //54c
							int pTargetMountId = pMob[pTarget].MOB.Equip[MOUNT].Index; //550
							if(pTarget < MAX_PLAYER && pTargetMountId >= 2360 && pTargetMountId < 2390 && pMob[pTarget].MOB.Equip[MOUNT].EF1 > 0)
							{
								_pDamage = (pDamage * 3) >> 2;
								_calcDamage = pDamage - _pDamage;
								if(_pDamage <= 0)
									_pDamage = 1;

								pAttack->Dam[i].Damage = _pDamage;
							}

							//0043467E
							int tDamage = _pDamage; // 554
							if(pMob[pTarget].MOB.Equip[PET].Index == 786)
							{
								//004346A8
								int itemSanc = BASE_GetItemSanc(&pMob[pTarget].MOB.Equip[PET]); //558
								if(itemSanc < 2)
									itemSanc = 2;

								tDamage = _pDamage / itemSanc;
								if(tDamage > pMob[pTarget].MOB.CurrentScore.Hp)
									tDamage = pMob[pTarget].MOB.CurrentScore.Hp;

								pMob[pTarget].MOB.CurrentScore.Hp = pMob[pTarget].MOB.CurrentScore.Hp - tDamage;
							}
							else
							{
								//00434751
								if(tDamage > pMob[pTarget].MOB.CurrentScore.Hp)
									tDamage = pMob[pTarget].MOB.CurrentScore.Hp;

								pMob[pTarget].MOB.CurrentScore.Hp = pMob[pTarget].MOB.CurrentScore.Hp - tDamage;
							}

							//004347B1
							if(_calcDamage > 0)
								ProcessAdultMount(pTarget, _calcDamage);

							if(LOCALSERVER != 0)
							{
								sprintf(temp, "%s: %d(%d) - %d", pMob[pTarget].MOB.Name, _pDamage, tDamage, pMob[pTarget].MOB.CurrentScore.Hp);
								SendSay(pTarget, temp);
							}

							//00434834
							if(pTarget > MOB_EMPTY && pTarget < MAX_PLAYER)
							{
								pUser[pTarget].CountHp = pUser[pTarget].CountHp - pDamage;
								SetReqHp(pTarget);
							}

							if(pTarget > MAX_PLAYER && pMob[pTarget].MOB.CapeInfo == 4)
								LinkMountHp(pTarget);

							if(pMob[pTarget].MOB.CurrentScore.Hp <= 0)
							{
								pMob[pTarget].MOB.CurrentScore.Hp = 0;
								unknow[i] = pTarget;
								continue;
							}

							//004348F5
							if(pMob[pTarget].Mode != MOB_EMPTY && pMob[pTarget].MOB.CurrentScore.Hp > 0)
							{
								//00434929
								SetBattle(pTarget, conn);
								pMob[conn].CurrentTarget = pTarget;
								int leader = pMob[conn].Leader; //55c
								if(leader <= MOB_EMPTY)
									leader = conn;

								int r; //560
								for(r = MOB_EMPTY; r < MAX_PARTY; r++)
								{
									int partyMemberId = pMob[leader].PartyList[r]; //564
									if(partyMemberId <= MAX_PLAYER)
										continue;

									if(pMob[partyMemberId].Mode == MOB_EMPTY || pMob[partyMemberId].MOB.CurrentScore.Hp <= 0)
									{
										if(pMob[partyMemberId].Mode != MOB_EMPTY)
											DeleteMob(partyMemberId, 1);

										pMob[leader].PartyList[r] = MOB_EMPTY;
									}
									else
										SetBattle(partyMemberId, pTarget);
								}

								//00434A5B
								leader = pMob[pTarget].Leader;
								if(leader <= MOB_EMPTY)
									leader = pTarget;

								for(r = MOB_EMPTY; r < MAX_PARTY; r++)
								{
									int ptMemberId = pMob[leader].PartyList[r]; //568
									if(ptMemberId <= MAX_PLAYER)
										continue;

									if(pMob[ptMemberId].Mode == MOB_EMPTY || pMob[ptMemberId].MOB.CurrentScore.Hp <= 0)
									{
										if(pMob[ptMemberId].Mode != MOB_EMPTY)
											DeleteMob(ptMemberId, 1);

										pMob[leader].PartyList[r] = MOB_EMPTY;
									}
									else
										SetBattle(ptMemberId, conn);
								}
							}
						}

						//00434B6B
						if(unk1 > 0)
							unk = unk1;

						if(skillId == 30) //Julgamento_Divino
							SendSetHpMp(conn);

						if(DOUBLEMODE == TRUE)
							unk = unk * 2;
						if(unk <= 0)
							unk = 0;
						if(unk > 200)
							unk = 200;

						pMob[conn].MOB.Exp = pMob[conn].MOB.Exp + unk;
						pAttack->CurrentExp = pMob[conn].MOB.Exp;
						if(pTimestamp == 0x0E0A1ACA)
							pAttack->Header.TimeStamp = CurrentTime;

						GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)pAttack, FALSE);

						for(int s = MOB_EMPTY; s < MAX_TARGET; s++) //56c
						{
							if(unknow[s] > MOB_EMPTY && unknow[s] < MAX_MOB && pMob[unknow[s]].Mode != MOB_EMPTY)
								MobKilled(unknow[s], conn, 0, 0);
						}

						//00434CF2
						int retSegment = pMob[conn].CheckGetLevel(); //570
						if(retSegment >= 1 && retSegment <= 4)
						{
							if(retSegment == 4)
								SendClientMessage(conn, g_pMessageStringTable[53]); //++++ Parabenz, Subiu de Level ++++
							if(retSegment == 3)
								SendClientMessage(conn, g_pMessageStringTable[54]); //Adquiriu 3/4 de bônus.
							if(retSegment == 2)
								SendClientMessage(conn, g_pMessageStringTable[55]); //Adquiriu 2/4 de bônus.
							if(retSegment == 1)
								SendClientMessage(conn, g_pMessageStringTable[56]); //Adquiriu 1/4 de bônus.

							SendScore(conn);
							SendEmotion(conn, 0xE, 3);
							if(retSegment == 4)
							{
								//00434DB7
								SendEtc(conn);
								int pkPoint = GetPKPoint(conn) + 5; //574
								SetPKPoint(conn, pkPoint);
								MSG_CreateMob pCreateMob; //578 - 5e0
								GetCreateMob(conn, &pCreateMob);
								GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&pCreateMob, FALSE);
								sprintf(temp, "lvl %s level up to %d", pMob[conn].MOB.Name, pMob[conn].MOB.BaseScore.Level);
								Log(temp, pUser[conn].AccountName, pUser[conn].IP);
							}
						}

						break;
					}

void CMob::GetCurrentScore(int idx)
{
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// Guican por descompilá-la

	if(idx < MAX_USER)
		pMob[idx].MOB.CapeInfo = 0;

	if(idx < MAX_USER && MOB.bStatus.Level < 1000)
	{
		MOB.Resist1 = BASE_GetMobAbility(&MOB, EF_RESIST1);
		MOB.Resist2 = BASE_GetMobAbility(&MOB, EF_RESIST2);
		MOB.Resist3 = BASE_GetMobAbility(&MOB, EF_RESIST3);
		MOB.Resist4 = BASE_GetMobAbility(&MOB, EF_RESIST4);

		MOB.Equip[FACE].EF1 = 0;
		MOB.Equip[FACE].EFV1 = 0;
		MOB.AffectInfo = 0;
	}
	else if(idx >= MAX_USER)
	{
		int geneidx = GenerateIndex;
		if(geneidx > 0 && geneidx < MAX_NPCGENERATOR)
		{
			MOB.Resist1 = mNPCGen.pList[geneidx].Leader.Resist1;
			MOB.Resist2 = mNPCGen.pList[geneidx].Leader.Resist2;
			MOB.Resist3 = mNPCGen.pList[geneidx].Leader.Resist3;
			MOB.Resist4 = mNPCGen.pList[geneidx].Leader.Resist4;
		}
	}

	Parry = BASE_GetMobAbility(&MOB, EF_PARRY);

	if(idx < MAX_USER)
	{
		pUser[idx].Range = BASE_GetMobAbility(&MOB, EF_RANGE);
	}

	BASE_GetCurrentScore(MOB, Affect);
    int Critical = BASE_GetMobAbility(&MOB, EF_CRITICAL);
	if(Critical >= 255) // implementado para proteger o overflow da variavel
		Critical = 255;

	MOB.Critical = Critical;

	int ItemInt = MOB.Status.INT - MOB.bStatus.INT;
	int ItemCon = MOB.Status.CON - MOB.bStatus.CON;
	int MPDelta = ItemInt << 1;
	int HPDelta = ItemCon << 1;

	MOB.Status.MaxHp = MOB.Status.MaxHp + HPDelta;
    MOB.Status.MaxMp = MOB.Status.MaxMp + MPDelta;
	if(MOB.Status.Hp >= MOB.Status.MaxHp) // implementado para proteger o overflow da variavel
		MOB.Status.Hp = MOB.Status.MaxHp;

	if(MOB.Status.Mp >= MOB.Status.MaxMp) // implementado para proteger o overflow da variavel
		MOB.Status.Mp = MOB.Status.MaxMp;

	int w1 = BASE_GetItemAbility(&MOB.Equip[WEAPON], EF_DAMAGE);
	int w2 = BASE_GetItemAbility(&MOB.Equip[SHIELD], EF_DAMAGE);
	if(w1 > w2)
		WeaponDamage = w1 + (w2 / 3);
	else
		WeaponDamage = w2 + (w1 / 3);

	//00412688
	int FirstWeaponID = MOB.Equip[WEAPON].Index;
	int FirstWeaponPOS = g_pItemList[FirstWeaponID].Pos;
	if(FirstWeaponID >= 0 || FirstWeaponID < MAX_ITEMLIST)
	{
		if(FirstWeaponPOS == WEAPON_POS || FirstWeaponPOS == WEAPON2HAND_POS)
		{
			int sanc = BASE_GetItemSanc(&MOB.Equip[WEAPON]);
			if(sanc == 9)
			{
				WeaponDamage += 40;
			}
		}
	}

	//004126F3
	int SecondWeaponID = MOB.Equip[SHIELD].Index;
	int SecondWeaponPOS = g_pItemList[SecondWeaponID].Pos;
	if(SecondWeaponID >= 0 || SecondWeaponID < MAX_ITEMLIST)
	{
		if(SecondWeaponPOS == WEAPON_POS || SecondWeaponPOS == WEAPON2HAND_POS)
		{
			int sanc = BASE_GetItemSanc(&MOB.Equip[SHIELD]);
			if(sanc == 9)
			{
				WeaponDamage += 40;
			}
		}
	}

	ExpBonus = 0;
	DropBonus = 0;
	ForceDamage = 0;
	ReflectDamage = 0;

	for(int i = 0; i < 16; i++)
	{
		int EquipID = MOB.Equip[i].Index;
		if(EquipID <= 0 || EquipID > MAX_ITEMLIST)
			continue;

		if(g_pItemList[EquipID].Grade == 5)
			DropBonus = DropBonus + 8;

		if(g_pItemList[EquipID].Grade == 6)
			ForceDamage = ForceDamage + 20;

		if(g_pItemList[EquipID].Grade == 7)
			ExpBonus = ExpBonus + 2;

		if(g_pItemList[EquipID].Grade == 8)
			ReflectDamage = ReflectDamage + 20;
	}

	return;
}

void ProcessDecayItem(void) 
{
	//0x004012F8


}

int CreateMob(char* Name, int arg2, int arg3, char* arg4) // Não está terminada, termino quando voltar ao pc
{
	//0x004013F7
	int LOCAL_1 = GetEmptyNPCMob();
	
	if(!LOCAL_1)
	{
		sprintf(0x008B7E678, "err, no emptymob create %s", arg1);

		Log(0x008B7E678, "-system", 0); 

		return -1;
	}

	strcpy(CMob[LOCAL_1].Name, arg1);
	memset(CMob[LOCAL_1].PartyList, 0, 0x18); 

	int LOCAL_2 = ReadMob(CMob(LOCAL_1], arg4);

	if(!LOCAL_2)
		return -1;

	CMob[LOCAL_1].Name[15] = 0;
	CMob[LOCAL_1].BaseScore.Reserved = 0;

	int LOCAL_3 = 0;
	for(; LOCAL_3 < 16; LOCAL_3++)
	{
		if(CMob[LOCAL_1].Name[LOCAL_3] == 0x5F)
			CMob[LOCAL_1].Name[LOCAL_3] = 0x20;
	}

	memset(CMob[LOCAL_1].Affects, 0, 0x20); 

	for(LOCAL_3 = 0; LOCAL_3 < 5; LOCAL_3++)
	{
		if(CMob[LOCAL_1].Equip[0].Index == 219)
		{
			CMob[LOCAL_1].SegmentListX[LOCAL_3] = arg2;
			CMob[LOCAL_1].SegmentListY[LOCAL_3] = arg3;

			continue;
		}

		CMob[LOCAL_1].SegmentListX[LOCAL_3] = arg2 + ((Rand() % 5) - 2);
		CMob[LOCAL_1].SegmentListY[LOCAL_3] = arg3 + ((Rand() % 5) - 2);
	}

	if(CMob[LOCAL_1].Equip[0].Index == 219)
	{
		int LOCAL_4 = 0x008BF1858;

		if(LOCAL_4 > 0 && LOCAL_4 < 100)
		{
			if(CUsers[LOCAL_4].Status == 22)
			{
				CMob[LOCAL_1].Equip[15].Index = CMob[LOCAL_4].Equip[15].Index;
				CMob[LOCAL_1].Equip[15].EFV2 = CMob[LOCAL_4].Equip[15].EFV2;

				if(CMob[LOCAL_1].Equip[0].Index == 219)
				{
					CMob[LOCAL_1].Equip[12].Index = CMob[LOCAL_4].Equip[12].Index;
					CMob[LOCAL_1].Equip[12].EFV2 = CMob[LOCAL_4].Equip[12].EFV2;
					
					GetGuild_OL1(LOCAL_1);

					if(CMob[LOCAL_1].Equip[12].Index == 509)
						CMob[LOCAL_1].Equip[12].Index = 508;
				}
			}
		}
	}

	CMob[LOCAL_1].GenerateIndex = -1; // Byte 960 da st_mob
	CMob[LOCAL_1].Formation = 0; // Byte 796
	CMob[LOCAL_1].RouteType = 0;
	CMob[LOCAL_1].Mode = 4;
	CMob[LOCAL_1].SegmentProgress = 0;
	CMob[LOCAL_1].Leader = 0;
	CMob[LOCAL_1].WaitSec = 10;
	CMob[LOCAL_1].LastTime = 0x008BF17D8;

	CMob::GetCurrentScore(100); // PUSH 64, ECX = CMob[LOCAL_1]

	CMob[LOCAL_1].Status.curHP = CMob[LOCAL_1].Status.maxHP;
	CMob[LOCAL_1].SegmentDirection = 0;

	memset(CMob[LOCAL_1].EnemyList, 0, 0x08);

	int  LOCAL_5 = CMob[LOCAL_1].SegmentListX[0],
		 LOCAL_6 = CMob[LOCAL_1].SegmentListY[0],
		 LOCAL_7 = GetEmptyMobGrid(LOCAL_1, &LOCAL_5, &LOCAL_6);

	if(!LOCAL_7)
	{
		strcpy(0x008B7E678, "err,No empty mobgrid:%s x:%d y:%d", Name, CMob[LOCAL_1].SegmentListX[0], CMob[LOCAL_1].SegmentListX[0]);
		Log(0x008B7E678, "-system", 0); 

		CMob[LOCAL_1].Mode = 0;
		CMob[LOCAL_1].Name[0] = 0;
		CMob[LOCAL_1].GenerateIndex = 0;

		return -2;
	}

	CMob[LOCAL_1].SegmentX = LOCAL_5;
	CMob[LOCAL_1].TargetX  = LOCAL_5;
	CMob[LOCAL_1].LastX    = LOCAL_5;

	CMob[LOCAL_1].SegmentY = LOCAL_6;
	CMob[LOCAL_1].TargetY  = LOCAL_6;
	CMob[LOCAL_1].LastY    = LOCAL_6;

	int LOCAL_8 = CMob[LOCAL_1].bStatus.maxMP;

	if(LOCAL_8)
	{
		SetAffect(LOCAL_1, LOCAL_8, 0x7530, 0xC8);
		SetTick(LOCAL_1, LOCAL_8, 0x7530, 0xC8);
	}

	MSG_CREATEMOB P;
	GetCreateMob(LOCAL_1, &P);

	int LOCAL_9 = (LOCAL_9 & 0x0FFFF) | 2;
	
	LOCAL_6 = LOCAL_6 << 0x0D;

	int UNKADRESS = (LOCAL_6 + LOCAL_5 * 2 + 0X003B07D14);
	UNKADRESS = LOCAL_1;
	// Provavelmente algum buffer que eu não sei qual é

	GridMulticast_OL2(LOCAL_5, LOCAL_6, &P, 0);

	return 1;
}

int GetAngle(int arg1, int arg2)
{ 
	//0x0040157D

	if(!arg1 || !arg2)
		return -1;


}

int GetEnemyFromView(/*Falso argumento*/int Cid)
{
	//0x0040151E

	//POP ECX
    //MOV [LOCAL.1],ECX
	st_Mob *LOCAL_1 = GetMobFromIndex(Cid);
	
	int LOCAL_2 = 0x9, //MOV [LOCAL.2],9
		LOCAL_3 = 0x9, //MOV [LOCAL.3],9
		LOCAL_4 = LOCAL_1->TargetX,
		LOCAL_5 = LOCAL_1->TargetY;

	if(LOCAL_1->CapeInfo != 7)
	{
	    if(LOCAL_1->CapeInfo == 8)
		{
			LOCAL_3 = 0x13;
			LOCAL_2 = 0x13;

			LOCAL_4 -= LOCAL_1->TargetX - 6;
			LOCAL_5 -= LOCAL_1->TargetY - 6;
		}
	}

	int LOCAL_6 = LOCAL_4,
		LOCAL_7 = LOCAL_5,
		LOCAL_8 = LOCAL_4 + LOCAL_3,
		LOCAL_9 = LOCAL_5 + LOCAL_2,
		LOCAL_10 = LOCAL_7;

	for(; LOCAL_10 < LOCAL_9; LOCAL_10++)
	{
		int LOCAL_11 = LOCAL_6;

		for(; LOCAL_11 < LOCAL_8; LOCAL_11++)
		{
			if(LOCAL_11 == player->TargetX ||
			   LOCAL_10 == player->TargetY)
			{
				if(LOCAL_11 < 0 || LOCAL_10 < 0 ||
				   LOCAL_11 > 1000 || LOCAL_10 > 1000)
				   continue;

				int LOCAL_12 = ((LOCAL_10 << 0x0D) + LOCAL_11 * 2 + 0x003B07D14); // Buffer ?

				if(!LOCAL_12)
					continue;

				st_Mob *tmpPlayer = GetMobFromIndex(LOCAL_12);

				if(tmpPlayer->Status.curHP < 0)
					continue;
				if(!tmpPlayer->Mode)
					continue;

				if(LOCAL_12 < 100)
				{
					if(tmpPlayer->AffectInfo.Value < 0)
						continue;
				}

				int LOCAL_13 = tmpPlayer->CapeInfo;

				if(LOCAL_1->CapeInfo >= 0)
				{
					if(LOCAL_1->CapeInfo < 9 &&
					   LOCAL_13 >= 0 && LOCAL_13 >= 9)
					{
						Log("err, clan out or range", LOCAL_1, 0);
						return -1;
					}
					
					LOCAL_1->CapeInfo *= 24;

					if((LOCAL_1->CapeInfo + LOCAL_13 * 4 + 0x004C8F74) <= 0)
						return LOCAL_12;
				}
			}
		}
	}

	return -1;
}

void ClearArea(int x_min, int y_min, int x_max, int y_max)	 
{
	//0x0040106E

	int LOCAL_1 = 0;

	for(; LOCAL_1 < 100; LOCAL_1++)
	{
		if(Users[LOCAL_1].Status != 22)
			continue;
		if(!player->Mode)
			continue;

		if(player->TargetX >= x_min && player->TargetX <= x_max &&
		   player->TargetY >= y_min && player->TargetY <= y_max)
		    DoRecall(LOCAL_1);
	}
}

void ClearAreaLevel(int arg1, int arg2, int arg3, int arg4, int lvl_min, int lvl_max) 
{
	//0x00401244
	int LOCAL_1 = 0;

	for(; LOCAL_1 < 100; LOCAL_1++)
	{
		if(Users[LOCAL_1].Status != 22)
			continue;

		st_Mob *player = GetMobFromIndex(LOCAL_1);

		if(!player->Mode)
			continue;

		if(player->TargetX >= arg1 && player->TargetX <= arg3 &&
		   player->TargetY >= arg2 && player->TargetY <= arg4)
			if(player->Status.Level >= lvl_min && player->Status.Level <= lxl_max)
				DoRecall(LOCAL_1);
	}
}

void ClearGuildPKZone(void)
{
	//0x00401235
	int LOCAL_1 = 80,
		LOCAL_2 = 80,
		LOCAL_3 = 100,
		LOCAL_4 = 100,
		LOCAL_5 = 0;

	for(; LOCAL_5 < 100; LOCAL_5++)
	{
		if(Users[LOCAL_5].Status != 22)
			continue;

		st_Mob *player = GetMobFromIndex(LOCAL_5);

		if(!player->Mode)
			continue;

		if(player->TargetX >= LOCAL_1 && player->TargetX <= LOCAL_3
		&& player->TargetY >= LOCAL_2 && player->TargetY <= LOCAL_4)
		    DoRecall(LOCAL_5);
	}
}

void ClearAreaTeleport(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)	
{
	//0x00401596

	int LOCAL_1 = 0;

	for(; LOCAL_1 < 100; LOCAL_1++)
	{
		if(Users[LOCAL_1].Status != 22)
			continue;

		if(!player->Mode)
			continue;

		if(player->TargetX >= arg1 && player->TargetX <= arg3 &&
		   player->TargetY >= arg2 && player->TargetY <= arg4)
		{
			//curHP
			if(!player->Status.curHP)
			{
				player->Status.curHP = 1;
				SendScore(LOCAL_1);
			}

			DoTeleport(LOCAL_1, arg5, arg6);
		}
	}
}

void ClearAreaGuild(int x1, int y1, int x2, int y2, int gIndex)
{
	//0x0040144C
	int LOCAL_1 = 0;

	for(; LOCAL_1 < 100; LOCAL_1++)
	{
		if(Users[LOCAL_1].Status != 22)
			continue;

		st_Mob *player = GetMobFromIndex(LOCAL_1);

		if(player->Mode)
		{
			if(player->TargetX >= arg1 && player->TargetX <= arg3
			&& player->TargetY >= arg2 && player->TargetY <= arg4)
				if(player->GuildIndex != arg5)
					DoRecall(LOCAL_1);
		}
	}
}

void DoRecall(int Cid)
{
	//0x00401294

    st_Mob *player = GetMobFromIndex(Cid);

	int LOCAL_1 = player->LastPosition.X,
		LOCAL_2 = player->LastPosition.Y,
		LOCAL_3 = player->Info.CityId;
	
	LOCAL_1 = rand() % 15 + *(DWORD*)(0x004C7BD0 + (LOCAL_3 * 0x50));
	LOCAL_2 = rand() % 15 + *(DWORD*)(0x004C7BD4 + (LOCAL_3 * 0x50));

	int LOCAL_4 = player->GuildIndex;

	if(LOCAL_4 > 0)
	{
		for(int LOCAL_5 = 0; LOCAL_5 < 5; LOCAL_5++)
		{
			if(LOCAL_4 == *(DWORD*)(0x004C7BC0 + (LOCAL_5 * 0x50)))
			{
				LOCAL_1 = *(DWORD*)(0x004C7BC8 + (LOCAL_5 * 0x50));
				LOCAL_2 = *(DWORD*)(0x004C7BCC + (LOCAL_5 * 0x50));

				break;
			}
		}
	}

	int LOCAL_6 = GetEmptyMobGrid(Cid, &LOCAL_1, &LOCAL_2);

	p366 LOCAL_19;
	GetAction(Cid, LOCAL_1, LOCAL_2, &LOCAL_19);

	LOCAL_19.mType = 1; // 0045FB55  |. C745 C8 010000>MOV [LOCAL.14],1

	if(Cid < 100)
		AddMessage(&LOCAL_19, Cid);
	
	GridMulticast_OL1(Cid, LOCAL_1, LOCAL_2, &LOCAL_19);
}

void DoRemoveHide(int Cid)
{
	//0x00401442

	if(Cid <= 0 || Cid > 100)
		return;

	int LOCAL_1 = 0;
	for(; LOCAL_1 < 4; LOCAL_1++)
	{
		//eax = player->Affects[i].Index
		if(player->Affects[i].Index == 0x1C)//28
		{
			player->Affects[i].Index = 0;

			CMob::GetCurrentScore(Cid);
			SendScore(Cid);

			break;
		}
	}
}

void DoSummon(int arg1, int arg2, int arg3)
{
	//0x004015FF

	int LOCAL_1 = GetEmptyMobGrid(arg1, &arg2, &arg3);

	p366 LOCAL_14;
	GetAction(arg1, arg2, arg3, &LOCAL_14);

	LOCAL_14.mType = 1;

	if(arg1 < 100)
		AddMessage(&LOCAL_14, arg1);

	GridMulticast_OL1(arg1, arg2, arg3, &LOCAL_14);
}

void SetReqHp(int Cid)
{
	//0x00401492

	if(Cid <= 0 || Cid >= 100)
		return;

	st_Mob *player = GetMobFromIndex(Cid);

	if(player->Status.curHP > player->Status.maxHP)
		player->Status.curHP = player->Status.maxHP;

	if(Users[Cid].Potion.CountHp < player->Status.curHP)
		Users[Cid].Potion.CountHp = player->Status.curHP;
}

void SendGuildNotice(int GIndex, char *Message)
{
	//0x00401479
	int LOCAL_1 = 0;
	for(; LOCAL_1 < 100; LOCAL_1++)
	{
		if(Users[LOCAL_1].Status != 22)
			continue;

		st_Mob *player = GetMobFromIndex(LOCAL_1);
		
		if(player->GuildIndex == GIndex)
            SendClientMessage(LOCAL_1, Message);
	}
}

void SendNoticeArea(char *Message, int x1, int y1, int x2, int y2)
{
	//0x00401177;
	int LOCAL_1 = 0;
	for(; LOCAL_1 < 100; LOCAL_1++)
	{
		if(Users[LOCAL_1].Status != 22)
			continue;

		st_Mob *player = GetMobFromIndex(LOCAL_1);

		if(player->TargetX >= x1 && player->TargetX <= x2
		&& player->TargetY >= y1 && player->TargetY <= y2)
		    SendClientMessage(LOCAL_1, Message);
	}
}

void GetRandomPos(int fakearg)//0x0040114F;
{
	st_Mob *LOCAL_1 = GetMobFromIndex(fakearg);

	
}

int ApplyHp(int Cid)
{
	//0x00401253
	st_Mob *player = GetMobFromIndex(Cid);

	if(Users[Cid].Potion.CountHP > player->Status.maxHP)
		Users[Cid].Potion.CountHP = player->Status.maxHP;
	
	int LOCAL_1 = player->Status.curHP,
		LOCAL_2 = Users[Cid].Potion.CountHP;

	if(LOCAL_2 <= LOCAL_1)
	{
		// eax = player->Status.Level
		int LOCAL_3 = player->Status.Level + 50;
		
		player->Status.curHP += LOCAL_3;
		
		if(player->Status.curHP > LOCAL_2)
			player->Status.curHP = LOCAL_2;
		
		return 1;
	}
	
	return -1;
}

int ApplyMp(int Cid)
{
	// 0x0040153C
	st_Mob *player = GetMobFromIndex(Cid);

	if(Users[Cid].Potion.CountMP > player->Status.maxHP)
		Users[Cid].Potion.CountMP = player->Status.maxHP;

	int LOCAL_1 = player->Status.curMP,
		LOCAL_2 = Users[Cid].Potion.CountMP;

	if(LOCAL_2 <= LOCAL_1)
	{
		// eax = player->Status.Level
		int LOCAL_3 = player->Status.Level + 50;
		
		player->Status.curMP += LOCAL_3;
		
		if(player->Status.curMP > LOCAL_2)
			player->Status.curMP = LOCAL_2;
		
		return 1;
	}
	
	return -1;
}

int PutItem(int clientID, st_Item* item)
{
	//0x00401320

	if(clientID <= 0 || clientID >= 100)
		return;
	else if(Users[clientID].Status != 22)
		return;

	int LOCAL_1 = 0;
	for(; LOCAL_1 < 64; LOCAL_1++)
	{
		// eax = local_1
		//ecx = 9

	}
}

void GetNextPos(int battle, int clientId)
{
	st_Mob *mob = (st_Mob*)GetMobFromIndex(clientId); //local1
	
	if(!mob->bStatus.Merchant.Direction)
	{
		mob->Next.X = mob->Target.X;
		mob->Next.Y = mob->Target.Y;
		return;
	}
	
	int speed = BASE_GetSpeed(&mob->Status); //local2
	int local3 = ((speed * 6) << 1) >> 2;
	
	if(local3 >= 24)
		local3 = 23;
	
	int local4;
	
	if(battle != 0)
	{
		local4 = (mob->bStatus.STR + 1) >> 1;
		if(local3 > local4)
			local3 = local4;
	}
	else
	{
		if(local3 > mob->bStatus.STR)
			local3 = mob->Status.STR;
	}
	
	mob->Last.X = mob->Target.X;
	mob->Last.Y = mob->Target.Y;
	mob->Next.X = mob->Segment.X;
	mob->Next.Y = mob->Segment.Y;

	int local5 = local3;
	for(int i = local5; i >= 0; i--)
	{// 413949
		
		BASE_GetRoute((LOCAL_1 + 0x324), (LOCAL_1 + 0x328), (LOCAL_1 + 0x33C), (LOCAL_1 + 0x340), (LOCAL_1 + 0x348), LOCAL_5, 0x007B7E678);
		
	}
}

void DoTeleport(int clientID, int posX, int posY)	
{
	//0x004010C8
	if(!GetEmptyMobGrid(clientID, &posX, &posY))
		return;

	p366 LOCAL_14;
	GetAction(clientID, posX, posY, &LOCAL_14);

	LOCAL_14.mType = 1;

	if(clientID < 100)
		AddMessage(&LOCAL_14, clientID);
	
	GridMulticast_OL1(clientID, posX, posY, &LOCAL_14);
}

int ProcessAffect(int Cid)
{
	st_Mob *player = GetMobFromIndex(Cid);
	// 0x004011F9
	int LOCAL_1 = 0,
		LOCAL_2 = 0,
		LOCAL_3 = 0,
		LOCAL_4 = 0,
		LOCAL_5 = player->Equip[13].Index;

	if(Cid < 0x64 || LOCAL_5 == 0x6BE)
	{
		
	}
	if(LOCAL_5 != 0x2F1 && LOCAL_5 != 0x301)
	{
		int LOCAL_6 = player->CurrentTarget;
		//004501CB
	}

}

unsigned char GetAttribute(int arg_1, int arg_2)
{
	//0x004014AB

	if(arg_1 < 0 || arg_1 > 1000 || arg_2 < 0 || arg_2 > 1000)
		return -1;

	int LOCAL_1 = (arg_1 & 3) >> 2;

	LOCAL_1 &= 0x3FF;

	int LOCAL_2 = (arg_2 & 3) >> 2;

	LOCAL_2 &= 0x3FF;

	LOCAL_2 <<= 0x0A;

	unsigned char LOCAL_3 = LOCAL_2 + LOCAL_1 + 0x007E4C00;

	return LOCAL_3;
}

void SetGuilty(int Cid, int arg_2)
{
	//0x00401488
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// ErickMota por descompilá-la

	if(Cid <= 0 || Cid >= 100)
		return;

	if(arg_2 < 0)
		arg_2 = 0;
	else if(arg_2 > 50)
		arg_2 = 50;

	int LOCAL_1 = arg_2;

	st_Mob *player = GetMobFromIndex(Cid);

	player->Inventory[63].EFV2 = LOCAL_1;
}

int GetCurKill(int Cid)
{
	//0x004014F1
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// ErickMota por descompilá-la

	if(Cid <= 0 || Cid >= 100)
	    return;

	st_Mob *player = GetMobFromIndex(Cid);

	int LOCAL_1 = player->Inventory[63].EFV1,
		LOCAL_2 = LOCAL_1 & 0xFF;

	return LOCAL_2;
}

int GetTotKill(int Cid)
{
	// 0x0040130C
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// ErickMota por descompilá-la

	if(Cid <= 0 || Cid >= 100)
		return;

	st_Mob *player = GetMobFromIndex(Cid);

	int LOCAL_1 = player->Inventory[63].EFV2,
		LOCAL_2 = player->Inventory[63].EFV3;

	LOCAL_1 &= 0xFF;
	LOCAL_2 &= 0xFF;

	LOCAL_2 <<= 8; // Só no LOCAL_2 ? Não deveria ser nos dois ?

	int LOCAL_3 = LOCAL_1 + LOCAL_2;
	return LOCAL_3;
}

int GetPkPoint(int Cid)
{
	// 0x004012FD
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// ErickMota por descompilá-la

	st_Mob *player = GetMobFromIndex(Cid);

	int LOCAL_1 = player->Inventory[63].EF1,
	    LOCAL_2 = LOCAL_1 & 0xFF;

	return LOCAL_2;
}

int GetGuilty(int Cid)
{
	// 0x004012CB
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// ErickMota por descompilá-la

	st_Mob *player = GetMobFromIndex(Cid);

	int LOCAL_1 = player->Inventory[63].EF2;
	int LOCAL_2 = LOCAL_1 & 0xFF;

	if(LOCAL_2 > 50)
	{
        player->Inventory[63].EF2 = 0; // 0041E775  |. C680 906C5C01 >MOV BYTE PTR DS:[EAX+15C6C90],0
        LOCAL_2 = 0;
	}

	return LOCAL_2;
}

int GetEmptyAffect(int clientId, int arg2)
{
	// 0x00401339
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// ErickMota por descompilá-la

	st_Mob *player = GetMobFromIndex(clientId);

	int LOCAL_1 = 0;
	for(; LOCAL_1 < 4; LOCAL_1++)	
		if(player->Affects[LOCAL_1].Index == arg2)
			LOCAL_1;

	for(LOCAL_1 = 0; LOCAL_1 < 4; LOCAL_1++)
		if(!player->Affects[LOCAL_1].Index)
		    return; LOCAL_1;
	
	return -1;
}

int BASE_GetDistance(int x1, int y1, int x2, int y2)
{
	// 0x004013AC
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// ErickMota por descompilá-la

	int LOCAL_1,
		LOCAL_2;

	if(x1 <= x2)
	    LOCAL_1 = x2 - x1;
	else
	    LOCAL_1 = x1 - x2;
		
	if(y1 <= y2)
		LOCAL_2 = y2 - y1;	
	else
		LOCAL_2 = y1 - y2;
		
	if(LOCAL_1 > 6 || LOCAL_2 > 6)
	{
		if(LOCAL_1 <= LOCAL_2)
			return LOCAL_1 + 1;
		else
			return LOCAL_2 + 1;
	}
	else
	{
		LOCAL_2 *= 0x1C;

		return (LOCAL_2 + LOCAL_1 * 4 + 4C80B8); // 4C80B8 = ??
	}
}

void BASE__GetCurrentScore(stMOB& mob, stAfects* affect)
{
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// Guican por descompilá-la

	mob.AffectInfo = 0;
	unsigned short currentHP = mob.Status.Hp;
	if(currentHP < 0)
		currentHP = 0;
	if(currentHP > 65000)
		currentHP = 65000;

	unsigned short currentMP = mob.Status.Mp;
	if(currentMP < 0)
		currentMP = 0;
	if(currentMP > 65000)
		currentMP == 65000;

	mob.Status = mob.bStatus;
	mob.Status.Hp = currentHP;
	mob.Status.Mp = currentHP;

	int defence = (BASE_GetMobAbility(&mob, EF_AC) + BASE_GetMobAbility(&mob, EF_ACADD));
	mob.Status.Defense += defence;



	mob.Status.Attack += BASE_GetMobAbility(&mob, EF_DAMAGE);


	mob.Status.MaxHp += BASE_GetMobAbility(&mob, EF_HP);
	mob.Status.MaxMp += BASE_GetMobAbility(&mob, EF_MP);

	mob.Status.STR += BASE_GetMobAbility(&mob, EF_STR);
	mob.Status.INT += BASE_GetMobAbility(&mob, EF_INT);
	mob.Status.DEX += BASE_GetMobAbility(&mob, EF_DEX);
	mob.Status.CON += BASE_GetMobAbility(&mob, EF_CON);

	int special1 = BASE_GetMobAbility(&mob, EF_SPECIAL1);
	if(special1 > 255)
		special1 == 255;
	int special2 = BASE_GetMobAbility(&mob, EF_SPECIAL2);
	if(special2 > 255)
		special2 == 255;
	int special3 = BASE_GetMobAbility(&mob, EF_SPECIAL3);
	if(special3 > 255)
		special3 == 255;
	int special4 = BASE_GetMobAbility(&mob, EF_SPECIAL4);
	if(special4 > 255)
		special4 == 255;

	mob.Status.wMaster = special1;
	mob.Status.fMaster = special2;
	mob.Status.sMaster = special3;
	mob.Status.tMaster = special4;
	mob.SaveMana += BASE_GetMobAbility(&mob, EF_SAVEMANA);

	int calcMagicIncrement = (BASE_GetMobAbility(&mob, EF_MAGIC) + BASE_GetMobAbility(&mob, EF_MAGICADD));
	calcMagicIncrement = ((calcMagicIncrement + 1) >> 1);
	if(calcMagicIncrement >= 255) // implementado para proteger o overflow da variavel
		calcMagicIncrement == 255;

	mob.MagicIncrement = calcMagicIncrement;

	int speed = (mob.Status.Reserved & 0xF);
	speed = (speed + BASE_GetMobAbility(&mob, EF_RUNSPEED));

	int attspeed = ((mob.bStatus.AttackRun >> 4) * 10);
	attspeed = (attspeed + BASE_GetMobAbility(&mob, EF_ATTSPEED));

	int regenHP = BASE_GetMobAbility(&mob, EF_REGENHP);
	int regenMP = BASE_GetMobAbility(&mob, EF_REGENMP);

	int body = mob.Equip[0].Index / 10;
	if(body < 4)
	{
		mob.Equip[0].EF1 = 43;
		mob.Equip[0].EFV1 = 0;

		if(mob.CapeInfo == 7 || mob.CapeInfo == 8 || mob.CapeInfo == 9)
			mob.CapeInfo = 0;
	}

	int cape = mob.Equip[15].Index;
	if(mob.CapeInfo != 4)
		if(cape == 543 || cape == 545 || cape == 734 || cape == 736)
			mob.CapeInfo = 7;
	if(mob.CapeInfo != 4)
		if(cape == 544 || cape == 546 || cape == 735 || cape == 737)
			mob.CapeInfo = 8;

	if(mob.ClassInfo == 3)
	{
		if((mob.Learn & LEARN_10) != 0)
		{
			int weapon = mob.Equip[6].Index;
			if(weapon > 0 || weapon < MAX_ITEMLIST)
			{
				int unique = g_pItemList[weapon].Unique;
				if(unique == 42 || unique == 43)
				{
					int calcsMaster = (special3 / 5) + 10;
					mob.Status.Attack += calcsMaster;
				}
			}
		}
	}

	int calcHPADD = (BASE_GetMobAbility(&mob, EF_HPADD) + 100);
	mob.Status.MaxHp = ((mob.Status.MaxHp * calcHPADD) / 100);

	int calcMPADD = (BASE_GetMobAbility(&mob, EF_MPADD) + 100);
	mob.Status.MaxMp = ((mob.Status.MaxMp * calcMPADD) / 100);

	if(mob.Equip[0].Index >= 20 || mob.Equip[0].Index < 30)
		mob.Equip[0].Index = 21;

	int local20 = 0;
	int local21 = 0;
	int local22 = 100;

	//Skills
	int i;
	for(i = 0; i < MAX_AFFECT; i++)
	{
		if(affect != 0)
		{
			int skillType = affect[i].Type;
			if(skillType != 0)
			{
				int skillValue = affect[i].Value;
				int skillLevel = affect[i].Level;
				if(skillType == 1) //Toque Sagrado - Lança de Gelo - Nevasca
				{
					speed = speed - skillValue;
					int decAttSpeed = 30;
					attspeed = attspeed - decAttSpeed;

					if(mob.Equip[0].Index <= 50)
						break;

					int Int = mob.Status.INT;
					Int = Int - (decAttSpeed + 10);
					mob.Status.INT = Int;
					break;
				}
				if(skillType == 2) //Velocidade
				{
					speed = speed + skillValue;
					mob.AffectInfo = mob.AffectInfo | RSV_VELOC;
					break;
				}
				if(skillType == 3) //Perseguição
				{
					int totResist = 0;
					int decResist = skillValue;
					if(mob.Equip[0].Index < 50)
						decResist = decResist >> 1;
					else
						decResist = decResist - 10;

					totResist = mob.Resist1 - decResist;
					if(totResist <= -50) // implementado para proteger o overflow da variavel
						totResist = -50;
					if(totResist >= 100) // implementado para proteger o overflow da variavel
						totResist = 100;

					mob.Resist1 = totResist;

					totResist = 0;
					totResist = mob.Resist2 - decResist;
					if(totResist <= -50) // implementado para proteger o overflow da variavel
						totResist = -50;
					if(totResist >= 100) // implementado para proteger o overflow da variavel
						totResist = 100;

					mob.Resist2 = totResist;

					totResist = 0;
					totResist = mob.Resist3 - decResist;
					if(totResist <= -50) // implementado para proteger o overflow da variavel
						totResist = -50;
					if(totResist >= 100) // implementado para proteger o overflow da variavel
						totResist = 100;

					mob.Resist3 = totResist;

					totResist = 0;
					totResist = mob.Resist3 - decResist;
					if(totResist <= -50) // implementado para proteger o overflow da variavel
						totResist = -50;
					if(totResist >= 100) // implementado para proteger o overflow da variavel
						totResist = 100;

					mob.Resist3 = totResist;
					break;
				}
				if(skillType == 4) // Limite da Alma
				{
					local22 = local22 + 3;
					mob.Status.Attack = mob.Status.Attack + 20;

					int calcMIncrement = mob.MagicIncrement + 5;
					if(calcMIncrement >= 255) // implementado para proteger o overflow da variavel
						calcMIncrement == 255;

					mob.MagicIncrement = calcMIncrement;
					break;
				}
				if(skillType == 5)
				{
					float decDex = (100 - skillValue) / 100;
					mob.Status.DEX = (mob.Status.DEX * decDex);
					break;
				}
				if(skillType == 6)
				{
					float incDex = (100 + skillValue) / 100;
					mob.Status.DEX = (mob.Status.DEX * incDex);
					break;
				}
				if(skillType == 7) //Lamina Congelada
				{
					int decAttSpeed = ((skillLevel / 10) + 10);
					attspeed = attspeed - decAttSpeed;
					if(mob.Equip[0].Index > 50)
					{
						int calcINT = mob.Status.INT;
						calcINT = (calcINT - (decAttSpeed + 10));
						mob.Status.INT = calcINT;
					}
					break;
				}
				if(skillType == 8) //Mestre das Armas
				{
					int incAttSpeed = ((skillLevel / 10) + 10);
					attspeed = attspeed + incAttSpeed;
					break;
				}
				if(skillType == 9) //Arma Magica - Visão De Caçadora - Toxina De Serpente
				{
					int incAttack = (((skillLevel * 5) / 20) + skillValue);
					incAttack = ((local22 * 3) >> 1);
					local22 = local22 + 5;
					if(mob.ClassInfo == 1)
					{
						if((mob.Learn & LEARN_19) != 0)
						{
							incAttack = incAttack * 3;
							local22 = local22 + 10;
						}
					}
					mob.Status.Attack = mob.Status.Attack + incAttack;
					break;
				}
				if(skillType == 10) //Enfraquecer
				{
					int decAttack = ((skillLevel / 5) + skillValue);
					mob.Status.Attack = mob.Status.Attack - decAttack;
					break;
				}
				if(skillType == 11) //Escudo Magico
				{
					int incDefence = ((skillLevel / 3) + skillValue);
					mob.Status.Defense = mob.Status.Defense + incDefence;
					break;
				}
				if(skillType == 12)
				{
					float decDefense = (100 - skillValue) / 100.0;
					mob.Status.Defense = (mob.Status.Defense * decDefense);
					break;
				}
				if(skillType == 13) //Assalto
				{
					int incHP = ((skillLevel / 10) + skillValue);
					local22 = local22 + incHP;

					incHP = mob.Status.MaxHp;
					incHP = (incHP * 9) / 10;

					mob.Status.MaxHp = incHP;
					break;
				}
				if(skillType == 14) //Samaritano
				{
					int incCon = ((skillLevel * 3) >> 2) + skillValue;
					mob.Status.CON = mob.Status.CON + incCon;
					break;
				}
				if(skillType == 15) //Toque de Atena
				{
					int incSpecial = (skillLevel / 10) + skillValue;
					int calcSpecial = 0;
					calcSpecial = mob.Status.wMaster + incSpecial;
					if(calcSpecial >= 255) // implementado para proteger o overflow da variavel
						calcSpecial = 255;

					mob.Status.wMaster = calcSpecial;

					calcSpecial = 0;
					calcSpecial = mob.Status.fMaster + incSpecial;
					if(calcSpecial >= 255) // implementado para proteger o overflow da variavel
						calcSpecial = 255;

					mob.Status.fMaster = calcSpecial;

					calcSpecial = 0;
					calcSpecial = mob.Status.sMaster + incSpecial;
					if(calcSpecial >= 255) // implementado para proteger o overflow da variavel
						calcSpecial = 255;

					mob.Status.sMaster = calcSpecial;

					calcSpecial = 0;
					calcSpecial = mob.Status.tMaster + incSpecial;
					if(calcSpecial >= 255) // implementado para proteger o overflow da variavel
						calcSpecial = 255;

					mob.Status.tMaster = calcSpecial;
					break;
				}
				if(skillType == 16) //Mutações BM
				{
					int incStatus;
					int local46;
					int local47;
					int local48;
					int local49;
					int transfID = skillValue - 1;
					if(transfID >= 0 && transfID < 5)
					{
						if(mob.ClassInfo == 2)
						{
							if(transfID == 4)
								mob.Equip[0].Index = transfID + 28;
							else
								mob.Equip[0].Index = transfID + 22;

							int local51 = 0;
							int local52 = 0;
							int local53 = 0;
							int local54 = 0;

							int incLobisomem = mob.Learn & LEARN_17;
							int incHomemUrso = mob.Learn & LEARN_19;
							int incAstaroth = mob.Learn & LEARN_21;

							int local58 = 0;

							if(mob.Equip[0].Index == 22) //Lobisomem
							{
								if(incLobisomem != 0)
								{
									local51 = 10;
									local58 = local58 & 15;
								}
							}
							else if(mob.Equip[0].Index == 23) //HomemUrso
							{
								if(incHomemUrso != 0)
								{
									local52 = 20;
									local58 = local58 + 30;
									local54 = local54 + 20;
								}
							}
							else if(mob.Equip[0].Index == 24) //Astaroth
							{
								if(incAstaroth != 0)
								{
									local51 = 10;
									local52 = 5;
									local53 = 5;
									local58 = local58 + 15;
									local54 = local54 + 20;
								}
							}
							else if(mob.Equip[0].Index == 25) //Titan
							{
								local58 = local58 + 30;
							}
							else if(mob.Equip[0].Index == 32) //Eden
							{
								//implementar bonus da eden
							}

							//00407770
							int local59 = (mob.Status.Level + special4) / 3;
							local59 = (local59 - pTransBonus[transfID].unk1) / 12;
							if(local59 < 0)
								local59 = 0;
							if(local59 > 9)
								local59 = 9;

							mob.Equip[0].EF1 = 43;
							mob.Equip[0].EFV1 = local59;

							//ataque
							local46 = pTransBonus[transfID].unk0 + local51;
							local47 = pTransBonus[transfID].unk01 + local51;
							local48 = local47 - local46;
							local49 = ((local48 * skillLevel) / 200) + local46;

							incStatus = mob.Status.Attack;
							if(mob.Equip[0].Index == 22)
								incStatus = incStatus + 10;

							mob.Status.Attack = incStatus;

							//defesa
							local22 = local22 + local49; //conferir 00407877
							local46 = pTransBonus[transfID].unk02 + local53;
							local47 = pTransBonus[transfID].unk03 + local53;
							local48 = local47 - local46;
							local49 = ((local48 * skillLevel) / 200) + local46;

							incStatus = mob.Status.Defense;
							incStatus = (incStatus * local49) / 100;
							if(mob.Equip[0].Index == 22)
								incStatus = incStatus + 5;

							mob.Status.Defense = incStatus;

							//maxHp
							//00407933
							local46 = pTransBonus[transfID].unk04 + local52;
							local47 = pTransBonus[transfID].unk05 + local52;
							local48 = local47 - local46;
							local49 = ((local48 * skillLevel) / 200) + local46;
							
							incStatus = mob.Status.MaxHp;
							incStatus = (incStatus * local49) / 100;
							mob.Status.MaxHp = incStatus;

							//resistencias
							int Res1 = mob.Resist1;
							if(Res1 <= -50) // implementado para proteger o overflow da variavel
								Res1 = -50;
							if(Res1 >= 100) // implementado para proteger o overflow da variavel
								Res1 = 100;

							mob.Resist1 = Res1;

							int Res2 = mob.Resist2;
							if(Res2 <= -50) // implementado para proteger o overflow da variavel
								Res2 = -50;
							if(Res2 >= 100) // implementado para proteger o overflow da variavel
								Res2 = 100;

							mob.Resist2 = Res2;

							int Res3 = mob.Resist3;
							if(Res3 <= -50) // implementado para proteger o overflow da variavel
								Res3 = -50;
							if(Res3 >= 100) // implementado para proteger o overflow da variavel
								Res3 = 100;

							mob.Resist3 = Res3;

							int Res4 = mob.Resist4;
							if(Res4 <= -50) // implementado para proteger o overflow da variavel
								Res4 = -50;
							if(Res4 >= 100) // implementado para proteger o overflow da variavel
								Res4 = 100;

							mob.Resist4 = Res4;

							local20 = pTransBonus[transfID].unk07 + local54;
							local21 = pTransBonus[transfID].unk06;
						}
					}
					break;
				}
				if(skillType == 18) //Controle de Mana - Troca de Espirito
				{
					//00407B2C
					int convMP = (mob.Status.MaxMp / 5) + ((mob.Status.Level + skillLevel) >> 1); //00407B56
					mob.Status.MaxHp = mob.Status.MaxHp + convMP;
					mob.Status.MaxMp = mob.Status.MaxMp - convMP;
					break;
				}
				if(skillType == 19) //Imunidade
				{
					//00407B89
					mob.AffectInfo = mob.AffectInfo | RSV_IMUNIT;
					break;
				}
				if(skillType == 21) //Meditação
				{
					//00407BA5
					int incDefense = (skillLevel / 3) + 10;
					mob.Status.Defense = mob.Status.Defense + incDefense;

					int local63 = (skillLevel / 10) + skillValue;
					local22 = local22 + local63;
					break;
				}
				if(skillType == 25) // Proteção Elemental
				{
					//00407BFA
					int incDefense = (skillLevel >> 2) + skillValue;
					mob.Status.Defense = mob.Status.Defense + incDefense;
					break;
				}
				if(skillType == 26) //Ligação Spectral - Evasão Aprimorada
				{
					//00407C2E
					mob.AffectInfo = mob.AffectInfo | RSV_PARRY;
					break;
				}
				if(skillType == 27) //Encantar Gelo
				{
					//00407C4A
					mob.AffectInfo = mob.AffectInfo | RSV_FROST;
					break;
				}
				if(skillType == 28) //Invisibilidade
				{
					//00407C63
					mob.AffectInfo = mob.AffectInfo | RSV_HIDE;
					break;
				}
				if(skillType == 29)
				{
					//00407C63
					mob.AffectInfo = mob.AffectInfo | RSV_DRAIN;
					break;
				}
				if(skillType == 30) //Olhos De Aguia
				{
					//00407C63
					mob.AffectInfo = mob.AffectInfo | RSV_VISION;
					break;
				}
				if(skillType == 31) //Armadura Critica - Escudo Dourado
				{
					//00407CAE
					int incDefense = (skillLevel >> 1) + skillValue;
					mob.Status.Defense = mob.Status.Defense + incDefense;
					break;
				}
			}
		}
	}
	int j;
	for(j = 1; j <= 7; j++)
	{
		int equipID = mob.Equip[i].Index;
		if(equipID < 0 || equipID > MAX_ITEMLIST)
			continue;

		int itemsanc = BASE_GetItemSanc(&mob.Equip[i]);
		if(itemsanc < 9)
			continue;

		int itempos = g_pItemList[equipID].Pos;
		if(itempos == HELMET)
		{
			int incResist = mob.Resist1 + 30;
			if(incResist > 100)
				incResist = 100;

			mob.Resist1 = incResist;

			incResist = mob.Resist2 + 30;
			if(incResist > 100)
				incResist = 100;

			mob.Resist2 = incResist;

			incResist = mob.Resist3 + 30;
			if(incResist > 100)
				incResist = 100;

			mob.Resist3 = incResist;

			incResist = mob.Resist4 + 30;
			if(incResist > 100)
				incResist = 100;

			mob.Resist4 = incResist;
			continue;
		}
		if(itempos == ARMOR)
		{
			mob.Status.Defense = mob.Status.Defense + 25;
			continue;
		}
		if(itempos == PANTS)
		{
			mob.Status.Defense = mob.Status.Defense + 25;
			continue;
		}
		if(itempos == GLOVES)
		{
			mob.AffectInfo = mob.AffectInfo | 64;
			continue;
		}
		if(itempos == SHIELD)
		{
			mob.Status.Defense = mob.Status.Defense + 25;
			int incResist = mob.Resist1 + 10;
			if(incResist >= 100) // implementado para proteger o overflow da variavel
				incResist = 100;

			mob.Resist1 = incResist;

			incResist = mob.Resist2 + 10;
			if(incResist >= 100) // implementado para proteger o overflow da variavel
				incResist = 100;

			mob.Resist2 = incResist;

			incResist = mob.Resist3 + 10;
			if(incResist >= 100) // implementado para proteger o overflow da variavel
				incResist = 100;

			mob.Resist3 = incResist;

			incResist = mob.Resist4 + 10;
			if(incResist >= 100) // implementado para proteger o overflow da variavel
				incResist = 100;

			mob.Resist4 = incResist;
			continue;
		}
		if(itempos == WEAPON_POS || itempos == WEAPON2HAND_POS)
		{
			int itemunique = g_pItemList[equipID].Unique;
			if(itemunique == 47)
			{
				mob.MagicIncrement = mob.MagicIncrement + 8;
				if(mob.MagicIncrement >= 255) // implementado para proteger o overflow da variavel
					mob.MagicIncrement = 255;
			}
			else
				mob.Status.Attack = mob.Status.Attack + 40;

			continue;
		}
		continue;
	}
	if(body < 4)
		mob.Status.Attack = (mob.Status.Attack + (mob.Status.STR / 3) + mob.Status.wMaster + mob.Status.Level);

	if(local22 != 100)
		mob.Status.Attack = (mob.Status.Attack * local22) / 100;

	//00408062
	if(regenHP <= 0) // implementado para proteger o overflow da variavel
		regenHP = 0;
	if(regenHP >= 255) // implementado para proteger o overflow da variavel
		regenHP = 255;

	mob.RegenHP = regenHP;

	if(regenMP <= 0) // implementado para proteger o overflow da variavel
		regenMP = 0;
	if(regenMP >= 255) // implementado para proteger o overflow da variavel
		regenMP = 255;

	mob.RegenMP = regenMP;

	//004080B4
	mob.Status.Reserved = (mob.Status.Reserved & 0xF0) | mob.Merchant;

	//004080D1
	attspeed = (attspeed + local20) + (mob.Status.DEX / 5);

	//004080EB
	speed = speed + local21;

	int mountID = mob.Equip[14].Index;
	if(body < 4)
	{
		if(mountID >= 2360 || mountID < 2390)
		{
			if(mob.Equip[14].EF1 > 0)
			{
				int mountIndex = mountID - 2360;
				if(speed < g_pMountBonus[mountIndex][4]) //conforme o id da mount, compara o speed dela com o speed do char
					speed = speed + g_pMountBonus[mountIndex][4];
			}
		}
	}
	if(speed <= 0) // implementado para proteger o overflow da variavel
		speed = 0;
	if(speed >= 6) // implementado para proteger o overflow da variavel
		speed = 6;

	if(attspeed <= 0) // implementado para proteger o overflow da variavel
		attspeed = 0;
	if(attspeed >= 150) // implementado para proteger o overflow da variavel
		attspeed = 150;

	attspeed = attspeed / 10;
	mob.Status.AttackRun = ((attspeed << 4) + speed);

	if(mob.Status.Hp >= mob.Status.MaxHp) // implementado para proteger o overflow da variavel
		mob.Status.Hp = mob.Status.MaxHp;

	if(mob.Status.Mp >= mob.Status.MaxMp) // implementado para proteger o overflow da variavel
		mob.Status.Mp = mob.Status.MaxMp;

	return;
}

bool PutItem(unsigned int Index, sItem *item)
{
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// Bruno Garcia (nikkw) por descompilá-la

	sSpawn *spw = &Spawn.pMob[Index];

	bool carry = false;

	int i = 0;
	for(i = 0; i < 63; i ++)
	{
		int slotError = -1;
		carry = CanCarry(item, &spw->Character.Inventory[0], (i % 9), (i / 9), &slotError);

		if(carry)
			break;
	}

	if(i < 0 || i >= 63)
		return false;

	memcpy(&spw->Character.Inventory[i], item, sizeof(sItem));
	CreateItem(Index, INV_TYPE, i, &spw->Character.Inventory[i]);
	return true;
}

bool GetInView(int Index, int OtherIndex)
{
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// Bruno Garcia (nikkw) por descompilá-la

    sCharacter user = &Spawn.pMob[Index];
    sCharacter other = &Spawn.pMob[OtherIndex];

    if(user->Target.X < (other->Target.X - 0x17))
        return false;

    else if(user->Target.X > (other->Target.X + 0x17))
        return false;

    else if(user->Target.Y < (other->Target.Y - 0x17))
        return false;

    else if(user->Target.X > (other->Target.X + 0x17))
        return false;

    return true;
}

bool GetInHalf(int Index, int OtherIndex)
{
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// Bruno Garcia (nikkw) por descompilá-la

    sCharacter *user = &Spawn.pMob[Index];
    sCharacter *other = &Spawn.pMob[OtherIndex];

    if(user->Target.X < (other->Target.X - 0x20))
        return false;

    else if(user->Target.X > (other->Target.X + 0x20))
        return false;

    else if(user->Target.Y < (other->Target.Y - 0x20))
        return false;

    else if(user->Target.X > (other->Target.X + 0x20))
        return false;

    return true;
}

int GetExpApply(int exp, int attacker, int target)
{
	// Créditos desta func 
	// Programadores da TMSRV por criá-la
	// Bruno Garcia (nikkw) por descompilá-la

	if (attacker>=400 || target>=400 || attacker<0 || target<0)
		return exp;

	attacker++;
	target++;

	int multiexp = target*100/attacker;  //  0-100 // 100-200
	if (multiexp<80 && attacker>=50) 
		multiexp = ((multiexp-80)*2)+60; 
	else if  (multiexp>200)     
		multiexp = 200;
	if (multiexp<0)     
		multiexp=0;
	exp=exp*multiexp / 100;
	return exp;
}

void RemoveParty(INT32 conn)
{
	//função descompilada
	//não descompilei as verificações de segurança (se ta on, clientid, etc)
	//bruno garcia.

	st_Mob *player = GetMobFromIndex(conn);
	INT32 leader = player->Leader;
	st_Mob *otherPlayer = GetMobFromIndex(leader);

	SendRemoveParty(conn, 0);

	if(leader == 0)
	{
		for(INT32 i = 0; i < 12; i ++)
		{
			INT32 otherClientID = player->PartyList[i];
			player->PartyList[i] = 0;			
			otherPlayer->Leader = 0;
			SendRemoveParty(otherClientID, 0);
		}
	}
	else
	{
		SendRemoveParty(leader, conn);
		player->Leader = 0;

		for(INT32 i = 0; i < 12; i ++)
		{
			INT32 other = otherPlayer->PartyList[i];			
				
			if(i == conn)			
				otherPlayer->PartyList[i] = 0;			

			SendRemoveParty(conn, other);
		}
	}
}

JMP_NEAR(0x00411ED5, &NKD_AddAccount_CreateAccount);
__declspec(naked) void NKD_AddAccount_CreateAccount()
{
	_asm
	{
		PUSH DWORD PTR SS:[EBP - 04h]
		PUSH DWORD PTR SS:[EBP - 01068h]
		CALL CreateAccount

		TEST EAX,EAX
		JNZ lbl_accountSucess

		PUSH 0421h

		MOV EDX,00411EDAh
		JMP EDX

		lbl_accountSucess:
		MOV EDX,00411E65h
		JMP EDX
	}
}

struct stAccount
{
	char Login[16]; 
	char Password[16]; 
	BYTE unk[10A4];
}

BYTE __stdcall CreateAccount(p20D *p, UINT32 addr)
{
	FILE*pFile = NULL;

	stAccount acc;
	memset(&acc, 0, sizeof acc);

	strncpy(acc.Username, p->Login, 16);
	strncpy(acc.Password, p->Password, 16);

	char firstKey[4];
	char szTMP[256];
	BASE_GetFirstKey(p->Login, firstKey);

	sprintf(szTMP, "account\\%s\\%s", firstKey, p->Login);

	pFile = fopen(szTMP, "wb+");
	if(pFile)
	{
		fwrite((void*)&acc, sizeof stAccount, 1, pFile);

		fclose(pFile);
		return 1;
	}
	return 0;
}

void DeleteColoseum()
{
	// 0x0040121C
	for(int LOCAL_1 = 100; LOCAL_1 < 30000; LOCAL_1++)
	{
		if(!cMob[LOCAL_1].Mode)
			continue;

		if(!cMob[LOCAL_1].Status.curHP)
			continue;

		if(!cMob[LOCAL_1].GenerateIndex || cMob[LOCAL_1].GenerateIndex == 1 || cMob[LOCAL_1].GenerateIndex == 2)
			DeleteMob(LOCAL_1, 2);

		if(cMob[LOCAL_1].GenerateIndex != 5 && cMob[LOCAL_1].GenerateIndex != 6 && cMob[LOCAL_1].GenerateIndex != 7)
			continue;

		DeleteMob(LOCAL_1, 2);
	}
}

void GenerateColoseum(int arg1)
{
	// 0x0040142E
	int LOCAL_1 = (Rand() & 80000003) + 4,
		LOCAL_2 = 0;

	for(; LOCAL_2 < LOCAL_1; LOCAL_2++)
		GenerateMob(arg1, 0, 0);
}

int GetInHalf(int cId1, int cId2)
{
	// 0x00401159

	if(cMob[cId1].Target.X >= (cMob[cId2].Target.X - 0xB) && cMob[cId1].Target.X <= (cMob[cId2].Target.X + 0xB)
	&& cMob[cId1].Target.Y >= (cMob[cId2].Target.Y - 0xB) && cMob[cId1].Target.Y <= (cMob[cId2].Target.Y + 0xB))
		return 1;
	
	return -1;
}

int GetIntView(int arg1, int arg2)
{
	// 0x004011FE
	if(cMob[arg1].Target.X >= (cMob[arg2].Target.X - 0x17) && cMob[arg1].Target.X <= (cMob[arg2].Target.X + 0x17)
	&& cMob[arg1].Target.Y >= (cMob[arg2].Target.Y - 0x17) && cMob[arg1].Target.Y <= (cMob[arg2].Target.Y + 0x17))
	    return 1;

	return -1;
}

int GetHide(int arg1)
{
	//  0x00401505
	if(arg1 > 0 && arg1 < MAX_PLAYER)
		if(cMob[arg1].Affects[0].Index == 0x1C ||
		   cMob[arg1].Affects[1].Index == 0x1C ||
		   cMob[arg1].Affects[2].Index == 0x1C ||
		   cMob[arg1].Affects[3].Index == 0x1C)
		   return 1;

	return -1;
}

void SaveALL()
{
	// 0x004014B0

	int LOCAL_1 = 0;

	for(; LOCAL_1 < MAX_PLAYER; LOCAL_1++)
	{
		if(cUsers[LOCAL_1].Status != 22)
			continue;

		CharLogOut(LOCAL_1); // 0x004013B6
		//Log("saveall", cUsers[LOCAL_1].Username, cUsers[LOCAL_1].In_Addr);
	}
}

void CharLogOut(int arg1)
{
	// 0x004013B6

	if(cUsers[arg1].Status != 22)
	{
		//Log("err,char logout - not user_play", cUsers[arg1].Username, cUsers[arg1].In_Addr);
		SendClientSignal(arg1, arg1, 0x116); // 0040145B
		return;
	}

	if(cUsers[arg1].IsBillConnect || *(DWORD*)0x004CBBA8 == 0) // 0x004CBBA8 = ?
		SendBilling(arg1, cUsers[arg1].Username, 2, 0);
	
	int LOCAL_1 = cUsers[arg].Trade.OtherClientId;

	if(LOCAL_1 > 0 && LOCAL_1 < 750)
	{
		if(cUsers[LOCAL_1].Status == 22)
			if(cUsers[LOCAL_1].Trade.OtherClientId == arg1)
				RemoveTrade(LOCAL_1);
	}

	int LOCAL_2 = 0;
	
	for(; LOCAL_2 < 5; LOCAL_2++)
	{
		if((LOCAL_2 * 4 + *(DWORD*)0x008BF1848) == arg1)
		    *(DWORD*)0x008BF1848 + (LOCAL_2 * 4) = 0;
	}

	cUsers[arg1].Status = 0xB;

	SaveChar(arg1, 1);
	DeleteMob(arg1, 2);

	cMob[arg1].Target.X = cMob[arg1].LastPosition.X;
	cMob[arg1].Target.Y = cMob[arg1].LastPosition.Y;
	cMob[arg1].Mode = 0;

	SendClientSignal(arg1, arg1, 0x116);
}

void MobKilled(int cId1, int cId2, int arg3, int arg4)
{
	// 0x004011A4

	if(cId1 <= 0 || cId1 >= 0x7530/*30k*/)
		return;
	if(cId2 <= 0 || cId2 >= 0x7530)
		return;
	if(!pMob[cId1].Mode)
		return;

	st_Item *LOCAL_1 = &pMob[cId1].Equip[13];

	if(LOCAL_1->Index == 769)
	{
		int LOCAL_2 = BASE_GetItemSanc(&LOCAL_1);

		if(LOCAL_2 <= 0)
			BASE_ClearItem(LOCAL_1);
		else
		{
			LOCAL_2--;

			if(LOCAL_1->EF1 == EF_SANC)
				LOCAL_1->EFV1 = LOCAL_2;
			else if(LOCAL_1->EF2 == EF_SANC)
				LOCAL_1->EFV2 = LOCAL_2;
			else if(LOCAL_1->EF3 == EF_SANC)
				LOCAL_1->EFV3 = LOCAL_2;
		}

		if(cId1 > 0 && cId1 < MAX_PLAYER)
		{
			SendItem(cId1, 0, 13, LOCAL_1);
			SendEmotion(cId1, 0xE, 2);
		}
		//0x0045AC2B
		SendEquip(cId1, 0);

		pMob[cId1].Status.curHp = pMob[cId1].Status.maxHp;

		if(cId1 <= MAX_PLAYER)
			SetReqHp(cId1);

		SendScore(cId1);

		return;
	}
	// 0x0045AC7C
	if(CastleState > 1 && pMob[cId1].TargetX == 0x416 && pMob[cId1].TargetY == 0x69A
	&& cId1 > 0 && cId1 < MAX_PLAYER)
	{
		DoTeleport(cId1, 0x421, 0x6CE);

		return;
	}


}

void MobKilled(int cId1, int cId2, int arg3, int arg4)
{
	// 0x004011A4
	if(cId1 < 0 || cId1 > 30000)
		return;
	if(cId2 < 0 || cId2 > 30000)
		return;

	if(!cMob[cId1].Mode)
		return;

	int LOCAL_1 = cMob[cId1].Equip[13].Index;

	if(cMob[cId1].Equip[13].Index == 769)
	{
		int LOCAL_2 = BASE_GetItemSanc(&cMob[cId1].Equip[13]);

		if(LOCAL_2 <= 0)
		{
			BASE_ClearItem(&cMob[cId1].Equip[13]);

			return;
		}

		LOCAL_2--;

		if(cMob[cId1].Equip[13].EF1 == EF_SANC)
			cMob[cId1].Equip[13].EFV1 = LOCAL_2;
		else if(cMob[cId1].Equip[13].EF2 == EF_SANC)
			cMob[cId1].Equip[13].EFV2 = LOCAL_2;
		else if(cMob[cId1].Equip[13].EF3 == EF_SANC)
			cMob[cId1].Equip[13].EFV3 = LOCAL_2;

		if(cId1 > 0 && cId1 < MAX_PLAYER)
		{
			SendItem(cId1, 0, 13, &cMob[cId1].Equip[13]);
			SendEmotion(cId1, 0xE, 2);
		}

		SendEquip(cId1, 0);

		cMob[cId1].Status.curHP = cMob[cId1].Status.maxHP;

		if(cId1 < MAX_PLAYER)
			SetReqHp(cId1);

		SendScore(cId1);

		return;
	}

	if(*(DWORD*)0x008BF1860 > 1) // ?????
	{
		if(cMob[cId1].Target.X == 1046 && cMob[cId1].Target.Y == 1690)
		{
			if(cId1 > 0 && cId1 < MAX_PLAYER)
			{
				DoTeleport(cId1, 1057, 1742);

				return;
			}
		}
	}

	int LOCAL_3 = cMob[cId2].Equip[0].Index;

	if(cId2 > MAX_PLAYER && cMob[cId2].CapeInfo == 4 && LOCAL_3 >= 315 && 345 && cId1 > MAX_PLAYER && cMob[cId1].CapeInfo != 4)
	{
		int LOCAL_4 = cMob[cId2].Summoner;

		if(LOCAL_4 > 0 && LOCAL_4 < MAX_PLAYER && cUsers[LOCAL_4].Status)
		{
			if(cMob[LOCAL_4].Mode)
			{
				int LOCAL_5 = cMob[LOCAL_4].Equip[14].Index;

				if(LOCAL_5 >= 2330 && LOCAL_5 < 2360)
				{
					int LOCAL_6 = cMob[LOCAL_4].Equip[14].EF2,
						LOCAL_7 = cMob[LOCAL_4].Equip[14].EF3,
						LOCAL_8 = (LOCAL_6 & 0xFF) + 100;

					if(LOCAL_5 == 2330)
						LOCAL_8 = (LOCAL_6 & 0xFF) + 25;
					else if(LOCAL_5 == 2331)
						LOCAL_8 = (LOCAL_ & 0xFF) + 50;

					if((LOCAL_6 & 0xFF) < cMob[cId1].Status.Level && (LOCAL_6 & 0xFF) < 100)
					{
						LOCAL_8 = LOCAL_8 + 1;

						if((LOCAL_7 & 0xFF) >= (LOCAL_8 & 0xFF))
						{
							LOCAL_7 = 1;
							LOCAL_6++;

							cMob[LOCAL_4].Equip[14].EFV3 = LOCAL_7;
							cMob[LOCAL_4].Equip[14].EF2 = LOCAL_6;

							SendClientMessage(LOCAL_4, 0x007D8958);

							SendItem(LOCAL_4, 0, 14, &cMob[LOCAL_4].Equip[14]);
							MountProcess(LOCAL_4, 0);
						}
						else
						{
							cMob[LOCAL_4].Equip[14].EFV3 = LOCAL_7;
							SendItem(LOCAL_4, 0, 14, &cMob[LOCAL_4].Equip[14]);
						}
					}
				}
			}
		}
	}
	
	// Code do Kevin \/

	p338 LOCAL_13;
	LOCAL_13.Header.PacketId = 0x338;
	LOCAL_13.Header.Size = sizeof p338; // 0x14
	LOCAL_13.Header.ClientId = 30000;

	LOCAL_13.Unknow1 = arg1;
	LOCAL_13.killed = arg2;

	cMob[cId1].Status.curHP = 0;

	INT32 LOCAL_14 = cMob[cId2].Leader;
	if(LOCAL_14 == 0)
		LOCAL_14 = arg2;

	// 45AF56

	if(cId2 >= MAX_PLAYER && cMob[cId2].CapeInfo == 4)
	{
		INT32 LOCAL_15 = cMob[cId2].Summoner;

		if(LOCAL_15 <= 0 || LOCAL_15 >= MAX_PLAYER || cUsers[LOCAL_15].Status != 22)
		{
			GridMulticast_2(cMob[cId1].Target.X, cMob[cId1].Target.Y, &LOCAL_13, 0);

			if(cId1 > 100)
				DeleteMob(cId1, 1);

			return;
		}
		else
			cId2 = LOCAL_15;
	}

	if(cId1 < MAX_PLAYER && cMob[cId1].bStatus.Level <= 359)
	{
		INT32 LOCAL_16 = cMob[cId1].bStatus.Level;

		if(LOCAL_16 < 0 || LOCAL_16 >= 355)
			return;

		INT32 LOCAL_17 = g_pNextLevel[LOCAL_16];
		INT32 LOCAL_18 = g_pNextLevel[LOCAL_16 + 1];

		INT32 LOCAL_19 = LOCAL_18 - LOCAL_17;

		INT32 LOCAL_20 = LOCAL_19 / 20;

		if(LOCAL_16 >= 30)
			LOCAL_20 = LOCAL_19 / 22;
		
		if(LOCAL_16 >= 40)
			LOCAL_20 = LOCAL_19 / 25;

		if(LOCAL_16 >= 50)
			LOCAL_20 = LOCAL_19 / 30;

		if(LOCAL_16 >= 60)
			LOCAL_20 = LOCAL_19 / 35;

		if(LOCAL_16 >= 70)
			LOCAL_20 = LOCAL_19 / 40;

		if(LOCAL_16 >= 80)
			LOCAL_20 = LOCAL_19 / 45;

		if(LOCAL_16 >= 90)
			LOCAL_20 = LOCAL_19 / 50;

		if(LOCAL_16 >= 100)
			LOCAL_20 = LOCAL_19 / 55;

		if(LOCAL_16 >= 150)
			LOCAL_20 = LOCAL_19 / 70;

		if(LOCAL_16 >= 200)
			LOCAL_20 = LOCAL_19 / 85;

		if(LOCAL_16 >= 250)
			LOCAL_20 = LOCAL_19 / 100;

		// 0045B154
		if(LOCAL_20 < 0)
			LOCAL_20 = 0;

		if(LOCAL_20 > 30000)
			LOCAL_20 = 30000;

		INT32 LOCAL_21 = GetCurKill(cId2);
		INT32 LOCAL_22 = GetTotKill(cId2);
		INT32 LOCAL_23 = GetPKPoint(cId2);
		INT32 LOCAL_24 = GetPKPoint(cId1);
		INT32 LOCAL_25 = GetGuilty(cId1);
		INT32 LOCAL_26 = GetCurKill(cId1);
		
		INT32 LOCAL_27 = cMob[cId1].CapeInfo;
		INT32 LOCAL_28 = cMob[cId1].CapeInfo; 

		INT32 LOCAL_29 = 0;
		INT32 LOCAL_30 = 0;

		if(LOCAL_24 <= 0)
			LOCAL_20 = LOCAL_20 * 5;
		else if(LOCAL_24 <= 25)
			LOCAL_20 = LOCAL_20 * 3;

		INT32 LOCAL_31 = cMob[cId1].Target.X >> 7;
		INT32 LOCAL_32 = cMob[cId1].Target.Y >> 7;

		if(cId2 < MAX_PLAYER)
		{
			if(TESTSERVER != 0)
				LOCAL_20 = LOCAL_20 / 3;
			else
				LOCAL_20 = LOCAL_20 / 6;

			if((LOCAL_27 == 7 && LOCAL_28 == 8) || (LOCAL_27 == 8 && LOCAL_28 == 7))
				LOCAL_29 = 1;

			INT32 LOCAL_33 = cMob[cId1].GuildIndex;
			INT32 LOCAL_34 = cMob[cId2].GuildIndex;

			INT32 LOCAL_35 = 65536;

			if(LOCAL_33 > 0 && LOCAL_33 < LOCAL_35 && LOCAL_34 > 0 && LOCAL_34 < LOCAL_35 && g_pGuildWar[LOCAL_33] == LOCAL_34 && g_pGuildWar[LOCAL_34] == LOCAL_33)
				LOCAL_30 = 1;

			if(CastleState != 0 && LOCAL_31 == 8 && LOCAL_32 == 13)
				LOCAL_30 = 1;

			GridMulticast_2(cMob[cId1].Target.X, cMob[cId1].Target.Y, &LOCAL_13, 0);

			INT32 LOCAL_36 = BASE_GetArena(  cMob[cId1].Target.X, cMob[cId1].Target.Y);
			INT32 LOCAL_37 = BASE_GetVillage(cMob[cId1].Target.X, cMob[cId1].Target.Y);

			INT32 LOCAL_38 = 0;

			if(LOCAL_31 == 0 && LOCAL_32 == 31)
				LOCAL_38 = 1;

			if(LOCAL_36 == 5 && LOCAL_37 == 5 && LOCAL_38 == 0)
			{
				if(TESTSERVER != 0)
					LOCAL_20 = LOCAL_20 >> 2;

				if(LOCAL_29 != 0)
					LOCAL_20 = LOCAL_20 + ((LOCAL_20 * LOCAL_26) >> 2);

				if(LOCAL_20 > 150000)
					LOCAL_20 = 150000;

				if(LOCAL_20 < 0)
					LOCAL_20 = 0;

				// 0045B47B
				if(LOCAL_16	>= 20)
				{
					if(cId2 < MAX_PLAYER)
						cMob[cId1].Exp = cMob[cId1].Exp - LOCAL_20;
					else if(DEADPOINT != 0)
						cMob[cId1].Exp = cMob[cId1].Exp - LOCAL_20;

					if(cMob[cId1].Exp < 0)
						cMob[cId1].Exp = 0;

					if(DEADPOINT != 0 || cId2 < 100)
					{
						sprintf(temp, "Você perdeu %d de experiência", LOCAL_20);
						SendClientMessage(cId1, temp);

						SendEtc(cId1);
					}
				}
				else
					SendClientMessage(cId1, "Level abaixo de 20 não perde experiência."); // No caso, MeessageString, ou seilá o nome

				if(LOCAL_29 != 0)
				{
					INT32 LOCAL_39 = LOCAL_20 << 1 / 3; // 0045B578

					INT32 LOCAL_40 = cMob[cId1].Status.Level;
					if(LOCAL_40 < 0)
						LOCAL_40 = 0;

					if(LOCAL_40 > 300)
						LOCAL_40 = 300;

					INT32 LOCAL_41 = g_pNextLevel[LOCAL_40];
					if(cMob[cId1].Exp < LOCAL_41)
						LOCAL_39 = 0;

					cMob[cId2].Exp = cMob[cId2].Exp + LOCAL_39;
					if(cMob[cId2].Exp < 0)
						cMob[cId2].Exp = 0;

					sprintf(temp, "Você ganhou %d de experiência", LOCAL_39); // string table
					SendClientMessage(cId2, temp);

					SendEtc(cId2); //  45B668
					
					SetCurKill(cId2, LOCAL_21 + 1);
					SetTotKill(cId2, LOCAL_22 + 1);

					if(LOCAL_30 == 0 && LOCAL_25 == 0)
					{
						INT32 LOCAL_42 = (-(LOCAL_24 / 20)) * 3;

						if(LOCAL_42 < -9)
							LOCAL_42 = -9;

						if(LOCAL_42 > 0)
							LOCAL_42 = 0;

						if(LOCAL_25 > 0)
							LOCAL_42 = 0;

						LOCAL_23 = LOCAL_23 + LOCAL_42;

						SetPKPoint(cId2, LOCAL_23);
						sprintf(temp, "CP %d diminuiu em %d", LOCAL_23 - 75, -1);

						SendClientMessage(cId2, temp);
					}
				}
				else if(LOCAL_30 == 0) // 0045B74F
				{
					INT32 LOCAL_43 = (-(LOCAL_24 / 25) * 3);

					if(LOCAL_43 < -9)
						LOCAL_43 = -9;

					if(LOCAL_43 > 0)
						LOCAL_43 = 0;

					if(LOCAL_25 > 0)
						LOCAL_43 = 0;

					if(cMob[cId1].Equip[15].Index == 548 || cMob[cId1].Equip[15].Index == 549 || cMob[cId2].Equip[15].Index == 548 || cMob[cId2].Equip[15].Index == 549)
						LOCAL_43 = LOCAL_43 * 3;

					LOCAL_23 = LOCAL_23 + LOCAL_43;

					SetPKPoint(cId2, LOCAL_23);

					if(LOCAL_43 != 0)
					{
						sprintf(temp, "CP %d diminuiu em %d", LOCAL_23 - 75, -LOCAL_43);

						SendClientMessage(cId2, temp);
					}

					if(LOCAL_24 <= 60)
					{
						INT32 LOCAL_44 = (75 - LOCAL_24) / 10;
						INT32 LOCAL_45 = 0;

						for(INT32 LOCAL_46 = 0; LOCAL_46 < 63; LOCAL_46 ++)
						{
							if(Rand() % 5)
								continue;

							INT32 LOCAL_47 = cMob[cId1].Target.X;
							INT32 LOCAL_48 = cMob[cId1].Target.Y;
							
							st_Item *LOCAL_49 = &cMob[cId1].Inventory[LOCAL_46];

							if(LOCAL_49->Index <= 0 || LOCAL_49->Index > MAX_ITEM)
								continue;

							if(LOCAL_49->Index == 508 || LOCAL_49 ->Index == 509 || LOCAL_49->Index == 522 || LOCAL_49->Index == 531 || LOCAL_49->Index == 446)
								continue;

							INT32 LOCAL_50 = Rand() & 0x80000003;

							INT32 LOCAL_51 = CreateItem(LOCAL_47, LOCAL_48, LOCAL_49, 1);
							if(LOCAL_51 >= 5000 || LOCAL_51 <= 0)
								continue;

							if(BASE_NeedLog(LOCAL_49, 0))
							{
								char LOCAL_59 [32];
								BASE_GetItemCode(LOCAL_49, LOCAL_59);

								sprintf(temp, "cho %s", LOCAL_59);

//								BASE_Log(temp, Users[arg1].Username, Users[arg1].In_Addr.S_un.S_un_b.s_b1);
							}

							memset(LOCAL_49, 0, 8);
							// INICIO DO BUFFER -> EBP - 108h
							char buffer[28];

							*(WORD*)&buffer[4] = 0x175;
							*(WORD*)&buffer[0] = 28;
							*(DWORD*)&buffer[12] = 1;
							*(DWORD*)&buffer[16] = LOCAL_46;
							*(DWORD*)&buffer[20] = LOCAL_50;
							*(WORD*)&buffer[24] = LOCAL_47;
							*(WORD*)&buffer[28] = LOCAL_48;

							_SendOneMessage(buffer, *(WORD*)&buffer[0]);
							
							LOCAL_45 = LOCAL_45 + 1;
							if(!Rand() & 0x80000001)
								break;

							if(LOCAL_45 >= LOCAL_44)
								break;
						}
					}
					
					if(LOCAL_24 <= 35)
					{
						INT32 LOCAL_67 = (LOCAL_24 + 10) / 10;

						if(LOCAL_67 <= 0)
							LOCAL_67 = 1;

						INT32 LOCAL_68 = Rand() % LOCAL_67;
						//0045BB71
						INT32 LOCAL_69;
						// Não entendi direito essa parte, tá muito confuso
						while(!LOCAL_68)
						{ 
							LOCAL_69 = Rand() % 14 + 1;
							if(LOCAL_69 != 12)
							{
								INT32 LOCAL_70 = cMob[cId1].Target.X;
								INT32 LOCAL_71 = cMob[cId1].Target.Y;

								st_Item *LOCAL_72 = &cMob[cId1].Equip[LOCAL_69];
								if(LOCAL_72->Index <= 0  || LOCAL_72->Index > MAX_ITEM)
									break;
								
								if(LOCAL_72->Index == 508 || LOCAL_72->Index == 509 || LOCAL_72->Index == 522 || LOCAL_72->Index == 531 || LOCAL_72->Index == 446)
									break;

								INT32 LOCAL_73 = Rand() & 0x80000003;

								INT32 LOCAL_74 = CreateItem(LOCAL_70, LOCAL_71, LOCAL_72, 1);
								if(LOCAL_74 >= 5000 || LOCAL_74 <= 0)
									break;

								if(BASE_NeedLog(LOCAL_72, 0))
								{
									char LOCAL_82 [32];
									BASE_GetItemCode(LOCAL_72, LOCAL_82);

									sprintf(temp, "cho %s", LOCAL_82);

	//								BASE_Log(temp, Users[arg1].Username, Users[arg1].In_Addr.S_un.S_un_b.s_b1);
								}
								char buffer[28];

								*(WORD*)&buffer[4] = 0x175;
								*(WORD*)&buffer[0] = 28;
								*(DWORD*)&buffer[12] = 0;
								*(DWORD*)&buffer[16] = LOCAL_69;
								*(DWORD*)&buffer[20] = LOCAL_73;
								*(WORD*)&buffer[24] = LOCAL_70;
								*(WORD*)&buffer[28] = LOCAL_71;

								_SendOneMessage(buffer, *(WORD*)&buffer[0]);
							}
						}
					}
					
					p613_GetCreateMob LOCAL_116;
					GetCreateMob(cId2, &LOCAL_116);

					GridMulticast_2(cMob[cId2].Target.X, cMob[cId2].Target.Y, &LOCAL_116, 0);

					if(LOCAL_29 != 0)
						SetCurKill(cId1, 0);
								
					if(LOCAL_24 < 75 && LOCAL_30 == 0 && arg2 < MAX_PLAYER)
					{
						LOCAL_24 = LOCAL_24 + 1;

						SetPKPoint(cId1, LOCAL_24);
						// 0045BE65

						sprintf(temp, "CP %d aumentou em %d.", LOCAL_24 - 75, 1);
						SendClientMessage(cId1, temp);
					}
					
					GetCreateMob(cId1, &LOCAL_116);

					GridMulticast_2(cMob[cId1].Target.X, cMob[cId1].Target.Y, &LOCAL_116, 0);

					INT32 LOCAL_117 = cMob[cId2].Status.Level,
						  LOCAL_118 = cMob[cId1].Status.Level;

					// 0x0045BEE8
				}
			}
		}
	}
}

