#ifndef _TABRECORD_H_
#define _TABRECORD_H_

template <typename TKey, typename TData>
class TabRecord
{
protected:
	TKey key;
	TData* data;
public:
	TabRecord(TKey _key, TData *_data);
	TData* GetData();
	TKey GetKey();
	TabRecord* GetCopy();
};

template <typename TKey, typename TData>
TabRecord<TKey, TData>::TabRecord(TKey _key, TData* _data)
{
	key = _key;
	data = _data;
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* TabRecord<TKey, TData>::GetCopy()
{
	TabRecord<TKey, TData>* result;
	result->key = key;
	result->data = new TData(data);
	return result;
}

template <typename TKey, typename TData>
TData* TabRecord<TKey, TData>::GetData()
{
	return data;
}

template <typename TKey, typename TData>
TKey TabRecord<TKey, TData>::GetKey()
{
	return key;
}

#endif //!_TABRECORD_H_
