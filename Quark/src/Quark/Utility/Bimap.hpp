#pragma once

#include <map>

QK_BEGIN

	/**
	 * @brief A utility class for bi-directional map lookups.
	 */
	// TODO: This sucks
	template<class FromType, class ToType>
	class Bimap
	{
	public:
		explicit Bimap(std::initializer_list<std::pair<FromType, ToType>> ilist)
		{
			for (auto pair : ilist)
			{
				m_FwdMap.insert(pair);
				std::pair<ToType, FromType> tempPair = std::make_pair(pair.second, pair.first);
				m_BwdMap.insert(tempPair);
			}
		}

		ToType& operator[](const FromType& key) {
			return m_FwdMap[key];
		}

		FromType& operator[](const ToType& key) {
			return m_BwdMap[key];
		}

	private:
		std::map<FromType, ToType> m_FwdMap;
		std::map<ToType, FromType> m_BwdMap;
	};

QK_END