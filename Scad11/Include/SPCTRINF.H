#pragma pack(push,1)
struct SPECTR_INFORM {
	short NumLoad;
	BYTE  Ort;
	WORD  NumAksel;
	short NumNode;
	short QuantityOften;
	DWORD PosOften;
};

struct TYPE_SPECTR {
	BYTE  Type;
	float Value;
	float Often;
};
#pragma pack(pop)

