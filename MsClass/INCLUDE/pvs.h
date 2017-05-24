#pragma pack(push, 1)

	static short pvs0[] = {
		0		};
	static short pvs1[] = {
		-1		};
	static short pvs2[] = {
		1,127,0, 1,2		};
	static short pvs3[] = {
		3,2,1,   1,2, 2,3, 3,1		};
	static short pvs4[] = {
		4,2,1,   1,2, 2,4, 4,3, 3,1		};
	static short pvs8[] = {
		12,2,0,  1,2, 2,4, 4,3, 3,1, 1,5, 5,6, 6,2,
		6,8, 8,4, 8,7, 7,3, 7,5		};
	static short pvs6[] = {6,2,0, 1,2, 2,3, 3,1, 3,4, 2,4, 1,4};
	static short pvs9[] = {9,2,0, 1,2, 2,3, 3,1, 1,4, 2,5, 3,6,
				     4,5, 5,6, 6,4};
	static short pvs36[] = {6,2,0, 1,2, 2,3, 3,5, 5,6, 6,4, 4,1};
	static short pvs48[] = {8,2,0, 1,2, 2,3, 3,5, 5,8, 8,7, 7,6, 6,4,
				      4,1};
	static short pvs481[] = {8,2,0, 1,2, 2,3, 3,4, 4,5, 5,6, 6,7, 7,8, 8,1};
	static short pvs361[] = {6,2,0, 1,2, 2,3, 3,4, 4,5, 5,6, 6,1};
	static short *pvs[501]={
		pvs0,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2, /*   1-10 */
		pvs4,pvs3,pvs4,pvs3,pvs3,pvs1,pvs1,pvs4,pvs4,pvs4,    /*  11-20 */
		pvs4,pvs3,pvs4,pvs3,pvs3,pvs481,pvs4,pvs361,pvs4,pvs4,  /*  21-30 */
		pvs8,pvs6,pvs9,pvs9,pvs1,pvs8,pvs1,pvs1,pvs1,pvs1,      /*  31-40 */
		pvs4,pvs3,pvs1,pvs4,pvs3,pvs1,pvs1,pvs1,pvs1,pvs4,      /*  41-50 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs4,pvs4,pvs1,pvs2,pvs1,      /*  51-60 */
		pvs4,pvs3,pvs1,pvs4,pvs1,pvs2,pvs1,pvs1,pvs1,pvs2,      /*  61-70 */
		pvs4,pvs3,pvs4,pvs4,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  71-80 */
		pvs4,pvs3,pvs4,pvs4,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  81-90 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  91-100 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  101-110 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  111-120 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  121-130 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  131-140 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  141-150 */
		pvs1,pvs1,pvs1,pvs2,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  151-160 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  161-170 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  171-180 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  181-190 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  191-200 */
		pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,	/*  201-210 */
		pvs4,pvs3,pvs4,pvs3,pvs36,pvs1,pvs1,pvs4,pvs4,pvs48,    /*  211-220 */
		pvs4,pvs3,pvs4,pvs3,pvs1,pvs481,pvs4,pvs361,pvs4,pvs4,  /*  221-230 */
		pvs8,pvs6,pvs9,pvs1,pvs1,pvs8,pvs1,pvs1,pvs1,pvs1,      /*  231-240 */
		pvs4,pvs3,pvs1,pvs4,pvs4,pvs1,pvs1,pvs1,pvs1,pvs4,      /*  241-250 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs4,pvs4,pvs1,pvs2,pvs1,      /*  251-260 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs2,      /*  261-270 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  271-280 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  281-290 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  291-300 */
		pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,	/*  301-310 */
		pvs4,pvs3,pvs4,pvs3,pvs36,pvs1,pvs1,pvs4,pvs4,pvs48,    /*  311-320 */
		pvs4,pvs3,pvs4,pvs3,pvs1,pvs481,pvs4,pvs361,pvs4,pvs4,  /*  321-330 */
		pvs8,pvs6,pvs9,pvs1,pvs1,pvs8,pvs1,pvs1,pvs1,pvs1,      /*  331-340 */
		pvs4,pvs3,pvs1,pvs4,pvs4,pvs1,pvs1,pvs1,pvs1,pvs4,      /*  341-350 */
		pvs1,pvs2,pvs1,pvs1,pvs1,pvs4,pvs4,pvs1,pvs2,pvs1,      /*  351-360 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs2,      /*  361-370 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  371-380 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  381-390 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  391-400 */
		pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2,pvs2, 	/*  401-410 */
		pvs4,pvs3,pvs4,pvs3,pvs36,pvs1,pvs1,pvs4,pvs4,pvs48,    /*  411-420 */
		pvs4,pvs3,pvs4,pvs3,pvs1,pvs481,pvs4,pvs361,pvs4,pvs4,  /*  421-430 */
		pvs8,pvs6,pvs9,pvs1,pvs1,pvs8,pvs1,pvs1,pvs1,pvs1,      /*  431-440 */
		pvs4,pvs3,pvs1,pvs4,pvs4,pvs1,pvs1,pvs1,pvs1,pvs4,      /*  441-450 */
		pvs1,pvs1,pvs2,pvs1,pvs1,pvs4,pvs4,pvs1,pvs2,pvs1,      /*  451-460 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs2,      /*  461-470 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  471-480 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,      /*  481-490 */
		pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1,pvs1};      /*  491-500 */
#pragma pack(pop)
