#include "ArrayList.h"


template<class T>
ArrayList<T>::ArrayList() :
	m_size(0),
	m_capacity(SIZE_INCREMENT)
{
	pElements = new T[SIZE_INCREMENT];
}
template<class T>
void ArrayList<T>::clear()
{
	pElements= NULL;
	m_size = 0;
}

/**
 * @brief      Adds a thing to the ArrayList
 *
 * @param[in]  toPush  The to be added.
 *
 * @tparam     T       Typename
 */
template<class T>
void ArrayList<T>::add(const T& toPush)
{
	if(m_size == m_capacity)
	{
		m_capacity *= SIZE_INCREMENT;
		T * newTarr = new T[m_capacity];
		int i;
	 	for(i = 0; i < m_size; i++)
	 		newTarr[i] = pElements[i];
	 	newTarr[i] = toPush;
	 	pElements = newTarr;
	}
	else 
		pElements[m_size] = toPush;
	m_size++;
}


/**
 * @brief      Adds a thing in a specific index.
 *
 * @param[in]  toPush  Thing to add
 * @param[in]  index   Where it is to be added.
 *
 * @tparam     T       Type of thing
 */
template<class T>
void ArrayList<T>::add(const T& toPush, int index)
{
	if(index == m_size && m_size < m_capacity)
		pElements[index] = toPush;
	else
	{
		m_capacity += SIZE_INCREMENT;
		T * newTarr = new T[m_capacity];
		newTarr[index] = toPush;
		for(int i = 0, k = 0; i < m_size; i++, k++)
	 	{
	 		if( k == index)
		 		newTarr[++k] = pElements[i];
	 		else
	 			newTarr[k] = pElements[i];
	 	}
	 	pElements = newTarr;	 	
	}
	m_size++;
}

/**
 * @brief      Pushes to the back of the list.
 *
 * @param[in]  toPush  Thing to push back.
 *
 * @tparam     T       Typename
 */
template<class T>
void ArrayList<T>::push_back(const T& toPush)
{
	this->add(toPush, m_size);
}

/**
 * @brief      Push a thing to the front of the list.
 *
 * @param[in]  toPush  Thing to be pushed.
 *
 * @tparam     T       Typename
 */
template<class T>
void ArrayList<T>::push_front(const T& toPush)
{
	this->add(toPush, 0);
}

/**
 * @brief      Remove the item at a specific index.
 *
 * @param[in]  index  Index of the thing to be removed.
 *
 * @tparam     T      Typename
 *
 * @return     Shallow copy of the item we removed.
 */
template<class T>
const T ArrayList<T>::remove(int index)
{
	const T myT = T();
	if(index <= m_size)
	{		
		T * newTarr = new T[m_capacity];
		pElements[index] = myT;
		for(int i = 0, k = 0; i < m_size; i++, k++)
		{
		 	if( i == index)
		 		newTarr[k] = pElements[++i];
		 	else
		 		newTarr[k] = pElements[i];
		}
		pElements = newTarr;
		m_size--;		
	}
	return myT;
}

/**
 * @brief      Removes a particular item from the list.
 *
 * @param[in]  toRemove  Thing to remove.
 * @param      ok        True upon successful removal.
 *
 * @tparam     T         Typename
 */
template<class T>
void ArrayList<T>::remove(const T & toRemove, bool * ok) 
{
	int index = this->indexOf(toRemove);
	if(index == -1)
		*ok = false;
	else
	{
		this->remove(index);
		*ok = true;
	}	
	
}

/**
 * @brief      Check if an item is in the ArrayList.
 *
 * @param[in]  object The thing we want to know about.
 *
 * @tparam     T       Typename
 *
 * @return     Returns true if it's there.
 */
template<class T>
bool ArrayList<T>::contains(const T& object)
{
	for(int i = 0; i < m_size; i++)
	{
		if(pElements[i] == object)
			return true;
	}	
	return false;
}

/**
 * @brief      Returns the first index of T.
 *
 * @param[in]  object  Thing.
 *
 * @tparam     T       Typename
 *
 * @return     The first index of thing.
 */
template<class T>
int ArrayList<T>::indexOf(const T& object)
{
	for(int i = 0; i < m_size; i++)
	{
		if(pElements[i] == object)
			return i;
	}	
	return -1;
}

/**
 * @brief      Return the ith occurance of T.
 *
 * @param[in]  object     Thing.
 * @param[in]  occurance  Occurance of thing to find.
 *
 * @tparam     T          Type of thing.
 *
 * @return     Location of thing.
 */
template<class T>
int ArrayList<T>::indexOf(const T& object, int occurrence)
{
	int n = 0;
	for(int i = 0; i < m_size; i++)
	{
		if(pElements[i] == object)
			n++;
		if(pElements[i] == object && n==occurrence)
			return i;
	}	
	return -1;
}

/**
 * @brief      Check for the last index of an object.
 *
 * @param[in]  object  Thing to check
 *
 * @tparam     T       Typename
 *
 * @return     Integer location of the last location, or -1.
 */
template<class T>
int ArrayList<T>::lastIndexOf(const T& object)
{
	int t = -1;
	for(int i = 0; i < m_size; i++)
	{
		if(pElements[i] == object)
			t = i;
	}
	return t;
}

/**
 * @brief      Sorts the given list in ascending order.
 * 
 * This sorts the list in ascending order. It is assumed
 * that the < operator has been overloaded.
 *
 * @tparam     T   type.  
 */
template<class T>
void ArrayList<T>::sort()
{
	for(int i = 1; i < m_size; i++)
	{
		for(int j = 0; j < (m_size-i); j++)
		{
			if( pElements[j] > pElements[j+1] )
			{
				T temp = T();
				temp = pElements[j];
				pElements[j] = pElements[j+1];
				pElements[j+1] = temp;
			}
		}
	}
}
