#ifndef _SORTTABLE_H_
#define _SORTTABLE_H_
#include "../include/ScanTable.h"
#include "../include/TabRecord.h"

template <typename TKey, typename TData>
class SortTable : protected ScanTable<TKey, TData>
{
protected:
	void SortData();

public:
	SortTable(int _tabSize);
	SortTable(const ScanTable<TKey, TData>* table);

	virtual TabRecord* FindRecord(TKey key);
	virtual void InsertRecord(TKey key, TData* data);
	virtual void RemoveRecord(TKey key);
};

template <typename TKey, typename TData>
void SortTable<TKey, TData>::SortData()
{

}

template <typename TKey, typename TData>
SortTable<TKey, TData>::SortTable(int _tabSize) : ScanTable(_tabSize) {}

template <typename TKey, typename TData>
SortTable<TKey, TData>::SortTable(const ScanTable<TKey, TData>* table)
{

}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* SortTable<TKey, TData>::FindRecord(TKey key)
{
	int i, i1 = 0, i2 = dataCount - 1;
	TabRecord<TKey, TData>* rec = nullptr;
	while (i1 <= i2)
	{
		i = (i1 + i2) / 2;
		if (key == records[i]->key)
		{
			i1 = i + 1;
			i2 = i;
			rec = records[i];
		}
		else if (key > records[i]->key)
			i1 = i + 1;
		else
			i2 = i - 1;
		currPos = i2;;
		return rec;
	}
}

template <typename TKey, typename TData>
void SortTable<TKey, TData>::InsertRecord(TKey key, TData* data)
{
	if (!IsFull())
	{
		TabRecord<TKey, TData>* rec = FindRecord(key);
		for (int i = dataCount; i > currPos; i--)
		{
			records[i] = records[i - 1];
		}
		records[currPos] = new TabRecord(key, data);
		dataCount++;
	}
}

template <typename TKey, typename TData>
void SortTable<TKey, TData>::RemoveRecord(TKey key)
{
	if (!IsEmpty())
	{
		TabRecord<TKey, TData>* rec = FindRecord(key);
		if (rec != NULL)
		{
			delete records[currPos];
			for (int i = currPos; i < dataCount - 1; i++)
			{
				records[i] = records[i + 1];
			}
			dataCount--;
		}
	}
}
#endif //!_SORTTABLE_H_
