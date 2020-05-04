#ifndef _SCANTABLE_H_
#define _SCANTABLE_H_
#include "../include/Table.h"
#include "../include/TabRecord.h"

template <typename TKey, typename TData>
class ScanTable : public Table<TKey, TData>
{
protected:
	TabRecord** records;
public:
	ScanTable(int _tabSize);
	virtual TabRecord* FindRecord(TKey key);
	virtual void InsertRecord(TKey key, TData* data);
	virtual void RemoveRecord(TKey key);
};

template <typename TKey, typename TData>
ScanTable<TKey, TData>::ScanTable(int _tabSize) : Table(_tabSize) {}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ScanTable<TKey, TData>::FindRecord(TKey key)
{
	for (int i = 0; i < dataCount; i++)
	{
		if (records[i]->key == key)
		{
			currPos = i;
			return records[i];
		}
	}
	return nullptr;
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::InsertRecord(TKey key, TData* data)
{
	if (!IsFull())
	{
		records[dataCount++] = new TabRecord<TKey, TData>(key, data);
	}
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::RemoveRecord(TKey key)
{
	if (!IsEmpty())
	{
		if (FindRecord(key) != nullptr)
		{
			delete records[currPos];
			records[currPos] = records[--dataCount];
		}
	}
}

#endif // ! _SCANTABLE_H_

