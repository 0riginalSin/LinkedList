/******************************************************************************
 * LinkedList version 1.0
 * @files linkedList.hpp linkedList.shpp
 * @author 0riginalSin
 * @brief Contains class declaration with comments.
 *
 * Standart linked list implimentation with class. You could use pointers to
 * have access to your data even after another data deleted pointer would stay
 * constant.
 *
 ******************************************************************************
 */
#pragma once

#include <stdint.h>
#include <functional>

namespace DataStructs {
	/*
	* @brief Linked list of template data.
	*/
	template <typename DataType>
	class LinkedList {
	protected:
		struct Member {
			DataType data_;
			Member* memberPointer_;
		};
		struct Member* lastMemberPointer_;
		size_t size_;

		static bool StandartCompareFunction(const DataType& first, const DataType& second);
	public:
		/*
		* @brief Creates void LinkedList instance.
		* @return LinkedList instance.
		*/
		LinkedList();

		/*
		* @brief Creates and initializes LinkedList.
		* @param quantityOfMembers Quantity of members to initialize.
		* @param firstData First member of LinkedList.
		* @return LinkrfList instance.
		*/
		LinkedList(const uint8_t quantityOfMembers, const DataType* firstData, ...);

		/*
		* @brief Copy constructor.
		*/
		LinkedList(const LinkedList& copyInstance);

		/*
		* @brief Free memory, allocated for instance.
		*/
		virtual ~LinkedList();

		/*
		* @brief Get the state of list.
		* @return True if list is empty, false if isn't.
		*/
		bool IsEmpty() const;
		/*
		* @brief Add new member to the top of LinkedList.
		* @param data Data to add.
		*/
		void Add(const DataType& data);

		/*
		* @brief Add many new members to the top of LinkedList.
		* @param quantityOfMembers Quantity of members to add.
		* @param firstData First member of data sequence to add.
		*/
		void Add(const uint8_t quantityOfMembers, const DataType* firstData, ...);

		/*
		* @brief Delete member of LinkedList.
		* @param ordinalNum Index of element to delete.
		* @return Information about existing a member or not.
		*/
		bool Delete(size_t ordinalNum);

		/*
		* @brief Clear content of the list.
		*/
		void Clear();

		/*
		* @brief Find and get first from the end coincidental member if LinkedList.
		* @param dataToFind What to find.
		* @param compareFunc Function to use to compare for equality of dataToFind and list member.
		* @return Pointer to the data.
		*/
		DataType* Find(const DataType& dataToFind,
		 std::function<bool(const DataType&, const DataType&)> compareFunc = StandartCompareFunction) const;

		/*
		* @brief Find and get first from the end coincidental member if LinkedList.
		* @param dataToFind What to find.
		* @param ordinalNum (return)Ordinal number of founded member from the end of list.
		* @param compareFunc Function to use to compare for equality of dataToFind and list member.
		* @return Pointer to the data.
		*/
		DataType* Find(const DataType& dataToFind, size_t& ordinalNum,
		 std::function<bool(const DataType&, const DataType&)> compareFunc = StandartCompareFunction) const;

		/*
		* @brif Get the member of list with the current ordinal number.
		* @param ordinalNum number from the top of the linked list.
		* @return Pointer to the data with current ordinal number.
		*/
		DataType* operator[](size_t ordinalNum) const;

		/*
		* @brief Comparing for equality; operator== should be defined for DataType that list store!
		* @param compare List to compare with.
		* @return True if lists are equal, false if not.
		*/
		bool operator==(const LinkedList& compare) const;

		/*
		* @brief Compare two lists with compare function.
		* @param compare List to compare with.
		* @param compareFunc std::function could be converted from lambda expr or function pointer.
		* @return True if lists are equal, false if not.
		*/
		bool Compare(const LinkedList& compare,
		 std::function<bool(const DataType&, const DataType&)> compareFunc = StandartCompareFunction) const;

		/*
		* @brief Get size of list.
		* @return Size of linked list.
		*/
		size_t Size() const;
	};
}

//thanks to template, that needs to be implemented in hpp file, where they declared
#include "linkedlist.cpp"
