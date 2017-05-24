#include <stdafx.h>
#include <schema.h>
#include <time.h>
#include <assert.h>
void			MultMatr(double a[], double b[], short ia, short ja, short jb, double c[]);
void			ElemBodyGeom(DECART *Coord, float Eps, ELEM_BODY &EB, ELEM_BODY_GEOM &EBG);
BOOL			Progress(int);
LPCSTR EXPORT	GetPath(HINSTANCE, LPCSTR);

void EXPORT SCHEMA::LookBody(double *MK, BYTE TypeProfile, BYTE TypePlate)
{
	long		i, j, kG, kGD, n, kU, k, m, kGF;
	long		*NumElemBody;
	DECART		*LookCoord, *pD;
	double		xMax, xMin, zMax, zMin, rCK[3], MKR[9];
	float		Eps;
	ELEM_BODY	*pEB;
	FORMAT		*pF;
	BYTE		YesVol = 0, Modify = 0, Control;
	WORD		kNode, kElem;
	int			Type;
	long		*Num;
	char		cd[40];

	if(this == NULL)
		return;

	if(MK == NULL)
	{
		ZeroMemory(MKR, 9 * sizeof(double));
		MKR[0] = MKR[4] = MKR[8] = 1;
	}
	else
		memcpy(MKR, MK, 9 * sizeof(double));

	if(QuantityNode == 0 || QuantityElem == 0)
		return;
	if(memcmp(MKR, Video.MK, 9 * sizeof(double)))
		Modify = 1;

	if
	(
		Video.TypeProfile != TypeProfile ||
		Video.TypePlate != TypePlate ||
		//		 Video.Fragm != Video.FragmParam ||
		Video.QuantityElemMask != QuantityElem
	) Modify = 1;
	else
	{
		if(Video.MaskFragm)
			for(i = 0; i < QuantityElem; i++)
				if(BitRead(Video.MaskFragm, i) != GetBitFlag(i + 1, 0))
				{
					Modify = 1;
					break;
				}

		if(Video.MaskElem)
			for(i = 0; i < QuantityElem; i++)
				if(BitRead(Video.MaskElem, i) != GetBitFlag(i + 1, 7))
				{
					Modify = 1;
					break;
				}
	}

	if(Modify == 0)
		return;
	DeleteLookBody();
	Video.DelProfile = 1;
	if(GetPrivateProfileString("SCHEMA", "DelProfile", "", cd, 40, GetPath(hINST, "FORUM.INI")))
	{
		Video.DelProfile = CharDouble(cd, Control);
		if(Control)
			Video.DelProfile = 1;
	}
	else
	{
		if
		(
			GetPrivateProfileString
				(
					"SCHEMA",
					"DelProfile",
					"",
					cd,
					40,
					GetPath(hINST, "SCAD.INI")
				)
		)
		{
			Video.DelProfile = CharDouble(cd, Control);
			if(Control)
				Video.DelProfile = 1;
		}
	}

	Video.MaskElem = (BYTE *) Memory(QuantityElem / 8 + 1);
	Video.MaskFragm = (BYTE *) Memory(QuantityElem / 8 + 1);
	for(i = 0; i < QuantityElem; i++)
	{
		if(Video.FragmParam)
			if(GetBitFlag(i + 1, 0))
				BitOn(Video.MaskFragm, i);
		if(GetBitFlag(i + 1, 7))
			BitOn(Video.MaskElem, i);
	}

	Video.TypeProfile = TypeProfile;
	Video.TypePlate = TypePlate;
	Video.QuantityElemMask = QuantityElem;
	memcpy(Video.MK, MKR, 9 * sizeof(double));

	kG = kU = kGD = 0;
	RigidInFormat();

	for(i = 0; i < QuantityElem; i++)
	{
		pF = (FORMAT *) &pFormat[i];

		for(j = 0; j < pF->QuantityNode; j++)
		{
			m = pF->pNode[j];
			if(m == 0 || m > QuantityNode)
				break;
		}

		if(j < pF->QuantityNode)
			continue;

		pF->Check = 0;
		if(BitRead((BYTE *) &pF->Flags, 0))
			continue;
		if
		(
			pF->TypeElem == 200 ||
			pF->TypeElem > 2000 ||
			BitRead((BYTE *) &pF->Flags, 7) ||
			pF->QuantityNode < 2
		) continue;		//MP

		if(TypeProfile)
		{
			ProfileInform(*pF, kNode, kElem);
			if(kNode)
			{
				kU += kNode;
				kGD += kElem;
				kG++;
				continue;
			}
		}

		kG++;
		n = pFormat[i].TypeElem % 100;
		if(TypePlate)
		{
			if
			(
				pF->TypeElem == 1060 ||
				pF->TypeElem == 1061 ||
				pF->TypeElem == 1080 ||
				pF->TypeElem == 1085
			)
			{
				kG += 3 * pF->QuantityNode;
				kU += 2 * pF->QuantityNode;
			}
			else if(ElemType(pF->TypeElem) == 2)
			{
/*
				if(pF->QuantityNode == 3)
					kG += 4;
				if(pF->QuantityNode == 4)
					kG += 5;
*/
				kG += pF->QuantityNode+1;
				kU += 2 * pF->QuantityNode;
				YesVol = 1;
			}
		}
		else
		{
			if
			(
				pF->TypeElem == 1060 ||
				pF->TypeElem == 1061 ||
				pF->TypeElem == 1080 ||
				pF->TypeElem == 1085
			) kG += pF->QuantityNode;
		}

		if
		(
			n > 30 &&
			n <= 40
		) YesVol = 1;
			if(n == 31 || n == 36 || n == 37)
				kG += 5;
			if(n == 32)
				kG += 3;
			if(n == 33 || n == 34)
				kG += 4;
		}

		//     Progress(2);
		if(kU)
		{
			Video.Coord = (CK *) Memory(kU + 1, sizeof(CK));
			Video.GrafCoord = (GrafCK *) Memory(kU + 1, sizeof(GrafCK));
		}

		kGF = kG + kGD;
		Video.ElemBody = pEB = (ELEM_BODY *) Memory(2*kGF + 2, sizeof(ELEM_BODY));
		NumElemBody = (long *) Memory(kGF + 2, sizeof(long));
		LookCoord = (DECART *) Memory(kU + QuantityNode + 1, sizeof(DECART));

		for(i = 0; i < QuantityNode; i++)
		{
			MultMatr(MKR, (double *) &Coord[i], 3, 3, 1, rCK);
			LookCoord[i].x = rCK[0];
			LookCoord[i].y = rCK[1];
			LookCoord[i].z = rCK[2];
		}

		for(i = 1; i <= QuantityElem; i++)
		{
			if(Video.DeleteProcess)
			{
				DeleteLookBody();
				goto _10;
			}

			pF = (FORMAT *) &pFormat[i - 1];
			for(j = 0; j < pF->QuantityNode; j++)
			{
				m = pF->pNode[j];
				if(m == 0 || m > QuantityNode)
					break;
			}

			if(j < pF->QuantityNode)
				continue;
			if(BitRead((BYTE *) &pF->Flags, 0))
				continue;
			if
			(
				pF->TypeElem == 200 ||
				pF->TypeElem > 2000 ||
				BitRead((BYTE *) &pF->Flags, 7) ||
				pF->QuantityNode < 2
			) continue; //MP

			n = pF->TypeElem % 100;
			Type = ElemType(pF->TypeElem);
			pEB->NumElem = i;

			if(Type == 1)
			{
				if(TypeProfile)
				{
					ProfileInform(*pF, kNode, kElem);
					if(kNode)
					{
						if(ProfileNode(MKR, LookCoord, i, pEB) == 0)
						{
							pEB++;
							continue;
						}

						pF->Check = 0;
					}
				}

				CopyWordToLong(pEB->Node, pF->pNode, 2);
				pEB->Type = 2;
				pEB++;
				continue;
			}

			if(n < 31 || n > 40)
			{
				pEB->Type = pF->QuantityNode;
				if(n == 15 || n == 25 || n == 45)
				{
					if(pEB->Type > 3)
						pEB->Type = 3;
				}
				else if(pEB->Type > 4)
					pEB->Type = 4;
				CopyWordToLong(pEB->Node, pF->pNode, pEB->Type);
				if(TypePlate)
				{
					if
					(
						pF->TypeElem == 1060 ||
						pF->TypeElem == 1061 ||
						pF->TypeElem == 1080 ||
						pF->TypeElem == 1085
					)
					{
						if(ConturPlate(pEB, LookCoord))
							if(ConturPlate(pEB))
								continue;
					}
					else if(Type == 2)
						if(ProfilePlate(pEB, LookCoord, NumElemBody))
						{
							pEB++;
							continue;
						}
				}
				else
				{
					if
					(
						pF->TypeElem == 1060 ||
						pF->TypeElem == 1061 ||
						pF->TypeElem == 1080 ||
						pF->TypeElem == 1085
					)
					{
						if(ConturPlate(pEB))
							continue;
					}
					else
					{
						pEB++;
						continue;
					}
				}

				pEB = &Video.ElemBody[Video.QuantityElemBody];
				continue;
			}

			if(n == 31 || n == 36 || n == 37)
			{
				pEB->Type = 4;
				CopyWordToLong(pEB->Node, pF->pNode, 4);
				(++pEB)->Type = 4;
				pEB->NumElem = i;
				CopyWordToLong(pEB->Node, &pF->pNode[4], 4);
				(++pEB)->Type = 4;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[0];
				pEB->Node[1] = pF->pNode[1];
				pEB->Node[2] = pF->pNode[4];
				pEB->Node[3] = pF->pNode[5];
				(++pEB)->Type = 4;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[1];
				pEB->Node[1] = pF->pNode[3];
				pEB->Node[2] = pF->pNode[5];
				pEB->Node[3] = pF->pNode[7];
				(++pEB)->Type = 4;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[2];
				pEB->Node[1] = pF->pNode[3];
				pEB->Node[2] = pF->pNode[6];
				pEB->Node[3] = pF->pNode[7];
				(++pEB)->Type = 4;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[0];
				pEB->Node[1] = pF->pNode[2];
				pEB->Node[2] = pF->pNode[4];
				pEB->Node[3] = pF->pNode[6];
			}

			if(n == 32)
			{
				pEB->Type = 3;
				CopyWordToLong(pEB->Node, pF->pNode, 3);
				(++pEB)->Type = 3;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[0];
				pEB->Node[1] = pF->pNode[1];
				pEB->Node[2] = pF->pNode[3];
				(++pEB)->Type = 3;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[1];
				pEB->Node[1] = pF->pNode[2];
				pEB->Node[2] = pF->pNode[3];
				(++pEB)->Type = 3;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[0];
				pEB->Node[1] = pF->pNode[2];
				pEB->Node[2] = pF->pNode[3];
			}

			if(n == 33 || n == 34)
			{
				pEB->Type = 3;
				CopyWordToLong(pEB->Node, pF->pNode, 3);
				(++pEB)->Type = 3;
				pEB->NumElem = i;
				CopyWordToLong(pEB->Node, &pF->pNode[3], 3);
				(++pEB)->Type = 4;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[0];
				pEB->Node[1] = pF->pNode[1];
				pEB->Node[2] = pF->pNode[3];
				pEB->Node[3] = pF->pNode[4];
				(++pEB)->Type = 4;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[1];
				pEB->Node[1] = pF->pNode[2];
				pEB->Node[2] = pF->pNode[4];
				pEB->Node[3] = pF->pNode[5];
				(++pEB)->Type = 4;
				pEB->NumElem = i;
				pEB->Node[0] = pF->pNode[0];
				pEB->Node[1] = pF->pNode[2];
				pEB->Node[2] = pF->pNode[3];
				pEB->Node[3] = pF->pNode[5];
			}

			pEB++;
		}

		//      Progress(5);
		Video.QuantityElemBody = (pEB - Video.ElemBody);
		kU = QuantityNode + Video.QuantityNodeBody;

		for(i = 0; i < kU; i++)
		{
			pD = (DECART *) &LookCoord[i];
			if(i == 0)
			{
				xMax = xMin = pD->x;
				zMax = zMin = pD->z;
			}

			if(xMax < pD->x)
				xMax = pD->x;
			if(xMin > pD->x)
				xMin = pD->x;
			if(zMax < pD->z)
				zMax = pD->z;
			if(zMin > pD->z)
				zMin = pD->z;
		}

		Eps = 1e-5 * (xMax - xMin + zMax - zMin);

		//       kG += Video.QuantityElemBody;
		if(MK && (YesVol || TypePlate))
			LookEqBody(LookCoord, Eps);

		if(MK == NULL)
		{
			if(Video.TypeProfile == 0 && Video.TypePlate == 0)
			{
				MemoryFree(LookCoord);
				MemoryFree(NumElemBody);
				return;
			}

			for(i = 0; i < kG; i++)
				NumElemBody[i] = i + 1;
			goto _05;
		}

		if(Video.DeleteProcess)
		{
			DeleteLookBody();
			goto _10;
		}

		//      Progress(6);
		n = 1;
		if(TypeSystem.Num < 4 && TypeProfile == 0 && TypePlate == 0)
		{
			for(i = 0; i < QuantityNode; i++)
			{
				if(TypeSystem.Num < 3 && fabs(Coord[i].y - Coord[0].y) > Eps)
					break;
				if(TypeSystem.Num == 3 && fabs(Coord[i].z - Coord[0].z) > Eps)
					break;
			}

			if(i == QuantityNode)
			{
				for(i = 0; i < kG; i++)
					NumElemBody[i] = i + 1;
				n = 0;
			}
		}

		//Printf("2");
		if(n)
		{
			if(Video.DeleteProcess)
			{
				DeleteLookBody();
				goto _10;
			}

			LookProc(LookCoord, Eps, Video.QuantityElemBody, Video.ElemBody, NumElemBody);
			if(Video.ElemBody == NULL)
				goto _10;
		}

		//      Progress(96);
	_05:
		if(TypeProfile)
		{
			pEB = Video.ElemBody;
			kG = Video.QuantityElemBody;
			for(i = 0; i < kG; i++, pEB++)
			{
				if(Video.DeleteProcess)
				{
					DeleteLookBody();
					goto _10;
				}

				n = NumElemBody[i];
				if(pFormat[pEB->NumElem - 1].Check)
				{
					ProfileElem(Eps, LookCoord, pEB, kElem, NumElemBody);
					k = kElem - 1;
					for(j = 0; j < Video.QuantityElemBody - k; j++)
						if(NumElemBody[j] > n)
							NumElemBody[j] += k;
					Num = &NumElemBody[Video.QuantityElemBody - k];
					NumElemBody[i] += Num[0] - 1;
					for(j = 0; j < k; j++)
						Num[j] = Num[j + 1] + n - 1;
				}
			}
		}

		if(MK)
		{
			Video.Order = (long *) Memory(kGF + 1, sizeof(long));
			for(i = 0; i < Video.QuantityElemBody; i++)
				Video.Order[NumElemBody[i] - 1] = i;
		}

	_10:
		MemoryFree(LookCoord);
		MemoryFree(NumElemBody);

		for(i = 0; i < QuantityElem; i++)
			pFormat[i].Check = 0;
		//assert(Video.QuantityElemBody<=kGF+2);
		//Printf("4");
	}
	