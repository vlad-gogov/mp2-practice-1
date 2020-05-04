#ifndef _SORTTABLE_H_
#define _SORTTABLE_H_
#include "../include/ScanTable.h"
#include "../include/TabRecord.h"

template <typename TKey, typename TData>
class SortTable : public ScanTable<TKey, TData>
{
protected:
	void SortData();

public:
	SortTable(int _tabSize);
	SortTable(const ScanTable* table);

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

}

template <typename TKey, typename TData>
void SortTable<TKey, TData>::InsertRecord(TKey key, TData* data)
{

}

template <typename TKey, typename TData>
void SortTable<TKey, TData>::RemoveRecord(TKey key)
{

}
#endif //!_SORTTABLE_H_
