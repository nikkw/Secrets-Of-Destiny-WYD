#define EF_NONE     			  0	// * EFFECT TypeÀÌ 0 ÀÌ¸é ÀÌÆåÆ®°¡ ¾ø´Ù.  ITEM¿¡¼­ Score[0]ÀÇ °ªÀ» ´õÇÒ¼ö ¾ø´Ù.

#define EF_LEVEL     			  1	// ·¹º§ * Score[1] - Score[15] Bonus Score°ªÀ» ±×´ë·Î ´õÇØ ¹ö¸°´Ù.
#define EF_DAMAGE                 2 // Áõµ©
#define EF_AC       			  3	// ¹æ¾î
#define EF_HP        			  4	// ÇÇÁõ  HP,MP,°ø°Ý¼Óµµ,ÀÌµ¿¼Óµµ,°¢Á¾ MAXµîµî
#define EF_MP       			  5	// ¸¶Áõ
#define EF_EXP      			  6	// °æÇè
#define EF_STR      		      7	// Èû
#define EF_INT      		      8	// Á¤½Å
#define EF_DEX       		      9	// ¹ÎÃ¸
#define EF_CON      		     10	// Ã¼°Ý
#define EF_SPECIAL1    		     11	// ¹«¸¶
#define EF_SPECIAL2    			 12	// Æ¯1
#define EF_SPECIAL3    			 13	// Æ¯2
#define EF_SPECIAL4    			 14	// Æ¯3
// Score ³¡.
#define EF_SCORE14     			 15	//
#define EF_SCORE15     			 16	//
////////////////      REQUIREMENT        //////////////////////////////////////////
#define EF_POS                   17  // À§Ä¡ ÀÔÀ»¼ö ÀÖ´Â Àå¼Ò bit°ª         - µðÆúÆ® NOWHERE (0ºñÆ® °¡ EQUIP 0)
#define EF_CLASS                 18  // Á÷¾÷ ÀÔÀ»¼ö ÀÖ´Â (¼ºº°)Å¬·¡½º bit°ª - µðÆúÆ® YES
#define EF_R1SIDC                19  // ÇÑ¼Õ 1ÇÚµå ¶Ç´Â °©¿ÊÀÇ ÀÔÀ»¼ö ÀÖ´Â STR INT DEC CON         - µðÆúÆ® 0
#define EF_R2SIDC                20  // µÎ¼Õ 2ÇÚµå          ÀÇ ÀÔÀ»¼ö ÀÖ´Â STR INT DEC CON         - µðÆúÆ® ºÒ°¡
////////////////   BONUS  ////////////////////////////////
#define EF_WTYPE         	     21	 // ¹«·ù ¹«±âºÐ·ù (¾Ö´Ï¸ÞÀÌ¼Ç)
////////////////////////////////////////////////////////////////////////////
#define EF_REQ_STR               22  // ÈûÁ¦
#define EF_REQ_INT               23  // Á¤Á¦
#define EF_REQ_DEX               24  // ¹ÎÁ¦
#define EF_REQ_CON               25  // ÄÜÁ¦
/////////////////////////////////////////////////////////////////////////
// * ÁÖ ¿ä±¸Ä¡ÀÌ³ª, ¾ÆÀÌÅÛÀº ±âº» SIDC¿¡ Ãß°¡µÇ´Â °ªÀÌ´Ù.
/////////////////////////////////////////////////////////////////////////


#define EF_ATTSPEED  	       	 26	 // °ø¼Ó °ø°Ý¼Óµµ
#define EF_RANGE                 27  // »çÁ¤ »çÁ¤°Å¸®. ÀüÃ¼Áß ÃÖ´ë°ªÀÌ Àû¿ëµÊ.
////#define EF_PRICE				 28	 // °¡°Ý
#define EF_RUNSPEED              29  // ·±´× ´Þ¸®±â¼Óµµ.
#define EF_SPELL    	    	 30	 // ½ºÆç ItemÀ» ¸Ô°Å³ª ÀÔ¾úÀ»¶§ °É¸®´Â ¸¶¹ý
#define EF_DURATION              31  // Áö¼Ó Item ÆÄ¶ó¸ÞÅ¸1 - ¸ÔÀ»¶§ È¿·ÂÀÌ ¹ß»ýÇÏ´Â ½Ã°£, ÀÔ´Â¾ÆÀÌÅÛÀº Ç×»ó
#define EF_PARM2     			 32	 // ÆÄ¶÷ Item ÆÄ¶ó¸ÞÅ¸2
#define EF_GRID                  33  // Å©±â Carry¸¦ Â÷ÁöÇÏ´Â ¾ÆÀÌÅÛ±×¸®µå
#define EF_GROUND                34  // ¶¥Ä­ ¼º¹®µî¿¡¼­ ¶¥À» Â÷ÁöÇÏ´Â Å©±â
#define EF_CLAN                  35  // Á¾Á·
#define EF_HWORDCOIN             36  // ´ëµ·
#define EF_LWORDCOIN             37  // ¼Òµ·
#define EF_VOLATILE              38  // ¼Ò¸ð ¸ÔÀ¸¸é ¹Ù·Î »ç¶óÁö´Â ¾ÆÀÌÅÛ.  0:ÀÏ¹ÝÀå±¸  1:¹°¾à°èÅë  2:µ·°èÅë   3:¿­¼è 4:Ãà1  5:Ãà2  6:Ãà3
                                     //                               6:½ºÆç+15   7:·¹º§+1
#define EF_KEYID                 39  // Å°¹ø
#define EF_PARRY                 40  // È¸ÇÇ È¸ÇÇÀ² º¸³ª½º
#define EF_HITRATE               41  // ¹ÖÁß ¸íÁß·ü º¸³ª½º
#define EF_CRITICAL              42  // Å©¸® Å©¸®Æ¼ÄÃ
#define EF_SANC                  43  // Á¦·Ã Sanctuary ÁÖ·Î º¸³ª½º Æ÷ÀÎÆ®¿¡ Æí¼ºµÇ¸ç
#define EF_SAVEMANA              44  // ¸¶Àý 1 -> 99%
#define EF_HPADD                 45  // ÇÇ»½ 1 -> 101%   MAX_MP
#define EF_MPADD                 46  // ¸¶»½ 1 -> 101%   MAX_MP
#define EF_REGENHP               47  // ÇÇÈ¸
#define EF_REGENMP               48  // ¸¶È¸
#define EF_RESIST1               49  // ºÒÀú
#define EF_RESIST2               50  // ¾óÀú
#define EF_RESIST3               51  // ½ÅÀú
#define EF_RESIST4               52  // ¹øÀú
#define EF_ACADD                 53  // ¹æÁõ
#define EF_RESISTALL             54  // ¿ÃÀú
#define EF_BONUS                 55  // º¸³ª
#define EF_HWORDGUILD            56  // ±æµå
#define EF_LWORDGUILD            57  // ±æµå
#define EF_QUEST                 58  // ÀÓ¹« ¹Ýµå½Ã 1ºÎÅÍ ½ÃÀÛ, ´ëºÎºÐ Volatile°ú ÇÔ°Ô ¼¼ÆÃµÉ °Í ÀÓ.
#define EF_UNIQUE                59  // °íÀ¯
#define EF_MAGIC                 60  // ¸¶°ø 1 -> 1% ÁõÆø
#define EF_AMOUNT                61  // °¹¼ö
#define EF_HWORDINDEX            62  // ¹øÈ£
#define EF_LWORDINDEX            63  // ¹øÈ£
#define EF_INIT1                 64  // ÃÊ±â
#define EF_INIT2                 65  // ÃÊ±â
#define EF_INIT3                 66  // ÃÊ±â
#define EF_DAMAGEADD             67  // ´ï»Ç
#define EF_MAGICADD              68  // ¸¶»Ç
                                     // ´ÙÀ½ 2µéÀº º°·Îµµ Äõ¸®¸¦ ´øÁöÁö ¾Ê°í º£ÀÌ½º¸¦ Äõ¸®¸¦ ´øÁö¸é À¯´Ð ¿É¿¡¼­ ÀÚµ¿ Ã¼Å·ÇÏ´Â ºÎºÐ.
                                     // Å¬¶óÀÌ¾ðÆ® Ç¥±â½Ã´Â ÀÌ°ÍÀ» ¸ÕÀú ´øÀú¼­ ÀÌ°ÍÀÌ ³ª¿À¸é º£ÀÌ½º´Â ´øÁöÁö ¾Ê´Â´Ù.
#define EF_HPADD2                69  // ÇÇ2   ÇÇ»½°ú °°À¸³ª ±âº» ¿É¿¡ Æ÷ÇÔµÇ¾î Ç¥½ÃµÈ´Ù.
#define EF_MPADD2                70  // ÇÇ2   ÇÇ»½°ú °°À¸³ª ±âº» ¿É¿¡ Æ÷ÇÔµÇ¾î Ç¥½ÃµÈ´Ù.
#define EF_CRITICAL2             71  // Å©¸® Å©¸®Æ¼ÄÃ
#define EF_ACADD2                72  // ¹æÁõ
#define EF_DAMAGE2               73  //
#define EF_SPECIALALL            74  // ¸¶½ºÅÍ¸® ¹«¸¶Á¦¿Ü Áõ°¡

#define	EF_CURKILL				 75  // not used
#define EF_LTOTKILL				 76  // not used
#define EF_HTOTKILL				 77  // not used
#define EF_INCUBATE				 78  // ºÎÈ­ÀÓ°èÄ¡


#define EF_MOUNTLIFE			 79  // ¸» ÃÑ »ý¸í
#define EF_MOUNTHP				 80  // ¸» Çö ÇÇ
#define EF_MOUNTSANC			 81  // ¸» ¼ºÀåµµ
#define EF_MOUNTFEED			 82  // ¸» ¹èºÎ¸§ Á¤µµ
#define EF_MOUNTKILL			 83  // ¸»ÀÌ Á×ÀÎ ¸ó½ºÅÍ °¹¼ö?

#define EF_INCUDELAY             84
#define EF_SUBGUILD				 85	// SUB±æµå, 0ÀÌ¸é ÃÖ´ë±æµå 1,2,3±îÁö ÀÖ´Ù

#define EF_MOBFACE				 86

#define EF_GRADE0				 100 // 0±Þ
#define EF_GRADE1				 101 // 1±Þ
#define EF_GRADE2				 102 // 2±Þ
#define EF_GRADE3				 103 // 3±Þ
#define EF_GRADE4				 104 // 4±Þ
#define EF_GRADE5				 105 // 5±Þ

#define EF_GETHP                 106 // Extração de saúde
#define EF_GETMP                 107 // Extração de mana

#define EF_MOBTYPE				 112
#define EF_ITEMTYPE				 116
/*
116~125 CORES
*/
