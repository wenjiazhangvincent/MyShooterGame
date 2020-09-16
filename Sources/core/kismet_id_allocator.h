#ifndef _KISMET_ID_ALLOCATOR_H_
#define _KISMET_ID_ALLOCATOR_H_

#include <ctime>

namespace Kismet
{
	template <class T, class IDRawType = unsigned int>
	class IDAllocator
	{
	public:
		using RawType = IDRawType;
		using ValueType = typename std::decay<T>::type;

		RawType allocateID(const ValueType& instance)
		{
			if (m_current_entry_index == k_invalid_index)
			{
				return NULL;
			}
			else
			{
				m_data_entries[m_current_entry_index] = instance;
				return m_current_entry_index++;
			}
		}

		const RawType fillbits(size_t bit_count)
		{
			return (bit_count <= 1) ? ((RawType)1) : (((RawType)1 << (bit_count - 1)) | fillbits(bit_count - 1));
		}

	private:
		std::map<int, ValueType> m_data_entries;
		RawType m_current_entry_index{ 1 };
		RawType k_invalid_index = fillbits(sizeof(RawType) * 8 / 2 - 1);
	};

	class RandomAllocator
	{
		RandomAllocator()
		{
			srand((unsigned)time(NULL));
		}

	public:
		int generate(int upper_bound)
		{
			return rand() % upper_bound;
		}
	};
}

#endif // !_KISMET_ID_ALLOCATOR_H_
