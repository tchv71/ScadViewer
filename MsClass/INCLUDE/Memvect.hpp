#ifndef MEMORY_VECTOR_FLAG_H
#define MEMORY_VECTOR_FLAG_H

#pragma pack(push, 1)
struct MEM_VECTOR {
	   void FAR * P;
	   MEM_VECTOR FAR * pV;
	   MEM_VECTOR FAR * pN;
};

class MEMORY_VECTOR {

private:

	   WORD ElemSize;
	   WORD Quantity;
	   MEM_VECTOR FAR *Begin;
	   MEM_VECTOR FAR *End;

MEM_VECTOR FAR * GetMemElem(WORD Index);

public:

	   MEMORY_VECTOR(WORD ElemSizeByte);
	  ~MEMORY_VECTOR();
void	   Delete();
void       Add(void FAR *Elem);
void       Add(void FAR *Elem,WORD Size);
WORD       UpdateElem(void FAR *Elem, WORD Index);
WORD       UpdateElem(void FAR *Elem, WORD Size, WORD Index);
void FAR * GetElem(WORD Index);
void       DeleteElem(WORD Index);

};
#pragma pack(pop)

#endif
