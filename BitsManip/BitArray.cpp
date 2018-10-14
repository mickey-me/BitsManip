#include "BitArray.h"
#include <cstdlib>

BitArray::BitArray(unsigned __int8 Capacity=1) : OctetNum(((Capacity > 0) && (Capacity < MAXOctets * 8)) ? (Capacity / 8 + (Capacity % 8 != 0 ? 1 : 0)) : MAXOctets)
{
	Data = new unsigned __int8[OctetNum];
	if (Data == NULL) {
		exit(1);
	}
}

BitArray::~BitArray() {
	delete[] Data;
}

void BitArray::changeCapacity(unsigned __int8	 Capacity)
{
	changeOctetCapacity(((Capacity > 0) && (Capacity < MAXOctets * 8)) ? (Capacity / 8 + (Capacity % 8 != 0 ? 1 : 0)) : MAXOctets);
}

void BitArray::changeOctetCapacity(unsigned __int8	 NewOctetNum)
{
	if (NewOctetNum > MAXOctets) {
		NewOctetNum = MAXOctets;
	}

	if (NewOctetNum == OctetNum) {
		return;
	}
	else {
		unsigned __int8	* NewData = new unsigned __int8[NewOctetNum];
		if (NewData == NULL) exit(1);
		for (int i = 0; i < NewOctetNum && i < OctetNum; i++) {
			NewData[i] = Data[i];
		}
		delete[] Data;
		Data = NewData;
		OctetNum = NewOctetNum;
	}
}

void BitArray::ChangeElement(unsigned __int8	 ind, bool val)
{
	ind = (ind % (OctetNum *8) + (OctetNum * 8)) % (OctetNum * 8);
	Data[ind / 8] = val ? (Data[ind / 8] | ((unsigned __int8)0x01 << (ind % 8))) : (Data[ind / 8] & (((unsigned __int8)0xfe << (ind % 8)) | ((unsigned __int8)0x7f >> (7 - ind % 8))));
}

void BitArray::ChangeOctet(unsigned __int8 ind, unsigned __int8 val)
{
	ind = (ind % (OctetNum * 8) + (OctetNum * 8)) % (OctetNum * 8);
	Data[ind / 8] = val;
}

bool BitArray::getElement(unsigned __int8 ind)
{
	ind = (ind % (OctetNum * 8) + (OctetNum * 8)) % (OctetNum * 8);
	return (Data[ind / 8] >> (ind % 8)) & (unsigned __int8)0x01;
}

unsigned __int8 BitArray::GetOctetWithOctetInd(unsigned __int8	 Octetind)
{
	Octetind = Octetind % OctetNum;
	return Data[Octetind];
}

unsigned __int8 BitArray::getCapacity()
{
	return OctetNum * 8;
}