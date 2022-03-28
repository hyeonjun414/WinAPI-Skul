#pragma once

template<typename T>
void Safe_Delete_Array(T* _arr, int _size)
{
	for (int i = 0; i < _size; i++)
	{
		if (nullptr != _arr[i])
			delete _arr[i];
	}
}

template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}

template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); iter++)
	{
		if(nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}

