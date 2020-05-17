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

	virtual TabRecord<TKey, TData>* FindRecord(TKey key);
	virtual void InsertRecord(TKey key, TData* data);
	virtual void RemoveRecord(TKey key);
};

template <typename TKey, typename TData>
void SortTable<TKey, TData>::SortData()
{
	TabRecord<TKey, TData>* temp;
	for (int i = 1, j; i < this->dataCount; i++)
	{
		temp = this->records[i];
		for (j = i - 1; j > -1; j--)
		{
			if (this->records[j] > temp->GetKey())
			{
				this->records[j + 1] = this->records[j];
			}
			else
				break;
		}
		this->records[j + 1] = temp;
	}
}

template <typename TKey, typename TData>
SortTable<TKey, TData>::SortTable(int _tabSize) : ScanTable(_tabSize) {}

template <typename TKey, typename TData>
SortTable<TKey, TData>::SortTable(const ScanTable<TKey, TData>* table)
{
	this->dataCount = table->GetDataCount();
	this->tabSize = table->GetTabSize();
	this->currPos = 0;
	this->records = new TabRecord<TKey, TData>[this->tabSize];
	for (int i = 0; i < this->dataCount; i++)
	{
		this->records[i] = table->records[i]->GetCopy();
	}
	this->SortData();
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* SortTable<TKey, TData>::FindRecord(TKey key)
{
	int i, i1 = 0, i2 = this->dataCount - 1;
	TabRecord<TKey, TData>* rec = nullptr;
	while (i1 <= i2)
	{
		i = (i1 + i2) / 2;
		if (key == this->records[i]->key)
		{
			i1 = i + 1;
			i2 = i;
			rec = this->records[i];
		}
		else if (key > this->records[i]->key)
			i1 = i + 1;
		else
			i2 = i - 1;
		this->currPos = i2;;
		return rec;
	}
}

template <typename TKey, typename TData>
void SortTable<TKey, TData>::InsertRecord(TKey key, TData* data)
{
	if (!this->IsFull())
	{
		TabRecord<TKey, TData>* rec = FindRecord(key);
		for (int i = this->dataCount; i > this->currPos; i--)
		{
			this->records[i] = this->records[i - 1];
		}
		this->records[this->currPos] = new TabRecord<TKey, TData>(key, data);
		this->dataCount++;
	}
}

template <typename TKey, typename TData>
void SortTable<TKey, TData>::RemoveRecord(TKey key)
{
	if (!this->IsEmpty())
	{
		TabRecord<TKey, TData>* rec = FindRecord(key);
		if (rec != nullptr)
		{
			delete this->records[this->currPos];
			for (int i = this->currPos; i < this->dataCount - 1; i++)
			{
				this->records[i] = this->records[i + 1];
			}
			this->dataCount--;
		}
	}
}
#endif //!_SORTTABLE_H_
