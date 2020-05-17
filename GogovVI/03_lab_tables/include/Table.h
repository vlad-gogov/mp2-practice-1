#ifndef _TABLE_H_
#define _TABLE_H_
#include "../include/TabRecord.h"

template <typename TKey, typename TData>
class Table
{
protected:
	int tabSize;
	int dataCount;
	int currPos;
public:
	Table(int _tabSize);

	bool IsEmpty() const;
	bool IsFull() const;
	int GetDataCount() const;
	int GetTabSize() const;

	virtual TabRecord<TKey, TData>* FindRecord(TKey key) = 0;
	virtual void InsertRecord(TKey key, TData* data) = 0;
	virtual void RemoveRecord(TKey key) = 0;

	virtual bool Reset();
	virtual bool GetNext();
	virtual bool IsTabEnded() const;

	virtual TKey GetKey() const = 0;
	virtual TData* GetData() const = 0;
};

template <typename TKey, typename TData>
Table<TKey, TData>::Table(int _tabSize)
{
	dataCount = currPos = 0;
	tabSize = _tabSize;
}

template <typename TKey, typename TData>
bool Table<TKey, TData>::IsEmpty() const
{
	return dataCount == 0;
}

template <typename TKey, typename TData>
bool Table<TKey, TData>::IsFull() const
{
	return dataCount == tabSize;
}

template <typename TKey, typename TData>
int Table<TKey, TData>::GetDataCount() const
{
	return dataCount;
}

template <typename TKey, typename TData>
int Table<TKey, TData>::GetTabSize() const
{
	return tabSize;
}

template <typename TKey, typename TData>
bool Table<TKey, TData>::Reset()
{
	currPos = 0;
	return IsTabEnded();
}

template <typename TKey, typename TData>
bool Table<TKey, TData>::GetNext()
{
	if (!IsTabEnded())
		currPos++;
	return IsTabEnded();
}

template <typename TKey, typename TData>
bool Table<TKey, TData>::IsTabEnded() const
{
	return currPos >= tabSize;
}

#endif //!_TABLE_H_